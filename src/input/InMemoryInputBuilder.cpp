/*
 * InMemoryInputBuilder.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: davide
 */

#include "InMemoryInputBuilder.h"
#include "../grounder/atom/ClassicalLiteral.h"
#include "../grounder/atom/BuiltInAtom.h"
#include "../grounder/ground/ProgramGrounder.h"

#include <string>
#include "algorithm"

namespace DLV2 {
namespace grounder {

InMemoryInputBuilder::InMemoryInputBuilder() {
	termTable=TermTable::getInstance();
	predicateTable=PredicateTable::getInstance();
	statementDependency = StatementDependency::getInstance();
	instancesTable=PredicateExtTable::getInstance();

	currentRule = new Rule;
	currentAtom = nullptr;
	currentBinop = Binop::NONE_OP;
}

InMemoryInputBuilder::~InMemoryInputBuilder() {
	delete currentRule;
	delete currentAtom;
}

void InMemoryInputBuilder::onDirective(char* directiveName,
		char* directiveValue) {
}

void InMemoryInputBuilder::onRule() {
	if(currentRule->isAFact()){
		Atom *fact=*currentRule->getBeginHead();
		Predicate* predicate=fact->getPredicate();
		Atom* genericAtom=new GenericAtom(fact->getTerms(),true);
		delete fact;
		if(!(instancesTable->getPredicateExt(predicate)->addGenericAtom(FACT,genericAtom,false)))
			delete genericAtom;
		else{
			ClassicalLiteral::print(predicate,genericAtom->getTerms(),false,false);cout<<"."<<endl;
		}

		currentRule->clear();
	}else{
		set_predicate pred_head=currentRule->getPredicateInHead();
		for(auto p:pred_head)p->setIdb();
		statementDependency->addRuleMapping(currentRule);
		currentRule= new Rule;
	}
}

void InMemoryInputBuilder::onConstraint() {
	statementDependency->addRuleMapping(currentRule);
	currentRule= new Rule;
}

void InMemoryInputBuilder::onWeakConstraint() {
}

void InMemoryInputBuilder::onQuery() {
}

void InMemoryInputBuilder::onHeadAtom() {
	currentRule->addInHead(currentAtom);
	currentAtom= nullptr;
}

void InMemoryInputBuilder::onHead() {

}

void InMemoryInputBuilder::onBodyLiteral() {
	currentRule->addInBody(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onBody() {
}

void InMemoryInputBuilder::onNafLiteral(bool naf) {
	currentAtom->setNegative(naf);
}

void InMemoryInputBuilder::onAtom(bool isStrongNeg) {
	currentAtom->setHasMinus(isStrongNeg);
}

void InMemoryInputBuilder::onExistentialAtom() {
}

void InMemoryInputBuilder::onPredicateName(char* name) {
	string name_predicate(name);
	Predicate *predicate=new Predicate(name_predicate,terms_parsered.size());
	predicateTable->getInstance()->insertPredicate(predicate);
	instancesTable->addPredicateExt(predicate);
	currentAtom =new ClassicalLiteral(predicate,terms_parsered,false,false);
	terms_parsered.clear();
}

void InMemoryInputBuilder::onExistentialVariable(char* var) {
}

void InMemoryInputBuilder::onEqualOperator() {
	currentBinop = Binop::EQUAL;
}

void InMemoryInputBuilder::onUnequalOperator() {
	currentBinop = Binop::UNEQUAL;
}

void InMemoryInputBuilder::onLessOperator() {
	currentBinop = Binop::LESS;
}

void InMemoryInputBuilder::onLessOrEqualOperator() {
	currentBinop = Binop::LESS_OR_EQ;
}

void InMemoryInputBuilder::onGreaterOperator() {
	currentBinop = Binop::GREATER;
}

void InMemoryInputBuilder::onGreaterOrEqualOperator() {
	currentBinop = Binop::GREATER_OR_EQ;
}

bool isNumeric(const char* pszInput, int nNumberBase )
{
    istringstream iss( pszInput );

    if ( nNumberBase == 10 )
    {
        double dTestSink;
        iss >> dTestSink;
    }
    else if ( nNumberBase == 8 || nNumberBase == 16 )
    {
        int nTestSink;
        iss >> ( ( nNumberBase == 8 ) ? oct : hex ) >> nTestSink;
    }
    else
        return false;

    // Was any input successfully consumed/converted?
    if ( !iss )
        return false;

    // Was all the input successfully consumed/converted?
    return ( iss.rdbuf()->in_avail() == 0 );
}

void InMemoryInputBuilder::newTerm(char* value)
{

    if( value[0] >= 'A' && value[0] <='Z' ) // Variable
    {
    	string name(value);
		Term *term=new VariableTerm(false,name);
		termTable->addTerm(term);
		terms_parsered.push_back(term);
    }
    else if( (value[0] == '\"' && value[strlen(value)-1] == '\"') ||
            (value[0] >= 'a' && value[0] <='z') )   // String constant
    {
    	string name(value);
    	Term *term=new StringConstantTerm(false,name);
		termTable->addTerm(term);
		terms_parsered.push_back(term);
    }
    else //if( isNumeric( value, 10 ) ) // Numeric constant
    {
    	int val = atoi(value);
    	onTerm(val);
    }
}

void InMemoryInputBuilder::onTerm(char* value) {
	newTerm(value);
}

void InMemoryInputBuilder::onTerm(int value) {
	Term *term=new NumericConstantTerm(false,value);
	termTable->addTerm(term);
	terms_parsered.push_back(term);
}

void InMemoryInputBuilder::onUnknownVariable() {
	string name("_");
	Term *term=new VariableTerm(false,name);
	termTable->addTerm(term);
	terms_parsered.push_back(term);
}

void InMemoryInputBuilder::onFunction(char* functionSymbol, int nTerms) {
	string name(functionSymbol);
	vector<Term*> termsInFunction(nTerms);

	for(int i=0;i<nTerms;i++){
		termsInFunction[nTerms-i-1]=terms_parsered.back();
		terms_parsered.pop_back();
	}

	Term *term=new FunctionTerm(name,false,termsInFunction);
	termTable->addTerm(term);
	terms_parsered.push_back(term);
}

void InMemoryInputBuilder::onTermDash() {
}

void InMemoryInputBuilder::onTermParams() {
}

void InMemoryInputBuilder::onTermRange(char* lowerBound, char* upperBound) {
}

void InMemoryInputBuilder::onArithmeticOperation(char arithOperator) {
	auto second_last=--(--terms_parsered.end());
	Term *arithTerm=nullptr;
	if((*second_last)->getType()!=TermType::ARITH){
		//First occurrence of arithmetic
		arithTerm=new ArithTerm;

		arithTerm->addTerm(*second_last);
		arithTerm->addTerm(*(++second_last));



	}else{

		arithTerm = *second_last;

		arithTerm->addTerm(terms_parsered.back());

	}

	arithTerm->setOperator(ArithTerm::getOperatorName(arithOperator));

	terms_parsered.pop_back();
	terms_parsered.pop_back();
	terms_parsered.push_back(arithTerm);
	termTable->addTerm(arithTerm);
}

void InMemoryInputBuilder::onWeightAtLevels(int nWeight, int nLevel,
		int nTerm) {
}

void InMemoryInputBuilder::onChoiceLowerGuard() {
}

void InMemoryInputBuilder::onChoiceUpperGuard() {
}

void InMemoryInputBuilder::onChoiceElementAtom() {
}

void InMemoryInputBuilder::onChoiceElementLiteral() {
}

void InMemoryInputBuilder::onChoiceElement() {
}

void InMemoryInputBuilder::onChoiceAtom() {
}

void InMemoryInputBuilder::onBuiltinAtom() {
	currentAtom = new BuiltInAtom(currentBinop,false,terms_parsered);
}

void InMemoryInputBuilder::onAggregateLowerGuard() {
}

void InMemoryInputBuilder::onAggregateUpperGuard() {
}

void InMemoryInputBuilder::onAggregateFunction(char* functionSymbol) {
}

void InMemoryInputBuilder::onAggregateGroundTerm(char* value, bool dash) {
}

void InMemoryInputBuilder::onAggregateVariableTerm(char* value) {
}

void InMemoryInputBuilder::onAggregateUnknownVariable() {
}

void InMemoryInputBuilder::onAggregateNafLiteral() {
}

void InMemoryInputBuilder::onAggregateElement() {
}

void InMemoryInputBuilder::onAggregate(bool naf) {
}

} /* namespace grounder */
} /* namespace DLV2 */

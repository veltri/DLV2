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
#include "../grounder/atom/AggregateAtom.h"

#include <string>
#include "algorithm"

namespace DLV2 {
namespace grounder {

InMemoryInputBuilder::InMemoryInputBuilder() {
	termTable=TermTable::getInstance();
	predicateTable=PredicateTable::getInstance();
	statementDependency = StatementDependency::getInstance();
	instancesTable=PredicateExtTable::getInstance();
	inputRewriter=new BaseInputRewriter;

	currentRule = new Rule;
	currentAtom = nullptr;
	currentBinop = Binop::NONE_OP;
	currentAggregateElement= nullptr;
	currentAggregate = nullptr;
	foundAnAggregateAtom=false;
}

InMemoryInputBuilder::~InMemoryInputBuilder() {
	delete currentRule;
	delete currentAtom;
	delete inputRewriter;
}

void InMemoryInputBuilder::onDirective(char* directiveName,
		char* directiveValue) {
}

void InMemoryInputBuilder::onRule() {
	if(currentRule->isAFact()){
		Atom *fact=*currentRule->getBeginHead();
		if(fact->containsRangeTerms()){
			vector<Atom*> atomExpanded;
			expandRangeAtom(fact,atomExpanded);
			for (auto atom : atomExpanded)
				createFact(atom);
		}
		else
			createFact(fact);
		currentRule->clear();
	}else{
		currentRule->print();
		set_predicate pred_head=currentRule->getPredicateInHead();
		for(auto p:pred_head)p->setIdb();
		if(currentRule->containsRangeAtoms()){
			vector<vector<Atom*>> headExpanded; expandRulePart(currentRule->getBeginHead(),currentRule->getEndHead(), headExpanded);
			vector<vector<Atom*>> bodyExpanded;
			if(currentRule->getSizeBody()>0) expandRulePart(currentRule->getBeginBody(),currentRule->getEndBody(), bodyExpanded);
			for(auto head: headExpanded){
				if(bodyExpanded.size()>0)
					for(auto body: bodyExpanded) createRule(&head,&body);
				else
					createRule(&head);
			}
			currentRule->clear();
		}
		else{
			addRuleMapping(currentRule);
			currentRule = new Rule;
		}
	}
	foundAnAggregateAtom=false;
}

void InMemoryInputBuilder::onConstraint() {
	if(currentRule->containsRangeAtoms()){
		vector<vector<Atom*>> bodyExpanded;
		expandRulePart(currentRule->getBeginBody(),currentRule->getEndBody(), bodyExpanded);
		for(auto body: bodyExpanded)
			createRule(0,&body);
		currentRule->clear();
	}
	else{
		addRuleMapping(currentRule);
		currentRule = new Rule;
	}
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
	Predicate *predicate = new Predicate(name_predicate,terms_parsered.size());
	predicateTable->getInstance()->insertPredicate(predicate);
	instancesTable->addPredicateExt(predicate);
	currentAtom = new ClassicalLiteral(predicate,terms_parsered,false,false);
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
	if(isNumeric(lowerBound,10) && isNumeric(upperBound,10)){
		Term* rangeTerm=new RangeTerm(atoi(lowerBound),atoi(upperBound));
		terms_parsered.push_back(rangeTerm);
	}
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
	termTable->addTerm(arithTerm);
	terms_parsered.push_back(arithTerm);
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
	if(currentAggregate==nullptr)
		currentAggregate = new AggregateAtom;
	currentAggregate->setLowerGuard(terms_parsered.back());
	currentAggregate->setFirstBinop(currentBinop);
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateUpperGuard() {
	currentAggregate->setUpperGuard(terms_parsered.back());
	currentAggregate->setSecondBinop(currentBinop);
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateFunction(char* functionSymbol) {
	foundAnAggregateAtom=true;
	if(currentAggregate==nullptr)
		currentAggregate = new AggregateAtom;
	if(strcmp(functionSymbol,"#count")==0){
		currentAggregate->setAggregateFunction(AggregateFunction::COUNT);
	}else if(strcmp(functionSymbol,"#sum")==0){
		currentAggregate->setAggregateFunction(AggregateFunction::SUM);
	}else if(strcmp(functionSymbol,"#min")==0){
		currentAggregate->setAggregateFunction(AggregateFunction::MIN);
	}else if(strcmp(functionSymbol,"#max")==0){
		currentAggregate->setAggregateFunction(AggregateFunction::MAX);
	}
}

void InMemoryInputBuilder::onAggregateGroundTerm(char* value, bool dash) {
}

void InMemoryInputBuilder::onAggregateVariableTerm(char* value) {
	string value_string(value);
	Term *term=new VariableTerm(false,value_string);
	termTable->addTerm(term);
	if(currentAggregateElement==nullptr)
		currentAggregateElement=new AggregateElement;
	currentAggregateElement->addTerm(term);
}

void InMemoryInputBuilder::onAggregateUnknownVariable() {
}

void InMemoryInputBuilder::onAggregateNafLiteral() {
	if(currentAggregateElement==nullptr)
		currentAggregateElement=new AggregateElement;
	currentAggregateElement->addNafLiterals(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onAggregateElement() {
	currentAggregate->addAggregateElement(*currentAggregateElement);
	currentAggregateElement=nullptr;
}

void InMemoryInputBuilder::onAggregate(bool naf) {
	currentAtom = currentAggregate;
	currentAggregate = nullptr;
}

void InMemoryInputBuilder::addRuleMapping(Rule* rule) {
	if (foundAnAggregateAtom) {
		vector<Rule*> rules;
		inputRewriter->translateAggregate(rule, rules);
		delete rule;
		for (auto r : rules)
			statementDependency->addRuleMapping(r);
	} else
		statementDependency->addRuleMapping(rule);
}

void InMemoryInputBuilder::createRule(vector<Atom*>* head, vector<Atom*>* body) {
	Rule* rule=new Rule;
	if(head!=0) rule->setHead(*head);
	if(body!=0) rule->setBody(*body);
	addRuleMapping(rule);
}

void InMemoryInputBuilder::createFact(Atom* fact) {
	Predicate* predicate = fact->getPredicate();
	Atom* genericAtom = new GenericAtom(fact->getTerms(), true);
	delete fact;
	if (!(instancesTable->getPredicateExt(predicate)->addGenericAtom(FACT, genericAtom)))
		delete genericAtom;
	else
		if (!Options::globalOptions()->isNofacts()) {
			ClassicalLiteral::print(predicate, genericAtom->getTerms(), false, false);
			cout << "." << endl;
		}
}

void InMemoryInputBuilder::expandTermsRecursive(Atom* atom, vector<Term*>& currentTerms, vector<Atom*>& atomExpanded,unsigned currentPosition){
	if(currentPosition<atom->getTermsSize()-1){
		currentPosition++;
		expandTerms(atom,currentTerms,atomExpanded,currentPosition);
		currentTerms.pop_back();
	}
	else{
		ClassicalLiteral* newAtom = new ClassicalLiteral(atom->getPredicate(),atom->isHasMinus(),atom->isNegative());
		newAtom->setTerms(currentTerms);
		atomExpanded.push_back(newAtom);
		currentTerms.pop_back();
	}
}

void InMemoryInputBuilder::expandTerms(Atom* atom, vector<Term*>& currentTerms, vector<Atom*>& atomExpanded, unsigned currentPosition){
	Term* t=atom->getTerm(currentPosition);
	if(!t->isRange()){
		currentTerms.push_back(t);
		expandTermsRecursive(atom,currentTerms,atomExpanded,currentPosition);
		return;
	}
	RangeTerm* rt=dynamic_cast<RangeTerm*>(t);
	for(int i=rt->getLowerBound();i<=rt->getUpperBound();i++){
		Term* t = new NumericConstantTerm(rt->isNegative(),i);
		termTable->addTerm(t);
		currentTerms.push_back(t);
		expandTermsRecursive(atom,currentTerms,atomExpanded,currentPosition);
	}
}

void InMemoryInputBuilder::expandRangeAtom(Atom* atom, vector<Atom*>& atomExpanded) {
	vector<Term*> currentTerms;
	expandTerms(atom, currentTerms, atomExpanded, 0);
	for (auto t : atom->getTerms())
		if(t->isRange())
			delete t;
	delete atom;
}

void InMemoryInputBuilder::expandAtoms(const vector<vector<Atom*>>& atoms, vector<Atom*>& currentAtoms, vector<vector<Atom*>>& atomsExpanded, unsigned currentPosition){
	for(auto it=atoms[currentPosition].begin();it!=atoms[currentPosition].end();it++){
		Atom* atom = (*it)->clone();
		currentAtoms.push_back(atom);
		if(currentPosition<atoms.size()-1){
			currentPosition++;
			expandAtoms(atoms,currentAtoms,atomsExpanded,currentPosition);
			currentPosition--;
		}
		else
			atomsExpanded.push_back(currentAtoms);
		currentAtoms.pop_back();
	}
}

void InMemoryInputBuilder::expandRulePart(vector<Atom*>::const_iterator start, vector<Atom*>::const_iterator end, vector<vector<Atom*> >& atomsExpanded) {
	vector<vector<Atom*>> atoms;
	for (auto it = start; it != end; it++) {
		vector<Atom*> atomExpanded;
		if((*it)->containsRangeTerms())
			expandRangeAtom(*it,atomExpanded);
		else
			atomExpanded.push_back(*it);
		atoms.push_back(atomExpanded);
	}
	vector<Atom*> currentAtoms;
	expandAtoms(atoms,currentAtoms,atomsExpanded,0);
	for(auto vectorAtom:atoms)
		for(auto atom: vectorAtom)
			delete atom;
}

} /* namespace grounder */
} /* namespace DLV2 */

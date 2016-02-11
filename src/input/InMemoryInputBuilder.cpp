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
#include "../grounder/atom/Choice.h"
#include "../util/Utils.h"

#include <string>
#include "algorithm"

namespace DLV2 {
namespace grounder {


pair<string,unsigned> extractPredicateNameArity(string& predicateArity){
	vector<string> splitString=Utils::split(predicateArity,'/');
	if(splitString.size()!=2)
		assert_msg(false,"#show value:"+predicateArity+" unsafe ");

	string predicateName=splitString[0];
	//Remove space
	predicateName.erase(std::remove(predicateName.begin(),predicateName.end(),' '),predicateName.end());
	string arityString=splitString[1];
	arityString.erase(std::remove(arityString.begin(),arityString.end(),' '),arityString.end());
	unsigned arity;
	try{arity=atoi(arityString.c_str());}catch(...){assert_msg(false,"#show value:"+predicateArity+" unsafe, failed to parse arity");}

	return {predicateName,arity};
}

InMemoryInputBuilder::InMemoryInputBuilder() :
	termTable(TermTable::getInstance()),
	predicateTable(PredicateTable::getInstance()),
	statementDependency(StatementDependency::getInstance()),
	instancesTable(PredicateExtTable::getInstance()),
	foundARangeAtomInCurrentRule(false),
	currentRule(new Rule()),
	currentAtom(nullptr),
	currentBinop(Binop::NONE_OP),
	currentAggregate(nullptr),
	currentAggregateElement(new AggregateElement),
	currentChoice(nullptr),
	currentChoiceElement(new ChoiceElement),
	weight(nullptr),
	level(nullptr),
	hiddenNewPredicate(false)
{

	Options * opt=Options::globalOptions();

	switch (opt->getRewritingType()) {
		case DISJUNCTION:
			inputRewriter=new BaseInputRewriter();
			break;
		default:
			inputRewriter=new ChoiceBaseInputRewriter();
			break;
	}

	string filter=opt->getPredicateToFilter();
	if(filter.size()>0){
		//If exist a filter hidden all new predicate and create the predicate to show and set hidden to this predicate to false
		hiddenNewPredicate=true;
		vector<string> splitString=Utils::split(filter,',');
		for(auto predicateArity:splitString){
			auto nameArity = extractPredicateNameArity(predicateArity);
			Predicate *predicate = new Predicate(nameArity.first,nameArity.second);
			predicate->setHiddenForPrinting(false);
			predicateTable->getInstance()->insertPredicate(predicate);
		}
	}

}

InMemoryInputBuilder::~InMemoryInputBuilder() {
	delete currentRule;
	delete currentAtom;
	delete inputRewriter;
	delete currentAggregateElement;
	delete currentChoiceElement;
}

void InMemoryInputBuilder::onDirective(char* directiveName,
		char* directiveValue) {

	if(strcmp(directiveName,"#show")==0){
		hiddenNewPredicate=true;
		string value(directiveValue);

		auto nameArity=extractPredicateNameArity(value);

		Predicate *predicate = new Predicate(nameArity.first,nameArity.second);
		predicate->setHiddenForPrinting(false);
		predicateTable->getInstance()->insertPredicate(predicate);
	}

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
		if(foundARangeAtomInCurrentRule){
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
			addRule(currentRule);
			currentRule = new Rule;
		}
	}

	foundARangeAtomInCurrentRule=false;
}

void InMemoryInputBuilder::onConstraint() {
	if(foundARangeAtomInCurrentRule){
		vector<vector<Atom*>> bodyExpanded;
		expandRulePart(currentRule->getBeginBody(),currentRule->getEndBody(), bodyExpanded);
		for(auto body: bodyExpanded)
			createRule(0,&body);
		currentRule->clear();
	}
	else{
		addRule(currentRule);
		currentRule = new Rule;
	}
	foundARangeAtomInCurrentRule=false;
}

void InMemoryInputBuilder::onWeakConstraint() {

	Rule * weakRule=new WeakConstraint(currentRule->getBody(),weight,level,terms_parsered);
	OrderRule orderRule(weakRule);
	bool isSafe = orderRule.order();
	safetyError(isSafe,"RULE IS UNSAFE");
	statementDependency->addRuleMapping(weakRule);

	delete currentRule;
	currentRule = new Rule;
	terms_parsered.clear();
	weight=nullptr;
	level=nullptr;
}

void InMemoryInputBuilder::onQuery() {
}

void InMemoryInputBuilder::onHeadAtom() {
	currentRule->addInHead(currentAtom);
	if(currentAtom->containsAnonymous()){
		currentAtom->print();cout<<" ";
		safetyError(false, "ATOM IS UNSAFE");
	}
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
	if(naf && currentAtom->containsAnonymous()){
		currentAtom->print();cout<<" ";
		safetyError(false, "ATOM IS UNSAFE");
	}
}

void InMemoryInputBuilder::onAtom(bool isStrongNeg) {
	if(isStrongNeg){
		//Create a new predicate like the old predicate but with trueNegative = true
		Predicate * oldPredicate=currentAtom->getPredicate();
		string predicatename=oldPredicate->getName();
		Predicate *strongPredicate=new Predicate(predicatename,oldPredicate->getArity(),oldPredicate->isEdb());
		strongPredicate->setTrueNegated(true);
		strongPredicate->setHiddenForPrinting(hiddenNewPredicate);
		predicateTable->getInstance()->insertPredicate(strongPredicate);
		instancesTable->addPredicateExt(strongPredicate);
		currentAtom->setPredicate(strongPredicate);
	}
}

void InMemoryInputBuilder::onExistentialAtom() {
}

void InMemoryInputBuilder::onPredicateName(char* name) {
	string name_predicate(name);
	Predicate *predicate = new Predicate(name_predicate,terms_parsered.size());
	predicate->setHiddenForPrinting(hiddenNewPredicate);
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
	Term *oldTerm=terms_parsered.back();
	if(oldTerm->isRange()){
		oldTerm->setNegative(true);
	}
	else
	{
		Term *newTerm = nullptr;

		if(oldTerm->getType()==NUMERIC_CONSTANT)
			newTerm=new NumericConstantTerm(false,oldTerm->getConstantValue()*(-1));
		else{
			vector<Operator> op(1,TIMES);
			vector<Term*> terms={oldTerm,termTable->term_minus_one};
			newTerm = new ArithTerm(false,op,terms);
		}
		TermTable::getInstance()->addTerm(newTerm);
		terms_parsered.pop_back();
		terms_parsered.push_back(newTerm);
	}
}

void InMemoryInputBuilder::onTermParams() {

}

void InMemoryInputBuilder::onTermRange(char* lowerBound, char* upperBound) {
	foundARangeAtomInCurrentRule=true;
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
		arithTerm->setOperator(ArithTerm::getOperatorName(arithOperator));
		termTable->addTerm(arithTerm);

	}else{
		arithTerm = *second_last;
		arithTerm->addTerm(terms_parsered.back());
		arithTerm->setOperator(ArithTerm::getOperatorName(arithOperator));
	}

	terms_parsered.pop_back();
	terms_parsered.pop_back();
	terms_parsered.push_back(arithTerm);
}

void InMemoryInputBuilder::onWeightAtLevels(int nWeight, int nLevel,
		int nTerm) {
	//TODO ERROR IN PARSER
	if(nWeight==0){
		nTerm--;
		nWeight=1;
	}
	weight=terms_parsered[0];
	if(nLevel>0){
		level=terms_parsered[nWeight];
	}
	if(nLevel+nWeight>0)
		terms_parsered.erase(terms_parsered.begin(),terms_parsered.begin()+nLevel+nWeight);
}

void InMemoryInputBuilder::onChoiceLowerGuard() {
	if(currentChoice==nullptr)
		currentChoice = new Choice;
	Term* firstGuard=terms_parsered.back();
	currentChoice->setFirstGuard(firstGuard);
	currentChoice->setFirstBinop(currentBinop);
	if(firstGuard->contain(TermType::ANONYMOUS)){
		currentChoice->print();cout<<" ";
		safetyError(false,"ATOM IS UNSAFE");
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onChoiceUpperGuard() {
	if(currentChoice==nullptr)
		currentChoice = new Choice;
	Term* secondGuard=terms_parsered.back();
	currentChoice->setSecondGuard(secondGuard);
	currentChoice->setSecondBinop(currentBinop);
	if(secondGuard->contain(TermType::ANONYMOUS)){
		currentChoice->print();cout<<" ";
		safetyError(false,"ATOM IS UNSAFE");
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onChoiceElementAtom() {
	if(currentChoice==nullptr)
		currentChoice = new Choice;
	currentChoiceElement->add(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onChoiceElementLiteral() {
	currentChoiceElement->add(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onChoiceElement() {
	currentChoice->addChoiceElement(currentChoiceElement);
	currentChoiceElement=new ChoiceElement;
}

void InMemoryInputBuilder::onChoiceAtom() {
	if(currentChoice->getFirstBinop()==NONE_OP && currentChoice->getSecondBinop()==NONE_OP){
		currentChoice->setSecondBinop(GREATER_OR_EQ);
		currentChoice->setSecondGuard(termTable->term_zero);
	}
	currentAtom=currentChoice;
	currentRule->addInHead(currentAtom);
	currentChoice=nullptr;
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onBuiltinAtom() {
	currentAtom = new BuiltInAtom(currentBinop,false,terms_parsered);
	if(currentAtom->containsAnonymous()){
		currentAtom->print();cout<<" ";
		safetyError(false,"ATOM IS UNSAFE");
	}
}

void InMemoryInputBuilder::onAggregateLowerGuard() {
	if(currentAggregate==nullptr)
		currentAggregate = new AggregateAtom;
	Term* firstGuard=terms_parsered.back();
	currentAggregate->setFirstGuard(firstGuard);
	currentAggregate->setFirstBinop(currentBinop);
	if(firstGuard->contain(TermType::ANONYMOUS)){
		currentAggregate->print();cout<<" ";
		safetyError(false,"ATOM IS UNSAFE");
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateUpperGuard() {
	if(currentAggregate==nullptr)
		currentAggregate = new AggregateAtom;
	Term* secondGuard=terms_parsered.back();
	currentAggregate->setSecondGuard(secondGuard);
	currentAggregate->setSecondBinop(currentBinop);
	if(secondGuard->contain(TermType::ANONYMOUS)){
		currentAggregate->print();cout<<" ";
		safetyError(false,"ATOM IS UNSAFE");
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateFunction(char* functionSymbol) {
	currentRule->setMustBeRewritedForAggregates(true);
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
	newTerm(value);
	currentAggregateElement->addTerm(terms_parsered.back());
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateVariableTerm(char* value) {
	string value_string(value);
	Term *term=new VariableTerm(false,value_string);
	termTable->addTerm(term);

	currentAggregateElement->addTerm(term);
}

void InMemoryInputBuilder::onAggregateUnknownVariable() {
	currentAggregate->print();cout<<" ";
	safetyError(false,"ATOM IS UNSAFE");
}

void InMemoryInputBuilder::onAggregateNafLiteral() {
	currentAggregateElement->addNafLiterals(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onAggregateElement() {
	currentAggregate->addAggregateElement(currentAggregateElement);
	if(!currentAggregateElement->areAggregationTermsSafe())
	{
		currentAggregate->print();cout<<" ";
		safetyError(false,"ATOM IS UNSAFE");
	}
	currentAggregateElement=new AggregateElement;
}

void InMemoryInputBuilder::onAggregate(bool naf) {
	currentAggregate->setNegative(naf);
	currentAtom = currentAggregate;
	currentAtom->changeInStandardFormat();
	currentAggregate = nullptr;
}

void InMemoryInputBuilder::rewriteAggregate(Rule* rule) {
	//Sort the rule and check for safety
	OrderRule orderRule(rule);
	bool isSafe = orderRule.order();
	safetyError(isSafe,"RULE IS UNSAFE");

	//Translate the rule
	vector<Rule*> rules;
	inputRewriter->translateAggregate(rule, rules, &orderRule);
	for (auto r : rules) {
		OrderRule orderR(r);
		isSafe = orderR.order();
		if (!isSafe)
			safetyError(isSafe,"RULE IS UNSAFE");
		statementDependency->addRuleMapping(r);
	}

	statementDependency->addRuleMapping(rule);
}

void InMemoryInputBuilder::rewriteChoice(Rule* rule) {
	vector<Rule*> rules;
	inputRewriter->translateChoice(rule, rules);
	for (auto r : rules){
		if(r->isMustBeRewritedForAggregates()){
			rewriteAggregate(r);
		}else
			manageSimpleRule(r);
	}
}

void InMemoryInputBuilder::manageSimpleRule(Rule* rule) {
	OrderRule orderRule(rule);
	bool isSafe = orderRule.order();
	safetyError(isSafe,"RULE IS UNSAFE");
	statementDependency->addRuleMapping(rule);
	rule->setUnsolvedPredicates();
}

void InMemoryInputBuilder::addRule(Rule* rule) {
	if(rule->isChoiceRule())
		rewriteChoice(rule);
	else if(rule->isMustBeRewritedForAggregates())
		rewriteAggregate(rule);
	else
		manageSimpleRule(rule);
}

void InMemoryInputBuilder::createRule(vector<Atom*>* head, vector<Atom*>* body) {
	Rule* rule=new Rule;
	if(head!=0) rule->setHead(*head);
	if(body!=0) rule->setBody(*body);
	addRule(rule);
}

void InMemoryInputBuilder::createFact(Atom* fact) {
//	if(!fact->isGround()) {
//		fact->print();
//		assert_msg(false, "ATOM IS UNSAFE");
//	}
	fact->setFact(true);
	Predicate* predicate = fact->getPredicate();
//	if (!(instancesTable->getPredicateExt(predicate)->addAtom(FACT, fact)))
	IndexingStructure* atomSearcher=nullptr;
	instancesTable->getPredicateExt(predicate)->getAtomSearcher(FACT);
	if(Options::globalOptions()->getCheckFactDuplicate())
		atomSearcher=instancesTable->getPredicateExt(predicate)->addAtomSearcher(FACT,HASHSET,nullptr);

	if(atomSearcher==nullptr || atomSearcher->find(fact)==nullptr){
		instancesTable->getPredicateExt(predicate)->addAtom(fact,FACT);
		if (!Options::globalOptions()->isNofacts()) {
				OutputBuilder::getInstance()->onFact(fact);
		}
	}else
		delete fact;
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

void InMemoryInputBuilder::safetyError(bool condition, string message) {
	assert_msg(condition, message);
}

} /* namespace grounder */
} /* namespace DLV2 */

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
#include "../grounder/statement/GroundingPreferences.h"

#include <string>
#include "algorithm"

namespace DLV2 {
namespace grounder {

bool InMemoryInputBuilder::foundASafetyError=false;
bool InMemoryInputBuilder::currentRuleIsUnsafe=false;

string InMemoryInputBuilder::safetyErrorMessage="";

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
	hiddenNewPredicate(false),
	currentRuleOrdering(-1),
	globalOrdering(-1)
{

	Options * opt=Options::globalOptions();

	switch (opt->getRewritingType()) {
		case DISJUNCTION:
			inputRewriter=new BaseInputRewriter();
			break;
		case COMPACT_NATIVE_CHOICE:
			inputRewriter=new AdvancedChoiceBaseInputRewriter();
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
	if(foundASafetyError) return;
	if(strcmp(directiveName,"#show")==0){
		hiddenNewPredicate=true;
		string value(directiveValue);

		auto nameArity=extractPredicateNameArity(value);

		Predicate *predicate = new Predicate(nameArity.first,nameArity.second);
		predicate->setHiddenForPrinting(false);
		predicateTable->getInstance()->insertPredicate(predicate);
	}

}

void InMemoryInputBuilder::manageRuleAnnotations() {
	if (currentRuleOrdering != -1)
		if(!GroundingPreferences::getGroundingPreferences()->addRuleOrderingType(
				currentRule, currentRuleOrdering))
			cout<<"--> Warning : The ordering type "<<currentRuleOrdering<<" is not valid."<<endl;
	currentRuleOrdering = -1;

	for (unsigned i = 0; i < currentRuleAtomsIndexed.size(); ++i) {
		AnnotationsError error=GroundingPreferences::getGroundingPreferences()->addRuleAtomIndexingSetting(
				currentRule, currentRuleAtomsIndexed[i],
				currentRuleAtomsIndexedArguments[i]);
		if(error==ATOM_NOT_PRESENT){
			cout<<"--> Warning : The atom ";currentRuleAtomsIndexed[i]->print();cout<<" is not present in the specified rule."<<endl;
			currentRule->print();
		}
	}
	for(auto atom:currentRuleAtomsIndexed)
		delete atom;
	currentRuleAtomsIndexed.clear();
	currentRuleAtomsIndexedArguments.clear();

	for(unsigned i=0;i<currentRuleAtomsBefore.size();++i){
		for(auto atom:currentRuleAtomsBefore[i]){
			AnnotationsError error=GroundingPreferences::getGroundingPreferences()->addRulePartialOrderBefore(currentRule, atom);
			if(error==ATOM_NOT_PRESENT){

				cout<<"--> Warning : The atom ";atom->print();cout<<" is not present in the specified rule."<<endl;
			}
		}
		for(auto atom:currentRuleAtomsAfter[i]){
			AnnotationsError error=GroundingPreferences::getGroundingPreferences()->addRulePartialOrderAfter(currentRule, atom);
			if(error==ATOM_NOT_PRESENT){
				cout<<"--> Warning : The atom ";atom->print();cout<<" is not present in the specified rule."<<endl;
			}
		}
		if(GroundingPreferences::getGroundingPreferences()->checkRulePartialOrderConflicts(currentRule)==CONFLICT_FOUND){
			cout<<"--> Warning : In the rule ";currentRule->print();cout<<"The partial ordering specified cannot be applied."<<endl;
		}
		for(auto atom:currentRuleAtomsBefore[i])
			delete atom;
		for(auto atom:currentRuleAtomsAfter[i])
			delete atom;
	}
	currentRuleAtomsBefore.clear();
	currentRuleAtomsAfter.clear();
//	GroundingPreferences::getGroundingPreferences()->print(currentRule);
}

void InMemoryInputBuilder::onRule() {
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
	Rule * weakRule=new WeakConstraint(currentRule->getBody(),weight,level,terms_parsered);
	if(currentRuleIsUnsafe){
		safetyError(false,weakRule);
		return;
	}
	OrderRule orderRule(weakRule);
	bool isSafe = orderRule.order();
	safetyError(isSafe,weakRule);
	statementDependency->addRuleMapping(weakRule);

	delete currentRule;
	currentRule = new Rule;
	terms_parsered.clear();
	weight=nullptr;
	level=nullptr;
}

void InMemoryInputBuilder::onQuery() {
	if(foundASafetyError) return;
}

void InMemoryInputBuilder::onHeadAtom() {
	if(foundASafetyError) return;
	currentRule->addInHead(currentAtom);
	if(currentAtom->containsAnonymous()){
		currentRuleIsUnsafe=true;
	}
	currentAtom= nullptr;
}

void InMemoryInputBuilder::onHead() {
	if(foundASafetyError) return;
}

void InMemoryInputBuilder::onBodyLiteral() {
	if(foundASafetyError) return;
	currentRule->addInBody(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onBody() {
	if(foundASafetyError) return;
}

void InMemoryInputBuilder::onNafLiteral(bool naf) {
	if(foundASafetyError) return;
	currentAtom->setNegative(naf);
	if(naf && currentAtom->containsAnonymous()){
		currentRuleIsUnsafe=true;
//		currentAtom->print();cout<<" ";
//		safetyError(false, "ATOM IS UNSAFE");
	}
}

void InMemoryInputBuilder::onAtom(bool isStrongNeg) {
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
}

void InMemoryInputBuilder::onPredicateName(char* name) {
	if(foundASafetyError) return;
	string name_predicate(name);
	Predicate *predicate = new Predicate(name_predicate,terms_parsered.size());
	predicate->setHiddenForPrinting(hiddenNewPredicate);
	predicateTable->getInstance()->insertPredicate(predicate);
	instancesTable->addPredicateExt(predicate);
	currentAtom = new ClassicalLiteral(predicate,terms_parsered,false,false);
	terms_parsered.clear();
}

void InMemoryInputBuilder::onExistentialVariable(char* var) {
	if(foundASafetyError) return;
}

void InMemoryInputBuilder::onEqualOperator() {
	if(foundASafetyError) return;
	currentBinop = Binop::EQUAL;
}

void InMemoryInputBuilder::onUnequalOperator() {
	if(foundASafetyError) return;
	currentBinop = Binop::UNEQUAL;
}

void InMemoryInputBuilder::onLessOperator() {
	if(foundASafetyError) return;
	currentBinop = Binop::LESS;
}

void InMemoryInputBuilder::onLessOrEqualOperator() {
	if(foundARangeAtomInCurrentRule) return;
	currentBinop = Binop::LESS_OR_EQ;
}

void InMemoryInputBuilder::onGreaterOperator() {
	if(foundASafetyError) return;
	currentBinop = Binop::GREATER;
}

void InMemoryInputBuilder::onGreaterOrEqualOperator() {
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
	newTerm(value);
}

void InMemoryInputBuilder::onTerm(int value) {
	if(foundASafetyError) return;
	Term *term=new NumericConstantTerm(false,value);
	termTable->addTerm(term);
	terms_parsered.push_back(term);
}

void InMemoryInputBuilder::onUnknownVariable() {
	if(foundASafetyError) return;
	string name("_");
	Term *term=new VariableTerm(false,name);
	termTable->addTerm(term);
	terms_parsered.push_back(term);
}

void InMemoryInputBuilder::onFunction(char* functionSymbol, int nTerms) {
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;

}

void InMemoryInputBuilder::onTermRange(char* lowerBound, char* upperBound) {
	if(foundASafetyError) return;
	foundARangeAtomInCurrentRule=true;
	if(isNumeric(lowerBound,10) && isNumeric(upperBound,10)){
		Term* rangeTerm=new RangeTerm(atoi(lowerBound),atoi(upperBound));
		terms_parsered.push_back(rangeTerm);
	}
}

void InMemoryInputBuilder::onArithmeticOperation(char arithOperator) {
	if(foundASafetyError) return;
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
		ArithTerm *arithCasted=dynamic_cast<ArithTerm*>(*second_last);
		arithTerm = new ArithTerm(*arithCasted);
		arithTerm->addTerm(terms_parsered.back());
		arithTerm->setOperator(ArithTerm::getOperatorName(arithOperator));
		termTable->addTerm(arithTerm);
	}

	terms_parsered.pop_back();
	terms_parsered.pop_back();
	terms_parsered.push_back(arithTerm);
}

void InMemoryInputBuilder::onWeightAtLevels(int nWeight, int nLevel,
		int nTerm) {
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
	if(currentChoice==nullptr)
		currentChoice = new Choice;
	Term* firstGuard=terms_parsered.back();
	currentChoice->setFirstGuard(firstGuard);
	currentChoice->setFirstBinop(currentBinop);
	if(firstGuard->contain(TermType::ANONYMOUS)){
		currentRuleIsUnsafe=true;
//		currentChoice->print();cout<<" ";
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onChoiceUpperGuard() {
	if(foundASafetyError) return;
	if(currentChoice==nullptr)
		currentChoice = new Choice;
	Term* secondGuard=terms_parsered.back();
	currentChoice->setSecondGuard(secondGuard);
	currentChoice->setSecondBinop(currentBinop);
	if(secondGuard->contain(TermType::ANONYMOUS)){
		currentRuleIsUnsafe=true;
//		currentChoice->print();cout<<" ";
//		safetyError(false,"ATOM IS UNSAFE");
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onChoiceElementAtom() {
	if(foundASafetyError) return;
	if(currentChoice==nullptr)
		currentChoice = new Choice;
	currentChoiceElement->add(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onChoiceElementLiteral() {
	if(foundASafetyError) return;
	currentChoiceElement->add(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onChoiceElement() {
	if(foundASafetyError) return;
	currentChoice->addChoiceElement(currentChoiceElement);
	currentChoiceElement=new ChoiceElement;
}

void InMemoryInputBuilder::onChoiceAtom() {
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
	currentAtom = new BuiltInAtom(currentBinop,false,terms_parsered);
	if(currentAtom->containsAnonymous()){
		currentRuleIsUnsafe=true;
//		currentAtom->print();cout<<" ";
//		safetyError(false,"ATOM IS UNSAFE");
	}
}

void InMemoryInputBuilder::onAggregateLowerGuard() {
	if(foundASafetyError) return;
	if(currentAggregate==nullptr)
		currentAggregate = new AggregateAtom;
	Term* firstGuard=terms_parsered.back();
	currentAggregate->setFirstGuard(firstGuard);
	currentAggregate->setFirstBinop(currentBinop);
	if(firstGuard->contain(TermType::ANONYMOUS)){
		currentRuleIsUnsafe=true;
//		currentAggregate->print();cout<<" ";
//		safetyError(false,"ATOM IS UNSAFE");
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateUpperGuard() {
	if(foundASafetyError) return;
	if(currentAggregate==nullptr)
		currentAggregate = new AggregateAtom;
	Term* secondGuard=terms_parsered.back();
	currentAggregate->setSecondGuard(secondGuard);
	currentAggregate->setSecondBinop(currentBinop);
	if(secondGuard->contain(TermType::ANONYMOUS)){
		currentRuleIsUnsafe=true;
//		currentAggregate->print();cout<<" ";
//		safetyError(false,"ATOM IS UNSAFE");
	}
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateFunction(char* functionSymbol) {
	if(foundASafetyError) return;
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
	if(foundASafetyError) return;
	newTerm(value);
	currentAggregateElement->addTerm(terms_parsered.back());
	terms_parsered.pop_back();
}

void InMemoryInputBuilder::onAggregateVariableTerm(char* value) {
	if(foundASafetyError) return;
	string value_string(value);
	Term *term=new VariableTerm(false,value_string);
	termTable->addTerm(term);

	currentAggregateElement->addTerm(term);
}

void InMemoryInputBuilder::onAggregateUnknownVariable() {
	if(foundASafetyError) return;
	currentRuleIsUnsafe=true;
//	currentAggregate->print();cout<<" ";
//	safetyError(false,"ATOM IS UNSAFE");
}

void InMemoryInputBuilder::onAggregateNafLiteral() {
	if(foundASafetyError) return;
	currentAggregateElement->addNafLiterals(currentAtom);
	currentAtom=nullptr;
}

void InMemoryInputBuilder::onAggregateElement() {
	if(foundASafetyError) return;
	currentAggregate->addAggregateElement(currentAggregateElement);
	if(!currentAggregateElement->areAggregationTermsSafe())
	{
		currentRuleIsUnsafe=true;
//		currentAggregate->print();cout<<" ";
//		safetyError(false,"ATOM IS UNSAFE");
	}
	currentAggregateElement=new AggregateElement;
}

void InMemoryInputBuilder::onAggregate(bool naf) {
	if(foundASafetyError) return;
	currentAggregate->setNegative(naf);
	currentAtom = currentAggregate;
	currentAtom->changeInStandardFormat();
	currentAggregate = nullptr;
}

void InMemoryInputBuilder::rewriteAggregate(Rule* rule) {
	rewriteAggregate(rule,inputRewriter,statementDependency);
}

void InMemoryInputBuilder::rewriteAggregate(Rule* rule,InputRewriter* inputRewriter,StatementDependency* statementDependency) {
	//Sort the rule and check for safety
	if(currentRuleIsUnsafe){
		safetyError(false,rule);
		statementDependency->addRuleMapping(rule);
		return;
	}
	OrderRule orderRule(rule);
	bool isSafe = orderRule.order();
	safetyError(isSafe,rule);

	//Translate the rule
	vector<Rule*> rules;
	inputRewriter->translateAggregate(rule, rules, &orderRule);
	for (auto r : rules) {
		OrderRule orderR(r);
		isSafe = orderR.order();
		if (!isSafe)
			safetyError(isSafe,r);
//			safetyError(isSafe,"RULE IS UNSAFE");
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
	manageSimpleRule(rule,statementDependency);
	manageRuleAnnotations();
}

void InMemoryInputBuilder::manageSimpleRule(Rule* rule,StatementDependency * statementDependency) {
	if(currentRuleIsUnsafe){
		safetyError(false,rule);
		statementDependency->addRuleMapping(rule);
		return;
	}
	OrderRule orderRule(rule);
	bool isSafe = orderRule.order();
	safetyError(isSafe,rule);
//	safetyError(isSafe,"RULE IS UNSAFE");
	statementDependency->addRuleMapping(rule);
	rule->setUnsolvedPredicates();
}

void InMemoryInputBuilder::addRule(Rule* rule) {
	if(rule->isChoiceRule()){
		rewriteChoice(rule);
	}else if(rule->isMustBeRewritedForAggregates())
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

void InMemoryInputBuilder::onAnnotationRuleOrdering(char* annotation) {
	if(isNumeric(annotation,10))
		currentRuleOrdering = atoi(annotation);
	//FIXME check that the number is a val ordering type
}

void InMemoryInputBuilder::onAnnotationRuleAtomIndexedArgument(char* annotation) {
	int argument=0;
	if(!isNumeric(annotation,10)){
		//FIXME warning
		return;
	}
	argument=atoi(annotation);
	if(argument>=0 && argument<currentRuleAtomsIndexed.back()->getPredicate()->getArity())
		currentRuleAtomsIndexedArguments.back().push_back(argument);
	else{
		cout<<"--> Warning : The arguments specified for the atom ";currentRuleAtomsIndexed.back()->print();cout<<" are not valid."<<endl;
	}
}

void InMemoryInputBuilder::onAnnotationRuleAtomIndexedLiteral(bool naf) {
	currentAtom->setNegative(naf);
	currentRuleAtomsIndexed.push_back(currentAtom);
	currentRuleAtomsIndexedArguments.push_back(vector<unsigned>());
}

void InMemoryInputBuilder::onAnnotationRulePartialOrderingBefore(bool naf) {
	currentAtom->setNegative(naf);
	currentRuleAtomsBefore.back().push_back(currentAtom);
}

void InMemoryInputBuilder::onAnnotationRulePartialOrderingAfter(bool naf) {
	currentAtom->setNegative(naf);
	currentRuleAtomsAfter.back().push_back(currentAtom);
}

void InMemoryInputBuilder::onAnnotationAggregateRulePartialOrderingAfter(bool naf) {
	currentAggregate->setNegative(naf);
	currentRuleAtomsAfter.back().push_back(currentAggregate);
}

void InMemoryInputBuilder::onAnnotationAggregateRulePartialOrderingBefore(bool naf) {
	currentAggregate->setNegative(naf);
	currentRuleAtomsBefore.back().push_back(currentAggregate);
}

void InMemoryInputBuilder::onAnnotationGlobalOrdering(char* annotation) {
	if(isNumeric(annotation,10) && globalOrdering>-1)
		globalOrdering = atoi(annotation);
	//FIXME check that the number is a val ordering type and has not yet been set
}

void InMemoryInputBuilder::onAnnotationGlobalAtomIndexedArgument(char* annotation) {
	int argument=0;
	if(!isNumeric(annotation,10)){
		//FIXME warning
		return;
	}
	argument=atoi(annotation);
	if(argument>=0 && argument<globalAtomsIndexed.back()->getPredicate()->getArity())
		globalAtomsIndexedArguments.back().push_back(argument);
	//else	FIXME WARNING
}

void InMemoryInputBuilder::onAnnotationGlobalAtomIndexedLiteral(bool naf) {
	currentAtom->setNegative(naf);
	globalAtomsIndexed.push_back(currentAtom);
	globalAtomsIndexedArguments.push_back(vector<unsigned>());
}

void InMemoryInputBuilder::onAnnotationGlobalPartialOrderingBefore(bool naf) {
	currentAtom->setNegative(naf);
	globalAtomsBefore.back().push_back(currentAtom);
}

void InMemoryInputBuilder::onAnnotationGlobalPartialOrderingAfter(bool naf) {
	currentAtom->setNegative(naf);
	globalAtomsAfter.back().push_back(currentAtom);
}

void InMemoryInputBuilder::onAnnotationAggregateGlobalPartialOrderingAfter(bool naf) {
	currentAggregate->setNegative(naf);
	globalAtomsAfter.back().push_back(currentAggregate);
}

void InMemoryInputBuilder::onAnnotationAggregateGlobalPartialOrderingBefore(bool naf) {
	currentAggregate->setNegative(naf);
	globalAtomsBefore.back().push_back(currentAggregate);
}

void InMemoryInputBuilder::safetyError(bool condition, Rule* rule) {
	if(!condition){
		stringstream tmp;
		rule->print(tmp);
		safetyErrorMessage="--> Safety Error: "+tmp.str();
		foundASafetyError=true;
	}
}

} /* namespace grounder */
} /* namespace DLV2 */


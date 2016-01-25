/*
 * ProgramGrounder.cpp
 *
 *  Created on: 10/apr/2014
 *      Author: Davide
 */



#include <list>

#include "ProgramGrounder.h"
#include "../atom/ClassicalLiteral.h"
#include "../../util/Timer.h"
#include "../../util/Utils.h"
#include "../../util/Options.h"
#include "../../util/Trace.h"
#include "../statement/OrderRuleGroundable.h"



namespace DLV2{

namespace grounder{

void ProgramGrounder::printProgram(const vector<vector<Rule*> >& exitRules,	const vector<vector<Rule*> >& recursiveRules) {
	for (unsigned int component = 0; component < exitRules.size();
			component++) {
		for (Rule* r : exitRules[component])
			r->print();
		for (unsigned int i = 0; i < recursiveRules[component].size(); i++)
			recursiveRules[component][i]->print();
	}
	for (unsigned int i = 0; i < statementDependency->getConstraintSize(); i++)
		if (statementDependency->getConstraint(i)->getSizeBody() > 0)
			statementDependency->getConstraint(i)->print();


}

#ifdef TRACE_ON
void printTableInRule(Rule *rule,vector<vector<unsigned>>& predicate_searchInsert_table,bool body=true){
	cerr<<endl;
	PredicateExtTable *predicateExtTable=PredicateExtTable::getInstance();
//	if(body){
		for(unsigned i=0;i<rule->getSizeBody();i++){
			Predicate* p=rule->getAtomInBody(i)->getPredicate();
			if(p==nullptr) continue;
			cerr<<"---> ATOM: ";rule->getAtomInBody(i)->print(cerr);cerr<<endl;
			for(auto tableToSearch:predicate_searchInsert_table[i+rule->getSizeHead()]){
				cerr<<"TABLE: "<<tableToSearch<<" --> ";
				predicateExtTable->getPredicateExt(p)->getAtomSearcher(tableToSearch,0)->print(cerr);
				cerr<<endl;
			}
		}
//	}
//	else{
		for(unsigned i=0;i<rule->getSizeHead();i++){
			Predicate* p=rule->getAtomInHead(i)->getPredicate();
			if(p==nullptr) continue;
			cerr<<"---> ATOM: ";rule->getAtomInHead(i)->print(cerr);cerr<<endl;
			for(auto tableToSearch:predicate_searchInsert_table[i]){
				cerr<<"TABLE: "<<tableToSearch<<" --> ";
				predicateExtTable->getPredicateExt(p)->getAtomSearcher(tableToSearch,0)->print(cerr);
				cerr<<endl;
			}
		}
//	}
}
#endif

void ProgramGrounder::findRecursivePredicatesInComponentRules(const unordered_set<index_object>& componentPredicateInHead, vector<unsigned>& recursivePredicatesPositions, Rule* rule, vector<unsigned >& orderedBody) {
	for (unsigned j = 0; j < rule->getSizeBody(); ++j) {
		Predicate* pred = rule->getAtomInBody(j)->getPredicate();
		if (pred != nullptr	&& componentPredicateInHead.count(pred->getIndex()))
			recursivePredicatesPositions.push_back(j);
		orderedBody.push_back(j);
	}
}

void ProgramGrounder::orderPositiveAtomsBody(vector<unsigned>& originalOrderBody,Rule* rule) {
	rule->computeVariablesLocalIndices();
	OrderRuleGroundable* orderRuleGroundable = OrderRuleGroundableFactory::getInstance(rule);
	if (orderRuleGroundable != nullptr) {
		orderRuleGroundable->order(predicate_searchInsert_table,originalOrderBody);
		delete orderRuleGroundable;
	}
}

void ProgramGrounder::orderPositiveAtomsBody(Rule* rule) {
	rule->computeVariablesLocalIndices();
	OrderRuleGroundable* orderRuleGroundable = OrderRuleGroundableFactory::getInstance(rule);
	if (orderRuleGroundable != nullptr) {
		orderRuleGroundable->order(predicate_searchInsert_table);
		delete orderRuleGroundable;
	}
}

void ProgramGrounder::ground() {

	//Create the dependency graph
	statementDependency->createDependencyGraph(predicateTable);
	bool foundEmptyConstraint=false;

	// Create the component graph and compute an ordering among components.
	// Components' rules are classified as exit or recursive.
	// An rule occurring in a component is recursive if there is a predicate belonging
	// to the component in its positive body, otherwise it is said to be an exit rule.
	vector<vector<Rule*>> exitRules;
	vector<vector<Rule*>> recursiveRules;
	vector<vector<Rule*>> constraintRules;
	vector<Rule*> remainedConstraint;
	vector<unordered_set<index_object>> componentPredicateInHead;
	statementDependency->createComponentGraphAndComputeAnOrdering(exitRules, recursiveRules, componentPredicateInHead,constraintRules,remainedConstraint);

	trace_msg(grounding,1,"Grounding Starts Now.");


	// Ground each module according to the ordering:
	// For each component, each rule is either recursive or exit,
	// Exit rules are grounded just once, while recursive rules are grounded until no more knowledge is derived
	for (unsigned int component = 0; component < exitRules.size()&&!foundEmptyConstraint; ++component) {

		trace_msg(grounding,1,"Component: "<<component);
		trace_msg(grounding,1,"Exit rules: "<<exitRules[component].size());
		trace_msg(grounding,1,"Recursive rules: "<<recursiveRules[component].size());

		iteration=0;
		iterationToInsert=0;

		// Ground exit rules
		for (Rule* rule : exitRules[component]){
//			r->sortPositiveLiteralInBody(predicate_searchInsert_table);
			if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule)){
				continue;
			}
			trace_action_tag(grounding,1,cerr<<"Grounding Exit Rule: ";rule->print(cerr););
			orderPositiveAtomsBody(rule);
			groundRule(rule);

#ifdef DEBUG_RULE_TIME
			Timer::getInstance()->print();
#endif
		}

		if (recursiveRules[component].size() != 0){
			// Ground recursive rules
			unsigned int n_rules = recursiveRules[component].size();
			bool found_something = false;

			vector<vector<unsigned>> recursivePredicatesPositions;
			recursivePredicatesPositions.resize(n_rules);

			// A vector containing for each atom in the body (according to the current order) their original position (in the original body)
			vector<vector<unsigned>> originalOrderBody;
			originalOrderBody.resize(n_rules);

			++iterationToInsert;


			// First iteration
			for (unsigned int i = 0; i < n_rules; ++i) {
				Rule *rule=recursiveRules[component][i];

				trace_action_tag(grounding,1,cerr<<"Grounding Recursive Rule: ";rule->print(cerr););

				if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule)){
					if(n_rules>1) findRecursivePredicatesInComponentRules(componentPredicateInHead[component], recursivePredicatesPositions[i], rule, originalOrderBody[i]);
					trace_msg(grounding,1,"Rule simplified: no grounding is needed.");
					continue;
				}
				trace_msg(grounding,1,"At first iteration the tables to search in  are: ");
				trace_action_tag(grounding,2,printTableInRule(rule,predicate_searchInsert_table););

				findRecursivePredicatesInComponentRules(componentPredicateInHead[component], recursivePredicatesPositions[i], rule, originalOrderBody[i]);
				orderPositiveAtomsBody(originalOrderBody[i], rule);
				if(groundRule(rule,&componentPredicateInHead[component]))
					found_something=true;

				trace_action_tag(grounding,1,cerr<<"Found New Knowledge: "<<found_something;);
				trace_msg(grounding,1,"After the first iteration the tables to insert in  are: ");
				trace_action_tag(grounding,2,printTableInRule(rule,predicate_searchInsert_table,false););

			}
			++iterationToInsert;
			++iteration;

			//Further Iterations
			while (found_something) {
//				trace_msg(grounding,1,"Further Iterations");
				found_something = false;

				// Since in the first iteration search is performed in facts and no facts tables,
				// while in the next iteration search is performed in the delta table, it is needed
				// to keep track if the current iteration is the first or not.
				for (unsigned int i = 0; i < n_rules; ++i) {
					Rule* rule = recursiveRules[component][i];
					trace_action_tag(grounding,1,cerr<<"Grounding Recursive Rule: ";rule->print(cerr););

					//If no more knowledge is derived the grounding of this component can stop
					for(auto token: recursivePredicatesPositions[i]){
						if(nextSearchInsertPredicate(rule,componentPredicateInHead[component],token,originalOrderBody[i])){
							continue;
						}
//						rule->sortPositiveLiteralInBody(predicate_searchInsert_table,originalOrderBody[i]);
						trace_msg(grounding,1,"At this iteration the tables to search in  are: ");
						trace_action_tag(grounding,2,printTableInRule(rule,predicate_searchInsert_table););

						orderPositiveAtomsBody(originalOrderBody[i],rule);
						if (groundRule(rule,&componentPredicateInHead[component]))
							found_something = true;

						trace_action_tag(grounding,1,cerr<<"Found New Knowledge: "<<found_something;);
						trace_msg(grounding,1,"After the first iteration the tables to insert in  are: ");
						trace_action_tag(grounding,2,printTableInRule(rule,predicate_searchInsert_table,false););
					}
				}

				++iteration;
				++iterationToInsert;

//				// If more rule share a recursive predicate, only the first rule
//				// have to swap the delta, then we need a set of predicate evaluated
//				set_predicate predicateEvaluated;
//				for (unsigned int i = 0; i < n_rules; i++){
//					// Move the content of the delta table in the no fact table,
//					// and fill delta with the content of the next delta table.
//					swapInDelta(recursiveRules[component][i],predicateEvaluated);
//					trace_action_tag(grounding,1,cerr<<"Swap Delta Rule: ";recursiveRules[component][i]->print(cerr););
//					trace_action_tag(grounding,2,printTableInRule(recursiveRules[component][i],predicate_searchInsert_table););
//				}


			}
		}

		// Ground constraint rules
		for (Rule* rule : constraintRules[component]){
			if (rule->getSizeBody() == 0) continue;
			if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule)){
				continue;
			}
			try{
				orderPositiveAtomsBody(rule);
				trace_action_tag(grounding,1,cerr<<"Grounding Constraint Rule: ";rule->print(cerr););
				groundRule(rule);
			}
			catch (exception& e){
				foundEmptyConstraint=true;
				break;
			}
		}
	}


	// Remained Constraints are grounded at the end
	if(!foundEmptyConstraint)
	{
		for (auto rule:remainedConstraint)
			if (rule->getSizeBody() > 0){
				if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule)){
					continue;
				}
				try{
					orderPositiveAtomsBody(rule);
					trace_action_tag(grounding,1,cerr<<"Grounding Constraint Rule: ";rule->print(cerr););
					groundRule(rule);
				}catch (exception& e){
					break;
				}
			}
		substituteIndicesInRulesWithPossibleUndefAtoms();
	}

	outputBuilder->onEnd();

//	Timer::getInstance()->printSumTime(cerr);

	//Print and simplify the rule
//	evaluator.printAndSimplify(predicateExtTable);


}
bool ProgramGrounder::isNotEmptyPredExt(Predicate* pred,unsigned table) {
	return PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(
			table) > 0;
}

bool ProgramGrounder::inizializeSearchInsertPredicateBody(Rule* rule) {
	for (auto atom = rule->getBeginBody(); atom != rule->getEndBody(); atom++) {
		vector<pair<unsigned,SearchType>> tableToInsert;
		Predicate* pred = (*atom)->getPredicate();

		//Add fact if or the predicate is not nullptr and or the atom is not negative and then the table is not empty or the atom is negative
		// If the predicate is nullptr add FACT
		if((pred != nullptr && ( (!(*atom)->isNegative()&&isNotEmptyPredExt(pred,FACT)) || (*atom)->isNegative()) )
				|| pred == nullptr)
			tableToInsert.push_back({FACT,ALL});

		//Add nofact if the atom is not nullptr and or the atom is not negative is not EDB and the table is not empty, or if the atom is negative
		// If the pred is nullptr check if is an aggregate
		if((pred != nullptr && ( (!(*atom)->isNegative()&&!pred->isEdb()&&isNotEmptyPredExt(pred,NOFACT)) || (*atom)->isNegative()) )
				|| (pred == nullptr && (*atom)->isAggregateAtom()))
			tableToInsert.push_back({NOFACT,ALL});

		if(!(*atom)->isNegative() && tableToInsert.empty())
			return true;
		predicate_searchInsert_table.push_back(tableToInsert);
	}
	return false;
}


bool ProgramGrounder::inizializeSearchInsertPredicate(Rule* rule) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();atom++){
		vector<pair<unsigned,SearchType>> tableToInsert(1,{NOFACT,ALL});
		predicate_searchInsert_table.push_back(tableToInsert);
	}

	return inizializeSearchInsertPredicateBody(rule);
}

bool ProgramGrounder::nextSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead,unsigned token,const vector<unsigned>& originalOrderBody) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();++atom){
		vector<pair<unsigned,SearchType>> tableToInsert(1,{NOFACT,ALL});
		predicate_searchInsert_table.push_back(tableToInsert);
	}

	unsigned i=0;
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++i){
		Predicate* pred=(*atom)->getPredicate();
		vector<pair<unsigned,SearchType>> tableToInsert;


		if(pred!=nullptr){
			//Init the type of ALL (for the non recursive predicate and for recursive predicate > than a toke)
			SearchType type= ALL;

			if(componentPredicateInHead.count(pred->getIndex())){

				if(originalOrderBody[i]<token)
					type=OLD;
				else if(originalOrderBody[i]==token)
					type=NEW;
			}

			if(isNotEmptyPredExt(pred,FACT))
				tableToInsert.push_back({FACT,type});
			if(isNotEmptyPredExt(pred,NOFACT))
				tableToInsert.push_back({NOFACT,type});

		}else
			tableToInsert.push_back({FACT,ALL});




		if(!(*atom)->isNegative() && tableToInsert.empty())
			return true;

		predicate_searchInsert_table.push_back(tableToInsert);
	}

	return false;
}


void ProgramGrounder::swapInDelta(Rule *rule,set_predicate &predicateEvaluated){
	for (auto it = rule->getBeginHead(); it != rule->getEndHead(); it++) {
		set_predicate predicates=(*it)->getPredicates();
		for(auto predicate:predicates){
			PredicateExtension* predicateExt = predicateExtTable->getPredicateExt(predicate);
			if (predicateExt != nullptr && !predicateEvaluated.count(predicate)){
				predicateExt->swapTables(DELTA,NOFACT);
//				predicateExt->swapTables(NEXTDELTA,DELTA);
				predicateExt->swapPointersTables(NEXTDELTA,DELTA);
				predicateEvaluated.insert(predicate);
			}
		}
	}
}

bool ProgramGrounder::groundRule(Rule* rule, unordered_set<index_object>* componentPredicateInHead) {

	if (Options::globalOptions()->isPrintRewrittenProgram())
		{cerr<<"RULE: ";rule->print(cerr);}
	bool printTime=Options::globalOptions()->getRuleTime();
	clock_t start=0;

	if(printTime){
		cerr<<endl<<"RULE ORDERED: \t";rule->print(cerr);
		start=Timer::getInstance()->getClock();
	}

	inizialize(rule,componentPredicateInHead);

	if(rule->getSizeBody()==0){
		foundAssignment();
		if(printTime){
			clock_t end=Timer::getInstance()->getClock();
			Timer::printTimeElapsed(end-start,cerr);
		}
		return true;
	}

	bool find_assignment=false;

	if(isCartesianProductRule(rule)){
		find_assignment=groundCartesian(rule);
		if(printTime){
			clock_t end=Timer::getInstance()->getClock();
			Timer::printTimeElapsed(end-start,cerr);
		}
		return find_assignment;
	}

	bool finish=false;

	while(!finish){

		if(match()){
			if(!next()) {
				if(foundAssignment()){
					find_assignment=true;
				}
				if(!back())
					finish=true;
			}
		}else
			{
				if(!back())
					finish=true;
			}

	}

	if(printTime){
		clock_t end=Timer::getInstance()->getClock();
		Timer::printTimeElapsed(end-start,cerr);
	}

	return find_assignment;
}

void ProgramGrounder::substituteIndicesInRulesWithPossibleUndefAtoms(){
	for(unsigned i=0;i<rulesWithPossibleUndefAtoms.size();i++){
		Rule* rule=rulesWithPossibleUndefAtoms[i];
		bool ruleSimplified=false;
		for(unsigned possibleUndef:atomsPossibleUndefPositions[i]){
			Atom* atom=rule->getAtomInBody(possibleUndef);
			Atom* atomFound=predicateExtTable->getPredicateExt(atom->getPredicate())->getGroundAtom(atom);
			if(atomFound!=nullptr){
				atom->setIndex(atomFound->getIndex());
				//Simplification now can be done
				//TODO Move in the ground simplification or elsewhere
				if(atomFound->isFact()){
					ruleSimplified=true;
					break;
				}
			}
			else
				rule->setAtomToSimplifyInBody(possibleUndef);
		}
		if(!ruleSimplified)
			outputBuilder->onRule(rule);
		rule->deleteGroundRule();
	}
}

ProgramGrounder::~ProgramGrounder() {
	HashString::freeInstance();
	HashVecInt::freeInstance();
	OutputBuilder::freeInstance();
	delete statementDependency;
	delete predicateExtTable;
	delete termsMap;
	delete predicateTable;
}

//void ProgramGrounder::createAtomSearchersForPredicateBody(unsigned position, Predicate* predicate, unsigned sizeRule) {
//	PredicateExtension* predicateExtension = predicateExtTable->getPredicateExt(predicate);
//	for(auto table:predicate_searchInsert_table[position]){
//
//		auto atomSearcher=predicateExtension->addAtomSearcher(table,MAP_VECTOR,);
//		predicateExtension->getAtomSearcher(table)->setSizeResultVector(sizeRule);
//		predicate_searchInsert_atomSearcher[position].push_back(atomSearcher);
//	}
//}

void ProgramGrounder::createAtomSearchersForPredicateHead(unsigned position, Predicate* predicate, Rule* rule) {
	unsigned sizeRule=rule->getSizeBody();
	PredicateExtension* predicateExtension = predicateExtTable->getPredicateExt(predicate);

	for(unsigned i=0;i<=predicate_searchInsert_table[position][0].first;++i){
		predicateExtension->getAtomSearcher(i)->setSizeResultVector(sizeRule);
		vector<unsigned> indexing(1,0);
		auto atomSearcher=predicateExtension->addAtomSearcher(i,MAP,&indexing);
// 		auto atomSearcher=predicateExtension->addAtomSearcher(i,HASHSET,nullptr);
		if(i==predicate_searchInsert_table[position][0].first || predicateExtension->getPredicateExtentionSize(i))
			predicate_searchInsert_atomSearcher[position].push_back(atomSearcher);
		else
			predicate_searchInsert_atomSearcher[position].push_back(0);
	}
}

void ProgramGrounder::setDefaultAtomSearchers(Rule* rule, unordered_set<index_object>* componentPredicateInHead) {
	unsigned sizeRule=rule->getSizeBody();
	predicate_searchInsert_atomSearcher.clear();
	unsigned atomIndex=rule->getSizeHead();
	predicate_searchInsert_atomSearcher.resize(atomIndex+rule->getSizeBody());
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atomIndex){
		if((*atom)->isClassicalLiteral()){
			Predicate *predicate=(*atom)->getPredicate();
			createAtomSearchersForPredicateBody(atomIndex, 0, predicate, sizeRule,componentPredicateInHead);
		}
		else if((*atom)->isAggregateAtom()){
			for(unsigned i=0;i<(*atom)->getAggregateElementsSize();++i){
				Predicate *predicate=(*atom)->getAggregateElement(i)->getNafLiteral(0)->getPredicate();
				if(predicate!=nullptr)
					createAtomSearchersForPredicateBody(atomIndex, i, predicate, sizeRule,componentPredicateInHead);
			}
		}
	}
	atomIndex=0;
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();++atom,++atomIndex){
		if((*atom)->isClassicalLiteral()){
			Predicate *predicate=(*atom)->getPredicate();
			createAtomSearchersForPredicateHead(atomIndex, predicate,rule);
		}
		else if((*atom)->isChoice()){
			for(unsigned i=0;i<(*atom)->getChoiceElementsSize();++i){
				Predicate *predicate=(*atom)->getChoiceElement(i)->getFirstAtom()->getPredicate();
				if(predicate!=nullptr)
					createAtomSearchersForPredicateHead(atomIndex, predicate,rule);
			}
		}
	}

//	rule->print();
//	cout<<"Size = "<<predicate_searchInsert_atomSearcher.size()<<endl;
//	for(unsigned atom=0;atom<predicate_searchInsert_table.size();atom++){
//		cout<<"Atom: "<<atom<<" --> ";
//		for(auto i:predicate_searchInsert_table[atom]){
//			cout<<i<<" ";
//		}
//		cout<<endl;
//	}
//	cout<<endl;
//
//	for(unsigned atom=0;atom<predicate_searchInsert_atomSearcher.size();atom++){
//		cout<<"Atom: "<<atom<<" --> ";
//		for(auto i:predicate_searchInsert_atomSearcher[atom]){
//			if(i!=nullptr)
//				cout<<i->getType()<<" ";
//		}
//		cout<<endl;
//	}
//	cout<<endl;


}

}}



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

void printTableInRule(Rule *rule,vector<vector<unsigned>>& predicate_searchInsert_table){
	rule->sortPositiveLiteralInBody(predicate_searchInsert_table);
	PredicateExtTable *predicateExtTable=PredicateExtTable::getInstance();
	cerr<<"GROUND ";
	rule->print(cerr);
	for(unsigned i=0;i<rule->getSizeBody();i++){
		Predicate* p=rule->getAtomInBody(i)->getPredicate();
		if(p==nullptr) continue;
		rule->getAtomInBody(i)->print(cerr);cerr<<endl;
		for(auto tableToSearch:predicate_searchInsert_table[i+rule->getSizeHead()]){
			cerr<<"TABLE: "<<tableToSearch<<" --> ";
			predicateExtTable->getPredicateExt(p)->getAtomSearcher(tableToSearch)->print(cerr);
			cerr<<endl;
		}
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

	// Ground each module according to the ordering:
	// For each component, each rule is either recursive or exit,
	// Exit rules are grounded just once, while recursive rules are grounded until no more knowledge is derived
	for (unsigned int component = 0; component < exitRules.size()&&!foundEmptyConstraint; ++component) {

		trace_msg(grounding,1,"Component: "<<component);
		trace_msg(grounding,1,"Exit rules: "<<exitRules[component].size());
		trace_msg(grounding,1,"Recursive rules: "<<recursiveRules[component].size());

		// Ground exit rules
		for (Rule* rule : exitRules[component]){
//			r->sortPositiveLiteralInBody(predicate_searchInsert_table);
			if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule))
				continue;
			trace_action_tag(grounding,1,cerr<<"Grounding Exit Rule: ";rule->print(cerr););
			groundRule(rule);

#ifdef DEBUG_RULE_TIME
			Timer::getInstance()->print();
#endif
		}

		if (recursiveRules[component].size() != 0){
			// Ground recursive rules
			unsigned int n_rules = recursiveRules[component].size();
			bool found_something = false;

			// First iteration
			trace_msg(grounding,1,"First Iteration");
			for (unsigned int i = 0; i < n_rules; i++) {
				Rule *rule=recursiveRules[component][i];
				if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule,componentPredicateInHead[component]))
					continue;

				trace_action_tag(grounding,2,
						printTableInRule(rule,predicate_searchInsert_table);
				);

				if(groundRule(rule))
					found_something=true;


//				trace_action_tag(grounding,1,cerr<<"Found New Knowledge: "<<found_something<<" Grounding Recursive Rule: ";rule->print(cerr););
			}
			while (found_something) {
//				trace_msg(grounding,1,"Further Iterations");
				found_something = false;

				// Since in the first iteration search is performed in facts and no facts tables,
				// while in the next iteration search is performed in the delta table, it is needed
				// to keep track if the current iteration is the first or not.
				for (unsigned int i = 0; i < n_rules; i++) {
					Rule* rule = recursiveRules[component][i];
					//If no more knowledge is derived the grounding of this component can stop
					inizializeRecursiveCombinationPredicate(rule,componentPredicateInHead[component]);
					for(unsigned i=0;i<pow(2,predicate_combination.size())-1;i++){
						computeRecursiveCombinationPredicate();
						if(nextSearchInsertPredicate(rule,componentPredicateInHead[component]))
							continue;
						rule->sortPositiveLiteralInBody(predicate_searchInsert_table);

						trace_action_tag(grounding,2,
								printTableInRule(rule,predicate_searchInsert_table);
						);

						if (groundRule(rule))
							found_something = true;

						trace_action_tag(grounding,1,cerr<<"Found New Knowledge: "<<found_something<<" Grounding Recursive Rule: ";rule->print(cerr););
					}
				}

				for (unsigned int i = 0; i < n_rules; i++){
					// Move the content of the delta table in the no fact table,
					// and fill delta with the content of the next delta table.
					swapInDelta(recursiveRules[component][i]);
					trace_action_tag(grounding,1,cerr<<"Swap Delta Rule: ";recursiveRules[component][i]->print(cerr););
				}

			}
		}

		// Ground constraint rules
		for (Rule* rule : constraintRules[component]){
			if (rule->getSizeBody() == 0) continue;
			if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule))
				continue;
			try{
				groundRule(rule);
				trace_action_tag(grounding,1,cerr<<"Grounding Constraint Rule: ";rule->print(cerr););
			}
			catch (exception& e){
				foundEmptyConstraint=true;
			}
		}
	}


	// Remained Constraints are grounded at the end
	if(!foundEmptyConstraint)
	{
		for (auto rule:remainedConstraint)
			if (rule->getSizeBody() > 0){
				if(nonGroundSimplificator.simplifyRule(rule) || inizializeSearchInsertPredicate(rule))
					continue;
				try{
					groundRule(rule);
					trace_action_tag(grounding,1,cerr<<"Grounding Constraint Rule: ";rule->print(cerr););
				}catch (exception& e){
					break;
				}
			}
		substituteIndicesInRulesWithPossibleUndefAtoms();
	}

	outputBuilder->onEnd();


	//Print and simplify the rule
//	evaluator.printAndSimplify(predicateExtTable);


}

void ProgramGrounder::inizializeRecursiveCombinationPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead){
	predicate_combination.clear();
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();atom++){
		if((*atom)->getPredicate()!=nullptr && componentPredicateInHead.count((*atom)->getPredicate()->getIndex())){
			predicate_combination.push_back(false);
		}
	}
}

void ProgramGrounder::computeRecursiveCombinationPredicate(){
	for(unsigned i=predicate_combination.size()-1;i>=0;i--){
		if(!predicate_combination[i]){
			predicate_combination[i]=true;
			break;
		}
		predicate_combination[i]=false;
	}
}

bool ProgramGrounder::inizializeSearchInsertPredicateBody(Rule* rule) {
	for (auto atom = rule->getBeginBody(); atom != rule->getEndBody(); atom++) {
		vector<unsigned> tableToInsert;
		Predicate* pred = (*atom)->getPredicate();
		if (pred != nullptr){
			if (PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(FACT) > 0)
				tableToInsert.push_back(FACT);
			if(!pred->isEdb() && PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(NOFACT) > 0)
				tableToInsert.push_back(NOFACT);
		}
		else{
			tableToInsert.push_back(0);
		}
		if(!(*atom)->isNegative() && tableToInsert.empty())
			return true;
		predicate_searchInsert_table.push_back(tableToInsert);
	}
	return false;
}

bool ProgramGrounder::inizializeSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();atom++){
		unordered_set<index_object> indicesPredicates=(*atom)->getPredicatesIndices();
		if(!Utils::isDisjoint(componentPredicateInHead,indicesPredicates)){
			vector<unsigned> tableToInsert(1,DELTA);
			predicate_searchInsert_table.push_back(tableToInsert);
		}else{
			vector<unsigned> tableToInsert(1,NOFACT);
			predicate_searchInsert_table.push_back(tableToInsert);
		}
	}
	return inizializeSearchInsertPredicateBody(rule);
}

bool ProgramGrounder::inizializeSearchInsertPredicate(Rule* rule) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();atom++){
		vector<unsigned> tableToInsert(1,NOFACT);
		predicate_searchInsert_table.push_back(tableToInsert);
	}

	return inizializeSearchInsertPredicateBody(rule);
}

bool ProgramGrounder::nextSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();atom++){
		unordered_set<index_object> indicesPredicates=(*atom)->getPredicatesIndices();
		if(!Utils::isDisjoint(componentPredicateInHead,indicesPredicates)){
			vector<unsigned> tableToInsert(1,NEXTDELTA);
			predicate_searchInsert_table.push_back(tableToInsert);
		}else{
			vector<unsigned> tableToInsert(1,NOFACT);
			predicate_searchInsert_table.push_back(tableToInsert);
		}
	}

	unsigned currentRecursivePredicate=0;
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();atom++){
		Predicate* pred=(*atom)->getPredicate();
		if(pred!=nullptr){
			if(componentPredicateInHead.count(pred->getIndex())){
				if(predicate_combination[currentRecursivePredicate]){
					if (PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(DELTA) > 0){
						vector<unsigned> tableToInsert(1,DELTA);
						predicate_searchInsert_table.push_back(tableToInsert);
					}
					else
						if(!(*atom)->isNegative())
							return true;
				}else{
					vector<unsigned> tableToInsert;
					if (PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(NOFACT) > 0)
						tableToInsert.push_back(NOFACT);
					if (PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(FACT) > 0)
						tableToInsert.push_back(FACT);
					if(!(*atom)->isNegative() && tableToInsert.empty())
						return true;
					predicate_searchInsert_table.push_back(tableToInsert);
				}
				currentRecursivePredicate++;
		}else{
			vector<unsigned> tableToInsert;
			if (PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(NOFACT) > 0)
				tableToInsert.push_back(NOFACT);
			if (PredicateExtTable::getInstance()->getPredicateExt(pred)->getPredicateExtentionSize(FACT) > 0)
				tableToInsert.push_back(FACT);
			if(!(*atom)->isNegative() && tableToInsert.empty())
				return true;
			predicate_searchInsert_table.push_back(tableToInsert);
			}
		}
		else{
			vector<unsigned> tableToInsert(1,0);
			predicate_searchInsert_table.push_back(tableToInsert);
		}
	}
	return false;
}


void ProgramGrounder::swapInDelta(Rule *rule){
	for (auto it = rule->getBeginHead(); it != rule->getEndHead(); it++) {
		set_predicate predicates=(*it)->getPredicates();
		for(auto predicate:predicates){
			PredicateExtension* predicateExt = predicateExtTable->getPredicateExt(predicate);
			if (predicateExt != nullptr){
				predicateExt->swapTables(DELTA,NOFACT);
//				predicateExt->swapTables(NEXTDELTA,DELTA);
				predicateExt->swapPointersTables(NEXTDELTA,DELTA);
			}
		}
	}
}

void printTimeElapsed(clock_t time,ostream& stream){
	stream<<"TIME: \t"<<((time)/(double) CLOCKS_PER_SEC)<<endl;
	stream<<"----------------------"<<endl;
}

bool ProgramGrounder::groundRule(Rule* rule) {

	if (Options::globalOptions()->isPrintRewrittenProgram())
		{cout<<"RULE: ";rule->print();}
#ifdef DEBUG_GRULE_TIME
	cerr<<endl<<"RULE ORDERED: \t";rule->print(cerr);
	clock_t start=Timer::getInstance()->getClock();
#endif

	inizialize(rule);

	if(rule->getSizeBody()==0){
		foundAssignment();
#ifdef DEBUG_GRULE_TIME
	clock_t end=Timer::getInstance()->getClock();
	printTimeElapsed(end-start,cerr);
#endif
		return true;
	}

	bool find_assignment=false;
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

#ifdef DEBUG_GRULE_TIME
	clock_t end=Timer::getInstance()->getClock();
	printTimeElapsed(end-start,cerr);
#endif

	return find_assignment;
}

void ProgramGrounder::substituteIndicesInRulesWithPossibleUndefAtoms(){
	for(unsigned i=0;i<rulesWithPossibleUndefAtoms.size();i++){
		Rule* rule=rulesWithPossibleUndefAtoms[i];
		bool ruleSimplified=false;
		for(unsigned possibleUndef:atomsPossibleUndefPositions[i]){
			Atom* atom=rule->getAtomInBody(possibleUndef);
			Atom* atomFound=predicateExtTable->getPredicateExt(atom->getPredicate())->getAtom(atom);
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

};

};

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

namespace DLV2{

namespace grounder{

#define DEBUG 0

void ProgramGrounder::ground() {

	//Create the dependency graph
	statementDependency->createDependencyGraph(predicateTable);

	// Create the component graph and compute an ordering among components.
	// Components' rules are classified as exit or recursive.
	// An rule occurring in a component is recursive if there is a predicate belonging
	// to the component in its positive body, otherwise it is said to be an exit rule.
	vector<vector<Rule*>> exitRules;
	vector<vector<Rule*>> recursiveRules;
	vector<unordered_set<index_object>> componentPredicateInHead;
	statementDependency->createComponentGraphAndComputeAnOrdering(exitRules, recursiveRules, componentPredicateInHead);

	// Ground each module according to the ordering:
	// For each component, each rule is either recursive or exit,
	// Exit rules are grounded just once, while recursive rules are grounded until no more knowledge is derived
	for (unsigned int component = 0; component < exitRules.size(); component++) {

#if DEBUG == 1
		cout<<"Component: "<<component;
		cout<<"\tExit rules: "<<exitRules[component].size();
		cout<<"\tRecursive rules: "<<recursiveRules[component].size()<<endl;
#endif

		// Ground exit rules
		for (Rule* r : exitRules[component]){
			inizializeSearchInsertPredicate(r);
			groundRule(r);
#ifdef DEBUG_RULE_TIME
			Timer::getInstance()->print();
#endif
		}

		// Ground recursive rules
		if (recursiveRules[component].size() > 0) {
			unsigned int n_rules = recursiveRules[component].size();
			bool found_something = false;

			// First iteration
			for (unsigned int i = 0; i < n_rules; i++) {
				Rule *rule=recursiveRules[component][i];
				inizializeSearchInsertPredicate(rule,componentPredicateInHead[component]);
				if(groundRule(rule))
					found_something=true;
			}
			while (found_something) {
				found_something = false;

				// Since in the first iteration search is performed in facts and no facts tables,
				// while in the next iteration search is performed in the delta table, it is needed
				// to keep track if the current iteration is the first or not.
				for (unsigned int i = 0; i < n_rules; i++) {
					Rule* r = recursiveRules[component][i];
					//If no more knowledge is derived the grounding of this component can stop
#if DEBUG == 1
					r->print();
#endif

					inizializeRecursiveCombinationPredicate(r,componentPredicateInHead[component]);
					for(unsigned i=0;i<pow(2,predicate_combination.size())-1;i++){
						computeRecursiveCombinationPredicate();
						nextSearchInsertPredicate(r,componentPredicateInHead[component]);
						if (groundRule(r)){
							found_something = true;
						}
					}
				}

				for (unsigned int i = 0; i < n_rules; i++)
					// Move the content of the delta table in the no fact table,
					// and fill delta with the content of the next delta table.
					swapInDelta(recursiveRules[component][i]);

			}
		}
	}

	// Constraints are grounded at the end
	for (unsigned int i = 0; i < statementDependency->getConstraintSize(); i++)
		if (statementDependency->getConstraint(i)->getSizeBody() > 0){
			Rule *rule=statementDependency->getConstraint(i);
			inizializeSearchInsertPredicate(rule);
			groundRule(rule);
		}

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

void ProgramGrounder::inizializeSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();atom++){
		if(componentPredicateInHead.count((*atom)->getPredicate()->getIndex())){
			vector<unsigned> tableToInsert(1,DELTA);
			predicate_searchInsert_table.push_back(tableToInsert);
		}else{
			vector<unsigned> tableToInsert(1,NOFACT);
			predicate_searchInsert_table.push_back(tableToInsert);
		}
	}

	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();atom++){
			vector<unsigned> tableToInsert;
			if((*atom)->getPredicate()!=nullptr && (*atom)->getPredicate()->isEdb())
				{tableToInsert.push_back(FACT);}
			else
				{tableToInsert.push_back(FACT);tableToInsert.push_back(NOFACT);}
			predicate_searchInsert_table.push_back(tableToInsert);
	}
}

void ProgramGrounder::inizializeSearchInsertPredicate(Rule* rule) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();atom++){
		vector<unsigned> tableToInsert(1,NOFACT);
		predicate_searchInsert_table.push_back(tableToInsert);

	}

	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();atom++){
		vector<unsigned> tableToInsert;
		if((*atom)->getPredicate()!=nullptr && (*atom)->getPredicate()->isEdb())
			{tableToInsert.push_back(FACT);}
		else
			{tableToInsert.push_back(FACT);tableToInsert.push_back(NOFACT);}
		predicate_searchInsert_table.push_back(tableToInsert);
	}
}

void ProgramGrounder::nextSearchInsertPredicate(Rule* rule,unordered_set<index_object>& componentPredicateInHead) {
	predicate_searchInsert_table.clear();
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();atom++){
		if(componentPredicateInHead.count((*atom)->getPredicate()->getIndex())){
			vector<unsigned> tableToInsert(1,NEXTDELTA);
			predicate_searchInsert_table.push_back(tableToInsert);
		}else{
			vector<unsigned> tableToInsert(1,NOFACT);
			predicate_searchInsert_table.push_back(tableToInsert);
		}
	}

	unsigned currentRecursivePredicate=0;
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();atom++){
		if((*atom)->getPredicate()!=nullptr && componentPredicateInHead.count((*atom)->getPredicate()->getIndex())){
			if(predicate_combination[currentRecursivePredicate]){
				vector<unsigned> tableToInsert(1,DELTA);
				predicate_searchInsert_table.push_back(tableToInsert);
			}else{
				vector<unsigned> tableToInsert(2);
				tableToInsert[0]=NOFACT;tableToInsert[1]=FACT;
				predicate_searchInsert_table.push_back(tableToInsert);
			}
			currentRecursivePredicate++;
		}else{
			vector<unsigned> tableToInsert(2);
			tableToInsert[0]=NOFACT;tableToInsert[1]=FACT;
			predicate_searchInsert_table.push_back(tableToInsert);
		}
	}
}


void ProgramGrounder::swapInDelta(Rule *rule){
	for (auto it = rule->getBeginHead(); it != rule->getEndHead(); it++) {
		PredicateExtension* predicateExt = predicateExtTable->getPredicateExt((*it)->getPredicate());
		if (predicateExt != nullptr){
			predicateExt->swapTables(DELTA,NOFACT);
			predicateExt->swapTables(NEXTDELTA,DELTA);
		}
	}

}

bool ProgramGrounder::groundRule(Rule* rule) {

//	cout<<"RULE ";rule->print();
//	unsigned i=0;
//	for(auto v1:predicate_searchInsert_table){
//		cout<<"ATOM "<<i<<endl;
//		for(auto v2:v1){
//			cout<<"\t TABLE "<<v2<<endl;
//		}
//		i++;
//	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("RULE");
#endif

	inizialize(rule);

	if(rule->getSizeBody()==0){
		foundAssignment();
		return true;
	}

	bool find_assignment=false;
	bool finish=false;

	while(!finish){

		if(match()){
			if(!next()) {
				do{if(foundAssignment())find_assignment=true;}while(match());
				if(!back())finish=true;
			}
		}else if(!back())
			finish=true;

	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("RULE");
#endif
	return find_assignment;
}


ProgramGrounder::~ProgramGrounder() {
	HashString::freeInstance();
	HashVecInt::freeInstance();
	delete statementDependency;
	delete predicateExtTable;
	delete termsMap;
	delete predicateTable;
}

};

};

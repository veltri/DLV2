/*
 * OrderRuleGroundable.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: jessica
 */

#include "OrderRuleGroundable.h"
#include <list>
#include "../../util/Trace.h"
#include "../../util/Options.h"
#include "../../util/Utils.h"

namespace DLV2 {
namespace grounder {

vector<unsigned> OrderRuleGroundable::order(Rule* rule,vector<vector<unsigned>>& predicate_searchInsert_table) {
	unsigned sizeBody=rule->getSizeBody();

	vector<Atom*> orderedBody;
	orderedBody.reserve(sizeBody);

	vector<unsigned> orderedPositions;
	orderedPositions.reserve(sizeBody);

	vector<vector<unsigned>> orderdedPredicateSearchInsertTable;
	orderdedPredicateSearchInsertTable.reserve(predicate_searchInsert_table.size());

	set_term variablesInBody;

	unsigned sizeHead=predicate_searchInsert_table.size()-sizeBody;

	list<unsigned> atomsToInsert;
	for(unsigned i=0;i<sizeHead;++i)
		orderdedPredicateSearchInsertTable.push_back(predicate_searchInsert_table[i]);

	for(unsigned i=0;i<sizeBody;++i)
		atomsToInsert.push_back(i);

	trace_action_tag(grounding,1,
		cerr<<"Before Ordering Body and Search/Insert tables are: ";
		for(unsigned i=0;i<rule->getSizeBody();++i){
			rule->getAtomInBody(i)->print(cerr);
			for(auto j:predicate_searchInsert_table[i+sizeHead])
				cerr<<" "<<j;
			cerr<<"  ";
		}
		cerr<<endl;
	);

	while(!atomsToInsert.empty()){
		list<unsigned>::iterator bestAtom=assignWeights(rule,atomsToInsert,variablesInBody);
		orderdedPredicateSearchInsertTable.push_back(predicate_searchInsert_table[sizeHead+*bestAtom]);
		Atom* atom=rule->getAtomInBody((*bestAtom));
		orderedBody.push_back(atom);
		orderedPositions.push_back(*bestAtom);
		set_term variables=atom->getVariable();
		variablesInBody.insert(variables.begin(),variables.end());
		atomsToInsert.erase(bestAtom);
	}

	rule->setBody(orderedBody);
	predicate_searchInsert_table=orderdedPredicateSearchInsertTable;

	trace_action_tag(grounding,1,
		cerr<<"After Ordering Body and Search/Insert tables are: ";
		for(unsigned i=0;i<rule->getSizeBody();++i){
			rule->getAtomInBody(i)->print(cerr);
			for(auto j:orderdedPredicateSearchInsertTable[i+sizeHead])
				cerr<<" "<<j;
			cerr<<"  ";
		}
		cerr<<endl;
	);

	return orderedPositions;

}

void OrderRuleGroundable::order(Rule* rule, vector<vector<unsigned> >& predicate_searchInsert_table, vector<unsigned>& originalOrderBody) {
	vector<unsigned> orderedPositions=order(rule,predicate_searchInsert_table);
	vector<unsigned> newOriginalOrderBody;
	newOriginalOrderBody.resize(originalOrderBody.size());
	for(unsigned i=0;i<orderedPositions.size();++i){
		unsigned pos=orderedPositions[i];
		newOriginalOrderBody[i]=originalOrderBody[pos];
	}
	originalOrderBody=newOriginalOrderBody;
}

bool OrderRuleGroundable::isBound(Atom* atom, Rule* rule, set_term& variableInTheBody) {
	if(atom->isBuiltIn() && atom->isAssignment()){
		Term* firstTerm=atom->getTerm(0);
		set_term varsFirst;
		firstTerm->getVariable(varsFirst);

		bool firstContained;
		if(varsFirst.empty())
			firstContained=true;
		else
			firstContained = Utils::isContained(varsFirst,variableInTheBody);
		if(varsFirst.size()>1 &&  !firstContained)
			return false;

		Term* secondTerm=atom->getTerm(1);
		set_term varsSecond;
		secondTerm->getVariable(varsSecond);
		bool secondContained;
		if(varsSecond.empty())
			secondContained=true;
		else
			secondContained = Utils::isContained(varsSecond,variableInTheBody);
		if(firstContained && secondContained)
			atom->setAssignment(false);
		if(secondContained || firstContained)
			return true;
		return false;
	}
	else if(atom->isAggregateAtom()){
		set_term variables=atom->getSharedVariable(rule->getBeginBody(),rule->getEndBody(),!atom->isAssignment());
		if(atom->isAssignment())
			variables.erase(atom->getFirstGuard());
		return Utils::isContained(variables,variableInTheBody);
	}
	set_term variables=atom->getVariable();
	return Utils::isContained(variables,variableInTheBody);

}




list<unsigned>::iterator AllOrderRuleGroundable::assignWeights(Rule* rule, list<unsigned>& atomsToInsert, set_term& variableInTheBody) {
	int bestWeight=INT_MAX;
	list<unsigned>::iterator bestAtomIt;
	for(list<unsigned>::iterator it=atomsToInsert.begin();it!=atomsToInsert.end();++it){
		Atom* atom=rule->getAtomInBody(*it);
		double weight=INT_MAX;

		if(atom->isClassicalLiteral() && !atom->isNegative()){
			weight=assignWeightPositiveClassicalLit(atom);
		}
		else if(isBound(atom,rule,variableInTheBody)){
			if(atom->isClassicalLiteral() && atom->isNegative()){
				weight=assignWeightNegativeClassicalLit(atom);
			}
			else if(atom->isBuiltIn()){
				weight=assignWeightBuiltInAtom(atom);
			}
			else if(atom->isAggregateAtom()){
				weight=assignWeightAggregateAtom(atom);
			}
		}
//		else
//			continue;

		if(weight<bestWeight){
			bestWeight=weight;
			bestAtomIt=it;
		}
	}
	return bestAtomIt;
}



}
}



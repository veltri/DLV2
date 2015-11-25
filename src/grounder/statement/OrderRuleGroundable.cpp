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

list<unsigned>::iterator AllOrderRuleGroundable::assignWeights(Rule* rule, list<unsigned>& atomsToInsert, set_term& variableInTheBody) {
	int bestWeight=INT_MAX;
	list<unsigned>::iterator bestAtomIt;
	for(list<unsigned>::iterator it=atomsToInsert.begin();it!=atomsToInsert.end();++it){
		Atom* atom=rule->getAtomInBody(*it);
		double weight=-1;

		if(atom->isClassicalLiteral() && !atom->isNegative()){
			weight=assignWeightPositiveClassicalLit(atom);
		}
		else if(!isBound(variableInTheBody,atom)){
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

		if(weight<bestWeight){
			bestWeight=weight;
			bestAtomIt=it;
		}
	}
	return bestAtomIt;

}

bool AllOrderRuleGroundable::isBound(set_term& variableInTheBody, Atom* atom) {
	set_term variables=atom->getVariable(); //TODO check aggregate
	return Utils::isContained(variables,variableInTheBody);
}

}
}



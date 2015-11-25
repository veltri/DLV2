/*
 * OrderRuleGroundable.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: jessica
 */

#include "OrderRuleGroundable.h"

namespace DLV2 {
namespace grounder {
#include <list>
#include "../../util/Trace.h"

void OrderRuleGroundable::order(Rule* rule,const vector<Atom*>& ruleBody,vector<vector<unsigned>>& predicate_searchInsert_table) {

	vector<Atom*> orderedBody;
	orderedBody.reserve(ruleBody.size());

	vector<vector<unsigned>> orderdedPredicateSearchInsertTable;
	orderdedPredicateSearchInsertTable.reserve(predicate_searchInsert_table.size());

	unsigned sizeHead=predicate_searchInsert_table.size()-ruleBody.size();

	list<unsigned> atomsToInsert;
	for(unsigned i=0;i<sizeHead;++i)
		orderdedPredicateSearchInsertTable.push_back(predicate_searchInsert_table[i]);

	for(unsigned i=0;i<ruleBody.size();++i)
		atomsToInsert.push_back(i);

	trace_action_tag("Grounding",1,
		cerr<<"Before Ordering Body and Search/Insert tables are: "
		for(unsigned i=0;i<ruleBody.size();++i){
			ruleBody[i]->print(cerr);
			for(auto j:predicate_searchInsert_table[i+sizeHead])
				cerr<<" "<<j;
			cerr<<"  ";
		}
		cerr<<endl;
	);

	while(!atomsToInsert.empty()){
		list<unsigned>::iterator bestAtom=assignWeights(ruleBody,atomsToInsert);
		orderdedPredicateSearchInsertTable.push_back(predicate_searchInsert_table[sizeHead+*bestAtom]);
		orderedBody.push_back(ruleBody[(*bestAtom)]);
		atomsToInsert.erase(bestAtom);
	}

	rule->setBody(orderedBody);
	predicate_searchInsert_table=orderdedPredicateSearchInsertTable;

	trace_action_tag("Grounding",1,
		cerr<<"After Ordering Body and Search/Insert tables are: "
		for(unsigned i=0;i<orderedBody.size();++i){
			ruleBody[i]->print(cerr);
			for(auto j:orderdedPredicateSearchInsertTable[i+sizeHead])
				cerr<<" "<<j;
			cerr<<"  ";
		}
	cerr<<endl;
	);

}

list<unsigned>::iterator SimpleOrderRuleGroundable::assignWeights(const vector<Atom*>& ruleBody, list<unsigned>& atomsToInsert) {
	int bestWeight=INT_MAX;
	list<unsigned>::iterator bestAtomIt;
	for(list<unsigned>::iterator it=atomsToInsert.begin();it!=atomsToInsert.end();++it){
		unsigned atomPosition=(*it);
		Atom* atom=ruleBody[atomPosition];
		int weight=-1;

		if(atom->isClassicalLiteral() && !atom->isNegative()){
			weight=0;
		}
		else if(atom->isClassicalLiteral() && atom->isNegative()){
			weight=1;
		}
		else if(atom->isBuiltIn()){
			if(atom->isAssignment())
				weight=0;
			else
				weight=2;
		}
		else if(atom->isAggregateAtom()){
			if(atom->isAssignment())
				weight=0;
			else
				weight=3;
		}

		if(weight<bestWeight){
			bestWeight=weight;
			bestAtomIt=it;
		}
	}
	return bestAtomIt;

}

}
}



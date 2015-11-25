/*
 * OrderRuleGroundable.h
 *
 *  Created on: Nov 25, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_
#define SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_

#include "Rule.h"

namespace DLV2 {
namespace grounder {

class OrderRuleGroundable {
public:
	virtual ~OrderRuleGroundable(){};
	void order(Rule* rule,const vector<Atom*>& ruleBody,vector<vector<unsigned>>& predicate_searchInsert_table);
	virtual list<unsigned>::iterator assignWeights(const vector<Atom*>& ruleBody, list<unsigned>& atomsToInsert) = 0;
};

class SimpleOrderRuleGroundable : public OrderRuleGroundable{
public:
	virtual ~SimpleOrderRuleGroundable(){};
	virtual list<unsigned>::iterator assignWeights(const vector<Atom*>& ruleBody, list<unsigned>& atomsToInsert);
};

}}

#endif /* SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_ */

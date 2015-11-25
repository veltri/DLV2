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
	vector<unsigned> order(Rule* rule, vector<vector<unsigned>>& predicate_searchInsert_table);
	void order(Rule* rule, vector<vector<unsigned>>& predicate_searchInsert_table, vector<unsigned>& originalOrderBody);
	virtual list<unsigned>::iterator assignWeights(Rule* rule, list<unsigned>& atomsToInsert) = 0;
};

class SimpleOrderRuleGroundable : public OrderRuleGroundable{
public:
	virtual ~SimpleOrderRuleGroundable(){};
	virtual list<unsigned>::iterator assignWeights(Rule* rule, list<unsigned>& atomsToInsert);
};

}}

#endif /* SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_ */

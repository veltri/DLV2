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
	///This method orders the body of a given exit rule
	vector<unsigned> order(Rule* rule, vector<vector<unsigned>>& predicate_searchInsert_table);
	///This method orders the body of a given recursive rule
	void order(Rule* rule, vector<vector<unsigned>>& predicate_searchInsert_table, vector<unsigned>& originalOrderBody);

	/// This method assigns to each remained atom (to be added in the sorted body) a weight,
	/// and returns the iterator to the atom with the best weight.
	/// It is virtual pure, because it has to be defined in each concrete class.
	virtual list<unsigned>::iterator assignWeights(Rule* rule, list<unsigned>& atomsToInsert) = 0;
};

class AllOrderRuleGroundable : public OrderRuleGroundable{
public:
	virtual ~AllOrderRuleGroundable(){};
	virtual list<unsigned>::iterator assignWeights(Rule* rule, list<unsigned>& atomsToInsert);
};

}}

#endif /* SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_ */

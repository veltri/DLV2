/*
 * OrderRuleGroundable.h
 *
 *  Created on: Nov 25, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_
#define SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_

#include "Rule.h"
#include "../table/PredicateExtension.h"

namespace DLV2 {
namespace grounder {

class OrderRuleGroundable {
public:
	OrderRuleGroundable(Rule* rule):predicateExtTable(PredicateExtTable::getInstance()),rule(rule){}
	virtual ~OrderRuleGroundable(){}
	///This method orders the body of a given exit rule
	vector<unsigned> order(vector<vector<unsigned>>& predicate_searchInsert_table);
	///This method orders the body of a given recursive rule
	void order(vector<vector<unsigned>>& predicate_searchInsert_table, vector<unsigned>& originalOrderBody);

	/// This method assigns to each remained atom (to be added in the sorted body) a weight,
	/// and returns the iterator to the atom with the best weight.
	/// It is virtual pure, because it has to be defined in each concrete class.
	virtual list<unsigned>::iterator assignWeights(list<unsigned>& atomsToInsert) = 0;


	virtual bool isBound(Atom* atom, unsigned orginalPosition);
protected:
	vector<vector<unsigned>> predicate_searchInsert_table;
	PredicateExtTable* predicateExtTable;
	Rule* rule;
	set_term variablesInTheBody;
	vector<set_term> atomsVariables;
};

class AllOrderRuleGroundable : public OrderRuleGroundable{
public:
	AllOrderRuleGroundable(Rule* rule):OrderRuleGroundable(rule){}
	virtual ~AllOrderRuleGroundable(){}
	virtual list<unsigned>::iterator assignWeights(list<unsigned>& atomsToInsert);

	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition){return 0;};
	virtual double assignWeightNegativeClassicalLit(Atom* atom, unsigned originalPosition){return 1;};
	virtual double assignWeightBuiltInAtom(Atom* atom, unsigned originalPosition){return 2;};
	virtual double assignWeightAggregateAtom(Atom* atom, unsigned originalPosition){return 3;};
	virtual void update(Atom* atomAdded){};
};

class CombinedCriterion : public AllOrderRuleGroundable {
public:
	CombinedCriterion(Rule* rule):AllOrderRuleGroundable(rule){}
	virtual ~CombinedCriterion(){}
	virtual double assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition);
	virtual double assignWeightNegativeClassicalLit(Atom* atom, unsigned originalPosition);
	virtual double assignWeightAggregateAtom(Atom* atom, unsigned originalPosition);
	virtual double assignWeightBuiltInAtom(Atom* atom, unsigned originalPosition);
	virtual void update(Atom* atomAdded){updateVariableSelectivity(atomAdded);};
private:
	void computeVariablesDomains();
	void updateVariableSelectivity(Atom* atomAdded);
	map_term<unsigned> variablesDomains;
	map_term<double> variablesSelectivities;

};

}}

#endif /* SRC_GROUNDER_STATEMENT_ORDERRULEGROUNDABLE_H_ */

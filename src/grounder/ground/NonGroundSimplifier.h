/*
 * NonGroundSimplifier.h
 *
 *  Created on: Jul 3, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_GROUND_NONGROUNDSIMPLIFIER_H_
#define SRC_GROUNDER_GROUND_NONGROUNDSIMPLIFIER_H_

#include "StatementDependency.h"
#include "../table/PredicateExtension.h"

using namespace std;

namespace DLV2 {
namespace grounder {

enum Simplify {SIMPLIFY_RULE,SIMPLIFY_ATOM,NO_SIMPLIFY};

class NonGroundSimplifier {

public:
	NonGroundSimplifier():predicateExtTable(PredicateExtTable::getInstance()),statementDependency(StatementDependency::getInstance()){};
	virtual ~NonGroundSimplifier(){};

	///Simplify the given rule according to the simplification methods
	//TODO to safely remove atoms check if their predicates are stratified
	bool simplifyRule(Rule *r);

protected:
	bool checkDuplicate(vector<Atom*>::const_iterator begin,vector<Atom*>::const_iterator end,vector<Atom*>::const_iterator currentIt) const;
	bool checkOpposite(vector<Atom*>::const_iterator begin,vector<Atom*>::const_iterator end,vector<Atom*>::const_iterator currentIt) const;
	bool checkFalsity(vector<Atom*>::const_iterator currentIt) const;
	bool checkAggregateSumCountStringGuard(vector<Atom*>::const_iterator currentIt,bool& alwaysTrue) const;
	bool checkAggregateAllAggTermShared(Rule *rule,vector<Atom*>::const_iterator currentIt,bool& alwaysTrue) const;
	bool checkAggregateCountNegativeGuard(vector<Atom*>::const_iterator currentIt,bool& alwaysTrue) const;

private:
	///A pointer to the instances table
	PredicateExtTable* predicateExtTable;
	///A pointer to the statement table
	StatementDependency* statementDependency;

	void removeSimplifiedLiterals(Rule* r,vector<unsigned> atoms_to_delete);
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_NONGROUNDSIMPLIFIER_H_ */

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

class NonGroundSimplifier {
public:
	NonGroundSimplifier():predicateExtTable(PredicateExtTable::getInstance()),statementDependency(StatementDependency::getInstance()){};
	///Simplify the rules and constraints in the statement Dependency
	bool simplifyRule(Rule *r);
	virtual ~NonGroundSimplifier(){};

protected:
	bool checkDuplicate(vector<Atom*>::const_iterator begin,vector<Atom*>::const_iterator end,vector<Atom*>::const_iterator currentIt)const;
	bool checkOpposite(vector<Atom*>::const_iterator begin,vector<Atom*>::const_iterator end,vector<Atom*>::const_iterator currentIt)const;
	bool checkFalsity(vector<Atom*>::const_iterator currentIt)const;
	bool checkAggregateSumCountStringGuard(vector<Atom*>::const_iterator currentIt,bool& alwaysTrue) const ;


private:
	///A pointer to the instances table
	PredicateExtTable* predicateExtTable;
	///A pointer to the statement table
	StatementDependency* statementDependency;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_NONGROUNDSIMPLIFIER_H_ */

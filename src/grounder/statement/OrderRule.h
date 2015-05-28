/*
 * OrderRule.h
 *
 *  Created on: May 28, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_STATEMENT_ORDERRULE_H_
#define SRC_GROUNDER_STATEMENT_ORDERRULE_H_

#include "../atom/AggregateAtom.h"
#include <list>

namespace DLV2 {
namespace grounder {

class OrderRule {
private:
	Rule* rule;
	set_term safeVariables;
	list<unsigned> builtInAtoms;
	list<unsigned> negativeAtoms;
	list<unsigned> aggregatesAtoms;
	unordered_map<unsigned,set_term> mapAtomsVariables;
	vector<Atom*> orderedBody;

	//Utility methods
	void checkBuiltInSafety(bool& firstSafe, Term* firstTerm,Term*& bindVariable);
	void lookForVariablesUnsafe(set_term& variables,Atom* atom, list<unsigned>::iterator it, vector<list<unsigned>::iterator>& atomsUnlocked);

public:
	OrderRule(Rule* r);
	void order();
	void addSafeVariablesInAtom(Atom* atom, unsigned pos);
	void unlockAtoms(list<unsigned>& atoms);
	//TODO method for cyclic dependency
	void computeAtomsVariables();
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_ORDERRULE_H_ */

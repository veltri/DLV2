/*
 * OrderRule.h
 *
 *  Created on: May 28, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_STATEMENT_ORDERRULE_H_
#define SRC_GROUNDER_STATEMENT_ORDERRULE_H_

#include "Rule.h"
#include <list>

namespace DLV2 {
namespace grounder {

class OrderRule {
private:
	Rule* rule;
	set_term safeVariables;
	list<Atom*> builtInAtoms;
	list<Atom*> negativeAtoms;
	list<Atom*> aggregatesAtoms;
	vector<Atom*> orderedBody;
public:
	void order();
	void addSafeVariablesInAtom(Atom* atom);
	void unlockAtoms(list<Atom*>& atoms);
	//TODO method for cyclic dependency
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_ORDERRULE_H_ */

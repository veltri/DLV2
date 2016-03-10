/*
 * GroundingPreferences.h
 *
 *  Created on: Mar 10, 2016
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_STATEMENT_GROUNDINGPREFERENCES_H_
#define SRC_GROUNDER_STATEMENT_GROUNDINGPREFERENCES_H_

#include <unordered_map>
#include "Rule.h"
using namespace std;

namespace DLV2 {
namespace grounder {

//TODO
// Remember to delete the atoms
class GroundingPreferences {
public:
	bool addRuleOrderingType(Rule* rule, unsigned orderingType);
	bool addRuleAtomIndexingSetting(Rule* rule, Atom* atom, vector<unsigned>& arguments);
	bool addRulePartialOrder(Rule* rule, const vector<Atom*>& beforeAtoms, const vector<Atom*>& afterAtoms);

	bool addGlobalOrderingType(unsigned orderingType);
	bool addGlobalAtomIndexingSetting(Atom* atom, vector<unsigned>& arguments);
	bool addGlobalPartialOrder(const vector<Atom*>& beforeAtoms, const vector<Atom*>& afterAtoms);
private:
	unordered_map<unsigned,unsigned> rulesOrderingTypes;
	unordered_map<unsigned,vector<unsigned,vector<unsigned>>> rulesAtomsIndexingArguments;
	unordered_map<unsigned,vector<vector<bool>>> rulesPartialOrders;

	unsigned globalOrderingType;

	int checkIfAtomIsPresentInRule(Rule* rule, Atom* atom);
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_GROUNDINGPREFERENCES_H_ */

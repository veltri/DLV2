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
#include <iostream>
using namespace std;

namespace DLV2 {
namespace grounder {

//TODO
// Remember to delete the atoms

enum AnnotationsError {OK, ATOM_NOT_PRESENT, ARITY_ERROR, CONFLICT_FOUND};

class GroundingPreferences {
public:
	bool addRuleOrderingType(Rule* rule, unsigned orderingType);
	AnnotationsError addRuleAtomIndexingSetting(Rule* rule, Atom* atom, vector<unsigned>& arguments);
	AnnotationsError addRulePartialOrderBefore(Rule* rule, Atom* beforeAtom);
	AnnotationsError addRulePartialOrderAfter(Rule* rule, Atom* afterAtom);
	AnnotationsError checkRulePartialOrderConflicts(Rule* rule);

	bool addGlobalOrderingType(unsigned orderingType);
	bool addGlobalAtomIndexingSetting(Atom* atom, vector<unsigned>& arguments);
	bool addGlobalPartialOrder(const vector<Atom*>& beforeAtoms, const vector<Atom*>& afterAtoms);

	static void freeInstance(){ delete groundingPreferences;}

	static GroundingPreferences* getGroundingPreferences() {
		if(groundingPreferences==0)
			groundingPreferences=new GroundingPreferences();
		return groundingPreferences;
	}
	void print(Rule* rule) const;
private:
	unordered_map<unsigned,unsigned> rulesOrderingTypes;
	unordered_map<unsigned,vector<pair<unsigned,vector<unsigned>>>> rulesAtomsIndexingArguments;
	unordered_map<unsigned,vector<vector<bool>>> rulesPartialOrders;
	vector<vector<unsigned>> ruleBeforeAtoms,ruleAfterAtoms;
	unsigned globalOrderingType;

	void checkIfAtomIsPresentInRule(Rule* rule, Atom* atom, vector<unsigned>& positions);

	GroundingPreferences():globalOrderingType(0){};
	static GroundingPreferences* groundingPreferences;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_GROUNDINGPREFERENCES_H_ */

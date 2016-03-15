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
	AnnotationsError addRulePartialOrderAtom(Rule* rule, Atom* atom);
	AnnotationsError checkRulePartialOrderConflicts(Rule* rule);

	bool addGlobalOrderingType(unsigned orderingType);
	bool addGlobalAtomIndexingSetting(Atom* atom, vector<unsigned>& arguments);
	bool addGlobalPartialOrder(const vector<Atom*>& beforeAtoms, const vector<Atom*>& afterAtoms);

	int getOrderingType(Rule* r) const;
	bool checkPartialOrder(unsigned ruleIndex,unsigned atomPosition,const list<unsigned>& atoms) const;

	static GroundingPreferences* getGroundingPreferences() {
		if(groundingPreferences==0)
			groundingPreferences=new GroundingPreferences();
		return groundingPreferences;
	}

	static void freeInstance(){ delete groundingPreferences;}
	void print(Rule* rule) const;
private:
	unordered_map<unsigned,unsigned> rulesOrderingTypes;
	unordered_map<unsigned,vector<pair<unsigned,vector<unsigned>>>> rulesAtomsIndexingArguments;
	unordered_map<unsigned,vector<vector<bool>>> rulesPartialOrders;
	vector<vector<unsigned>> rulePartialOrderAtoms;
	int globalOrderingType;

	void checkIfAtomIsPresentInRule(Rule* rule, Atom* atom, vector<unsigned>& positions);

	GroundingPreferences():globalOrderingType(-1){};
	static GroundingPreferences* groundingPreferences;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_GROUNDINGPREFERENCES_H_ */

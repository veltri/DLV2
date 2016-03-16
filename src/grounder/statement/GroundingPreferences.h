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
typedef unordered_map<Atom*,vector<unsigned>,HashForTable<Atom>,HashForTable<Atom>> unordered_map_atom_arguments;

class GroundingPreferences {
public:
	bool addRuleOrderingType(Rule* rule, unsigned orderingType);
	AnnotationsError addRuleAtomIndexingSetting(Rule* rule, Atom* atom, vector<unsigned>& arguments);
	AnnotationsError addRulePartialOrderAtom(Rule* rule, Atom* atom);
	void addRulePartialOrder(Rule* rule){
		rulesPartialOrders[rule->getIndex()].emplace_back();
		rulesPartialOrdersAtoms[rule->getIndex()].emplace_back();
	};
	AnnotationsError checkRulePartialOrderConflicts(Rule* rule);
	AnnotationsError applyRulePartialOrder(Rule* rule);

	bool addGlobalOrderingType(unsigned orderingType);
	bool addGlobalAtomIndexingSetting(Atom* atom, vector<unsigned>& arguments);
	bool addGlobalPartialOrder(const vector<Atom*>& beforeAtoms, const vector<Atom*>& afterAtoms);

	int getOrderingType(Rule* r) const;
	bool checkPartialOrder(unsigned ruleIndex,unsigned atomPosition,const list<unsigned>& atoms) const;
	bool checkAtomIndexed(unsigned ruleIndex,Atom* atom,const vector<unsigned>& possibileArgs) const;

	static GroundingPreferences* getGroundingPreferences() {
		if(groundingPreferences==0)
			groundingPreferences=new GroundingPreferences();
		return groundingPreferences;
	}

	static void freeInstance(){	delete groundingPreferences;}
	~GroundingPreferences(){}

	void print(Rule* rule) const;
private:
	unordered_map<unsigned,unsigned> rulesOrderingTypes;
	unordered_map<unsigned,unordered_map_atom_arguments> rulesAtomsIndexed;
	unordered_map<unsigned,vector<vector<bool>>> rulesPartialOrders;
	unordered_map<unsigned,vector<vector<Atom*>>> rulesPartialOrdersAtoms;

	int globalOrderingType;

	void checkIfAtomIsPresentInRule(Rule* rule, Atom* atom, vector<unsigned>& positions);

	GroundingPreferences():globalOrderingType(-1){};
	static GroundingPreferences* groundingPreferences;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_GROUNDINGPREFERENCES_H_ */

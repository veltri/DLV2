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

struct HashAtomPointer{
	inline size_t operator()(Atom* obj) const {
		return size_t(obj);
	}
	inline bool operator()(Atom* obj1, Atom* obj2) const {
		return obj1==obj2;
	}
};

enum AnnotationsError {OK, ATOM_NOT_PRESENT, ARITY_ERROR, CONFLICT_FOUND};
typedef unordered_map<Atom*,vector<unsigned>,HashAtomPointer,HashAtomPointer> unordered_map_pointers_atom_arguments;
typedef unordered_map<Atom*,vector<unsigned>,HashForTable<Atom>,HashForTable<Atom>> unordered_map_atom_arguments;

class GroundingPreferences {
public:
	bool addRuleOrderingType(Rule* rule, unsigned orderingType);
	AnnotationsError addRuleAtomIndexingSetting(Rule* rule, Atom* atom, vector<unsigned>& arguments);
	void addRulePartialOrder(Rule* rule){rulesPartialOrders[rule->getIndex()].emplace_back();rulesPartialOrdersAtoms[rule->getIndex()].emplace_back();}
	AnnotationsError addRulePartialOrderAtom(Rule* rule, Atom* atom);
	AnnotationsError checkRulePartialOrderConflicts(Rule* rule);
	AnnotationsError applyRulePartialOrder(Rule* rule);

	bool addGlobalOrderingType(unsigned orderingType);
	void addGlobalAtomIndexingSetting(Atom* atom, vector<unsigned>& arguments);
	void addGlobalPartialOrder(){ globalPartialOrdersAtoms.emplace_back();}
	void addGlobalPartialOrderAtomStart(Atom* atom);
	void addGlobalPartialOrderAtomEnd(Atom* atom);

	int getOrderingType(Rule* r) ;
	bool checkPartialOrder(Rule* rule,unsigned atomPosition,const list<unsigned>& atoms) ;
	bool checkAtomIndexed(unsigned ruleIndex,Atom* atom,const vector<unsigned>& possibileArgs) ;

	static GroundingPreferences* getGroundingPreferences() {
		if(groundingPreferences==0)
			groundingPreferences=new GroundingPreferences();
		return groundingPreferences;
	}

	~GroundingPreferences(){};
	static void freeInstance(){	delete groundingPreferences;}

	static void checkIfAtomIsPresentInRule(Rule* rule, Atom* atom, vector<unsigned>& positions);

	void print(Rule* rule) const;
private:
	unordered_map<unsigned,unsigned> rulesOrderingTypes;
	unordered_map<unsigned,unordered_map_pointers_atom_arguments> rulesAtomsIndexed;
	unordered_map<unsigned,vector<vector<bool>>> rulesPartialOrders;
	unordered_map<unsigned,vector<vector<Atom*>>> rulesPartialOrdersAtoms;

	int globalOrderingType;
	unordered_map_atom_arguments globalAtomsIndexed;
	vector<list<Atom*>> globalPartialOrdersAtoms;

	bool applayedGlobalAnnotations;


	bool applyGlobalAtomIndexingSetting();
	bool applyGlobalPartialOrder();

	void setGlobalAnnotations();

	GroundingPreferences():globalOrderingType(-1),applayedGlobalAnnotations(false){};
	static GroundingPreferences* groundingPreferences;


};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_STATEMENT_GROUNDINGPREFERENCES_H_ */

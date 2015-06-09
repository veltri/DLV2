/*
 * BackTrackingGrounder.h
 *
 *  Created on: Jan 27, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_
#define SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_

#include "ProgramGrounder.h"

namespace DLV2 {
namespace grounder {

/*
 *  Simple backtrack algorithm to ground a rule
 */
class BackTrackingGrounder : public ProgramGrounder {
public:
	BackTrackingGrounder():ProgramGrounder(),currentRule(0),index_current_atom(0),callFoundAssignment(0),ground_rule(0) {};
	virtual ~BackTrackingGrounder() {
		for(auto atom:templateSetAtom) {if(atom==nullptr)continue;atom->deleteAtoms(); delete atom;}
		if(ground_rule!=0){
			for(auto it=ground_rule->getBeginBody();it!=ground_rule->getEndBody();it++)
				deleteGroundAtom(*it);
		}
		delete ground_rule;
	};

protected:

	virtual bool match();
	virtual bool next();
	virtual bool back();
	virtual void inizialize(Rule* rule);
	virtual bool foundAssignment();

	/// Generate the template atom of current atom (substitute at the current atom the current assignment)
	virtual void generateTemplateAtom();
	/// Remove the variable in the current assignment wich are in bind_variables
	virtual void removeBindValueInAssignment(const set_term& bind_variables);
	/// Call the first match with the current atom
	inline virtual bool firstMatch();
	/// Call the next match with the current atom
	inline virtual bool nextMatch();
	/// Return true if is ground the current atom
	virtual bool isGroundCurrentAtom();

	///Ground an aggregate atom and return true if math false otherwise
	virtual bool groundAggregate();

	/// Print the current assignment
	void printAssignment();

	//Delete the given atom if is a false negative atom or is an aggregate (atoms not present in PredicateExtension)
	void deleteGroundAtom(Atom* atom) {if(atom!=nullptr && ( (atom->isClassicalLiteral() && atom->isNegative() ) || atom->isAggregateAtom())) {delete atom;} }
	//Delete the atom at the given position and substitute it with the given atom at that position
	void substiteInGroundRule(unsigned position, Atom* new_atom) {deleteGroundAtom(ground_rule->getAtomInBody(position)); ground_rule->setAtomInBody(position,new_atom); }

private:
	/// Current assignment for grounding rule
	/// The map of the assignment, map each variables to its assigned value
	map_term_term current_var_assign;
	/// Current id of first match for grounding rule
	/// map of id of the atom and vector of pair : table to search and id of firstMatch (if is NOMATCH call first else next)
	unordered_map<unsigned,vector<pair<unsigned,int>>> current_id_match;
	/// Map of id of the atom and table of current searching (iterator of vector in current_id_match)
	unordered_map<unsigned,unsigned> current_id_match_iterator;

	/// Current variables for each atom for grounding rule
	vector<set_term> current_variables_atoms;
	/// Current rule
	Rule* currentRule;
	/// Current atom iterator for grounding rule
	vector<Atom*>::iterator current_atom_it;
	/// Current atom index for grounding rule
	int index_current_atom;
	//vector of bool if the atom is ground
	vector<bool> is_ground_atom;
	bool callFoundAssignment;
	//Partially ground rule built
	Rule* ground_rule;
	/// Set of current templateAtom
	vector<Atom*> templateSetAtom;

	///Find the bind variable on rule
	void findBindVariablesRule();

	//find the table to search for each atom in the body
	void findSearchTable();
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_ */

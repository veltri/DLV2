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
	BackTrackingGrounder():ProgramGrounder(),currentRule(0),index_current_atom(0),templateAtom(nullptr),start(true),lastMatch(false){};
	virtual ~BackTrackingGrounder() { delete templateAtom; };


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
	virtual bool firstMatch();
	/// Call the next match with the current atom
	virtual bool nextMatch();
	/// Return true if is ground the current atom
	virtual bool isGroundCurrentAtom();

	/// Print the current assignment
	void printAssignment();

protected:
	/// Current assignment for grounding rule
	/// The map of the assignment, map each variables to its assigned value
	map_term_term current_var_assign;
	/// Current id of first match for grounding rule
	/// map of id of the atom and vector of pair : table to search and id of firstMatch (if is NOMATCH call first else next)
	unordered_map<unsigned,vector<pair<unsigned,int>>> current_id_match;
	/// Current variables for each atom for grounding rule
	vector<set_term> current_variables_atoms;
	/// Current rule
	Rule* currentRule;
	/// Current atom iterator for grounding rule
	vector<Atom*>::iterator current_atom_it;
	/// Current atom index for grounding rule
	unsigned index_current_atom;
	//vector index atom and if is undefined
	vector<bool> atom_undef_inbody;

	/// Current templateAtom
	Atom * templateAtom;
	/// start is false if the grounding process not start, otherwise true
	bool start;
	/// Is true if is calling nextMatch on ground atom at the end of rule
	bool lastMatch;

	///Find the bind variable on rule
	void findBindVariablesRule();
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_ */

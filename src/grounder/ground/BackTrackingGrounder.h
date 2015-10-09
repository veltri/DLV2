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

/// If the firstMatch on table has not been called
#define NO_MATCH -1
/*
 *  Simple backtrack algorithm to ground a rule
 */
class BackTrackingGrounder : public ProgramGrounder {
public:
	BackTrackingGrounder():ProgramGrounder(),currentRule(0),index_current_atom(0),callFoundAssignment(0),ground_rule(0) {};
	virtual ~BackTrackingGrounder() {
		for(auto atom:templateSetAtom) {if(atom!=nullptr){atom->deleteAtoms(); delete atom;}}
		if(ground_rule!=0)
			ground_rule->deleteGroundRule();
	};

protected:

	virtual bool match();
	virtual bool next();
	virtual bool back();
	virtual void inizialize(Rule* rule);
	virtual bool foundAssignment();

	/// Generate the template atom of current atom (substitute at the current atom the current assignment)
	virtual void generateTemplateAtom();
	/// Remove the variable in the current assignment which are in bind_variables
	virtual void removeBindValueInAssignment(const set_term& bind_variables);
	/// Call the first match with the current atom
	virtual bool firstMatch();
	/// Call the next match with the current atom
	virtual bool nextMatch();
	/// Return true if is ground the current atom
	virtual bool isGroundCurrentAtom();

	///Ground an aggregate atom and return true if math false otherwise
	virtual bool groundAggregate();

	///Ground a choice in the head of the rule
	virtual void groundChoice(bool& find_new_true_atom,bool& ground_new_atom);

	/// Print the current assignment
	void printAssignment();

	//Delete the atom at the given position and substitute it with the given atom at that position
	void substiteInGroundRule(unsigned position, Atom* new_atom) {
		Atom* atom=(ground_rule->getAtomInBody(position));
		if(atom!=nullptr && ((atom->isClassicalLiteral() && atom->isNegative()) || atom->isAggregateAtom()))
			delete atom;
		ground_rule->setAtomInBody(position,new_atom);
	}

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

	///Determine the table to search for each atom in the body
	void findSearchTable();

	///The size is >0 if the current ground rule has at least a negative atom that an potentially be an undef atom (an atom without a valid index)
	vector<unsigned> indicesPossibleUndef;

	/// Is 1 if forward, 0 if backward
	bool direction;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_ */

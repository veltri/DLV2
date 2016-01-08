/*
 * BackTrackingGrounder.h
 *
 *  Created on: Jan 27, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_
#define SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_

#include "ProgramGrounder.h"
#include "../table/AdvancedArray.h"

namespace DLV2 {
namespace grounder {

/// If the firstMatch on table has not been called
#define NO_MATCH 0
#define MATCH 1

/*
 *  Simple backtrack algorithm to ground a rule
*/
class BackTrackingGrounder : public ProgramGrounder {
public:
	BackTrackingGrounder():ProgramGrounder(),currentRule(0),index_current_atom(0),ground_rule(0),callFoundAssignment(0),direction(1){};
	virtual ~BackTrackingGrounder() {
		for(auto atom:templateSetAtom) {if(atom!=nullptr){atom->deleteAtoms(); delete atom;}}
		for(auto atom:groundTemplateAtomHead) delete atom;
		if(ground_rule!=0)
			ground_rule->deleteGroundRule();

	};

	bool findGroundMatch();

protected:
	virtual bool match();
	virtual bool next();
	virtual bool back();
	virtual void inizialize(Rule* rule);
	virtual bool foundAssignment();

	/// Call the first match with the current atom
	virtual bool firstMatch();

	/// Call the next match with the current atom
	virtual bool nextMatch();

	///Ground an aggregate atom and return true if math false otherwise
	virtual bool groundAggregate();

	///Ground a choice in the head of the rule
	virtual void groundChoice(bool& find_new_true_atom,bool& ground_new_atom);

	///Find the bind variable on rule
	void findBindVariablesRule();

	///Determine the table to search for each atom in the body
	void findSearchTables();

	/// Remove the variable in the current assignment which are in bind_variables
	virtual void removeBindValueFromAssignment(const vector<index_object>& bind_variables);

	/// Generate the template atom of current atom (substitute at the current atom the current assignment)
	inline void generateTemplateAtom(){
		currentRule->getAtomInBody(index_current_atom)->ground(current_assignment,templateSetAtom[index_current_atom]);
	}

	//Delete the atom at the given position and substitute it with the given atom at that position
	void substiteInGroundRule(unsigned position, Atom* new_atom) {
		Atom* atom=(ground_rule->getAtomInBody(position));
		if(atom!=nullptr && ((atom->isClassicalLiteral() && atom->isNegative()) || atom->isAggregateAtom()))
			delete atom;
		ground_rule->setAtomInBody(position,new_atom);
	}

	virtual bool isCartesianProductRule(Rule *r);
	virtual void groundCartesian(Rule *r);

	///Find the builtin that can be evaluated while match an atom
	virtual void findBuiltinFastEvaluated();

	/// Current rule to be grounded
	Rule* currentRule;
	/// Position of the atom currently under evaluation
	int index_current_atom;
	/// Ground rule built by the grounding process
	Rule* ground_rule;

	/// Is 1 if a valid assignment has been found
	bool callFoundAssignment;
	/// The direction of the grounding process: 1 if forward, 0 if backward
	bool direction;

	/// Current assignment produced
	var_assignment current_assignment;

	/// Vector of current template atoms: partially ground atoms, in which bound variables have been substituted according to the current assignment
	vector<Atom*> templateSetAtom;

	/// Current id of first match for grounding rule
	/// Vector of the atom and vector of pair : table to search and id of firstMatch (if is NOMATCH call first else next)
	vector<vector<pair<unsigned,bool>>> current_id_match;
	/// Map of id of the atom and table of current searching (iterator of vector in current_id_match)
	vector<unsigned> current_id_match_iterator;

	/// Bind variables for each atom in the current rule
	vector<vector<index_object>> atoms_bind_variables;

	/// Positions of bound atoms
	vector<bool> is_bound_atom;

	/// The size is >0 if the current ground rule has at least a negative atom that an potentially be an undef atom (an atom without a valid index)
	vector<unsigned> atomsPossibleUndef;

	///Map each variable to its binder atom
	AdvancedArray<unsigned,ARRAY_SIZE> variablesBinder;

	///Vector of the size of the body. If the position of this vector is true then the builtin
	/// in the rule with this position is already evaluated
	vector<bool> builtAlreadyEvaluated;

	vector<vector<Atom*>> matchBuiltin;

	///This vector contains a kind of template atoms for head atoms
	vector<Atom*> groundTemplateAtomHead;

#ifdef TRACE_ON
	/// Print the current assignment
	void printAssignment();
#endif

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_ */

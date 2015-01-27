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

class BackTrackingGrounder : ProgramGrounder {
public:
	BackTrackingGrounder():ProgramGrounder(),currentRule(0), current_atom(0),index_current_atom(0){};
	virtual ~BackTrackingGrounder(){};

	virtual bool match();
	virtual bool next();
	virtual void foundAssignment();
	virtual bool back();
	virtual void inizialize(Rule* rule);



protected:
	/// Current assignment for grounding rule
	/// The map of the assignment, map each variables to its assigned value
	map_term_term current_var_assign;
	/// Current id of first match for grounding rule
	unordered_map<unsigned,unsigned> current_id_match;
	/// Current variables for each atom for grounding rule
	vector<set_term> current_variables_atoms;
	/// Current rule
	Rule* currentRule;
	/// Current atom iterator for grounding rule
	vector<Atom*>::iterator current_atom_it;
	/// Current atom index for grounding rule
	unsigned int index_current_atom;

	void findBindVariablesRule();
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_BACKTRACKINGGROUNDER_H_ */

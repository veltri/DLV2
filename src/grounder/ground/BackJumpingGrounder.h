/*
 * BackJumpingGrounder.h
 *
 *  Created on: Oct 7, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_GROUND_BACKJUMPINGGROUNDER_H_
#define SRC_GROUNDER_GROUND_BACKJUMPINGGROUNDER_H_

#include "BackTrackingGrounder.h"

namespace DLV2 {
namespace grounder {

//using pair_unsigned_iterator=pair<unsigned,vector<Atom*>::iterator>;

enum Status {SUCCESSFULL,FIRST_MATCH,NEXT_MATCH};

class BackJumpingGrounder: public BackTrackingGrounder {

public:
	BackJumpingGrounder():BackTrackingGrounder(),closestSuccessfulBinder_index(-1),current_status(SUCCESSFULL),historyBackFromSolutionFound(-1){};
	virtual ~BackJumpingGrounder(){};

protected:

	virtual bool match();
	virtual bool back();
	virtual void inizialize(Rule* rule);
	virtual bool foundAssignment();

	/// Call the first match with the current atom
	virtual bool firstMatch();
	/// Call the next match with the current atom
	virtual bool nextMatch();

	/// Given a literal and a set of variables
	/// computes the closest binder to that literal for that variables
	void closestBinder( int literal_pos, const set_term& variables, int& positionCB, bool includeCurrentLiteral);

	/// Given a literal computes the closest binder
	/// to that literal for the variables in the failure set
	void closestBinder( int literal_pos, int& positionCB);

	/// A total substitution is found, so we can jump
	/// to the closest literal binding a variable in head
	void backFromSolutionFound();

	/// A fail is found after a first match on a literal L, so we can jump
	/// to the closest literal binding a variable of L
	/// (respecting the barrier imposed by the CSB)
	void backFromFirstMatch();

	/// A fail is found after a next match on a literal L, so we can jump
	/// to the closest literal binding a variable of the dependency set of L
	/// (respecting the barrier imposed by the CSB)
	void backFromNextMatch();

private:
	/// The position of the current CSB
	int closestSuccessfulBinder_index;
	/// The current status of the procedure (can be SUCCESSFUL, FIRST_MATCH, NEXT_MATCH)
	Status current_status;
	/// The set of variables appearing in the head of the current rule
	set_term outputVariables;
	/// Map of variables bool. If the boolean is true the variable is in the failure set
	vector<bool> failureMap;
	///Map each variable to its binder atom
	AdvancedArray<unsigned,ARRAY_SIZE> variablesBinder;

	int historyBackFromSolutionFound;

	AdvancedArray<int,ARRAY_SIZE> historyBackOutputVars;

	AdvancedArray<int,ARRAY_SIZE> historyBackFromFirst;

	vector<set_term> atomsVariables;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_BACKJUMPINGGROUNDER_H_ */

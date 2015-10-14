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

using pair_unsigned_iterator=pair<unsigned,vector<Atom*>::iterator>;

enum Status {SUCCESSFULL,FIRST_MATCH,NEXT_MATCH};

class BackJumpingGrounder: public BackTrackingGrounder {

public:
	BackJumpingGrounder():BackTrackingGrounder(),closestSuccessfulBinder_index(0),current_status(SUCCESSFULL){};
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
	void closestBinder(vector<Atom*>::iterator literal_it, int literal_pos, const set_term& variables, int& positionCB,vector<Atom*>::iterator& iteratorCB, bool includeCurrentLiteral);

	/// Given a literal computes the closest binder
	/// to that literal for the variables in the failure set
	void closestBinder(vector<Atom*>::iterator literal_it, int literal_pos, int& positionCB, vector<Atom*>::iterator& iteratorCB);

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
	/// An iterator pointing to the current CSB
	vector<Atom*>::iterator closestSuccessfulBinder_it;
	/// The position of the current CSB
	int closestSuccessfulBinder_index;
	/// The current status of the procedure (can be SUCCESSFUL, FIRST_MATCH, NEXT_MATCH)
	Status current_status;
	/// The set of variables appearing in the head of the current rule
	set_term outputVariables;
	/// Map of variables bool. If the boolean is true the variable is in the failure set
	map_term<bool> failureMap;

	pair<int,vector<Atom*>::iterator> historyBackFromSolutionFound;

	unordered_map<unsigned,pair_unsigned_iterator> historyBackOutputVars;

	unordered_map<unsigned,pair_unsigned_iterator> historyBackFromFirst;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_GROUND_BACKJUMPINGGROUNDER_H_ */

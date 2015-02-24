/*
 * WeightConstraint.h
 *
 *  Created on: Feb 18, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_ATOM_WEIGHTCONSTRAINT_H_
#define SRC_GROUNDER_ATOM_WEIGHTCONSTRAINT_H_

#include "Atom.h"

namespace DLV2 {
namespace grounder {

class WeightConstraint: public Atom{
public:
	WeightConstraint();
	virtual ~WeightConstraint();


	Atom* clone() = 0;

	///Equal-to operator for atoms
	bool operator==(const Atom& a)=0;

	///Return the term of variable present in the Atom
	set_term getVariable(){};

	/// Return true if is ground, each term is constant term
	bool isGround(){}

	/// Return true if contains a range term
	bool containsRangeTerms(){
		return false;
	};

	/// Return true if contains an anonymous term
	bool containsAnonymous(){
		return false;
	};


	void setLowerGueard(Term* lower){};


	void expand(){};


	/// Substitute the terms in the atom with the given terms and return the atom with terms sobstitute
	/// @param substritutionTerm map of index_object. The first index is the ID of term to substitute and second the value
	virtual Atom* substitute(map_term_term& substitutionTerm){};
	/// Similiar to substitute(map_term_term& substitutionTerm) but not create new atom
	virtual void substitute(map_term_term& substitutionTerm,Atom* templateAtom){};

	///Printer method
	virtual void print() = 0;

private:
	Term* guard;
	vector<pair<Atom*,Term*> > weightAtoms;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_ATOM_WEIGHTCONSTRAINT_H_ */

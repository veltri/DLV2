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
	WeightConstraint() : Atom() {};
	WeightConstraint(vector<pair<Atom*,Term*> > weightAtoms ) : Atom(), weightAtoms(weightAtoms) {};
	WeightConstraint(vector<Term*> terms, vector<pair<Atom*,Term*> > weightAtoms ) : Atom(terms), weightAtoms(weightAtoms) {};
	WeightConstraint(Term* term, vector<pair<Atom*,Term*> > weightAtoms ) : Atom(), weightAtoms(weightAtoms) {terms.push_back(term);};


	virtual ~WeightConstraint() {};

	Term* getLowerGuard() const {return terms[0];}
	void setLowerGuard(Term* lower) {if(terms.empty()) terms.push_back(lower);}

	unsigned getWeightAtomsSize() const {return this->weightAtoms.size();};
	pair<Atom*,Term*> getWeightAtom(unsigned i) const {return weightAtoms[i];};
	void setWeightAtom(unsigned i, const pair<Atom*,Term*>& pair) {weightAtoms[i]=pair;};

	Atom* clone();

	size_t hash();

	///Equal-to operator for atoms
	bool operator==(const Atom& a);

	///Return the term of variable present in the Atom
	set_term getVariable();

	/// Return true if is ground, each term is constant term
	bool isGround();

	/// Return true if contains an anonymous term
	bool containsAnonymous();
	bool containsRangeTerms();

	Atom* expand();

	/// Substitute the terms in the atom with the given terms and return the atom with terms substitute
	/// @param substritutionTerm map of index_object. The first index is the ID of term to substitute and second the value
	Atom* substitute(map_term_term& substitutionTerm);
	/// Similiar to substitute(map_term_term& substitutionTerm) but not create new atom
	void substitute(map_term_term& substitutionTerm,Atom* templateAtom);

	///Printer method
	virtual void print();

private:
	/// A vector containing the atoms and the weight associated to them
	vector<pair<Atom*,Term*> > weightAtoms;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_ATOM_WEIGHTCONSTRAINT_H_ */

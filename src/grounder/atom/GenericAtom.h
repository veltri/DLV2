/*
 * GenericAtom2.h
 *
 *  Created on: Jan 23, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_ATOM_GENERICATOM_H_
#define SRC_GROUNDER_ATOM_GENERICATOM_H_

#include "Atom.h"
using namespace std;

namespace DLV2 {
namespace grounder {

class GenericAtom: public Atom {
public:
	GenericAtom() : Atom(), fact(true){};
	GenericAtom(vector<Term*>& terms, bool isFact): Atom(terms), fact(isFact){};
	GenericAtom(Atom* atom, bool fact): Atom(atom->getTerms()), fact(fact) { };

	bool operator==(const Atom& genericAtom) {
		if(terms.size()!=genericAtom.getTermsSize())
			return false;
		for(unsigned i=0;i<getTermsSize();i++)
			if(terms[i]->getIndex()!=genericAtom.getTerm(i)->getIndex())
				return false;
		return true;
	}

	size_t hash(){
		return HashVecInt::getHashVecIntFromConfig()->computeHashTerm(terms);
	}

	bool isFact() const { return fact; }
	void setFact(bool isFact) { this->fact = isFact; }

	void print() { };

private:
	bool fact;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_ATOM_GENERICATOM_H_ */

/*
 * AggregateElement.h
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#ifndef AGGREGATEELEMENT_H_
#define AGGREGATEELEMENT_H_


#include <vector>
#include "Atom.h"
#include "../../util/Constants.h"
#include "../term/Term.h"


using namespace std;

namespace DLV2{

namespace grounder{

class Atom;

/// This class represents an aggregate element
class AggregateElement {

	public:
		//Default constructor
		AggregateElement() {}

		AggregateElement* clone();

		///Getter for terms
		const vector<Term*>& getTerms() const {return terms;}
		///Setter for terms
		void setTerms(const vector<Term*>& terms) {this->terms = terms;}
		///Get the i-th term
		Term* getTerm(unsigned i) const {return terms[i];}
		///Getter for naf literals
		const vector<Atom*>& getNafLiterals() const {return nafLiterals;}
		///Getter for naf literal
		Atom* getNafLiteral(unsigned i) const {return nafLiterals[i];}
		///Setter for naf literals
		void setNafLiterals(const vector<Atom*>& nafLiterals) {this->nafLiterals = nafLiterals;}
		///Add term in terms
		void addTerm(Term* term){terms.push_back(term);}
		///Add Naf literal in nafLiterals
		void addNafLiterals(Atom* atom){nafLiterals.push_back(atom);}
		/// Remove all Naf literals
		void clearNafLiterals();
		/// Remove all terms
		void clearTerms(){terms.clear();}

		void deleteAtoms();

		//Destructor
		~AggregateElement() {};

	private:
		///Vector of terms
		vector<Term*> terms;
		///Vector of naf literals
		// Notice that the atoms must be naf literals, so either classical literals or built-in atoms
		vector<Atom*> nafLiterals;
};

};

};

#endif /* AGGREGATEELEMENT_H_ */

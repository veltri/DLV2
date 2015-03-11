/*
 * AggregateAtom.h
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#ifndef AGGREGATEATOM_H_
#define AGGREGATEATOM_H_

#include <vector>
#include "Atom.h"

using namespace std;

namespace DLV2{

namespace grounder{

/**
 * This class implements an aggregate atom extending atom
 */

class AggregateAtom: public Atom {
public:

	///Default constructor
	AggregateAtom(): firstBinop(Binop::NONE_OP), secondBinop(Binop::NONE_OP), aggregateFunction(AggregateFunction::NONE), negative(false) {lowerGueard=nullptr;upperGuard=nullptr;};

	/** Constructor
		 * @param f set the first term of comparison
		 * @param fB set the first binary operation
		 * @param s set the second term of comparison
		 * @param sB set the second binary operation
		 * @param aF set the aggregate function type
		 * @param aE set the vector of aggregate elements
		 * @param negative set whether the atom is negated with negation as failure
		 */
	AggregateAtom(Term* f, Binop fB,Term* s, Binop sB, AggregateFunction aF, vector<AggregateElement*> aE, bool n):
		firstBinop(fB), secondBinop(sB), aggregateFunction(aF), aggregateElements(move(aE)), negative(n) {lowerGueard=f;upperGuard=s;};

	Atom* clone() {
		Atom* atom = new AggregateAtom(lowerGueard,firstBinop,upperGuard,secondBinop,aggregateFunction,aggregateElements,negative);
		atom->setTerms(this->terms);
		return atom;
	};

	///This method compute the resulting hash a classical atom using its terms
	size_t hash() ;
	///This method compute the resulting hash for an aggregateElement TODO
	size_t getHash() const {return 0;};

	bool operator==(const Atom& a);

	///Getter method for the aggregate elements
	vector<AggregateElement*> getAggregateElements() {return aggregateElements;};
	///Getter method for the i-th aggregate element
	AggregateElement* getAggregateElement(unsigned i) {return aggregateElements[i];}
	///Setter method for the aggregate elements
	void setAggregateElements(const vector<AggregateElement*>& aggregateElements) {this->aggregateElements = aggregateElements;};
	///Setter method for the i-th aggregate element
	void setAggregateElement(unsigned i, const vector<Atom*>& nafLits, const vector<Term*>& terms) {
		aggregateElements[i]->clearNafLiterals();
		aggregateElements[i]->setNafLiterals(nafLits);
		aggregateElements[i]->clearTerms();
		aggregateElements[i]->setTerms(terms);
	}
	///Setter method for the i-th aggregate element
	void setAggregateElement(unsigned i, const vector<Atom*>& nafLits) {
		aggregateElements[i]->clearNafLiterals();
		aggregateElements[i]->setNafLiterals(nafLits);
	}
	///Getter method for the aggregate elements size
	virtual unsigned getAggregateElementsSize() {return aggregateElements.size();};
	/// Add aggregate element
	void addAggregateElement(AggregateElement *element){aggregateElements.push_back(element);};

	void setLowerGuard(Term* lower){lowerGueard=lower;};
	void setUpperGuard(Term* upper){upperGuard=upper;};

	Term* getLowerGuard(){return lowerGueard;};
	Term* getUpperGuard(){return upperGuard;};

	///Getter method for the aggregate function
	AggregateFunction getAggregateFunction() const {return aggregateFunction;};
	///Setter method for the aggregate function
	void setAggregateFunction(AggregateFunction aggregateFunction) {this->aggregateFunction = aggregateFunction;};
	///Getter method for the first binary operation
	Binop getFirstBinop() const {return firstBinop;};
	///Setter method for the first binary operation
	void setFirstBinop(Binop firstBinop) {this->firstBinop = firstBinop;};
	///Getter method for the second binary operation
	Binop getSecondBinop() const {return secondBinop;};
	///Setter method for the second binary operation
	void setSecondBinop(Binop secondBinop) {this->secondBinop = secondBinop;};
	///Returns true if the atom is negated with negation as failure
	bool isNegative() const {return negative;};
	///Set whether the atom is negated with negation as failure
	void setNegative(bool negative) {this->negative = negative;};

	/// Substitute the term with constant term and calculate the arithmetic terms
	/// The subclasses have to implement the substitute method for create correct type class of Atom
	/// Similiar to ground(map_term_term& substritutionTerm) but not create new atom
	virtual void ground(map_term_term& substritutionTerm,Atom*& templateAtom);

	///Printer method
	void print();

	~AggregateAtom() {for(auto& aggregateElem:aggregateElements) for(auto naf:aggregateElem->getNafLiterals()) delete naf;};

private:
	///First binary operation
	Binop firstBinop;
	///Second binary operation
	Binop secondBinop;
	///Aggregate function @see AggregateFunction
	AggregateFunction aggregateFunction;
	///Vector of the aggregate elements
	vector<AggregateElement*> aggregateElements;
	///Negated with naf
	bool negative;

	Term* lowerGueard;
	Term* upperGuard;

	/* For the vector of terms, it contains the first and the second term of comparison.
	 * Notice that the vector contains the terms in the same order as they appear: the first term in position 0, the second in position 1.
	 */
};

};

};

#endif /* AGGREGATEATOM_H_ */

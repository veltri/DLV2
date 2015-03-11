/*
 * Atom.h
 *
 *  Created on: 07/mar/2014
 *      Author: Jessica
 *
 */

#ifndef ATOM_H_
#define ATOM_H_



#include <vector>
#include <string>
#include <unordered_map>
#include "AggregateElement.h"
#include "ChoiceElement.h"
#include "../table/TermTable.h"
#include "Predicate.h"



using namespace std;

namespace DLV2{

namespace grounder{

class AggregateElement;
class ChoiceElement;

/// Aggregate Function Types
enum AggregateFunction {NONE=0,COUNT,MAX,MIN,SUM};

/// Binary Operation Types
enum Binop {NONE_OP=0,EQUAL,UNEQUAL,LESS,GREATER,LESS_OR_EQ,GREATER_OR_EQ};

/**      The hierarchy is this:
*      									Atom
*      	|					|				|					|
*   	ClassicalLiteral	BuiltInAtom		AggregateAtom		Choice
*
*	Atom acts like an interface for its subclasses.
*/

class Atom: public Hashable {
public:

	///Default constructor
	Atom() {};

	/** Constructor
	 * @param termsVec set the terms vector
	 */
	Atom(vector<Term*>& termsVec) : terms(move(termsVec)) {};

	/** Constructor
	 * @param negative set whether the atom is negated with negation as failure
	 */
	Atom(bool negative) {this->setNegative(negative);};

	virtual Atom* clone() = 0;

	///Equal-to operator for atoms
	virtual bool operator==(const Atom& a)=0;

	///Return the term of variable present in the Atom
	virtual set_term getVariable();

	/// Return true if is ground, each term is constant term
	virtual bool isGround(){
		for(auto term:terms)
			if(!term->isGround())return false;
		return true;
	}

	/// Return true if contains a range term
	virtual bool containsRangeTerms(){
		for(auto term:terms)
			if(term->isRange())return true;
		return false;
	};

	/// Return true if contains an anonymus term
	virtual bool containsAnonymous(){
		for(auto term:terms)
			if(term->contain(TermType::ANONYMOUS))return true;
		return false;
	};

	/******** Methods useful for ClassicalLiteral ********/
	/**
	 * Getter method for the predicate
	 */
	virtual Predicate* getPredicate() const {return nullptr;};
	///Setter method for the predicate
	virtual void setPredicate(Predicate* predicate) {};
	///This method returns the size of the terms' vector
	const unsigned int getTermsSize() const {return terms.size();};
	/**
	 * This method returns the term in the position i
	 */
	vector<Term*>& getTerms(){return terms;};
	Term* getTerm(unsigned int i) const {return terms[i];};
	///Push the term in terms at position i
	void setTerm(unsigned int i,Term* term) {terms[i]=term;};
	/// TODO
	void setTerms(const vector<Term*>& terms) {this->terms=terms;};
	///Returns true if the atom is negated with true negation
	virtual bool isHasMinus() const {return 0;};
	///Set whether the atom is negated with true negation
	virtual void setHasMinus(bool hasMinus) {};
	///Returns true if the atom is negated with negation as failure
	virtual bool isNegative() const {return 0;};
	///Set whether the atom is negated with negation as failure
	virtual void setNegative(bool negative) {};
	/*****************************************************/

	/******** Methods useful for BuiltInAtom ********/
	///Getter method for the binary operation
	virtual Binop getBinop() const {return Binop::NONE_OP;};
	///Setter method for the binary operation
	virtual void setBinop(Binop binop) {};
	/// Return true if is BuiltInAtom
	virtual bool isBuiltIn(){return false;};
	///This method evaluate the truth value of the built-in atom, if there is bind variable
	/// and equal then assign that value for the bind variable
	virtual bool evaluate(map_term_term& substitutionTerm){return false;};
	/*****************************************************/

	/******** Methods useful for AggregateAtom ********/
	///Getter method for the aggregate elements
	virtual vector<AggregateElement*> getAggregateElements() {return vector<AggregateElement*>(0);};
	///Getter method for the i-th aggregate element
	virtual AggregateElement* getAggregateElement(unsigned i) {return 0;}
	///Setter method for the aggregate elements
	virtual void setAggregateElements(const vector<AggregateElement*>& aggregateElements) {};
	///Getter method for the aggregate elements size
	virtual unsigned getAggregateElementsSize() {return 0;};
	///Setter method for the i-th aggregate element
	virtual void setAggregateElement(unsigned i, const vector<Atom*>& nafLits, const vector<Term*>& terms) {}
	///Setter method for the i-th aggregate element
	virtual void setAggregateElement(unsigned i, const vector<Atom*>& nafLits) {}
	///Getter method for the aggregate function
	virtual AggregateFunction getAggregateFunction() const {return AggregateFunction::NONE;};
	///Set lower guard of aggregate
	virtual void setLowerGuard(Term* lower){};
	///Set upper guard of aggregate
	virtual void setUpperGuard(Term* upper){};
	///Get lower guard of aggregate
	virtual Term* getLowerGuard(){return nullptr;};
	///Get upper guard of aggregate
	virtual Term* getUpperGuard(){return nullptr;};
	///Setter method for the aggregate function
	virtual void setAggregateFunction(AggregateFunction aggregateFunction) {};
	///Getter method for the first binary operation
	virtual Binop getFirstBinop() const {return Binop::NONE_OP;};
	///Setter method for the first binary operation
	virtual void setFirstBinop(Binop firstBinop) {};
	///Getter method for the second binary operation
	virtual Binop getSecondBinop() const {return Binop::NONE_OP;};
	///Setter method for the second binary operation
	virtual void setSecondBinop(Binop secondBinop) {};
	/// Add aggregate Element
	virtual void addAggregateElement(AggregateElement* element){};
	/*****************************************************/

	/******** Methods useful for Choice ********/
	///Getter method for the choice elements
	virtual const vector<ChoiceElement> getChoiceElements() const {return vector<ChoiceElement>(0);};
	///Setter method for the choice elements
	virtual void setChoiceElements(const vector<vector<index_object> >& choiceElements) {};
	/*****************************************************/

	/******** Methods useful for Generic Atom ********/
	virtual bool isFact() const { return false; }
	virtual void setFact(bool isFact) {  }
	/*****************************************************/


	/// Substitute the terms in the atom with the given terms and return the atom with terms sobstitute
	/// @param substritutionTerm map of index_object. The first index is the ID of term to substitute and second the value
	/// Similiar to substitute(map_term_term& substitutionTerm) but not create new atom
	virtual void substitute(map_term_term& substitutionTerm,Atom*& templateAtom){};


	/// Substitute the term with constant term and calculate the arithmetic terms
	/// The subclasses have to implement the substitute method for create correct type class of Atom
	/// Similiar to ground(map_term_term& substritutionTerm) but not create new atom
	virtual void ground(map_term_term& substritutionTerm,Atom*& templateAtom);
	///Printer method
	virtual void print() = 0;
	///Destructor
	virtual ~Atom() {};

	static void getVariables(Atom* atom,set_term& variables);
	static void getVariables(const vector<Atom*>& atoms,set_term& variables);

protected:
	vector<Term*> terms;
};

};

};

#endif /* ATOM_H_ */


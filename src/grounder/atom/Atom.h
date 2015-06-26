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

enum ResultEvaluation{
	SATISFY=0, UNSATISFY, UNDEF
};


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
	/// Not check the predicate of the atoms
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
	virtual set_predicate getPredicates() const {return set_predicate();};
	virtual unordered_set<index_object> getPredicatesIndices() const {return unordered_set<index_object>();};

	///Return true if is a Classical Literal
	virtual bool isClassicalLiteral(){return false;};

	///Setter method for the predicate
	virtual void setPredicate(Predicate* predicate) {};
	///This method returns the size of the terms' vector
	const unsigned int getTermsSize() const {return terms.size();};
	/**
	 * This method returns the term in the position i
	 */
	vector<Term*>& getTerms(){return terms;};
	Term* getTerm(unsigned int i) const {return terms[i];};
	Term* operator[](unsigned i) const {return terms[i];};

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
	///Return true if the built in assign value in term, else compare the variable like ==
	virtual bool isAssignment(){return false;};
	virtual void setAssignment(bool assigment){};
	/*****************************************************/

	/******** Methods useful for AggregateAtom ********/
	///Getter method for the aggregate elements
	virtual const vector<AggregateElement*>& getAggregateElements() const {return vector<AggregateElement*>(0);};
	///Getter method for the i-th aggregate element
	virtual AggregateElement* getAggregateElement(unsigned i) {return 0;}
	///Setter method for the aggregate elements
	virtual void setAggregateElements(const vector<AggregateElement*>& aggregateElements) {};
	///Getter method for the aggregate elements size
	virtual unsigned getAggregateElementsSize() {return 0;};
	/// Return true if is an aggregate atom
	virtual bool isAggregateAtom(){return false;}
	///Setter method for the i-th aggregate element
	virtual void setAggregateElement(unsigned i, const vector<Atom*>& nafLits, const vector<Term*>& terms) {}
	///Setter method for the i-th aggregate element
	virtual void setAggregateElement(unsigned i, const vector<Atom*>& nafLits) {}
	///Getter method for the aggregate function
	virtual AggregateFunction getAggregateFunction() const {return AggregateFunction::NONE;};
	///Set first guard of aggregate
	virtual void setFirstGuard(Term* lower){};
	///Set second guard of aggregate
	virtual void setSecondGuard(Term* upper){};
	///Get lower guard of aggregate
	virtual Term* getFirstGuard(){return nullptr;};
	///Get upper guard of aggregate
	virtual Term* getSecondGuard(){return nullptr;};
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

	virtual ResultEvaluation partialEvaluate(){return ResultEvaluation::SATISFY;};

	/// Return the result of the evaluation of the aggregate
	virtual ResultEvaluation finalEvaluate(){return ResultEvaluation::SATISFY;};

	///Return the value of evaluation
	virtual Term* getPartialEvaluation(){return 0;};

	virtual Term* getUndefEvaluation(){return 0;};

	//Return the variable in the guard of an aggregate
	virtual set_term getGuardVariable(){return set_term();};

	///return true if one guard is an equal
	virtual bool isAnAssigment(){return false;};

	virtual Term* generateNextCombination(bool& finish) {return 0;};

	virtual bool isUndefAssignment() {return false;}

	//Copy the guard of the atom
	virtual void copyGuard(Atom *atom){};
	/*****************************************************/

	/******** Methods useful for Choice ********/
	///Getter method for the choice elements
	virtual const vector<ChoiceElement*>& getChoiceElements() const {return vector<ChoiceElement*>(0);};
	///Setter method for the choice elements
	virtual void setChoiceElements(const vector<ChoiceElement*>& choiceElements) {};
	///Returns the choice elements size
	virtual unsigned getChoiceElementsSize() const {return 0;}
	///Returns the i-th choice element
	virtual ChoiceElement* getChoiceElement(unsigned i) const {return 0;}
	///Return true if is a choice atom
	virtual bool isChoice(){return false;}
	///Add a choice element
	virtual void addChoiceElement(ChoiceElement* choiceElement){}
	virtual void addSingleChoiceElement(Atom* atom){}
	///Return true if the choice atom have the default guard ({}>=0)
	virtual bool isDefaultGuard(){return false;}
	/*****************************************************/

	/******** Methods useful for Generic Atom ********/
	virtual bool isFact() const { return false; }
	virtual void setFact(bool isFact) {  }
	/*****************************************************/

	static string getBinopToStrng(Binop binop);


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

	virtual void deleteAtoms() {};

	///Destructor
	virtual ~Atom() {};

	static void getVariables(Atom* atom,set_term& variables);
	static void getVariables(const vector<Atom*>& atoms,set_term& variables);

protected:
	vector<Term*> terms;
};

using AtomTable = hashSet<Atom> ;

};

};

#endif /* ATOM_H_ */


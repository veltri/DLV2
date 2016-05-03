/*
 * BuiltInAtom.h
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#ifndef BUILTINATOM_H_
#define BUILTINATOM_H_

#include "Atom.h"

using namespace std;

namespace DLV2{

namespace grounder{

/**
 * This class implements a built-in atom extending atom
 */

class BuiltInAtom: public Atom {
public:

	///Default constructor
	BuiltInAtom(): binop(Binop::NONE_OP), negative(false), assignment(false) {}

	/** Constructor
	 * @param binop set the binary operation @see Binop
	 * @param negative set whether the atom is negated with negation as failure
	 * @param firstTerm set the first term
	 * @param secondTerm set the second term
	 * Notice that the vector of terms contains the terms in the same order as they appear: the first term in position 0, the second in position 1.
	 */
	BuiltInAtom(Binop binOperation, bool isNegative, Term* firstTerm, Term* secondTerm): binop(binOperation), negative(isNegative), assignment(false) {
		terms.push_back(firstTerm);
		terms.push_back(secondTerm);
	}

	/** Constructor
	 * @param binop set the binary operation @see Binop
	 * @param negative set whether the atom is negated with negation as failure
	 * @param termsVec set the terms
	 */
	BuiltInAtom(Binop binOperation, bool isNegative, vector<Term*>& termsVec): Atom(termsVec), binop(binOperation), negative(isNegative), assignment(false) {}

	BuiltInAtom(Binop binOperation, bool isNegative, vector<Term*>& termsVec,bool assignment): Atom(termsVec), binop(binOperation), negative(isNegative), assignment(assignment) {}


	BuiltInAtom(Binop binOperation, bool isNegative): Atom(), binop(binOperation), negative(isNegative), assignment(false) {}

	Atom* clone() { Atom* atom = new BuiltInAtom(this->binop,this->negative); atom->setTerms(this->terms); atom->setAssignment(assignment); return atom; }

	///Getter method for the binary operation
	Binop getBinop() const {return binop;};
	///Setter method for the binary operation
	void setBinop(Binop binop) {this->binop = binop;};
	///Returns true if the atom is negated with negation as failure
	bool isNegative() const {return negative;};
	///Set whether the atom is negated with negation as failure
	void setNegative(bool negative) {this->negative = negative;};

	///This method compute the resulting hash a built-in atom using its terms
	size_t hash();

	/** @brief Equal-to operator for built-in atom
	 * 	@details {Two built-in atoms are compared by the binary operation and the terms}
	 */
	virtual bool operator==(const Atom& a)const;

	///This method evaluate the truth value of the built-in atom
	bool evaluate(var_assignment& substritutionTerm);

	///This method first substitute the terms and after evaluate the truth value of the built-in atom
	bool groundAndEvaluate(var_assignment& substitutionTerm);


	/// Return true if is BuiltInAtom
	virtual bool isBuiltIn()const{return true;};

	///Printer Method
	void print(ostream& stream=cout);

	/// Substitute the term and return a new Atom with term substituted
	virtual void substitute(var_assignment& substritutionTerm,Atom*& templateAtom);

	virtual bool isAssignment(){return assignment;};
	virtual void setAssignment(bool assignment){this->assignment=assignment;};

	bool checkArithIsMinusOne(Term* term,TermTable* termTable){
		if(term->getSizeOperator()==1 && term->getOperator(0)==TIMES){
			if(term->getTermsSize()==2 && (term->getTerm(0)==termTable->term_minus_one || term->getTerm(1)==termTable->term_minus_one ))
				return true;
		}
		return false;
	}

	virtual bool plusMinusBuiltin(){
		//Check if is X=Y*-1
		TermTable *termTable=TermTable::getInstance();
		if(terms[0]->getType()==ARITH && terms[1]->getType()!=ARITH && checkArithIsMinusOne(terms[0],termTable)){
			return true;
		}else if(terms[1]->getType()==ARITH && terms[0]->getType()!=ARITH && checkArithIsMinusOne(terms[1],termTable)){
			return true;
		}

		for(unsigned i=0;i<terms.size();i++){
			Term *t=terms[i];
			if(t->getType()==FUNCTION)return false;
			for(unsigned j=0;j<t->getSizeOperator();j++)
				if(t->getOperator(j)==DIV || t->getOperator(j)==TIMES)
					return false;
		}
		return true;
	}

	///Destructor
	~BuiltInAtom() {};

	bool isVariableLessConstant() const{
		if(binop==Binop::LESS && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isConstantLessVariable() const{
		if(binop==Binop::LESS && terms[1]->getType()==TermType::VARIABLE && terms[0]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isVariableLessOrEqConstant() const{
		if(binop==Binop::LESS_OR_EQ && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isConstantLessOrEqVariable() const{
		if(binop==Binop::LESS_OR_EQ && terms[1]->getType()==TermType::VARIABLE && terms[0]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isVariableGreaterConstant() const{
		if(binop==Binop::GREATER && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isConstantGreaterVariable() const{
		if(binop==Binop::GREATER && terms[1]->getType()==TermType::VARIABLE && terms[0]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isVariableGreaterOrEqConstant() const{
		if(binop==Binop::GREATER_OR_EQ && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isConstantGreaterOrEqVariable() const{
		if(binop==Binop::GREATER_OR_EQ && terms[1]->getType()==TermType::VARIABLE && terms[0]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isVariableEqualConstantNotAssignment() const{
		if(binop==Binop::EQUAL && !assignment && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isConstantEqualVariableNotAssignment() const{
		if(binop==Binop::EQUAL && !assignment && terms[1]->getType()==TermType::VARIABLE && terms[0]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isVariableUnequalConstant() const{
		if(binop==Binop::UNEQUAL && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isConstantUnequalVariable() const{
		if(binop==Binop::UNEQUAL && terms[1]->getType()==TermType::VARIABLE && terms[0]->getType()==TermType::NUMERIC_CONSTANT)
			return true;
		return false;
	}
	bool isVariableLessVariable() const{
		if(binop==Binop::LESS && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::VARIABLE)
			return true;
		return false;
	}
	bool isVariableLessOrEqVariable() const{
		if(binop==Binop::LESS_OR_EQ && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::VARIABLE)
			return true;
		return false;
	}
	bool isVariableGreaterVariable() const{
		if(binop==Binop::GREATER && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::VARIABLE)
			return true;
		return false;
	}
	bool isVariableGreaterOrEqVariable() const{
		if(binop==Binop::GREATER_OR_EQ && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::VARIABLE)
			return true;
		return false;
	}
	bool isVariableEqualVariableNotAssignment() const{
		if(binop==Binop::EQUAL && !assignment && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::VARIABLE)
			return true;
		return false;
	}
	bool isVariableUnequalVariable() const{
		if(binop==Binop::UNEQUAL && terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==TermType::VARIABLE)
			return true;
		return false;
	}

	virtual bool isComparisonBuiltIn(Term*& variableTerm, Term*& constantTerm) const{
//		if(terms[0]->getType()==VARIABLE && terms[1]->getType()==VARIABLE && !assignment)
//			return true;
		if(terms[0]->getType()==TermType::NUMERIC_CONSTANT && terms[1]->getType()==VARIABLE && !assignment){
			variableTerm=terms[1];
			constantTerm=terms[0];
			return true;
		}
		if(terms[0]->getType()==TermType::VARIABLE && terms[1]->getType()==NUMERIC_CONSTANT && !assignment){
			variableTerm=terms[0];
			constantTerm=terms[1];
			return true;
		}
		return false;
	}

private:
	///Binary operation @see Binop
	Binop binop;
	///Negated with true negation
	bool negative;
	//Is true if the built-in assigns value to a term, false if it is a comparison (like ==)
	bool assignment;

	bool calculateVariableInAssignment(Term* firstTerm,	Term* secondTerm, var_assignment& substitutionTerm);
};

};

};

#endif /* BUILTINATOM_H_ */

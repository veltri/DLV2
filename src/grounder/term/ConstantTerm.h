/*
 * ConstantTerm.h
 *
 *  Created on: 27/feb/2014
 *      Author: Davide
 */

#ifndef CONSTANTTERM_H_
#define CONSTANTTERM_H_

#include <stdlib.h>

#include "Term.h"
#include "../hash/HashString.h"
#include <boost/lexical_cast.hpp>

namespace DLV2{

namespace grounder{


/*
 *  Represent a constant term (string,number...)
 *
 *  The constant is in IdsManager for avoiding duplication
 */

class ConstantTerm: public Term {
public:
	ConstantTerm(): Term(){};
	ConstantTerm(bool negative): Term(negative){};
	ConstantTerm(bool negative, index_object index): Term(negative,index){};

	virtual bool isGround() {return true;}

	/// Return the itself as constant term
	virtual Term* substitute(map_term_term& substritutionTerm){
//		auto find_it=substritutionTerm.find(this);
//		if(find_it!=substritutionTerm.end())
//			return (*find_it).second;
		return this;
	};

	virtual bool match(Term* termToMatch,map_term_term& varAssignment);

};

class NumericConstantTerm: public ConstantTerm{
public:
	NumericConstantTerm(bool negative,int n): ConstantTerm(negative), numeric_constant(n){};
	virtual bool contain(TermType type) { return TermType::NUMERIC_CONSTANT==type;};
	virtual bool operator==(const Term& term) {return (TermType::NUMERIC_CONSTANT==term.getType() && this->numeric_constant==term.getConstantValue());}
	virtual size_t hash() {return numeric_constant;};
	virtual int getConstantValue() const {return numeric_constant;};
	virtual string getName() const {return boost::lexical_cast<string>(numeric_constant);}
	virtual void print() {cout<<numeric_constant;}
private:
	int numeric_constant;
};

class StringConstantTerm: public ConstantTerm{
public:
	StringConstantTerm(bool negative,string& n): ConstantTerm(negative), string_constant(n){};
	virtual TermType getType() const {return TermType::STRING_CONSTANT;};
	virtual bool contain(TermType type) { return TermType::STRING_CONSTANT==type;};
	virtual bool operator==(const Term& term) {return (TermType::STRING_CONSTANT==term.getType() && this->string_constant==term.getName());}
	virtual size_t hash() {return HashString::getHashString()->computeHash(string_constant);};
	virtual string getName()const {return string_constant;};
	virtual void print() {cout<<string_constant;}
private:
	string string_constant;
};

};

};



#endif /* CONSTANTTERM_H_ */

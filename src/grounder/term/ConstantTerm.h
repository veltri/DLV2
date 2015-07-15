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

	virtual void getGroundTerm(set_term& variables){variables.insert(this);};

	virtual bool isGround() {return true;}

	/// Return the itself as constant term
	virtual Term* substitute(map_term_term& substritutionTerm){
//		auto find_it=substritutionTerm.find(this);
//		if(find_it!=substritutionTerm.end())
//			return (*find_it).second;
		return this;
	};


};

class NumericConstantTerm: public ConstantTerm{
public:
	NumericConstantTerm(bool negative,int n): ConstantTerm(negative), numeric_constant(n){};

	virtual Term* clone(){return new NumericConstantTerm(negative,numeric_constant);};

	virtual bool operator==(const Term& term) const {return (TermType::NUMERIC_CONSTANT==term.getType() && this->numeric_constant==term.getConstantValue());}

	virtual bool operator>(const Term& term)const;
	virtual bool operator>=(const Term& term)const;

	virtual bool operator<(const Term& term)const;
	virtual bool operator<=(const Term& term)const;

	virtual Term* increment();
	virtual Term* sum(Term* t);

	virtual bool contain(TermType type) { return TermType::NUMERIC_CONSTANT==type;};
	virtual size_t hash() {if(numeric_constant<0)return abs(numeric_constant); return numeric_constant;};
	virtual int getConstantValue() const {return numeric_constant;};
	virtual string getName() const {return boost::lexical_cast<string>(numeric_constant);}
	virtual void print(ostream& stream=cout) {stream<<numeric_constant;}
	void setNegative(bool n){numeric_constant=-numeric_constant;};

private:
	int numeric_constant;
};

class StringConstantTerm: public ConstantTerm{
public:
//	StringConstantTerm(bool negative,string& n): ConstantTerm(negative), string_constant(n){};
	StringConstantTerm(bool negative,const string& n): ConstantTerm(negative), string_constant(n){};

	virtual bool operator>(const Term& term)const;
	virtual bool operator>=(const Term& term)const;

	virtual bool operator<(const Term& term)const;
	virtual bool operator<=(const Term& term)const;

	virtual bool operator==(const Term& term) const {return getType()==term.getType() && this->string_constant==term.getName();}

	virtual TermType getType() const {if(string_constant[0]=='"')return STRING_CONSTANT; return SYMBOLIC_CONSTANT; };
	virtual bool contain(TermType type) { return TermType::STRING_CONSTANT==type;};
	virtual size_t hash() {return HashString::getHashString()->computeHash(string_constant);};
	virtual string getName()const {return string_constant;};
	virtual void print(ostream& stream=cout) {stream<<string_constant;}
private:
	string string_constant;
};

};

};



#endif /* CONSTANTTERM_H_ */

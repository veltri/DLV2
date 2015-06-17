/*
 * ConstantTerm.cpp
 *
 *  Created on: 27/feb/2014
 *      Author: Davide
 */

#include "ConstantTerm.h"
#include "../table/TermTable.h"

namespace DLV2{

namespace grounder{

 bool NumericConstantTerm::operator>(const Term& term)const{
	if(TermType::NUMERIC_CONSTANT==term.getType())
		return numeric_constant>term.getConstantValue();

	return false;
};
 bool NumericConstantTerm::operator>=(const Term& term)const{
	if(TermType::NUMERIC_CONSTANT==term.getType())
		return numeric_constant>=term.getConstantValue();

	return false;
}

 bool NumericConstantTerm::operator<(const Term& term)const {
	if(TermType::NUMERIC_CONSTANT==term.getType())
		return numeric_constant<term.getConstantValue();

	return true;
};
 bool NumericConstantTerm::operator<=(const Term& term)const{
	if(TermType::NUMERIC_CONSTANT==term.getType())
		return numeric_constant<=term.getConstantValue();

	return true;
};

Term* NumericConstantTerm::sum(Term* t){
	if(t->getType()==NUMERIC_CONSTANT){
		Term* term=new NumericConstantTerm(false,t->getConstantValue()+numeric_constant);
		TermTable::getInstance()->addTerm(term);
		return term;
	}
	return 0;
};

Term* NumericConstantTerm::increment(){
	Term* term=new NumericConstantTerm(false,numeric_constant+1);
	TermTable::getInstance()->addTerm(term);
	return term;
};

 bool StringConstantTerm::operator>(const Term& term)const{
	if(term.getType()==NUMERIC_CONSTANT)return true;

	if(getType()==STRING_CONSTANT && term.getType()==SYMBOLIC_CONSTANT)
		return true;

	if(term.getType()==getType())
		return string_constant>term.getName();

	return false;
};
 bool StringConstantTerm::operator>=(const Term& term)const{
	if(term.getType()==NUMERIC_CONSTANT)return true;

	if(getType()==STRING_CONSTANT && term.getType()==SYMBOLIC_CONSTANT)
		return true;

	if(term.getType()==getType())
		return string_constant>=term.getName();

	return false;
}

 bool StringConstantTerm::operator<(const Term& term)const {
	if(term.getType()==NUMERIC_CONSTANT)return false;

	if(getType()==STRING_CONSTANT && term.getType()==SYMBOLIC_CONSTANT)
		return false;

	if(term.getType()==getType())
		return string_constant<term.getName();

	return true;
};

 bool StringConstantTerm::operator<=(const Term& term)const{
	if(term.getType()==NUMERIC_CONSTANT)return false;

	if(getType()==STRING_CONSTANT && term.getType()==SYMBOLIC_CONSTANT)
		return false;

	if(term.getType()==getType())
		return string_constant<=term.getName();

	return true;
};

};

};

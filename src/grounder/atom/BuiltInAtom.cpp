/*
 * BuiltInAtom.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "BuiltInAtom.h"

#include <iostream>

#include "../table/TermTable.h"
#include "../hash/HashVecInt.h"

namespace DLV2{

namespace grounder{


//TODO - This method have to be removed, use only groundAndEvaluate
bool BuiltInAtom::evaluate(var_assignment& substitutionTerm){
	Term* firstTerm=terms[0];
	Term* secondTerm=terms[1];

	// If there is equal and variable assign that value
	if(assignment){
		if(firstTerm->getType()==TermType::VARIABLE || secondTerm->getType()!=TermType::VARIABLE ){
			substitutionTerm[firstTerm->getLocalVariableIndex()]=secondTerm->calculate();
			return true;
		}if(firstTerm->getType()!=TermType::VARIABLE || secondTerm->getType()==TermType::VARIABLE ){
			substitutionTerm[secondTerm->getLocalVariableIndex()]=firstTerm->calculate();
			return true;
	    }
	}


	if(binop==Binop::EQUAL)
		return firstTerm->getIndex()==secondTerm->getIndex();
	if(binop==Binop::UNEQUAL)
		return firstTerm->getIndex()!=secondTerm->getIndex();
	if(binop==Binop::LESS)
		return *firstTerm<*secondTerm;
	if(binop==Binop::LESS_OR_EQ)
		return *firstTerm<=*secondTerm;
	if(binop==Binop::GREATER)
		return *firstTerm>*secondTerm;
	if(binop==Binop::GREATER_OR_EQ)
		return *firstTerm>=*secondTerm;

	return false;
}

bool BuiltInAtom::groundAndEvaluate(var_assignment& substitutionTerm){
	Term* firstTerm=terms[0]->substitute(substitutionTerm)->calculate();

	Term* secondTerm=terms[1]->substitute(substitutionTerm)->calculate();

	// If there is equal and variable assign that value
	if(assignment){
		if(firstTerm->getType()==TermType::VARIABLE || secondTerm->getType()!=TermType::VARIABLE ){
			substitutionTerm[firstTerm->getLocalVariableIndex()]=secondTerm->calculate();
			return true;
		}if(firstTerm->getType()!=TermType::VARIABLE || secondTerm->getType()==TermType::VARIABLE ){
			substitutionTerm[secondTerm->getLocalVariableIndex()]=firstTerm->calculate();
			return true;
	    }
	}


	if(binop==Binop::EQUAL)
		return firstTerm->getIndex()==secondTerm->getIndex();
	if(binop==Binop::UNEQUAL)
		return firstTerm->getIndex()!=secondTerm->getIndex();
	if(binop==Binop::LESS)
		return *firstTerm<*secondTerm;
	if(binop==Binop::LESS_OR_EQ)
		return *firstTerm<=*secondTerm;
	if(binop==Binop::GREATER)
		return *firstTerm>*secondTerm;
	if(binop==Binop::GREATER_OR_EQ)
		return *firstTerm>=*secondTerm;

	return false;
}

size_t BuiltInAtom::hash(){
	return HashVecInt::getHashVecInt()->computeHashTerm(terms);
}

bool BuiltInAtom::operator==(const Atom& a) const {

	if(!a.isBuiltIn())return false;
	if(binop != a.getBinop()) return false;
	if(terms[0]->getIndex() != a.getTerm(0)->getIndex()) return false;
	if(terms[1]->getIndex() != a.getTerm(1)->getIndex()) return false;

	return true;
}

void BuiltInAtom::print(ostream& stream){
	Term* firstTerm=terms[0];
	Term* secondTerm=terms[1];

	firstTerm->print(stream);
	if(binop==Binop::EQUAL)
		stream<<"=";
	if(binop==Binop::UNEQUAL)
		stream<<"!=";
	if(binop==Binop::LESS)
		stream<<"<";
	if(binop==Binop::LESS_OR_EQ)
		stream<<"<=";
	if(binop==Binop::GREATER)
		stream<<">";
	if(binop==Binop::GREATER_OR_EQ)
		stream<<">=";
	secondTerm->print(stream);
}


void BuiltInAtom::substitute(var_assignment& substitutionTerm,Atom*& templateAtom){
	if(templateAtom==nullptr){
		vector<Term*> terms_substitute(terms.size());
		for(unsigned int i=0;i<terms.size();i++){
			terms_substitute[i]=terms[i]->substitute(substitutionTerm) ;
		}
		templateAtom=new BuiltInAtom(binop,negative,terms_substitute,assignment);
	}
	else
		for(unsigned int i=0;i<terms.size();i++){
			templateAtom->setTerm(i,terms[i]->substitute(substitutionTerm));

		}
};

};

};

/*
 * FunctionTerm.cpp
 *
 *  Created on: 25/feb/2014
 *      Author: Davide
 */

#include "FunctionTerm.h"

#include "../hash/HashVecInt.h"
#include "../hash/HashString.h"

namespace DLV2{

namespace grounder{

size_t FunctionTerm::hash() {
	vector<size_t> hashVec(terms.size()+1);
	hashVec[0]=HashString::getHashString()->computeHash(name);
	for(unsigned int i=0;i<terms.size();i++)
		hashVec[i+1]=terms[i]->getIndex();

	return HashVecInt::getHashVecInt()->computeHashSize_T(hashVec);

}

bool FunctionTerm::operator>(const Term& term) const {
	int checkMaxMin=checkMaxAndMinTerm(term,false);
	if(checkMaxMin!=2) return checkMaxMin;
	if(term.getType()==NUMERIC_CONSTANT || term.getType()==STRING_CONSTANT || term.getType()==SYMBOLIC_CONSTANT)
		return true;

	if(term.getType()==getType()){
		if(getTermsSize()>term.getTermsSize())return true;
		if(getTermsSize()==term.getTermsSize()){
			string functor_term=term.getName();
			if(name!=functor_term)return name>functor_term;
			bool findGreater=false;
			for(unsigned int i=0;i<terms.size();i++){
				if(*terms[i]<*term.getTerm(i))return false;
				if(!findGreater && *terms[i]>*term.getTerm(i))findGreater=true;
			}
			return findGreater;
		}
	}

	return false;

}

bool FunctionTerm::operator>=(const Term& term) const {
	int checkMaxMin=checkMaxAndMinTerm(term,true);
	if(checkMaxMin!=2) return checkMaxMin;
	if(term.getType()==NUMERIC_CONSTANT || term.getType()==STRING_CONSTANT || term.getType()==SYMBOLIC_CONSTANT)
		return true;

	if(term.getType()==getType()){
		if(getTermsSize()>term.getTermsSize())return true;
		if(getTermsSize()==term.getTermsSize()){
			string functor_term=term.getName();
			if(name!=functor_term)return name>=functor_term;
			for(unsigned int i=0;i<terms.size();i++)
				if(*terms[i]<*term.getTerm(i))return false;
			return true;
		}
	}

	return false;
}

bool FunctionTerm::operator<(const Term& term) const {
	int checkMaxMin=checkMaxAndMinTerm(term,false);
	if(checkMaxMin!=2) return !checkMaxMin;
	if(term.getType()==NUMERIC_CONSTANT || term.getType()==STRING_CONSTANT || term.getType()==SYMBOLIC_CONSTANT)
		return false;

	if(term.getType()==getType()){
		if(getTermsSize()<term.getTermsSize())return true;
		if(getTermsSize()==term.getTermsSize()){
			string functor_term=term.getName();
			if(name!=functor_term)return name<functor_term;
			bool findLess=false;
			for(unsigned int i=0;i<terms.size();i++){
				if(*terms[i]>*term.getTerm(i))return false;
				if(!findLess && *terms[i]<*term.getTerm(i))findLess=true;
			}
			return findLess;
		}
	}

	return false;
}

bool FunctionTerm::operator<=(const Term& term) const {
	int checkMaxMin=checkMaxAndMinTerm(term,true);
	if(checkMaxMin!=2) return !checkMaxMin;
	if(term.getType()==NUMERIC_CONSTANT || term.getType()==STRING_CONSTANT || term.getType()==SYMBOLIC_CONSTANT)
		return false;

	if(term.getType()==getType()){
		if(getTermsSize()<term.getTermsSize())return true;
		if(getTermsSize()==term.getTermsSize()){
			string functor_term=term.getName();
			if(name!=functor_term)return name<=functor_term;
			for(unsigned int i=0;i<terms.size();i++){
				if(*terms[i]>*term.getTerm(i))return false;
			}
			return true;
		}
	}

	return false;
}

void FunctionTerm::print(ostream& stream) {
	stream<<name<<"(";
	for(unsigned int i=0;i<terms.size();i++){
		if(i!=0)
			stream<<",";
		terms[i]->print(stream);
	}
	stream<<")";
}

Term* FunctionTerm::substitute(map_term<Term*>& substritutionTerm) {
	// Create a new function replacing the term in a vector
	// Recursively call substitute for nested function
	// At the end add a new function in a table and return index

	vector<Term*> subTerms(terms.size());
	for(unsigned int i=0;i<terms.size();i++){
		Term* sub_term=terms[i]->substitute(substritutionTerm);
		subTerms[i]=sub_term;
	}
	Term *newTerm=new FunctionTerm(name,negative,subTerms);
	TermTable::getInstance()->addTerm(newTerm);
	return newTerm;
}

Term* FunctionTerm::calculate() {
	// Create a new function replacing the term in a vector
	// Recursively call calculate for nested function
	// At the end add a new function in a table and return index
	if(!contain(TermType::ARITH)) return this;

	vector<Term*> sub_terms(terms.size());

	TermTable *termTable=TermTable::getInstance();

	for(unsigned int i=0;i<terms.size();i++){
		if(terms[i]->contain(TermType::ARITH)){
			sub_terms[i]=terms[i]->calculate();
		}else
			sub_terms[i]=terms[i];
	}

	Term *subTerm=new FunctionTerm(name,negative,sub_terms);
	termTable->addTerm(subTerm);
	return subTerm;
}

 bool FunctionTerm::operator==(const Term& term) const{
	if(getType()!=term.getType())return false;
	if(getName().compare(term.getName())!=0)return false;
	if(terms.size()!=term.getTermsSize())return false;
	for(unsigned int i=0;i<terms.size();i++)
		if(terms[i]->getIndex()!=term.getTerm(i)->getIndex())
			return false;

	return true;
}


};

};

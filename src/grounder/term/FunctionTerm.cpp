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

void FunctionTerm::print() {
	cout<<name<<"(";
	for(unsigned int i=0;i<terms.size();i++){
		if(i!=0)
			cout<<",";
		terms[i]->print();
	}
	cout<<")";
}

Term* FunctionTerm::substitute(map_term_term& substritutionTerm) {
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

 bool FunctionTerm::operator==(const Term& term){
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

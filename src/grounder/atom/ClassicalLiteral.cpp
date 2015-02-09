/*
 * ClassicalLiteral.cpp
 *
 *  Created on: 07/mar/2014
 *      Author: Jessica
 */

#include "ClassicalLiteral.h"

#include <iostream>

#include "../hash/HashVecInt.h"
#include "../table/TermTable.h"

namespace DLV2{

namespace grounder{



size_t ClassicalLiteral::hash(){
	return HashVecInt::getHashVecInt()->computeHashTerm(terms);
}


void ClassicalLiteral::print(){
	print(predicate,terms,negative,hasMinus);
}

void ClassicalLiteral::print(Predicate* predicate,const vector<Term*>& terms,bool negative,bool hasMinus){
	if(negative)
		cout<<"not ";
	if(hasMinus)
		cout<<"- ";
	cout<<predicate->getName();
	for (unsigned int i = 0; i < terms.size(); ++i){
		if(i==0)
			cout<<"(";
		terms[i]->print();
		if(i!=terms.size()-1)
			cout<<",";
		else
			cout<<")";
	}
}



bool ClassicalLiteral::operator==(const Atom& a) {

	if(a.getPredicate()==nullptr) return false;
	if(*predicate==*a.getPredicate())return false;
	if(terms.size()!=a.getTermsSize())return false;
	for(unsigned int i=0;i<terms.size();i++)
		if(terms[i]->getIndex()!=a.getTerm(i)->getIndex())
			return false;

	return true;
}

Atom* ClassicalLiteral::substitute(map_term_term& substitutionTerm){
	vector<Term*> terms_substitute(terms.size());
	for(unsigned int i=0;i<terms.size();i++){
		terms_substitute[i]=terms[i]->substitute(substitutionTerm) ;
	}
	return new ClassicalLiteral(predicate,terms_substitute,hasMinus,negative);
};


};

};

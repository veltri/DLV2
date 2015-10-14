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
	print(predicate,terms,negative,hasMinus,cout);
}

void ClassicalLiteral::print(Predicate* predicate,const vector<Term*>& terms,bool negative,bool hasMinus,ostream& stream){
	if(negative)
		stream<<"not ";
	if(hasMinus)
		stream<<"- ";
	stream<<predicate->getName();
	for (unsigned int i = 0; i < terms.size(); ++i){
		if(i==0)
			stream<<"(";
		terms[i]->print(stream);
		if(i!=terms.size()-1)
			stream<<",";
		else
			stream<<")";
	}
}



bool ClassicalLiteral::operator==(const Atom& a)const {

	if(a.getPredicate()==nullptr) return false;
	if(predicate->getIndex()!=a.getPredicate()->getIndex())return false;
	if(terms.size()!=a.getTermsSize())return false;
	for(unsigned int i=0;i<terms.size();i++)
		if(terms[i]->getIndex()!=a.getTerm(i)->getIndex())
			return false;

	return true;
}

void ClassicalLiteral::substitute(map_term<Term*>& substitutionTerm,Atom*& templateAtom){
	if(templateAtom==nullptr){
		vector<Term*> terms_substitute(terms.size());
		for(unsigned int i=0;i<terms.size();i++){
			terms_substitute[i]=terms[i]->substitute(substitutionTerm) ;
		}
		templateAtom=new ClassicalLiteral(predicate,terms_substitute,hasMinus,negative);
	}
	else
		for(unsigned int i=0;i<terms.size();i++)
			templateAtom->setTerm(i,terms[i]->substitute(substitutionTerm));

}


bool ClassicalLiteral::equal(const Atom& atom) const {
	if(!atom.isClassicalLiteral()) return false;
	if(negative!=atom.isNegative()) return false;
	if(hasMinus!=atom.isHasMinus()) return false;
	return (*this)==atom;
}

}}

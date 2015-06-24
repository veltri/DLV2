/*
 * Atom.cpp
 *
 *  Created on: 07/mar/2014
 *      Author: Jessica
 */

#include "Atom.h"

#include "../term/ConstantTerm.h"
#include "../table/TermTable.h"


namespace DLV2{

namespace grounder{


void Atom::ground(map_term_term& substritutionTerm,Atom*& templateAtom){
	substitute(substritutionTerm,templateAtom);

	for(unsigned int i=0;i<templateAtom->getTermsSize();i++){
		Term* term=templateAtom->getTerm(i);
		if(term->isGround() && term->contain(TermType::ARITH))
			/// Calculate the value of arithmetic term and add in terms table
			templateAtom->setTerm(i,term->calculate());
	}

};

set_term Atom::getVariable(){
	set_term variables;
	getVariables(this,variables);
	return variables;
}

void Atom::getVariables(Atom* atom,set_term& variables){
	for(auto term:atom->getTerms())
		term->getVariable(variables);
}

void Atom::getVariables(const vector<Atom*>& atoms,set_term& variables){
	for(auto atom:atoms)
		getVariables(atom,variables);
}

string Atom::getBinopToStrng(Binop binop){
	switch (binop) {
		case EQUAL:
			return "=";
			break;
		case UNEQUAL:
			return "!=";
			break;
		case LESS:
			return "<";
			break;
		case LESS_OR_EQ:
			return "<=";
			break;
		case GREATER:
			return ">";
			break;
		case GREATER_OR_EQ:
			return ">=";
			break;
		default:
			return "";
			break;
	}
}

}}

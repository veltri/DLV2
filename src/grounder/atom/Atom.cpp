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
	for(auto term:terms)
		term->getVariable(variables);
	return variables;
}

};

};

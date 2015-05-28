/*
 * OrderRule.cpp
 *
 *  Created on: May 28, 2015
 *      Author: jessica
 */

#include "OrderRule.h"

namespace DLV2 {
namespace grounder {

void OrderRule::order() {
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom){
		Atom* current_atom=*atom;
		 if(!(current_atom->isBuiltIn() || current_atom->isNegative() || current_atom->getAggregateElementsSize()>0)) {
			 addSafeVariablesInAtom(current_atom);
			 unlockAtoms(builtInAtoms);
		 }
	}
}

void OrderRule::addSafeVariablesInAtom(Atom* atom) {
	set_term variables=atom->getVariable();
	for(auto variable: variables)
		safeVariables.insert(variable);
	orderedBody.push_back(atom);
}

void OrderRule::unlockAtoms(list<Atom*>& atoms) {
	for(auto it=atoms.begin();it!=atoms.end();it++){
		Atom* atom=*it;
		set_term variables=atom->getVariable();
		bool foundAnUnsafeVar=false;
		for(auto variable: variables){
			if(!safeVariables.count(variable)){
				foundAnUnsafeVar=true;
				break;
			}
		}
		if(!foundAnUnsafeVar){
			orderedBody.push_back(atom);
			atoms.erase(it);
		}
	}
}

} /* namespace grounder */
} /* namespace DLV2 */

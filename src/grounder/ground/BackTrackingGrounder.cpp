/*
 * BackTrackingGrounder.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: davide
 */

#include "BackTrackingGrounder.h"

namespace DLV2 {
namespace grounder {


bool BackTrackingGrounder::match() {
}

bool BackTrackingGrounder::next() {
	if(index_current_atom+1>=currentRule->getSizeBody()) return false;
	current_atom_it++;
	index_current_atom++;
	return true;
}

void BackTrackingGrounder::foundAssignment() {
	Rule groundRule;
	for(auto atom=currentRule->getBeginBody();atom!=currentRule->getEndBody();atom++){

		Atom *bodyGroundAtom=(*atom)->ground(current_var_assign);

		PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(bodyGroundAtom->getPredicate());
		Atom *searchAtom=predicateExt->getGenericAtom(FACT,DELTA,bodyGroundAtom);

		if(searchAtom==nullptr){
			//FATAL ERRRO ANONIMUS

		}else{
			delete bodyGroundAtom;
			if(!bodyGroundAtom->isFact())
				groundRule.addInHead(searchAtom);

		}

	}

	unsigned atom_counter=0;
	for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();atom++,atom_counter++){
		Atom *headGroundAtom=(*atom)->ground(current_var_assign);

		PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(headGroundAtom->getPredicate());
		Atom *searchAtom=predicateExt->getGenericAtom(FACT,DELTA,headGroundAtom);

		if(searchAtom==nullptr){
			groundRule.addInHead(headGroundAtom);
			Atom *genericGroundAtom= new GenericAtom (headGroundAtom->getTerms(),false);
			for(unsigned i=0;i<predicate_searchInsert_table[atom_counter].size();i++)
				predicateExt->addGenericAtom(predicate_searchInsert_table[atom_counter][i],genericGroundAtom);
		}else{
			delete headGroundAtom;

			if(groundRule.getSizeBody()==0)
				searchAtom->setFact(true);

			groundRule.addInHead(searchAtom);

		}

	}


}

bool BackTrackingGrounder::back() {
	current_atom_it--;
	index_current_atom--;
	do{
		if (index_current_atom < 0) {
			return false;
		}
		current_atom_it--;
		index_current_atom--;
	}while ((*current_atom_it)->isBuiltIn() || (*current_atom_it)->isNegative() || current_variables_atoms[index_current_atom].size()==0);
	return true;
}

void BackTrackingGrounder::inizialize(Rule* rule) {
	currentRule=rule;
	current_var_assign.clear();
	current_id_match.clear();
	current_atom_it = currentRule->getBeginBody();
	index_current_atom = 0;
	findBindVariablesRule();
}

void BackTrackingGrounder::findBindVariablesRule() {
	set_term total_variable;
	unsigned int index_current_atom = 0;
	current_variables_atoms.clear();

	//For each atom determines the bound and the bind variables
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); current_atom_it++) {
		Atom *current_atom = *current_atom_it;
		set_term variablesInAtom = current_atom->getVariable();
		current_variables_atoms.push_back(set_term());

		for (auto variable : variablesInAtom) {
			if (!total_variable.count(variable))
				current_variables_atoms[index_current_atom].insert(variable);
		}

		for (auto variable : variablesInAtom)
			total_variable.insert(variable);
		index_current_atom++;

	}
}

} /* namespace grounder */
} /* namespace DLV2 */

/*
 * ChoiceElement.cpp
 *
 *  Created on: 04/ago/2014
 *      Author: tesi2
 */

#include "ChoiceElement.h"

namespace DLV2{

namespace grounder{


set_predicate ChoiceElement::getPredicateInNaf() {
	set_predicate predicates;
	for(unsigned i=1;i<choiceElement.size();i++){
		Predicate* predicate=choiceElement[i]->getPredicate();
		predicates.insert(predicate);
	}

	return predicates;
}

set_predicate ChoiceElement::getPredicatePositiveInNaf() {
	set_predicate predicates;
	for(unsigned i=1;i<choiceElement.size();i++)
		if(!choiceElement[i]->isNegative()){
			Predicate* predicate=choiceElement[i]->getPredicate();
			predicates.insert(predicate);
		}

	return predicates;
}

set_predicate ChoiceElement::getPredicateNegativeInNaf() {
	set_predicate predicates;
	for(unsigned i=1;i<choiceElement.size();i++)
		if(choiceElement[i]->isNegative()){
			Predicate* predicate=choiceElement[i]->getPredicate();
			predicates.insert(predicate);
		}

	return predicates;
}

set_term ChoiceElement::getVariableInNaf() {
	set_term terms;
	for(unsigned i=1;i<choiceElement.size();i++){
		const set_term& terms_in_atom=choiceElement[i]->getVariable();
		terms.insert(terms_in_atom.begin(),terms_in_atom.end());
	}
	return terms;
}

void ChoiceElement::deleteAtoms() {
	for(auto& atom:choiceElement)
		delete atom;
}

bool ChoiceElement::operator ==(const ChoiceElement& element) const {
	if(choiceElement.size()!=element.choiceElement.size())return false;
	for(unsigned i=0;i<choiceElement.size();i++)
		if(!(choiceElement[i]==element.choiceElement[i]))
			return false;


	return true;
}

}
}


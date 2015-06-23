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

}

}

/*
 * AggregateElement.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "AggregateElement.h"


namespace DLV2{

namespace grounder{

	AggregateElement* AggregateElement::clone(){
		AggregateElement *element=new AggregateElement;
		element->setTerms(terms);
		for(auto atom:nafLiterals)
			element->addNafLiterals(atom->clone());
		return element;
	}

	void AggregateElement::clearNafLiterals() {
		for(auto atom:nafLiterals)
			delete atom;
		nafLiterals.clear();
	}

	void AggregateElement::deleteAtoms() {
		for(auto atom:nafLiterals)
			delete atom;
	}

	set_term AggregateElement::getSafeVariable() {
		set_term safeVars;
		for(auto atom:nafLiterals)
			if(!atom->isNegative())
				for(auto variable:atom->getVariable())
					safeVars.insert(variable);
		return safeVars;
	}

	set_term AggregateElement::getUnsafeVariable() {
		set_term safeVars=getSafeVariable();
		set_term unsafeVars;
		for(auto atom:nafLiterals)
			if(atom->isNegative())
				for(auto variable:atom->getVariable())
					if(!safeVars.count(variable))
						unsafeVars.insert(variable);
		return unsafeVars;
	}
}
}




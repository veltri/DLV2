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

	AggregateElement::~AggregateElement() {
		clearNafLiterals();
	}

	void AggregateElement::clearNafLiterals() {
		for(auto naf:nafLiterals) delete naf;nafLiterals.clear();
	}
}

}


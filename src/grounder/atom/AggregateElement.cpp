/*
 * AggregateElement.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "AggregateElement.h"
#include "../../util/Utils.h"


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

	void AggregateElement::getPredicates(set_predicate& predicates)const{
		for(auto atom:nafLiterals){
			predicates.insert(atom->getPredicate());
		}
	}

	bool AggregateElement::areAggregationTermsSafe() const {
		for(auto term: terms){
			if(term->isGround())continue;
			bool ok=false;
			for(auto atom:nafLiterals){
				set_term variables=atom->getVariable();
				if(variables.count(term)){
					ok=true;
				}
			}
			if(!ok)
				return false;
		}
		return true;
	}

	bool AggregateElement::operator ==(const AggregateElement& element) const {
		if(terms.size()!=element.terms.size())return false;
		if(nafLiterals.size()!=element.nafLiterals.size())return false;
		for(unsigned i=0;i<terms.size();i++)
			if(terms[i]->getIndex()!=element.terms[i]->getIndex())
				return false;
		for(unsigned i=0;i<nafLiterals.size();i++)
			if(!(nafLiterals[i]==nafLiterals[i]))
				return false;

		return true;
	}

bool AggregateElement::isAllAggregateTermShared(set_term& shared_variable)const{
	for(auto term:terms){
		set_term variable_term;
		term->getVariable(variable_term);
		if(!Utils::isContained(variable_term,shared_variable))
			return false;
	}
	return true;
}

void AggregateElement::getUnsolvedPredicateVariable(set_term& vars) {
	for(auto atom:nafLiterals){
		if(atom->isClassicalLiteral() && !atom->getPredicate()->isSolved()){
			set_term variables=atom->getVariable();
			vars.insert(variables.begin(),variables.end());
		}
	}
}

}
}



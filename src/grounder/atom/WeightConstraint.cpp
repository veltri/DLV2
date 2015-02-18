/*
 * WeightConstraint.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: davide
 */

#include "WeightConstraint.h"

namespace DLV2 {
namespace grounder {

Atom* WeightConstraint::clone() {
	Atom* atom = new WeightConstraint(this->weightAtoms);
	atom->setTerms(this->terms);
	return atom;
}

size_t WeightConstraint::hash(){
	//TODO Hash weight constraint
	return 0;
}

bool WeightConstraint::operator == (const Atom& a) {
	if(this->terms[0]->getIndex()!=a.getLowerGuard()->getIndex())
		return false;
	if(this->weightAtoms.size()!=a.getWeightAtomsSize())
		return false;
	for(unsigned i=0;i<weightAtoms.size();i++){
		pair<Atom*,Term*> atomWeight=a.getWeightAtom(i);
		if(weightAtoms[i].first!=atomWeight.first)
			return false;
		if(weightAtoms[i].second!=atomWeight.second)
			return false;
	}
	return true;
}

set_term WeightConstraint::getVariable() {
	set_term variables;
	for(auto pair: weightAtoms){
		set_term atomVariable=pair.first->getVariable();
		variables.insert(atomVariable.begin(),atomVariable.end());
	}
	return variables;
}

bool WeightConstraint::isGround() {
	if(!terms[0]->isGround())
		return false;
	for(auto pair: weightAtoms)
		if(!pair.first->isGround())
			return false;
	return true;
}

bool WeightConstraint::containsAnonymous() {
	for(auto pair: weightAtoms)
		if(pair.first->containsAnonymous())
			return true;
	return false;
}

void WeightConstraint::expand() {
}

Atom* WeightConstraint::substitute(map_term_term& substitutionTerm) {
	vector<Term*> newTerms;
	if(!terms[0]->isGround())
		newTerms.push_back(terms[0]->substitute(substitutionTerm));
	else
		newTerms.push_back(terms[0]);
	vector<pair<Atom*,Term*>> newWeightAtoms;
	for(auto pair:weightAtoms){
		Atom* atomGround=pair.first->substitute(substitutionTerm);
		Term* termGround=pair.second->substitute(substitutionTerm);
		newWeightAtoms.push_back({atomGround,termGround});
	}
	return new WeightConstraint(terms,weightAtoms);
}

void WeightConstraint::substitute(map_term_term& substitutionTerm, Atom* templateAtom) {
	if(!templateAtom->getLowerGuard()->isGround())
		templateAtom->setLowerGuard(templateAtom->getLowerGuard()->substitute(substitutionTerm));
	for(unsigned i=0;i<weightAtoms.size();i++){
		Atom* atomGround=weightAtoms[i].first->substitute(substitutionTerm);
		Term* termGround=weightAtoms[i].second->substitute(substitutionTerm);
		templateAtom->setWeightAtom(i,{atomGround,termGround});
	}
}

bool WeightConstraint::containsRangeTerms() {
	for(auto pair: weightAtoms)
		if(pair.first->containsRangeTerms())
			return true;
	return false;
}

void WeightConstraint::print() {
	if(this->terms[0]!=nullptr)
		this->terms[0]->print();
	cout<<"{";
	bool first=true;
	for(auto& element:weightAtoms){
		if(!first) cout<<","; else first=false;
		element.first->print();
		cout<<"=";
		element.second->print();
	}
	cout<<"}";
}

} /* namespace grounder */
} /* namespace DLV2 */

/*
 * OrderRule.cpp
 *
 *  Created on: May 28, 2015
 *      Author: jessica
 */

#include "OrderRule.h"
#include "../../util/Assert.h"
#include "../../util/Options.h"

namespace DLV2 {
namespace grounder {

OrderRule::OrderRule(Rule* r):rule(r){
	unsigned atom_counter=0;
	bindAtomsDependency.reserve(r->getSizeBody());
	computeAtomsVariables();
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
		bindAtomsDependency.push_back(unordered_set<unsigned>());
		Atom* current_atom=*atom;
		if(current_atom->isNegative())
			 negativeAtoms.push_back(atom_counter);
		 else if(current_atom->isBuiltIn())
			 builtInAtoms.push_back(atom_counter);
		 else if(current_atom->getAggregateElementsSize()>0)
			 aggregatesAtoms.push_back(atom_counter);
	}
}

bool OrderRule::order() {
	// A first attempt to order the body ignoring cyclic dependencies
	// by iterating the atoms in the body and resolving their dependencies when are not cyclic
	unsigned atom_counter=0;
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
		Atom* current_atom=*atom;
		if(!(current_atom->isNegative()) && !(current_atom->isBuiltIn()) && current_atom->getAggregateElementsSize()==0) {
			addSafeVariablesInAtom(current_atom, atom_counter);
			unlockAtoms(negativeAtoms);
			unlockAtoms(builtInAtoms);
		}
	}

	cout<<"NEG: "<<negativeAtoms.size()<<endl;
	rule->print();
	for(auto it:mapVariablesAtoms){
		cout<<"VAR: ";it.first->print();cout<<" ";
		cout<<"ATOM: ";orderedBody[it.second]->print();cout<<endl;
	}
	cout<<"----------"<<endl;

	if(negativeAtoms.size()>0)
		return false;

	// Second, solve the cyclic dependencies
	while(builtInAtoms.size()>0 || aggregatesAtoms.size()>0){
		unsigned sizeBuiltIns=builtInAtoms.size();
		unlockAtoms(builtInAtoms);
		if(builtInAtoms.size()==sizeBuiltIns){
			unsigned sizeAggregates=aggregatesAtoms.size();
			unlockAtoms(aggregatesAtoms);
			if(aggregatesAtoms.size()==sizeAggregates)
				return false;
		}
	}
	// Finally, set the ordered body as the body of the rule
	rule->setBody(orderedBody);

	atom_counter=0;
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
		cout<<atom_counter<<" ";
		for(auto it:bindAtomsDependency[atom_counter]){
			orderedBody[it]->print();
			cout<<" ";
		}
		cout<<endl;
	}
	cout<<"*************"<<endl;

	if(Options::globalOptions()->isPrintRewritedProgram())
		rule->print();

	return true;
}

void OrderRule::addSafeVariablesInAtom(Atom* atom, unsigned pos) {
	set_term variables=mapAtomsVariables[pos];
	orderedBody.push_back(atom);
	for(auto variable: variables){
		if(!mapVariablesAtoms.count(variable))
			mapVariablesAtoms.insert({variable,orderedBody.size()-1});
		safeVariables.insert(variable);
	}
}

void OrderRule::foundAnAssigment(Atom* atom, Term* bindVariable, unsigned pos) {
	atom->setAssignment(true);
	safeVariables.insert(bindVariable);
	if (!mapVariablesAtoms.count(bindVariable))
		mapVariablesAtoms.insert( { bindVariable, orderedBody.size()-1 });
	set_term variables=mapAtomsVariables[pos];
	for(auto var: variables){
		if(var->getIndex()!=bindVariable->getIndex()){
			bindAtomsDependency[orderedBody.size()-1].insert(mapVariablesAtoms.find(var)->second);
		}
	}
}

void OrderRule::unlockAtoms(list<unsigned>& atoms) {
	vector<list<unsigned>::iterator> atomsUnlocked;
	for(auto it=atoms.begin();it!=atoms.end();++it){
		Atom* atom=rule->getAtomInBody(*it);
		set_term variables=mapAtomsVariables[*it];
		// If the atom is negative or is not an assignment or is an aggregate
		// then if every variable is safe, the atom is safe
		// and thus it can be added to the new body
		if(atom->isNegative() || (atom->isBuiltIn() && atom->getBinop()!=Binop::EQUAL) || (atom->getAggregateElementsSize()>0)){
			lookForVariablesUnsafe(variables, atom, it, atomsUnlocked);
		}
		//Moreover if it is an assignment aggregate the bind variable must be inserted into the safeVariables
		if(atom->getAggregateElementsSize()>0 && atom->getFirstBinop()==EQUAL && !safeVariables.count(atom->getFirstGuard())){
			Term* bindVariable=atom->getFirstGuard();
			foundAnAssigment(atom, bindVariable,*it);
		}
		if(atom->isBuiltIn() && atom->getBinop()==Binop::EQUAL){
			Term* firstTerm=atom->getTerm(0);
			Term* secondTerm=atom->getTerm(1);
			bool firstSafe=true;
			bool secondSafe=true;
			Term* bindVariable=0;

			checkBuiltInSafety(firstSafe, firstTerm, bindVariable);
			checkBuiltInSafety(secondSafe, secondTerm, bindVariable);

			if(firstSafe && secondSafe){
				orderedBody.push_back(atom);
				atomsUnlocked.push_back(it);
			}
			if((firstSafe && bindVariable==secondTerm) || (secondSafe && bindVariable==firstTerm)){
				atomsUnlocked.push_back(it);
				orderedBody.push_back(atom);
				foundAnAssigment(atom, bindVariable,*it);
			}
		}
	}
	for(auto iterator: atomsUnlocked)
		atoms.erase(iterator);
}

void OrderRule::computeAtomsVariables() {
	for (unsigned i = 0; i < rule->getSizeBody(); ++i) {
		Atom* atom = rule->getAtomInBody(i);
		if (atom->getAggregateElementsSize() == 0)
			mapAtomsVariables.insert( { i, atom->getVariable() });
		else{
			AggregateAtom* aggregate=dynamic_cast<AggregateAtom*>(atom);
			mapAtomsVariables.insert( { i, aggregate->getSharedVariable(rule) });
		}
	}
}

void OrderRule::checkBuiltInSafety(bool& safe, Term* term, Term*& bindVariable) {
	if (term->getType() == VARIABLE) {
		if (!safeVariables.count(term)) {
			safe = false;
			bindVariable = term;
		}
	} else {
		set_term firstTermVars;
		term->getVariable(firstTermVars);
		for (auto variable : firstTermVars) {
			if (!safeVariables.count(variable)) {
				safe = false;
				break;
			}
		}
	}
}

void OrderRule::lookForVariablesUnsafe(set_term& variables,Atom* atom, list<unsigned>::iterator it, vector<list<unsigned>::iterator>& atomsUnlocked){
	bool foundAnUnsafeVar=false;
	for(auto variable: variables){
		if(!safeVariables.count(variable)){
			foundAnUnsafeVar=true;
			break;
		}
	}
	if(!foundAnUnsafeVar){
		orderedBody.push_back(atom);
		atomsUnlocked.push_back(it);
	}
}

vector<Atom*> OrderRule::getAtomsFromWhichDepends(unsigned atom_position) const {
	vector<Atom*> atoms;
	atoms.reserve(orderedBody.size());
	for(auto atom_pos: bindAtomsDependency[atom_position])
		atoms.push_back(orderedBody[atom_pos]);
	return atoms;
}

} /* namespace grounder */
} /* namespace DLV2 */

/*
 * OrderRule.cpp
 *
 *  Created on: May 28, 2015
 *      Author: jessica
 */

#include "OrderRule.h"
#include "../../util/Assert.h"

namespace DLV2 {
namespace grounder {

OrderRule::OrderRule(Rule* r):rule(r){
	unsigned atom_counter=0;
	computeAtomsVariables();
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
		Atom* current_atom=*atom;
		if(current_atom->isNegative())
			 negativeAtoms.push_back(atom_counter);
		 else if(current_atom->isBuiltIn())
			 builtInAtoms.push_back(atom_counter);
		 else if(current_atom->getAggregateElementsSize()>0)
			 aggregatesAtoms.push_back(atom_counter);
	}
}

void OrderRule::order() {
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
	if(negativeAtoms.size()>0)
		assert_msg(true, "RULE IS UNSAFE");
	// Second, solve the cyclic dependency
	while(builtInAtoms.size()>0 || aggregatesAtoms.size()>0){
		unsigned sizeBuiltIns=builtInAtoms.size();
		unlockAtoms(builtInAtoms);
		if(builtInAtoms.size()==sizeBuiltIns){
			unsigned sizeAggregates=aggregatesAtoms.size();
			unlockAtoms(aggregatesAtoms);
			if(aggregatesAtoms.size()==sizeAggregates)
				assert_msg(true, "RULE IS UNSAFE");
		}
	}
	// Finally, set the ordered body as the body of the rule
	rule->setBody(orderedBody);
//	cout<<"----------- BODY ORDERED ---------------"<<endl;
//	for(auto atom: orderedBody){
//		atom->print();cout<<" ";
//	}
//	cout<<endl<<"----------------------------------------"<<endl;
}

void OrderRule::addSafeVariablesInAtom(Atom* atom, unsigned pos) {
	set_term variables=mapAtomsVariables[pos];
	for(auto variable: variables)
		safeVariables.insert(variable);
	orderedBody.push_back(atom);
}

void OrderRule::unlockAtoms(list<unsigned>& atoms) {
	vector<list<unsigned>::iterator> atomsUnlocked;
	unsigned atom_counter=0;
	for(auto it=atoms.begin();it!=atoms.end();++it,++atom_counter){
		Atom* atom=rule->getAtomInBody(*it);
		set_term variables=mapAtomsVariables[*it];
		// If the atom is negative or is not an assignment
		// then if every variable is safe, the atom is safe
		// and thus it can be added to the new body
		if(atom->isNegative() || (atom->isBuiltIn() && atom->getBinop()!=Binop::EQUAL) || (atom->getAggregateElementsSize()>0))
			lookForVariablesUnsafe(variables, atom, it, atomsUnlocked);
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
				orderedBody.push_back(atom);
				atomsUnlocked.push_back(it);
				safeVariables.insert(bindVariable);
				atom->setAssignment(true);
			}
		}
		if(atom->getAggregateElementsSize()>0 && atom->getFirstBinop()==EQUAL && !safeVariables.count(atom->getFirstGuard())){
			safeVariables.insert(atom->getFirstGuard());
			atom->setAssignment(true);
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

} /* namespace grounder */
} /* namespace DLV2 */

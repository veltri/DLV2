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
		if(current_atom->isClassicalLiteral() && current_atom->isNegative())
			 negativeAtoms.push_back(atom_counter);
		 else if(current_atom->isBuiltIn())
			 builtInAtoms.push_back(atom_counter);
		 else if(current_atom->isAggregateAtom())
			 aggregatesAtoms.push_back(atom_counter);
	}
}

bool OrderRule::order() {
	// A first attempt to order the body ignoring cyclic dependencies
	// by iterating the atoms in the body and resolving their dependencies when are not cyclic
	unsigned atom_counter=0;
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom,++atom_counter){
		Atom* current_atom=*atom;
		if(current_atom->isClassicalLiteral() && !current_atom->isNegative()){
			addSafeVariablesInAtom(current_atom, atom_counter);
			unlockAtoms(negativeAtoms);
			unlockAtoms(builtInAtoms);
		}
	}

	// Second, solve the cyclic dependencies
	while(builtInAtoms.size()>0 || negativeAtoms.size()>0|| aggregatesAtoms.size()>0){
		unsigned sizeBuiltIns=builtInAtoms.size();
		unsigned sizeNegatives=negativeAtoms.size();
		unlockAtoms(negativeAtoms);
		unlockAtoms(builtInAtoms);
		if(builtInAtoms.size()==sizeBuiltIns && sizeNegatives==negativeAtoms.size()){
			unsigned sizeAggregates=aggregatesAtoms.size();
			unlockAtoms(aggregatesAtoms);
			if(aggregatesAtoms.size()==sizeAggregates)
				return false;
		}
	}

	// Finally, set the ordered body as the body of the rule
	rule->setBody(orderedBody);

	// Check head safety once that the safe variables are known
	return checkHeadSafety();

}

bool OrderRule::checkHeadSafety(){
	set_term variableToCheck;
	for(auto atom=rule->getBeginHead();atom!=rule->getEndHead();++atom){
		//TODO Add check safety to choice
		if((*atom)->isChoice())continue;
		set_term tempVariables=(*atom)->getVariable();
		variableToCheck.insert(tempVariables.begin(),tempVariables.end());
	}
	if(safeVariables.size()<variableToCheck.size())
		return false;
	for(auto variable:variableToCheck)
		if(!safeVariables.count(variable))
			return false;
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
	if (!mapVariablesAtoms.count(bindVariable)){
		mapVariablesAtoms.insert( { bindVariable, orderedBody.size()-1 });
	}
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
		if(atom->isNegative() || (atom->isBuiltIn() && atom->getBinop()!=Binop::EQUAL) || (atom->isAggregateAtom())){
			bool containsUnsafe=lookForVariablesUnsafe(variables, atom, it, atomsUnlocked);
			//Moreover if it is an assignment aggregate the bind variable must be inserted into the safeVariables
			if(!containsUnsafe && !atom->isNegative() && atom->isAggregateAtom() && atom->getFirstBinop()==EQUAL && !safeVariables.count(atom->getFirstGuard())){
				Term* bindVariable=atom->getFirstGuard();
				foundAnAssigment(atom, bindVariable,*it);
			}
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
		if (!atom->isAggregateAtom())
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

bool OrderRule::lookForVariablesUnsafe(set_term& variables,Atom* atom, list<unsigned>::iterator it, vector<list<unsigned>::iterator>& atomsUnlocked){
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

	return foundAnUnsafeVar;
}

vector<pair<unsigned int, Atom*>> OrderRule::getAtomsFromWhichDepends(unsigned atom_position) const {
	vector<pair<unsigned int, Atom*>> atoms;
	atoms.reserve(orderedBody.size());
	for(auto atom_pos: bindAtomsDependency[atom_position])
		atoms.push_back({atom_pos,orderedBody[atom_pos]});
	return atoms;
}

} /* namespace grounder */
} /* namespace DLV2 */

/*
 * InputRewriter.cpp
 *
 *  Created on: 18/feb/2015
 *      Author: tesi2
 */

#include "InputRewriter.h"
#include "../table/IdGenerator.h"
#include "../atom/AggregateAtom.h"
#include "../../util/Utils.h"

namespace DLV2 {
namespace grounder {

const string AUXILIARY="aux";

const string SEPARATOR="_";

Atom* InputRewriter::generateNewAuxiliaryAtom(string& predicate_name, vector<Term*>& terms) {
	Predicate* predicate=new Predicate(predicate_name,terms.size());
	predicateTable->getInstance()->insertPredicate(predicate);
	predicateExtTable->addPredicateExt(predicate);
	Atom* auxiliaryAtom=new ClassicalLiteral(predicate,terms,false,false);

	return auxiliaryAtom;
}

void BaseInputRewriter::translateAggregate(Rule* r, vector<Rule*>& ruleRewrited, const OrderRule& orderRule) {

	/// First, auxiliary rules for aggregates elements are generated
	vector<unsigned int> aggregateAtoms;
	unsigned int index_atom=0;
	for(auto it=r->getBeginBody();it!=r->getEndBody();++it,++index_atom){
		unsigned aggElementsSize=(*it)->getAggregateElementsSize();
		if(aggElementsSize>0){
			AggregateAtom* aggregate=dynamic_cast<AggregateAtom*>(*it);
			set_term variablesRule=aggregate->getSharedVariable(r);
			aggregateAtoms.push_back(index_atom);
			unsigned id=IdGenerator::getInstance()->getId();
			unsigned counter=1;
			for(unsigned i=0;i<aggElementsSize;++i){
				AggregateElement* aggElem=(*it)->getAggregateElement(i);

				vector<Term*> terms;

				//For each variable in the aggregate element and in the rule add in head of auxiliary rule
				set_term variablesAggElem=getVariablesInAggregateElem((*it)->getAggregateElement(i));
				for(auto term:variablesAggElem)
					if(variablesRule.count(term))
						terms.push_back(term);

				terms.insert(terms.end(),aggElem->getTerms().begin(),aggElem->getTerms().end());

				// Avoid the rewriting if there is just one aggregate element and the rewritten atom will have have the same number of terms of the only atom
				// contained in the aggregate element
				if(aggElem->getNafLiteralsSize()<2 && terms.size()==aggElem->getNafLiteral(0)->getTermsSize()) continue;

				Rule* rule=new Rule;
				vector<Atom*> atoms=aggElem->getNafLiterals();

				set_term unsafeVars=aggElem->getUnsafeVariable();
				chooseBestSaviorForAggregate(r,aggElem,unsafeVars,atoms,orderRule);

				rule->addInBody(atoms.begin(),atoms.end());

				string predicate_name=AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+to_string(counter);
				Atom *auxiliaryAtom=generateNewAuxiliaryAtom(predicate_name,terms);

				rule->addInHead(auxiliaryAtom);
				counter++;
				ruleRewrited.push_back(rule);
				Atom* atomClone=auxiliaryAtom->clone();
				vector<Atom*> newAggElem;
				newAggElem.push_back(atomClone);
				aggElem->setNafLiterals(newAggElem);
			}
		}
	}

}

void BaseInputRewriter::chooseBestSaviorForAggregate(Rule* rule, AggregateElement* aggregateElement, set_term& unsafeVars, vector<Atom*>& atomToAdd, const OrderRule& orderRule) {
	unsigned int index_atom=0;
	list<Atom*> possibleAtomsBinding;
	for(auto var:unsafeVars){
		for(auto it=rule->getBeginBody();it!=rule->getEndBody();++it,++index_atom){
			Atom* atom=*it;
			set_term variables; //TODO togliere dal for o fare cache
			if (atom->isAggregateAtom()){
				if(atom->getFirstBinop()==Binop::EQUAL){
					AggregateAtom* aggregate=dynamic_cast<AggregateAtom*>(atom);
					variables=aggregate->getGuardVariable();
				}
			}
			else if (atom->isBuiltIn()){
				if (atom->getBinop()==Binop::EQUAL)
					variables=atom->getVariable();
			}
			else if (atom->isClassicalLiteral() && !atom->isNegative())
				variables=atom->getVariable();
			if(variables.count(var) && saviourChoosingPolicy->choose(atom,index_atom,possibleAtomsBinding,atomToAdd,(it==rule->getEndBody()-1), orderRule))
				break;
		}
	}
}

set_term BaseInputRewriter::getVariablesInAggregateElem(AggregateElement* aggregateElem){
	set_term variables;
	Atom::getVariables(aggregateElem->getNafLiterals(),variables);
	for(auto term:aggregateElem->getTerms())variables.erase(term);
	return variables;
}

void BaseInputRewriter::translateChoice(Rule* rule,vector<Rule*>& ruleRewrited) {

	unsigned id=IdGenerator::getInstance()->getId();
	unsigned counter=1;

	// Create an auxiliary rule in order to ground the body only once.
	// First the variables shared between the atoms in the body
	// and the choice atom are found, these variables will be
	// the term of the auxiliary atom in the head of the auxiliary rule

	Atom* choice =rule->getAtomInHead(0);
	set_term variables_in_choice=choice->getVariable();
	set_term variables_in_body;

	for(unsigned i=0;i<rule->getSizeBody();++i){
		auto atom=rule->getAtomInBody(i);
		if(atom->isNegative())continue;
		set_term variables;
		if(atom->isAggregateAtom())
			variables=atom->getGuardVariable();
		else
			variables=atom->getVariable();
		variables_in_body.insert(variables.begin(),variables.end());
	}

	set_term variables_intersection;
	Utils::intersectionSet(variables_in_choice,variables_in_body,variables_intersection);

	Rule * body_rule=new Rule;

	if(rule->isMustBeRewritedForAggregates()) body_rule->setMustBeRewritedForAggregates(true);

	//Body
	body_rule->setBody(rule->getBody());

	//Head
	string predicate_name=AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+to_string(counter);
	vector<Term*> terms(variables_intersection.begin(),variables_intersection.end());
	Atom *auxiliaryAtomBody=generateNewAuxiliaryAtom(predicate_name,terms);
	body_rule->addInHead(auxiliaryAtomBody);

	ruleRewrited.push_back(body_rule);
	counter++;

	// For each choice element a new disjunctive auxiliary rule is created.
	// Each rule has in the head a disjunction with a the first atom of the choice element and a new auxiliary atom
	// having the same terms of the first atom, while in the body it contains the remaining atoms of the choice element
	// and the auxiliary atom previously created for the body.

	// Also, the aggregate elements for the constraint rule are created (see below)
	vector<AggregateElement*> elements;

	for(unsigned i=0;i<choice->getChoiceElementsSize();++i){

		ChoiceElement* choiceElement=choice->getChoiceElement(i);

		Rule * aux_rule=new Rule;

		//Head
		Atom* first_atom=choiceElement->getFirstAtom();
		aux_rule->addInHead(first_atom);
		string predicate_name=AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+to_string(counter);
		vector<Term*> terms=first_atom->getTerms();
		Atom *auxiliaryAtom=generateNewAuxiliaryAtom(predicate_name,terms);
		aux_rule->addInHead(auxiliaryAtom);

		//Body
		vector<Atom*> naf_elements;
		choiceElement->getNafAtoms(naf_elements);
		aux_rule->addInBody(naf_elements);
		aux_rule->addInBody(auxiliaryAtomBody->clone());

		ruleRewrited.push_back(aux_rule);
		counter++;

		// Create a new aggregate element
		AggregateElement * element=new AggregateElement(first_atom->clone(),first_atom->getTerms());
		elements.push_back(element);
	}

	// Finally a constraint rule is created.
	// It has as body the auxiliary atom previously created for the body, and a negated count aggregate
	// whose guard are the same of the choice atom and inside contains the first atom of each choice element
	// and as aggregate terms all its terms

	Rule * constraint_aux_rule=new Rule;

	//Body
	constraint_aux_rule->addInBody(auxiliaryAtomBody->clone());
	Atom *aggregate_atom=new AggregateAtom;
	aggregate_atom->copyGuard(choice);
	aggregate_atom->setNegative(true);
	aggregate_atom->setAggregateFunction(AggregateFunction::COUNT);
	aggregate_atom->setAggregateElements(elements);
	constraint_aux_rule->addInBody(aggregate_atom);

	ruleRewrited.push_back(constraint_aux_rule);

	//TODO add delete for rule
}

void FirstSaviorChoosingPolicy::getRecursiveDependencies(const OrderRule& orderRule, unsigned savior_pos, vector<Atom*>& atomToAdd) {
	vector<pair<unsigned int, Atom*>> atomDependencies = orderRule.getAtomsFromWhichDepends(savior_pos);
	for (unsigned int i=0;i<atomDependencies.size();++i) {
		atomToAdd.push_back(atomDependencies[i].second->clone());
		getRecursiveDependencies(orderRule,atomDependencies[i].first,atomToAdd);
	}
}

bool FirstSaviorChoosingPolicy::choose(Atom* atom,unsigned savior_pos,list<Atom*>& possibleAtomsBinding, vector<Atom*>& atomToAdd, bool end, const OrderRule& orderRule) {
	atomToAdd.push_back(atom->clone());
	getRecursiveDependencies(orderRule, savior_pos, atomToAdd);
	return true;

	possibleAtomsBinding.push_back(atom);
	return false;
}

} /* namespace grounder */
} /* namespace DLV2 */



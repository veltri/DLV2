/*
 * InputRewriter.cpp
 *
 *  Created on: 18/feb/2015
 *      Author: tesi2
 */

#include "InputRewriter.h"
#include "../table/IdGenerator.h"
#include "../atom/AggregateAtom.h"

namespace DLV2 {
namespace grounder {

const string AUXILIARY="aux";

const string SEPARATOR="_";

void BaseInputRewriter::translateAggregate(Rule* r, vector<Rule*>& ruleRewrited) {

	/// First, auxiliary rules for aggregates elements are generated
	vector<unsigned int> aggregateAtoms;
	unsigned int index_atom=0;
	for(auto it=r->getBeginBody();it!=r->getEndBody();it++,index_atom++){
		unsigned aggElementsSize=(*it)->getAggregateElementsSize();
		if(aggElementsSize>0){
			AggregateAtom* aggregate=dynamic_cast<AggregateAtom*>(*it);
			set_term variablesRule=aggregate->getSharedVariable(r);
			aggregateAtoms.push_back(index_atom);
			unsigned id=IdGenerator::getInstance()->getId();
			unsigned counter=1;
			for(unsigned i=0;i<aggElementsSize;++i){
				vector<Term*> terms=(*it)->getAggregateElement(i)->getTerms();

				//For each variable in the aggregate element and in the rule add in head of auxiliary rule
				set_term variablesAggElem=getVariablesInAggregateElem((*it)->getAggregateElement(i));
				for(auto term:variablesAggElem)
					if(variablesRule.count(term))
						terms.push_back(term);

				Rule* rule=new Rule;
				vector<Atom*> atoms=(*it)->getAggregateElement(i)->getNafLiterals();

				rule->addInBody(atoms.begin(),atoms.end());
				string predName=AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+to_string(counter);
				Predicate* predicate=new Predicate(predName,terms.size());
				predicateTable->getInstance()->insertPredicate(predicate);
				predicateExtTable->addPredicateExt(predicate);
				Atom* auxiliaryAtom=new ClassicalLiteral(predicate,terms,false,false);
				rule->addInHead(auxiliaryAtom);
				counter++;
				ruleRewrited.push_back(rule);
				Atom* atomClone=auxiliaryAtom->clone();
				vector<Atom*> newAggElem;
				newAggElem.push_back(atomClone);
				(*it)->getAggregateElement(i)->setNafLiterals(newAggElem);

				rule->print();

			}
		}
	}


	ruleRewrited.push_back(r);
}

set_term BaseInputRewriter::getVariablesInAggregateElem(AggregateElement* aggregateElem){
	set_term variables;
	Atom::getVariables(aggregateElem->getNafLiterals(),variables);
	for(auto term:aggregateElem->getTerms())variables.erase(term);
	return variables;
}

} /* namespace grounder */
} /* namespace DLV2 */

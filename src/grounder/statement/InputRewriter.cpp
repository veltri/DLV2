/*
 * InputRewriter.cpp
 *
 *  Created on: 18/feb/2015
 *      Author: tesi2
 */

#include "InputRewriter.h"
#include "../table/IdGenerator.h"

namespace DLV2 {
namespace grounder {

const string AUXILIARY="#aux";

void BaseInputRewriter::translateAggregate(Rule* r, vector<Rule*>& ruleRewrited) {

	set_term variablesRule=getVariablesInClassicalLit(r);

	/// First, auxiliary rules for aggregates elements are generated
	for(auto it=r->getBeginBody();it!=r->getEndBody();it++){
		unsigned aggElementsSize=(*it)->getAggregateElementsSize();
		if(aggElementsSize>0){
			unsigned id=IdGenerator::getInstance()->getId();
			unsigned counter=1;
			for(unsigned i=0;i<aggElementsSize;++i){
				vector<Term*> terms=(*it)->getAggregateElement(i)->getTerms();

				//For each variable in the aggregate element and in the rule add in head of auxiliary rule
				set_term variablesAggElem=getVariablesInAggregateElem((*it)->getAggregateElement(i));
				for(auto term:variablesAggElem)if(variablesRule.count(term))terms.push_back(term);


				Rule* rule=new Rule;
				vector<Atom*> atoms=(*it)->getAggregateElement(i)->getNafLiterals();



				rule->addInBody(atoms.begin(),atoms.end());
				string predName=AUXILIARY+"."+to_string(id)+"."+to_string(counter);
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
			}
		}
	}

	ruleRewrited.push_back(r);
//	cout<<"AAA"<<endl;
//	for(auto r:ruleRewrited){
//		r->print();
//	}
}

set_term BaseInputRewriter::getVariablesInClassicalLit(Rule* rule){
	set_term variables;
	for(auto atom=rule->getBeginBody();atom!=rule->getEndBody();++atom){
		if((*atom)->getAggregateElementsSize()==0)
			Atom::getVariables(*atom,variables);
	}
	return variables;
}
set_term BaseInputRewriter::getVariablesInAggregateElem(AggregateElement* aggregateElem){
	set_term variables;
	Atom::getVariables(aggregateElem->getNafLiterals(),variables);
	for(auto term:aggregateElem->getTerms())variables.erase(term);
	return variables;
}

} /* namespace grounder */
} /* namespace DLV2 */


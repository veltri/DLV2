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

void BaseInputRewriter::translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited) {

	/// First, auxiliary rules for aggregates elements are generated
	for(auto it=rule->getBeginBody();it!=rule->getEndBody();it++){
		vector<AggregateElement> aggElements=(*it)->getAggregateElements();
		if(aggElements.size()>0){
			unsigned id=IdGenerator::getInstance()->getId();
			unsigned counter=1;
			for(auto& aggElem:aggElements){
				Rule* rule=new Rule;
				vector<Atom*> atoms=aggElem.getNafLiterals();
				vector<Term*> terms=aggElem.getTerms();
				rule->addInBody(atoms.begin(),atoms.end());
				string predName=AUXILIARY+"."+to_string(id)+".1."+to_string(counter);
				Predicate* predicate=new Predicate(predName,terms.size());
				predicateTable->getInstance()->insertPredicate(predicate);
				predicateExtTable->addPredicateExt(predicate);
				Atom* auxiliaryAtom=new ClassicalLiteral(predicate,terms,false,false);
				rule->addInHead(auxiliaryAtom);
				counter++;
				ruleRewrited.push_back(rule);
			}
		}
	}

	/// Second, rules with weight constraints are generated
	// TODO set the guard properly

	for(auto r:ruleRewrited){
		r->print();
	}

}

} /* namespace grounder */
} /* namespace DLV2 */


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

	/// First, auxiliary rules for aggregates elements are generated
	for(auto it=r->getBeginBody();it!=r->getEndBody();it++){
		unsigned aggElementsSize=(*it)->getAggregateElementsSize();
		if(aggElementsSize>0){
			unsigned id=IdGenerator::getInstance()->getId();
			unsigned counter=1;
			for(unsigned i=0;i<aggElementsSize;++i){
				Rule* rule=new Rule;
				vector<Atom*> atoms=(*it)->getAggregateElement(i)->getNafLiterals();
				vector<Term*> terms=(*it)->getAggregateElement(i)->getTerms();
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
				(*it)->setAggregateElement(i,newAggElem);
			}
		}
	}

	ruleRewrited.push_back(r);
//	cout<<"AAA"<<endl;
//	for(auto r:ruleRewrited){
//		r->print();
//	}
}

} /* namespace grounder */
} /* namespace DLV2 */


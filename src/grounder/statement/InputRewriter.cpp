/*
 * InputRewriter.cpp
 *
 *  Created on: 18/feb/2015
 *      Author: tesi2
 */

#include "InputRewriter.h"
#include "../table/IdGenerator.h"
#include "../term/ConstantTerm.h"
#include "../atom/WeightConstraint.h"
#include "../term/VariableTerm.h"
#include "../term/ArithTerm.h"

namespace DLV2 {
namespace grounder {


const string AUXILIARY="#aux";

void BaseInputRewriter::translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited) {

	/// First, auxiliary rules for aggregates elements are generated
	for(auto it=rule->getBeginBody();it!=rule->getEndBody();it++){
		vector<AggregateElement> aggElements=(*it)->getAggregateElements();
		if(aggElements.size()>0){
			//Atom that represent the aggregate
			Atom* rewritedAggregateAtom;
			unsigned id=IdGenerator::getInstance()->getId();
			unsigned counter=1;
			vector<pair<Atom*,Term*>> weightAtoms;
			Term * one_term=new NumericConstantTerm(false,1);
			TermTable::getInstance()->addTerm(one_term);
			for(auto& aggElem:aggElements){
				//Generation of set

				Rule* rule=new Rule;
				vector<Atom*> atoms=aggElem.getNafLiterals();
				vector<Term*> terms=aggElem.getTerms();
				rule->addInBody(atoms.begin(),atoms.end());

				Predicate* predicate=getPredicate(AUXILIARY+"."+to_string(id)+".1."+to_string(counter),terms.size());

				Atom* auxiliaryAtom=new ClassicalLiteral(predicate,terms,false,false);
				rule->addInHead(auxiliaryAtom);
				counter++;
				ruleRewrited.push_back(rule);

				if((*it)->getAggregateFunction()==AggregateFunction::COUNT)
					weightAtoms.push_back({auxiliaryAtom,one_term});
				else if((*it)->getAggregateFunction()==AggregateFunction::SUM)
					weightAtoms.push_back({auxiliaryAtom,auxiliaryAtom->getTerm(0)});

			}

			if((*it)->getFirstBinop()!=Binop::EQUAL && (*it)->getSecondBinop()!=Binop::EQUAL){
				Rule* rule=new Rule;
				Rule* aggregateRule=new Rule;

				Predicate* predicate=getPredicate(AUXILIARY+"."+to_string(id),0);

				rewritedAggregateAtom=new ClassicalLiteral(predicate,false,false);
				aggregateRule->addInHead(rewritedAggregateAtom);

				//Rule for lower guard
				Term *lowerGuard=(*it)->getLowerGuard();
				if(lowerGuard!=nullptr){
					Predicate* predicate=getPredicate(AUXILIARY+"."+to_string(id)+".2.1",0);
					Atom* auxiliaryAtom=new ClassicalLiteral(predicate,false,false);
					rule->addInHead(auxiliaryAtom);

					Atom *auxiliaryWeightAtom=new WeightConstraint(lowerGuard,weightAtoms);
					rule->addInBody(auxiliaryWeightAtom);
					ruleRewrited.push_back(rule);

					aggregateRule->addInBody(auxiliaryAtom);
				}

				//Rule for upper guard
				Term *upperGuard=(*it)->getUpperGuard();
				if(upperGuard!=nullptr){
					rule = new Rule;

					Predicate* predicate=getPredicate(AUXILIARY+"."+to_string(id)+".2.2",0);
					Atom* auxiliaryAtom=new ClassicalLiteral(predicate,false,false);
					rule->addInHead(auxiliaryAtom);

					Atom *auxiliaryWeightAtom=new WeightConstraint(upperGuard,weightAtoms);
					rule->addInBody(auxiliaryWeightAtom);

					ruleRewrited.push_back(rule);

					//set the auxiliary to false (Upper guard)
					auxiliaryAtom=new ClassicalLiteral(predicate,false,true);
					aggregateRule->addInBody(auxiliaryAtom);
				}

				ruleRewrited.push_back(aggregateRule);



			} else{
				//Aggregate with = Variable

				Rule* rule=new Rule;

				//Find the variable
				Term* variableTerm = nullptr;
				if((*it)->getLowerGuard()!=nullptr){
					variableTerm=(*it)->getLowerGuard();
				}else
					variableTerm=(*it)->getUpperGuard();

				//Generate WC rule

				Predicate* predicate=getPredicate(AUXILIARY+"."+to_string(id)+".2",1);

				vector<Term*> terms({variableTerm});
				Atom* auxiliaryAtom=new ClassicalLiteral(predicate,terms,false,false);
				rule->addInHead(auxiliaryAtom);

				Atom *auxiliaryWeightAtom=new WeightConstraint(variableTerm,weightAtoms);
				rule->addInBody(auxiliaryWeightAtom);

				ruleRewrited.push_back(rule);


				//Generate the lower not upper rule
				rule= new Rule;

				predicate=getPredicate(AUXILIARY+"."+to_string(id),1);
				//Reset the terms (moved previously)
				terms ={variableTerm};
				rewritedAggregateAtom = new ClassicalLiteral(predicate,terms,false,false);

				rule->addInHead(rewritedAggregateAtom);

				rule->addInBody(auxiliaryAtom);
				//Generate arith term (variable +1)
				vector<Term*> arith({variableTerm,one_term});
				vector<Operator> operators({Operator::PLUS});
				Term *arithTerm = new ArithTerm(false,operators,arith);
				vector<Term*> terms2({arithTerm});
				auxiliaryAtom=new ClassicalLiteral(auxiliaryAtom->getPredicate(),terms2,false,true);
				rule->addInBody(auxiliaryAtom);

				ruleRewrited.push_back(rule);



			}


			delete (*it);
			(*it)=rewritedAggregateAtom;
		}

	}

	/// Second, rules with weight constraints are generated
	// TODO set the guard properly

	for(auto r:ruleRewrited){
		r->print();
	}
	rule->print();

}

Predicate* BaseInputRewriter::getPredicate(string name,int arity){
	Predicate* predicate=new Predicate(name,arity);
	predicateTable->getInstance()->insertPredicate(predicate);
	predicateExtTable->addPredicateExt(predicate);
	return predicate;
}

} /* namespace grounder */
} /* namespace DLV2 */


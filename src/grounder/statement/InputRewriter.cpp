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
const string SEPARATOR=".";

void BaseInputRewriter::translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited) {
	Term * one_term=new NumericConstantTerm(false,1);
	TermTable::getInstance()->addTerm(one_term);

	for(auto it=rule->getBeginBody();it!=rule->getEndBody();it++){
		vector<AggregateElement> aggElements=(*it)->getAggregateElements();
		if(aggElements.size()>0){
			if((*it)->getLowerGuard()!=0 && (*it)->getUpperGuard()!=0 &&
					(*it)->getLowerGuard()->getConstantValue()>(*it)->getUpperGuard()->getConstantValue()){
				delete rule;
				for(auto rule:ruleRewrited)
					delete rule;
				ruleRewrited.clear();
				return;
			}
			//Atom that represent the aggregate
			Atom* rewritedAggregateAtom;
			unsigned id=IdGenerator::getInstance()->getId();
			unsigned counter=1;
			vector<pair<Atom*,Term*>> weightAtoms;

			/// First, auxiliary rules for aggregates elements are generated
			for(auto& aggElem:aggElements){
				Rule* aggElementRrule=new Rule;

				vector<Atom*> atoms=aggElem.getNafLiterals();
				vector<Term*> terms=aggElem.getTerms();
				aggElementRrule->addInBody(atoms.begin(),atoms.end());

				Predicate* predicate=createPredicate(AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+"1"+SEPARATOR+to_string(counter),terms.size());
				Atom* auxiliaryAtom=new ClassicalLiteral(predicate,terms,false,false);
				aggElementRrule->addInHead(auxiliaryAtom);

				counter++;
				ruleRewrited.push_back(aggElementRrule);

				if((*it)->getAggregateFunction()==AggregateFunction::COUNT)
					weightAtoms.push_back({auxiliaryAtom,one_term});
				else if((*it)->getAggregateFunction()==AggregateFunction::SUM)
					weightAtoms.push_back({auxiliaryAtom,auxiliaryAtom->getTerm(0)});

			}

			if((*it)->getFirstBinop()!=Binop::EQUAL && (*it)->getSecondBinop()!=Binop::EQUAL){

				///Set the head of aggregateRule
				Rule* aggregateRule=new Rule;
				Predicate* predicate=createPredicate(AUXILIARY+SEPARATOR+to_string(id),0);
				rewritedAggregateAtom=new ClassicalLiteral(predicate,false,false);
				aggregateRule->addInHead(rewritedAggregateAtom);

				//Rule for the lower guard
				Term *lowerGuard=(*it)->getLowerGuard();
				if(lowerGuard!=nullptr){

					Predicate* predicate=createPredicate(AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+"1"+SEPARATOR+"2",0);
					Atom* auxiliaryAtom=new ClassicalLiteral(predicate,false,false);

					Rule* guardRule=generateGuardRule(auxiliaryAtom,lowerGuard,weightAtoms);
					ruleRewrited.push_back(guardRule);

					aggregateRule->addInBody(auxiliaryAtom);
				}

				//Rule for the upper guard
				Term *upperGuard=(*it)->getUpperGuard();
				if(upperGuard!=nullptr){

					Predicate* predicate=createPredicate(AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+"2"+SEPARATOR+"2",0);
					Atom* auxiliaryAtom=new ClassicalLiteral(predicate,false,false);

					Rule* guardRule=generateGuardRule(auxiliaryAtom,upperGuard,weightAtoms);
					ruleRewrited.push_back(guardRule);

					//The auxiliary atom for the upper guard has to be negated
					auxiliaryAtom=new ClassicalLiteral(predicate,false,true);
					aggregateRule->addInBody(auxiliaryAtom);
				}

				ruleRewrited.push_back(aggregateRule);

			} else{ //Aggregate with = Variable

				//Find the variable among the guards
				Term* variableTerm = nullptr;
				if((*it)->getLowerGuard()!=nullptr){
					variableTerm=(*it)->getLowerGuard();
				}else
					variableTerm=(*it)->getUpperGuard();

				//Generate the WeightConstraint rule
				Rule* rule=new Rule;
				Predicate* predicate=createPredicate(AUXILIARY+SEPARATOR+to_string(id)+SEPARATOR+"2",1);
				vector<Term*> terms({variableTerm});
				Atom* auxiliaryAtom=new ClassicalLiteral(predicate,terms,false,false);
				rule->addInHead(auxiliaryAtom);
				Atom *auxiliaryWeightAtom=new WeightConstraint(variableTerm,weightAtoms);
				rule->addInBody(auxiliaryWeightAtom);
				ruleRewrited.push_back(rule);

				//Generate just the rule for the lower (not for the upper one)
				rule= new Rule;
				predicate=createPredicate(AUXILIARY+SEPARATOR+to_string(id),1);
				terms ={variableTerm}; //Reset the terms (moved previously)
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

			if((*it)->isNegative())
				rewritedAggregateAtom=new ClassicalLiteral(rewritedAggregateAtom->getPredicate(),false,true);
			delete (*it);
			(*it)=rewritedAggregateAtom;

		}
	}

	ruleRewrited.push_back(rule);
	for(auto r:ruleRewrited){
		r->print();
	}
}

Predicate* BaseInputRewriter::createPredicate(string name,int arity){
	Predicate* predicate=new Predicate(name,arity);
	predicateTable->getInstance()->insertPredicate(predicate);
	predicateExtTable->addPredicateExt(predicate);
	return predicate;
}

Rule* BaseInputRewriter::generateGuardRule(Atom* auxiliaryAtom,Term* guard,const vector<pair<Atom*,Term*>>& weightAtoms){
	Rule* guardRule = new Rule;
	guardRule->addInHead(auxiliaryAtom);
	Atom *auxiliaryWeightAtom=new WeightConstraint(guard,weightAtoms);
	guardRule->addInBody(auxiliaryWeightAtom);
	return guardRule;
}

} /* namespace grounder */
} /* namespace DLV2 */


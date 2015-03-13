/*
 * AggregateAtom.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "AggregateAtom.h"
#include "../../util/Assert.h"
#include "../table/PredicateExtension.h"
using namespace std;

namespace DLV2{
namespace grounder{


size_t AggregateAtom::hash() {
	return 0; //TODO
}

bool AggregateAtom::operator ==(const Atom& a) {
	return false; //TODO
}


void AggregateAtom::ground(map_term_term& substritutionTerm, Atom*& templateAtom) {
	//Ground guard
	Term* template_lowerGueard=nullptr,*template_upperGueard=nullptr;
	if(firstBinop!=NONE_OP)
		template_lowerGueard=lowerGueard->substitute(substritutionTerm);
	if(secondBinop!=NONE_OP)
		template_upperGueard=upperGuard->substitute(substritutionTerm);
	assert_msg(((firstBinop==NONE_OP ||template_lowerGueard->isGround()  )  && (secondBinop==NONE_OP || template_upperGueard->isGround())),"Arith term not safe");
	if(templateAtom==nullptr){
		//Ground Aggregate Element
		vector<AggregateElement*> template_aggregate_element;
		for(auto& agg_element:aggregateElements){
			AggregateElement *newElement=new AggregateElement;
			//Set all terms of aggregate in the new aggregate
			newElement->setTerms(agg_element->getTerms());
			//For each aggregate element ground the naf of the aggregate element and push
			//in the new aggregate element
			for(auto atom_agg_element:agg_element->getNafLiterals()){
				Atom *groundAtom=nullptr;
				atom_agg_element->ground(substritutionTerm,groundAtom);
				newElement->addNafLiterals(groundAtom);
			}
			template_aggregate_element.push_back(newElement);
		}
		templateAtom=new AggregateAtom(template_lowerGueard,firstBinop,template_upperGueard,secondBinop,aggregateFunction,template_aggregate_element,negative);

	}else{
		templateAtom->setLowerGuard(template_lowerGueard);
		templateAtom->setUpperGuard(template_upperGueard);
		//Ground Aggregate Element
		for(unsigned i=0;i<templateAtom->getAggregateElementsSize();i++){
			//Set all terms of aggregate in the new aggregate
			templateAtom->getAggregateElement(i)->setTerms(aggregateElements[i]->getTerms());
			//clear all the naf literal
			templateAtom->getAggregateElement(i)->clearNafLiterals();
			//For each aggregate element ground the naf of the aggregate element and push
			//in the new aggregate element
			for(auto atom_agg_element:aggregateElements[i]->getNafLiterals()){
				Atom *groundAtom=nullptr;
				atom_agg_element->ground(substritutionTerm,groundAtom);
				templateAtom->getAggregateElement(i)->addNafLiterals(groundAtom);
			}
		}
	}
}

ResultEvaluation AggregateAtom::partialEvaluate() {
	switch (aggregateFunction) {
		case COUNT:
			return partialEvaluateCount();
			break;
		case MIN:
			return partialEvaluateMin();

			break;
		case MAX:
			return partialEvaluateMax();

			break;
		case SUM:
			return partialEvaluateSum();

			break;
		default:
			break;
	}
}

void AggregateAtom::print() {
	if(lowerGueard!=nullptr)
		lowerGueard->print();
	cout<<"#";
	if(aggregateFunction==AggregateFunction::COUNT){
		cout<<"count";
	}else if(aggregateFunction==AggregateFunction::MIN){
		cout<<"min";
	}else if(aggregateFunction==AggregateFunction::MAX){
		cout<<"max";
	}else if(aggregateFunction==AggregateFunction::SUM){
		cout<<"sum";
	}
	cout<<"{";
	bool first=true;
	bool firstElement=true;
	for(auto& element:aggregateElements){
		if(!firstElement)cout<<";";else firstElement=false;
		for(auto& term:element->getTerms()){
			if(!first)cout<<",";else first=false;
			term->print();
		}
		cout<<":";first=true;
		for(auto& naf:element->getNafLiterals()){
			if(!first)cout<<",";else first=false;
			naf->print();
		}
		first=true;
	}
	cout<<"}";
	if(upperGuard!=nullptr)
		upperGuard->print();
}

ResultEvaluation AggregateAtom::partialEvaluateCount() {
	Atom *lastAtom=aggregateElements.back()->getNafLiteral(0);
	if(!PredicateExtTable::getInstance()->getPredicateExt(lastAtom->getPredicate())->getGenericAtom(lastAtom)->isFact())
		return UNDEF;

	partialEvaluation++;

	if(firstBinop==Binop::EQUAL && lowerGueard->isGround() && partialEvaluation>lowerGueard->getConstantValue())
		return UNSATISFY;

	if(secondBinop==Binop::EQUAL && upperGuard->isGround() && partialEvaluation>upperGuard->getConstantValue())
		return UNSATISFY;

	if(secondBinop!=NONE_OP && partialEvaluation>upperGuard->getConstantValue())
		return UNSATISFY;

	if(firstBinop!=NONE_OP && secondBinop==NONE_OP && partialEvaluation>= lowerGueard->getConstantValue())
		return SATISFY;
	return UNDEF;
}

ResultEvaluation AggregateAtom::partialEvaluateMax() {
}

ResultEvaluation AggregateAtom::partialEvaluateMin() {
}

ResultEvaluation AggregateAtom::partialEvaluateSum() {
}

}}

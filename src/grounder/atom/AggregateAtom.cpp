/*
 * AggregateAtom.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "AggregateAtom.h"
#include "../../util/Assert.h"
#include "../table/PredicateExtension.h"
#include "../term/ConstantTerm.h"
#include "../term/ArithTerm.h"
#include <algorithm>

using namespace std;

namespace DLV2{
namespace grounder{

static string getBinopToStrng(Binop binop){
	switch (binop) {
		case EQUAL:
			return "=";
			break;
		case UNEQUAL:
			return "!=";
			break;
		case LESS:
			return "<";
			break;
		case LESS_OR_EQ:
			return "<=";
			break;
		case GREATER:
			return ">";
			break;
		case GREATER_OR_EQ:
			return ">=";
			break;
		default:
			return "";
			break;
	}
}

set_term AggregateAtom::getVariable(){
	set_term variables;
	if(firstBinop!= NONE_OP && firstGuard->getType()==TermType::VARIABLE)
		variables.insert(firstGuard);
	if(secondBinop != NONE_OP && secondGuard->getType()==TermType::VARIABLE)
		variables.insert(secondGuard);

	return variables;
}


size_t AggregateAtom::hash() {
	return 0; //TODO
}

bool AggregateAtom::operator ==(const Atom& a) {
	return false; //TODO
}


void AggregateAtom::ground(map_term_term& substritutionTerm, Atom*& templateAtom) {
	//Ground guard
	Term* template_lowerGueard=nullptr,*template_upperGueard=nullptr;
	if(firstBinop!=NONE_OP){
		template_lowerGueard=firstGuard->substitute(substritutionTerm);
		if(template_lowerGueard->isGround() && firstGuard->contain(TermType::ARITH))
			template_lowerGueard=template_lowerGueard->calculate();
	}
	if(secondBinop!=NONE_OP){
		template_upperGueard=secondGuard->substitute(substritutionTerm);
		if(template_upperGueard->isGround() && secondGuard->contain(TermType::ARITH))
			template_upperGueard=template_upperGueard->calculate();
	}
	assert_msg(((firstBinop==NONE_OP || firstBinop==EQUAL ||template_lowerGueard->isGround()  )  && (secondBinop==NONE_OP || secondBinop==EQUAL || template_upperGueard->isGround())),"Arith term not safe");
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
		templateAtom->setFirstGuard(template_lowerGueard);
		templateAtom->setSecondGuard(template_upperGueard);
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
	if(invalideGuards())return UNSATISFY;
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

ResultEvaluation AggregateAtom::finalEvaluation() {
	switch (aggregateFunction) {
		case COUNT:
			return finalEvaluateCount();
			break;
		case MIN:
			return finalEvaluateMin();
			break;
		case MAX:
			return finalEvaluateMax();
			break;
		case SUM:
			return finalEvaluateSum();
			break;
		default:
			break;
	}
}


ResultEvaluation AggregateAtom::partialEvaluateCount() {

	Atom *lastAtom=aggregateElements.back()->getNafLiteral(0);
	if(!PredicateExtTable::getInstance()->getPredicateExt(lastAtom->getPredicate())->getGenericAtom(lastAtom)->isFact()){
		undefAtomEvaluation++;
		return UNDEF;
	}

	partialEvaluation++;


	if(checkEqualisGreater())
		return UNSATISFY;

	if(checkSecondGuardIsGreaterEqual())
		return UNSATISFY;

	if(checkFirstGuardIsGreaterOrEqual())
		return SATISFY;

	return UNDEF;
}

ResultEvaluation AggregateAtom::partialEvaluateMax() {
	Atom *lastAtom=aggregateElements.back()->getNafLiteral(0);
	if(!PredicateExtTable::getInstance()->getPredicateExt(lastAtom->getPredicate())->getGenericAtom(lastAtom)->isFact()){
		int value=aggregateElements.back()->getTerms().front()->getConstantValue();
		if(undefAtomEvaluation<value)
			undefAtomEvaluation=value;
		return UNDEF;
	}
	int value=aggregateElements.back()->getTerms().front()->getConstantValue();
	if(partialEvaluation<value)
		partialEvaluation=value;

	if(checkEqualisGreater())
		return UNSATISFY;

	if(checkSecondGuardIsGreaterEqual())
		return UNSATISFY;

	if(checkFirstGuardIsGreaterOrEqual())
		return SATISFY;

	return UNDEF;

}

ResultEvaluation AggregateAtom::partialEvaluateMin() {
	Atom *lastAtom=aggregateElements.back()->getNafLiteral(0);
	if(!PredicateExtTable::getInstance()->getPredicateExt(lastAtom->getPredicate())->getGenericAtom(lastAtom)->isFact()){
		int value=aggregateElements.back()->getTerms().front()->getConstantValue();
		if(undefAtomEvaluation>value)
			undefAtomEvaluation=value;
		return UNDEF;
	}
	int value=aggregateElements.back()->getTerms().front()->getConstantValue();
	if(partialEvaluation>value)
		partialEvaluation=value;

	if(checkEqualisGreater())
		return UNSATISFY;

	if(checkSecondGuardIsGreaterEqual())
		return UNSATISFY;

	if(checkFirstGuardIsGreaterOrEqual())
		return SATISFY;

	return UNDEF;
}

ResultEvaluation AggregateAtom::partialEvaluateSum() {
	Atom *lastAtom=aggregateElements.back()->getNafLiteral(0);
	if(!PredicateExtTable::getInstance()->getPredicateExt(lastAtom->getPredicate())->getGenericAtom(lastAtom)->isFact()){
		undefAtomEvaluation+=aggregateElements.back()->getTerms().front()->getConstantValue();
		return UNDEF;
	}

	partialEvaluation+=aggregateElements.back()->getTerms().front()->getConstantValue();

	return UNDEF;
}

ResultEvaluation AggregateAtom::finalEvaluateCount() {

	if(checkEqualisLess())
		return UNSATISFY;

	if(checkEqualisEqual())
		return SATISFY;

	if(checkFirstGuardIsLess())
		return UNSATISFY;

	if(checkSecondGuardIsLess())
		return SATISFY;

	if(checkSecondAndFirstGuard())
		return SATISFY;

	return UNDEF;
}

ResultEvaluation AggregateAtom::finalEvaluateMax() {
	if(checkEqualisLess())
		return UNSATISFY;

	if(checkEqualisEqual())
		return SATISFY;

	if(checkFirstGuardIsLess())
		return UNSATISFY;

	if(checkSecondGuardIsLess())
		return SATISFY;

	if(checkSecondAndFirstGuard())
		return SATISFY;

	return UNDEF;
}

ResultEvaluation AggregateAtom::finalEvaluateMin() {
//	if(checkEqualisLess())
//		return UNSATISFY;
//
//	if(checkEqualisEqual())
//		return SATISFY;
//
//	if(checkFirstGuardIsLess())
//		return UNSATISFY;
//
//	if(checkSecondGuardIsLess())
//		return SATISFY;
//
//	if(checkSecondAndFirstGuard())
//		return SATISFY;

	return UNDEF;
}

ResultEvaluation AggregateAtom::finalEvaluateSum() {
	if(checkEqualisGreater() || checkEqualisLess())
		return UNSATISFY;

	if(checkEqualisEqual())
		return SATISFY;

	if(checkFirstGuardIsLess())
		return UNSATISFY;

	if(checkSecondGuardIsGreaterEqual())
		return UNSATISFY;

	if(checkFirstGuardIsGreaterOrEqual())
		return SATISFY;

	if(checkSecondGuardIsLess())
		return SATISFY;

	if(checkSecondAndFirstGuard())
		return SATISFY;

	return UNDEF;

}

void AggregateAtom::print() {
	if(negative)
		cout<<"not ";
	if(firstGuard!=nullptr){
		firstGuard->print();
		cout<<getBinopToStrng(firstBinop);
	}
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
	if(secondGuard!=nullptr){
		cout<<getBinopToStrng(secondBinop);
		secondGuard->print();
	}
}

Term* AggregateAtom::changeInStandardFormatGuard(Term* guard) {
	Term* t = nullptr;
	if (guard->getType() == TermType::NUMERIC_CONSTANT) {
		t=new NumericConstantTerm(false, guard->getConstantValue() + 1);
		TermTable::getInstance()->addTerm(t);
	}
	if (guard->getType() == TermType::VARIABLE) {
		vector<Operator> operators;
		operators.push_back(Operator::PLUS);
		vector<Term*> terms;
		terms.push_back(guard);
		Term* one_term = new NumericConstantTerm(false, 1);
		TermTable::getInstance()->addTerm(one_term);
		terms.push_back(one_term);
		t = new ArithTerm(false, operators, terms);
		TermTable::getInstance()->addTerm(t);
	}
	return t;
}

void AggregateAtom::changeInStandardFormat() {

	// If one of the binop is UNEQUAL
	if(secondBinop==NONE_OP && firstBinop==Binop::UNEQUAL){
		firstBinop=EQUAL;
		this->negative=true;
	}
	if(firstBinop==NONE_OP && secondBinop==Binop::UNEQUAL){
		firstBinop=EQUAL;
		secondBinop=NONE_OP;
		firstGuard=secondGuard;
		secondGuard=0;
		this->negative=true;
	}

	// If the second binop is an EQUAL
	if(secondBinop==Binop::EQUAL){
		firstBinop=Binop::EQUAL;
		firstGuard=secondGuard;
		secondBinop=Binop::NONE_OP;
		secondGuard=0;
	}

	// One of the following cases hold:
	// Case: 1 > x > 3 or 1 >= x > 3 or 1 > x >= 3 or 1 >= x >= 3
	// Case: x >= 3 or x > 3
	// Case: 1 > x or 1 >= x
	if((firstBinop==Binop::GREATER || firstBinop==Binop::GREATER_OR_EQ) || (secondBinop==Binop::GREATER || secondBinop==Binop::GREATER_OR_EQ)){
		Binop tmpB=firstBinop;
		firstBinop=secondBinop;
		secondBinop=tmpB;
		Term* tmpT=firstGuard;
		firstGuard=secondGuard;
		secondGuard=tmpT;
		if(firstBinop==Binop::GREATER)
			firstBinop=Binop::LESS;
		if(secondBinop==Binop::GREATER)
			secondBinop=Binop::LESS;
		if(firstBinop==Binop::GREATER_OR_EQ)
			firstBinop=Binop::LESS_OR_EQ;
		if(secondBinop==Binop::GREATER_OR_EQ)
			secondBinop=Binop::LESS_OR_EQ;
	}

	// Case: 1 < x
	if(firstBinop==Binop::LESS && firstGuard!=0){
		firstGuard=changeInStandardFormatGuard(firstGuard);
		firstBinop=Binop::LESS_OR_EQ;
	}

	// Case: x >= 1
	if(secondBinop==Binop::LESS_OR_EQ && secondGuard!=0){
		secondGuard=changeInStandardFormatGuard(secondGuard);
		secondBinop=Binop::LESS;
	}
}

bool AggregateAtom::checkEqualisGreater() {
	if(firstBinop==Binop::EQUAL && firstGuard->isGround())
		if( partialEvaluation > firstGuard->getConstantValue())
			return true;
	return false;
}

int AggregateAtom::getCheckValue() {
	int value = partialEvaluation + undefAtomEvaluation;
	switch (aggregateFunction) {
	case MAX:
		value = max(partialEvaluation, undefAtomEvaluation);
		break;
	case MIN:
		value = min(partialEvaluation, undefAtomEvaluation);
		break;
	default:
		break;
	}
	return value;
}

bool AggregateAtom::checkEqualisLess() {
	if(firstBinop==Binop::EQUAL && firstGuard->isGround()){
		int value = getCheckValue();
		if(value < firstGuard->getConstantValue())
			return true;
	}
	return false;
}


bool AggregateAtom::checkEqualisEqual() {
	if(firstBinop==Binop::EQUAL && firstGuard->isGround())
		if(firstGuard->getConstantValue()==partialEvaluation && undefAtomEvaluation==0)
			return true;
	return false;
}

bool AggregateAtom::checkFirstGuardIsGreaterOrEqual() {
	if(firstBinop==LESS_OR_EQ && secondBinop==NONE_OP && partialEvaluation>=firstGuard->getConstantValue())
		return true;
	return false;
}

bool AggregateAtom::checkFirstGuardIsLess() {
	if(firstBinop==LESS_OR_EQ){
		int value = getCheckValue();
		if(value<firstGuard->getConstantValue())return true;
	}
	return false;
}

bool AggregateAtom::checkSecondGuardIsGreaterEqual() {
	if(secondBinop==LESS && partialEvaluation>=secondGuard->getConstantValue())
		return true;
	return false;
}

bool AggregateAtom::checkSecondGuardIsLess() {
	if(secondBinop==LESS && firstBinop==NONE_OP){
		int value = getCheckValue();
		if(value<secondGuard->getConstantValue())return true;
	}
	return false;
}

bool AggregateAtom::checkSecondAndFirstGuard() {
	if(secondBinop==LESS && firstBinop==LESS_OR_EQ){
		int value = getCheckValue();
		if(value<secondGuard->getConstantValue() && partialEvaluation>=firstGuard->getConstantValue())return true;
	}
	return false;
}

}
}



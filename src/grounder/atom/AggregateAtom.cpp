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


	if(checkOperator(firstGuard,firstBinop,EQUAL,GREATER,false))
		return UNSATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,GREATER_OR_EQ,false))
		return UNSATISFY;

	if(secondBinop==NONE_OP && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,false))
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

	if(checkOperator(firstGuard,firstBinop,EQUAL,GREATER,false))
		return UNSATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,GREATER_OR_EQ,false))
		return UNSATISFY;

	if(secondBinop==NONE_OP && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,false))
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

	if(checkOperator(firstGuard,firstBinop,EQUAL,LESS,false))
		return UNSATISFY;

	if(checkOperator(firstGuard,firstBinop,LESS_OR_EQ,LESS,false))
		return UNSATISFY;

	if(firstBinop==NONE_OP && checkOperator(secondGuard,secondBinop,LESS,LESS,false))
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

	if(checkOperator(firstGuard,firstBinop,EQUAL,LESS,true))
		return UNSATISFY;

	if(undefAtomEvaluation==0 && checkOperator(firstGuard,firstBinop,EQUAL,EQUAL,false))
		return SATISFY;

	if(checkOperator(firstGuard,firstBinop,LESS_OR_EQ,LESS,true))
		return UNSATISFY;

	if(firstBinop==NONE_OP && checkOperator(secondGuard,secondBinop,LESS,LESS,true))
		return SATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,LESS,true) && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,false))
		return SATISFY;

	findUndefAtoms();
	return UNDEF;
}

ResultEvaluation AggregateAtom::finalEvaluateMax() {
	if(checkOperator(firstGuard,firstBinop,EQUAL,LESS,true))
		return UNSATISFY;

	if(undefAtomEvaluation==INT_MIN && checkOperator(firstGuard,firstBinop,EQUAL,EQUAL,false))
		return SATISFY;

	if(checkOperator(firstGuard,firstBinop,LESS_OR_EQ,LESS,true))
		return UNSATISFY;

	if(firstBinop==NONE_OP && checkOperator(secondGuard,secondBinop,LESS,LESS,true))
		return SATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,LESS,true) && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,false))
		return SATISFY;

	if(isAnAssigment()) findUndefAtoms();
	return UNDEF;
}

ResultEvaluation AggregateAtom::finalEvaluateMin() {
	if(undefAtomEvaluation == INT_MAX && checkOperator(firstGuard,firstBinop,EQUAL,EQUAL,false))
		return SATISFY;

	if(secondBinop==NONE_OP && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,true))
		return SATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,GREATER_OR_EQ,true))
		return UNSATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,LESS,false) && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,true))
		return SATISFY;

	if(isAnAssigment()) findUndefAtoms();
	return UNDEF;
}

ResultEvaluation AggregateAtom::finalEvaluateSum() {
	if(checkOperator(firstGuard,firstBinop,EQUAL,LESS,true) || checkOperator(firstGuard,firstBinop,EQUAL,GREATER,false))
		return UNSATISFY;

	if(undefAtomEvaluation==0 && checkOperator(firstGuard,firstBinop,EQUAL,EQUAL,false))
		return SATISFY;

	if(checkOperator(firstGuard,firstBinop,LESS_OR_EQ,LESS,true))
		return UNSATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,GREATER_OR_EQ,false))
		return UNSATISFY;

	if(secondBinop==NONE_OP && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,false))
		return SATISFY;

	if(firstBinop==NONE_OP && checkOperator(secondGuard,secondBinop,LESS,LESS,true))
		return SATISFY;

	if(checkOperator(secondGuard,secondBinop,LESS,LESS,true) && checkOperator(firstGuard,firstBinop,LESS_OR_EQ,GREATER_OR_EQ,false))
		return SATISFY;

	if(isAnAssigment()) findUndefAtoms();
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


bool AggregateAtom::checkOperator(Term* term,Binop binopGuard,Binop binop, Binop op, bool checkUndef) {
	if(binopGuard!=binop)return false;
	if(binop==EQUAL && !term->isGround()) return false;
	int value=partialEvaluation;
	if(checkUndef)value=getCheckValue();
	switch (op) {
		case LESS:
			if(value<term->getConstantValue())return true;
			break;
		case LESS_OR_EQ:
			if(value<=term->getConstantValue())return true;
			break;
		case GREATER:
			if(value>term->getConstantValue())return true;
			break;
		case GREATER_OR_EQ:
			if(value>=term->getConstantValue())return true;
			break;
		case EQUAL:
			if(value==term->getConstantValue())return true;
			break;
		default:
			return false;
			break;
	}
	return false;
}

void AggregateAtom::computeNextCombination(){
	for(unsigned i=current_number.size()-1;i>=0;i--){
		if(!current_number[i]){
			current_number[i]=true;
			break;
		}
		current_number[i]=false;
	}
}

void AggregateAtom::findUndefAtoms(){
	//Compute the number of undefined atoms, and store the map between their position and the position in the boolean vector
	current_number.push_back(false);
	for(unsigned i=0;i<this->aggregateElements.size();i++){
		Atom* aggElementAtom=this->aggregateElements[i]->getNafLiteral(0);
		if(!PredicateExtTable::getInstance()->getPredicateExt(aggElementAtom->getPredicate())->getGenericAtom(aggElementAtom)->isFact()){
			map_undefAtom_position.insert({map_undefAtom_position.size()+1,i});
			current_number.push_back(false);
		}
	}
}

int AggregateAtom::generateNextCombination(bool& finish){
	if(current_number.front()){
		finish=true;
		return 0;
	}
	finish=false;
	int evaluation=partialEvaluation;
	for(unsigned j=0;j<current_number.size();j++){
		if(current_number[j]){
			int x=aggregateElements[map_undefAtom_position[j]]->getTerm(0)->getConstantValue();
			applayAggregateOperator(evaluation, x);
		}
	}
	computeNextCombination();
	return evaluation;
}

void AggregateAtom::applayAggregateOperator(int& n1, int n2){
	switch (aggregateFunction) {
		case MIN:
			n1=min(n1,n2);
			break;
		case MAX:
			n1=max(n1,n2);
			break;
		default:
			n1+=n2;
			break;
	}
}

}}


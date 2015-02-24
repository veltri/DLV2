/*
 * AggregateAtom.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "AggregateAtom.h"
#include "../../util/Assert.h"
#include "../term/ConstantTerm.h"
#include "../term/ArithTerm.h"
using namespace std;

size_t DLV2::grounder::AggregateAtom::hash() {
	// TODO Hash Aggregate Atoms
	return 0;
}

bool DLV2::grounder::AggregateAtom::operator ==(const Atom& a) {
	// TODO Op == Aggregate Atoms
	return false;
}

void DLV2::grounder::AggregateAtom::print() {
	if(negative)
		cout<<"not ";
	if(lowerGuard!=nullptr)
		lowerGuard->print();
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
		for(auto& term:element.getTerms()){
			if(!first)cout<<",";else first=false;
			term->print();
		}
		cout<<":";first=true;
		for(auto& naf:element.getNafLiterals()){
			if(!first)cout<<",";else first=false;
			naf->print();
		}
		first=true;
	}
	cout<<"}";
	if(upperGuard!=nullptr)
		upperGuard->print();
}

DLV2::grounder::Term* DLV2::grounder::AggregateAtom::changeInStandardFormatGuard(Term* guard) {
	Term* t = nullptr;
	if (guard->getType() == TermType::NUMERIC_CONSTANT) {
		t=new NumericConstantTerm(false, guard->getConstantValue() + 1);
		TermTable::getInstance()->addTerm(t);
	}
	if (guard->getType() == TermType::VARIABLE) {
		vector<Operator> operators(Operator::PLUS);
		vector<Term*> terms;
		terms[0] = guard;
		Term* one_term = new NumericConstantTerm(false, 1);
		TermTable::getInstance()->addTerm(one_term);
		terms[1] = one_term;
		t = new ArithTerm(false, operators, terms);
		TermTable::getInstance()->addTerm(t);
	}
	return t;
}

void DLV2::grounder::AggregateAtom::chechAggregateValidity() {
	assert_msg(
			!((firstBinop == Binop::LESS || firstBinop == Binop::LESS_OR_EQ)
					&& (secondBinop == Binop::GREATER
							|| secondBinop == Binop::GREATER_OR_EQ)),
			"Invalid Aggregate Operation.");
	assert_msg(
			!((firstBinop == Binop::GREATER
					|| firstBinop == Binop::GREATER_OR_EQ)
					&& (secondBinop == Binop::LESS
							|| secondBinop == Binop::LESS_OR_EQ)),
			"Invalid Aggregate Operation.");
	if(lowerGuard!=0){
		assert_msg(lowerGuard->getType() != TermType::STRING_CONSTANT,
				"Invalid lower guard");
		assert_msg(lowerGuard->getType() != TermType::ARITH, "Invalid lower guard");
		assert_msg(lowerGuard->getType() != TermType::FUNCTION,
				"Invalid lower guard");
		assert_msg(lowerGuard->getType() != TermType::ANONYMOUS,
				"Invalid lower guard");
	}
	if(upperGuard!=0){
	assert_msg(upperGuard->getType() != TermType::STRING_CONSTANT,
			"Invalid lower guard");
	assert_msg(upperGuard->getType() != TermType::ARITH, "Invalid lower guard");
	assert_msg(upperGuard->getType() != TermType::FUNCTION,
			"Invalid lower guard");
	assert_msg(upperGuard->getType() != TermType::ANONYMOUS,
			"Invalid lower guard");
	}
}

void DLV2::grounder::AggregateAtom::changeInStandardFormat() {
	if(secondBinop==NONE_OP && firstBinop==Binop::UNEQUAL){
		firstBinop=EQUAL;
		this->negative=true;
		this->print();
		return;
	}
	else
		if(firstBinop==NONE_OP && secondBinop==Binop::UNEQUAL){
			firstBinop=EQUAL;
			secondBinop=NONE_OP;
			this->negative=true;
			return;
	}
	else
		if((firstBinop==Binop::GREATER || firstBinop==Binop::GREATER_OR_EQ) || (secondBinop==Binop::GREATER || secondBinop==Binop::GREATER_OR_EQ)){
			Binop tmpB=firstBinop;
			firstBinop=secondBinop;
			secondBinop=tmpB;
			Term* tmpT=lowerGuard;
			lowerGuard=upperGuard;
			upperGuard=tmpT;
			if(firstBinop==Binop::GREATER)
				firstBinop=Binop::LESS;
			if(secondBinop==Binop::GREATER)
				secondBinop=Binop::LESS;
			if(firstBinop==Binop::GREATER_OR_EQ)
				firstBinop=Binop::LESS_OR_EQ;
			if(secondBinop==Binop::GREATER_OR_EQ)
				secondBinop=Binop::LESS_OR_EQ;
		}
	if(firstBinop==Binop::LESS && lowerGuard!=0){
		Term* t=changeInStandardFormatGuard(lowerGuard);
		lowerGuard=t;
		firstBinop==Binop::LESS_OR_EQ;
	}
	if(secondBinop==Binop::LESS_OR_EQ && upperGuard!=0){
		Term* t=changeInStandardFormatGuard(upperGuard);
		upperGuard=t;
		secondBinop==Binop::LESS;
	}

}

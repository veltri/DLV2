/*
 * AggregateAtom.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "AggregateAtom.h"
using namespace std;

size_t DLV2::grounder::AggregateAtom::hash() {
	return 0; //TODO
}

bool DLV2::grounder::AggregateAtom::operator ==(const Atom& a) {
	return false; //TODO
}

void DLV2::grounder::AggregateAtom::print() {
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

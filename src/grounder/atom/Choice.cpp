/*
 * Choice.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "Choice.h"

namespace DLV2{

namespace grounder{

void Choice::print() {
	if(terms[0]!=nullptr){
		terms[0]->print();
		cout<<getBinopToStrng(firstBinop);
	}
	cout<<"{";
	bool first=true;
	bool second=true;
	bool firstElement=true;
	for(auto& element:choiceElements){
		if(!firstElement)cout<<";";else firstElement=false;
		for(auto& naf:element->getChoiceElement()){
			if(!second)cout<<",";
			naf->print();
			if(!first && second) second=false;
			if(first) {cout<<":";first=false;}
		}
		first=true;
		second=true;
	}
	cout<<"}";
	if(terms[1]!=nullptr){
		cout<<getBinopToStrng(secondBinop);
		terms[1]->print();
	}
}

Atom* Choice::clone() {
	Atom* atom=new Choice;
	atom->setFirstBinop(firstBinop);
	atom->setSecondBinop(secondBinop);
	atom->setTerms(terms);
	atom->setChoiceElements(choiceElements);

	return atom;
}

}
}



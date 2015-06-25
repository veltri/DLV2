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
			if(first && element->getSize()>1) {cout<<":";first=false;}
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


set_term Choice::getGuardVariable(){
	set_term terms_variable;
	if (firstBinop != NONE_OP && !getTerm(0)->isGround())
			terms_variable.insert(getTerm(0));

	if (secondBinop != NONE_OP && !getTerm(1)->isGround())
		terms_variable.insert(getTerm(1));
	return terms_variable;
}

set_term Choice::getVariable() {
	set_term terms_variable;

	for(auto choice_element:choiceElements){
		for(unsigned i=0;i<choice_element->getSize();++i)
		{
			auto variables=choice_element->getAtom(i)->getVariable();
			terms_variable.insert(variables.begin(),variables.end());
		}
	}
	set_term guardTerms=getGuardVariable();
	terms_variable.insert(guardTerms.begin(), guardTerms.end());
	return terms_variable;
}

set_term Choice::getVariableToSave(){
	set_term terms_variable;
	for(auto choice_element:choiceElements){
		for(unsigned i=0;i<choice_element->getSize();++i)
		{
			if(i==0 || choice_element->getAtom(i)->isNegative()){
				auto variables=choice_element->getAtom(i)->getVariable();
				terms_variable.insert(variables.begin(),variables.end());
			}
		}
	}
	set_term guardTerms=getGuardVariable();
	terms_variable.insert(guardTerms.begin(), guardTerms.end());
	return terms_variable;
}

}
}



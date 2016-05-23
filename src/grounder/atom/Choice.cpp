/*
 * Choice.cpp
 *
 *  Created on: 08/mar/2014
 *      Author: Jessica
 */

#include "Choice.h"

namespace DLV2{

namespace grounder{

void Choice::print(ostream& stream) {
	if(terms[0]!=nullptr){
		terms[0]->print(stream);
		stream<<getBinopToStrng(firstBinop);
	}
	stream<<"{";
	bool first=true;
	bool second=true;
	bool firstElement=true;
	for(auto& element:choiceElements){
		if(!firstElement)stream<<";";else firstElement=false;
		for(auto& naf:element->getChoiceElement()){
			if(!second)stream<<",";
			naf->print(stream);
			if(!first && second) second=false;
			if(first && element->getSize()>1) {stream<<":";first=false;}
		}
		first=true;
		second=true;
	}
	stream<<"}";

	//Avoid print >=0, because is the default guard
	if(terms[0]==nullptr && secondBinop==GREATER_OR_EQ && terms[1]->getIndex()==TermTable::getInstance()->term_zero->getIndex())return;

	if(terms[1]!=nullptr){
		stream<<getBinopToStrng(secondBinop);
		terms[1]->print(stream);
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

bool Choice::operator ==(const Atom& a) const {
	if(!a.isChoice())return false;
	if(firstBinop!=a.getFirstBinop())return false;
	if(secondBinop!=a.getSecondBinop())return false;
	if(firstBinop!=NONE_OP && terms[0]->getIndex()!=a.getFirstGuard()->getIndex())return false;
	if(secondBinop!=NONE_OP && terms[1]->getIndex()!=a.getSecondGuard()->getIndex())return false;
	if(choiceElements.size()!=a.getChoiceElementsSize())return false;
	for(unsigned i=0;i<choiceElements.size();i++)
		if(!(*choiceElements[i]==*a.getChoiceElement(i)))
			return false;

	return true;
}

set_term Choice::getGuardVariable(){
	set_term terms_variable;
	if (firstBinop != NONE_OP && !getTerm(0)->isGround())
			terms_variable.insert(getTerm(0));

	if (secondBinop != NONE_OP && !getTerm(1)->isGround())
		terms_variable.insert(getTerm(1));
	return terms_variable;
}

const set_term Choice::getVariable(bool guard) {
	set_term variables;

	if(guard)
		variables=getGuardVariable();

	for(auto choice_element:choiceElements){
		for(unsigned i=0;i<choice_element->getSize();++i)
		{
			const set_term& var=choice_element->getAtom(i)->getVariable();
			variables.insert(var.begin(),var.end());
		}
	}
	return variables;
}


set_term Choice::getVariableToSave(){
	set_term terms_variable;
	set_term variableSafe;
	for(auto choice_element:choiceElements){
		for(unsigned i=0;i<choice_element->getSize();++i)
		{
			Atom* atom=choice_element->getAtom(i);
			if(i==0 || atom->isNegative()){
				const set_term& variables=atom->getVariable();
				terms_variable.insert(variables.begin(),variables.end());
			}
			if(i>0 && !atom->isNegative() && atom->isClassicalLiteral()){
				const set_term& variables=atom->getVariable();
				for(auto var:variables)
					terms_variable.erase(var);
			}
		}
	}

	set_term guardTerms=getGuardVariable();
	terms_variable.insert(guardTerms.begin(), guardTerms.end());
	return terms_variable;
}

}
}



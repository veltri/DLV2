/*
 * NumericOutputBuilder.cpp
 *
 *  Created on: Jul 7, 2015
 *      Author: davide
 */

#include "NumericOutputBuilder.h"
#include "../table/PredicateExtension.h"

namespace DLV2 {
namespace grounder {

void NumericOutputBuilder::onRule(Rule* rule) {
	cout<<"RULE ";
	rule->print();
	if(rule->isAStrongConstraint())
		onConstraint(rule);
	else{
		onHead(rule->getHead());
		onBody(rule);
	}
	cout<<endl;
}

void NumericOutputBuilder::onWeakConstraint() {
}

void NumericOutputBuilder::onQuery() {
}

void NumericOutputBuilder::onHeadAtom(Atom* atom) {
	cout<<"1 ";onClassicalLiteral(atom);
}

void NumericOutputBuilder::onHead(const vector<Atom*>& head) {
	if(head.size()>0 && head[0]->isChoice())
		onChoiceAtom(head[0]);
	if(head.size()>1)
		onDisjunctionAtom(head);
	else if(head.size()>0)
		onHeadAtom(head[0]);

}

void NumericOutputBuilder::onConstraint(Rule* rule){
	cout<<"1 1 ";
	onBody(rule);
}


void NumericOutputBuilder::onBody(Rule *rule) {
	unsigned body_size=rule->getSizeBody();
	vector<Atom*> negative,positive;
	negative.reserve(body_size);
	positive.reserve(body_size);
	Atom *atom;
	for(unsigned i=0;i<body_size;i++){
		if(rule->isAtomToSimplifyInBody(i))continue;
		atom=rule->getAtomInBody(i);
		if(!atom->isNegative())
			positive.push_back(atom);
		else
			negative.push_back(atom);
	}

	cout<<negative.size()+positive.size()<<" "<<negative.size();
	for(auto& atom:negative)
		onClassicalLiteral(atom);
	for(auto& atom:positive)
		onClassicalLiteral(atom);
}

void NumericOutputBuilder::onClassicalLiteral(Atom* atom) {
	cout<<atom->getIndex()<<" ";
}

void NumericOutputBuilder::onChoiceAtom(Atom* atom) {
	cout<<"3 "<<atom->getChoiceElementsSize()<<" ";
	for(unsigned i=0;i<atom->getChoiceElementsSize();i++)
		onClassicalLiteral(atom->getChoiceElement(i)->getFirstAtom());
}

void NumericOutputBuilder::onAggregate(Atom* atom) {
}

void NumericOutputBuilder::onDisjunctionAtom(const vector<Atom*>& head) {
	cout<<"8 "<<head.size()<<" ";
	for(auto& atom:head)
		onClassicalLiteral(atom);
}

void NumericOutputBuilder::onAggregateElement(Atom* atom) {
}

void NumericOutputBuilder::onEnd() {
	PredicateExtTable::getInstance()->print();
	cout<<"0"<<endl<<"B+"<<endl<<"0"<<endl<<"B-"<<endl<<"1"<<endl<<"0"<<endl<<"1"<<endl;
}

} /* namespace grounder */
} /* namespace DLV2 */

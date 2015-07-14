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
//	cout<<"RULE ";
//	rule->print();
	if(rule->isAStrongConstraint())
		onConstraint(rule);
	else{
		onHead(rule->getHead());
		onBody(rule);
	}
	cout<<endl;
	cout<<stream.str();
	stream.flush();
	stream.str("");
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
	else if(head.size()>1)
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

	cout<<negative.size()+positive.size()<<" "<<negative.size()<<" ";
	for(auto& atom:negative)
		if(atom->isAggregateAtom()){
			unsigned agg_pred=onAggregate(atom);
			cout<<agg_pred<<" ";
		}else
			onClassicalLiteral(atom);
	for(auto& atom:positive)
		if(atom->isAggregateAtom()){
			unsigned agg_pred=onAggregate(atom);
			cout<<agg_pred<<" ";
		}else
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

unsigned NumericOutputBuilder::onAggregate(Atom* atom) {
	AggregateFunction function=atom->getAggregateFunction();
	if(function==COUNT || function==SUM){
		return printCountSumAggregate(atom);
	}else if(function==MIN || function==MAX){
		return printMaxMinAggregate(atom);
	}
	return 0;
}

unsigned NumericOutputBuilder::printCountSumAggregate(Atom* atom) {
	unsigned pred_first_binop=0,pred_second_binop=0;
	//TODO we can optimize scan the aggregate one time also if there is two guard, saving the body of the rule in string
	if(atom->getFirstBinop()!=NONE_OP){
		unsigned bound=atom->getFirstGuard()->getConstantValue();
		if(atom->getFirstBinop()==LESS)bound++;
		if(atom->getAggregateFunction()==COUNT)
			pred_first_binop=onConstraintRule(atom,bound);
		else
			pred_first_binop=onWeightRule(atom,bound);
	}
	if(atom->getSecondBinop()!=NONE_OP || atom->getFirstBinop()==EQUAL){
		unsigned bound;
		if(atom->getFirstBinop()==EQUAL)
			bound=atom->getFirstGuard()->getConstantValue()+1;
		else
			bound=atom->getSecondGuard()->getConstantValue();
		if(atom->getSecondBinop()==LESS_OR_EQ)bound++;
		if(atom->getAggregateFunction()==COUNT)
			pred_second_binop=onConstraintRule(atom,bound);
		else
			pred_second_binop=onWeightRule(atom,bound);
	}
	unsigned index_aggregate=IdGenerator::getInstance()->getNewId(1);
	stream<<"1 "<<index_aggregate<<" "<<(pred_first_binop!=0 && pred_second_binop!=0)+1<<" "<<(pred_second_binop!=0)<<" ";
	if(pred_second_binop!=0)stream<<pred_second_binop<<" ";
	if(pred_first_binop!=0)stream<<pred_first_binop;
	stream<<endl;
	return index_aggregate;
}

void NumericOutputBuilder::onDisjunctionAtom(const vector<Atom*>& head) {
	cout<<"8 "<<head.size()<<" ";
	for(auto& atom:head)
		onClassicalLiteral(atom);
}

void NumericOutputBuilder::onAggregateElement(Atom* atom) {
}

void NumericOutputBuilder::onFact(Atom* atom) {
	onHeadAtom(atom);cout<<"0 0"<<endl;
}

unsigned NumericOutputBuilder::onWeightRule(Atom* aggregateAtom, unsigned bound) {
	unsigned pred_id=IdGenerator::getInstance()->getNewId(1);
	stream<<"5 "<<pred_id<<" "<<bound<<" ";
	unsigned body_size=aggregateAtom->getAggregateElementsSize();
	vector<Atom*> negative,positive;
	vector<int> weight_negative,weight_positive;
	negative.reserve(body_size);
	positive.reserve(body_size);
	weight_negative.reserve(body_size);
	weight_positive.reserve(body_size);
	Atom *atom;
	for(unsigned i=0;i<aggregateAtom->getAggregateElementsSize();i++){
		AggregateElement *element=aggregateAtom->getAggregateElement(i);
		atom=element->getNafLiteral(0);
		if(!atom->isNegative()){
			positive.push_back(atom);
			weight_positive.push_back(element->getTerm(0)->getConstantValue());
		}else{
			negative.push_back(atom);
			weight_negative.push_back(element->getTerm(0)->getConstantValue());
		}
	}

	stream<<negative.size()+positive.size()<<" "<<negative.size()<<" ";
	for(auto& atom:negative)
		stream<<atom->getIndex()<<" ";
	for(auto& atom:positive)
		stream<<atom->getIndex()<<" ";


	for(auto& weight:weight_negative)
		stream<<weight<<" ";
	for(auto& weight:weight_positive)
		stream<<weight<<" ";

	stream<<endl;
	return pred_id;
}

unsigned NumericOutputBuilder::onConstraintRule(Atom* aggregateAtom,unsigned bound) {
	unsigned pred_id=IdGenerator::getInstance()->getNewId(1);
	stream<<"2 "<<pred_id<<" ";
	unsigned body_size=aggregateAtom->getAggregateElementsSize();
	vector<Atom*> negative,positive;
	negative.reserve(body_size);
	positive.reserve(body_size);
	Atom *atom;
	for(unsigned i=0;i<aggregateAtom->getAggregateElementsSize();i++){
		AggregateElement *element=aggregateAtom->getAggregateElement(i);
		atom=element->getNafLiteral(0);
		if(!atom->isNegative())
			positive.push_back(atom);
		else
			negative.push_back(atom);

	}

	stream<<negative.size()+positive.size()<<" "<<negative.size()<<" "<<bound<<" ";
	for(auto& atom:negative)
		stream<<atom->getIndex()<<" ";
	for(auto& atom:positive)
		stream<<atom->getIndex()<<" ";

	stream<<endl;
	return pred_id;
}

void NumericOutputBuilder::printAuxRuleMinMax(Atom *aggregate,function<unsigned(Term*)>& function, unsigned & positivePredicate,unsigned & negativePredicate) {
	IdGenerator* generator=IdGenerator::getInstance();
	for(unsigned i=0;i<aggregate->getAggregateElementsSize();i++){

		unsigned index_agg_atom=aggregate->getAggregateElement(i)->getNafLiteral(0)->getIndex();
		Term *agg_term=aggregate->getAggregateElement(i)->getTerm(0);
		unsigned value=function(agg_term);
		switch (value) {
			case 1:
				if(positivePredicate==0)positivePredicate=generator->getNewId(1);
				stream<<"1 "<<positivePredicate<<" 1 0 "<<index_agg_atom<<endl;
				break;
			case 2:
				if(negativePredicate==0)negativePredicate=generator->getNewId(1);
				stream<<"1 "<<negativePredicate<<" 1 0 "<<index_agg_atom<<endl;
				break;
			default:
				break;
		}
	}
}

unsigned NumericOutputBuilder::printMaxMinAggregate(Atom* atom) {
	function<unsigned(Term*)> function;

	if(atom->getAggregateFunction()==MAX){

		if(atom->getFirstBinop()!=NONE_OP && atom->getFirstBinop()!=EQUAL && atom->getSecondBinop()==NONE_OP){
			function=[&](Term * term){
				if(atom->getFirstBinop()==LESS && *term>*(atom->getFirstGuard()))return 1;
				if(atom->getFirstBinop()==LESS_OR_EQ && *term>=*(atom->getFirstGuard()))return 1;
				return 0;
			};
		}else if(atom->getSecondBinop()!=NONE_OP && atom->getFirstBinop()==NONE_OP){
			function=[&](Term * term){
				if(atom->getSecondBinop()==LESS && *term>=*(atom->getSecondGuard()))return 2;
				if(atom->getSecondBinop()==LESS_OR_EQ && *term>*(atom->getSecondGuard()))return 2;
				return 0;
			};
		}else if(atom->getSecondBinop()!=NONE_OP && atom->getFirstBinop()!=NONE_OP){
			function=[&](Term * term){
				if(atom->getFirstBinop()==LESS && atom->getSecondBinop()==LESS  && *term>*(atom->getFirstGuard()) && *term<*(atom->getSecondGuard()))return 1;
				if(atom->getFirstBinop()==LESS && atom->getSecondBinop()==LESS_OR_EQ  && *term>*(atom->getFirstGuard()) && *term<=*(atom->getSecondGuard()))return 1;
				if(atom->getFirstBinop()==LESS_OR_EQ && atom->getSecondBinop()==LESS  && *term>=*(atom->getFirstGuard()) && *term<*(atom->getSecondGuard()))return 1;
				if(atom->getFirstBinop()==LESS_OR_EQ && atom->getSecondBinop()==LESS_OR_EQ  && *term>=*(atom->getFirstGuard()) && *term<=*(atom->getSecondGuard()))return 1;

				if(atom->getSecondBinop()==LESS  && *term>=*(atom->getSecondGuard()))return 2;
				if(atom->getSecondBinop()==LESS_OR_EQ  && *term>*(atom->getSecondGuard()))return 2;

				return 0;
			};
		}else if(atom->getFirstBinop()==EQUAL){
			function=[&](Term * term){
				if( *term==*(atom->getFirstGuard()) )return 1;
				if(*term>*(atom->getFirstGuard()))return 2;
				return 0;
			};
		}

	}else if(atom->getAggregateFunction()==MIN){


			if(atom->getFirstBinop()!=NONE_OP && atom->getFirstBinop()!=EQUAL && atom->getSecondBinop()==NONE_OP){
				function=[&](Term * term){
					if(atom->getFirstBinop()==LESS && *term<=*(atom->getFirstGuard()))return 2;
					if(atom->getFirstBinop()==LESS_OR_EQ && *term<*(atom->getFirstGuard()))return 2;
					return 0;
				};
			}else if(atom->getSecondBinop()!=NONE_OP && atom->getFirstBinop()==NONE_OP){
				function=[&](Term * term){
					if(atom->getSecondBinop()==LESS && *term<*(atom->getSecondGuard()))return 1;
					if(atom->getSecondBinop()==LESS_OR_EQ && *term<=*(atom->getSecondGuard()))return 1;
					return 0;
				};
			}else if(atom->getSecondBinop()!=NONE_OP && atom->getFirstBinop()!=NONE_OP){
				function=[&](Term * term){
					if(atom->getFirstBinop()==LESS && atom->getSecondBinop()==LESS  && *term>*(atom->getFirstGuard()) && *term<*(atom->getSecondGuard()))return 1;
					if(atom->getFirstBinop()==LESS && atom->getSecondBinop()==LESS_OR_EQ  && *term>*(atom->getFirstGuard()) && *term<=*(atom->getSecondGuard()))return 1;
					if(atom->getFirstBinop()==LESS_OR_EQ && atom->getSecondBinop()==LESS  && *term>=*(atom->getFirstGuard()) && *term<*(atom->getSecondGuard()))return 1;
					if(atom->getFirstBinop()==LESS_OR_EQ && atom->getSecondBinop()==LESS_OR_EQ  && *term>=*(atom->getFirstGuard()) && *term<=*(atom->getSecondGuard()))return 1;

					if(atom->getFirstBinop()==LESS && *term<=*(atom->getFirstGuard()))return 2;
					if(atom->getFirstBinop()==LESS_OR_EQ && *term<*(atom->getFirstGuard()))return 2;

					return 0;
				};
			}else if(atom->getFirstBinop()==EQUAL){
				function=[&](Term * term){
					if( *term==*(atom->getFirstGuard()) )return 1;
					if(*term<*(atom->getFirstGuard()))return 2;
					return 0;
				};
			}

	}





	unsigned  positivePredicate=0, negativePredicate=0;
	printAuxRuleMinMax(atom,function,positivePredicate,negativePredicate);
	unsigned index_aggregate=IdGenerator::getInstance()->getNewId(1);
	stream<<"1 "<<index_aggregate<<" "<<(positivePredicate!=0 && negativePredicate!=0)+1<<" "<<(negativePredicate!=0)<<" ";
	if(negativePredicate!=0)stream<<negativePredicate<<" ";
	if(positivePredicate!=0)stream<<positivePredicate;
	stream<<endl;
	return index_aggregate;
}

void NumericOutputBuilder::onEnd() {
	cout<<"0"<<endl;
	PredicateExtTable::getInstance()->print();
	cout<<"0"<<endl<<"B+"<<endl<<"0"<<endl<<"B-"<<endl<<"1"<<endl<<"0"<<endl<<"1"<<endl;
}

} /* namespace grounder */
} /* namespace DLV2 */



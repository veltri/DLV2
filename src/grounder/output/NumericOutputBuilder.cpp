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
	if(rule->isAStrongConstraint()){
		onConstraint(rule);
	}else if(rule->isWeakConstraint()){
		int level=rule->getLevel()->getConstantValue();
		unsigned idHead= rewriteBodyInAux(rule);
		if(levelWeak.count(level)){
			(*levelWeak[level]).second.push_back(make_tuple(idHead,rule->getWeight()->getConstantValue(),rule->getLabel()));
		}else{
			list<id_weight_label> list(1,make_tuple(idHead,rule->getWeight()->getConstantValue(),rule->getLabel()));
			pair_level_tuple_list pair={level,list};
			weakLevelConstraints.push_back(pair);
			levelWeak[level]=prev(weakLevelConstraints.end());
		}
	}else{
		onHead(rule->getHead());
		onBody(rule);
		cout<<endl;
	}
	if(printStream){
		cout<<stream.str();
		stream.str("");
		printStream=false;
	}
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
	cout<<endl;
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
	printStream=true;
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
	for(auto& atom:positive) {
		stream<<atom->getIndex()<<" ";
	}
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
	bool boolean=atom->getSecondBinop()!=NONE_OP && atom->getFirstBinop()!=NONE_OP && positivePredicate==0;
	stream<<"1 "<<index_aggregate<<" "<<(positivePredicate!=0 && negativePredicate!=0)+1+boolean<<" "<<(negativePredicate!=0)<<" ";
	if(negativePredicate!=0)stream<<negativePredicate<<" ";
	if(positivePredicate!=0)stream<<positivePredicate;
	else if(boolean) stream<<IdGenerator::getInstance()->getNewId(1);
	stream<<endl;
	return index_aggregate;
}

void NumericOutputBuilder::printWeak(){

	weakLevelConstraints.sort([](const pair_level_tuple_list& l1,const pair_level_tuple_list& l2){
		return l1.first < l2.first;
	});

	for(auto list:weakLevelConstraints){
		printWeakAtLevel(list.second);
	}

}



void NumericOutputBuilder::printWeakAtLevel(list<id_weight_label>& listOfWeak){

	auto hash=[](const pair<int,vector<Term*>>& ele){
		size_t seed=3;
		seed^= (ele.first + 0x9e3779b9 + (seed<<6) + (seed>>2));
		for(auto t:ele.second)
			seed ^= t->getIndex() + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	};
	auto equal=[](const pair<int,vector<Term*>>& ele1,const pair<int,vector<Term*>>& ele2){
		if(ele1.first!=ele2.first)return false;
		if(ele1.second.size()!=ele2.second.size())return false;
		for(unsigned i=0;i<ele1.second.size();i++)
			if(ele1.second[i]->getIndex()!=ele2.second[i]->getIndex())
				return false;
		return true;
	};



	unordered_map<pair<int,vector<Term*>>,unsigned,decltype(hash),decltype(equal)> weightLabel(1,hash,equal);
	vector<vector<id_weight_label>> weaks;
	for(auto idWeightLabel:listOfWeak){
		pair<int,vector<Term*>> pair={get<1>(idWeightLabel),get<2>(idWeightLabel)};
		auto it=weightLabel.find(pair);
		if(it!=weightLabel.end())
			weaks[it->second].push_back(idWeightLabel);
		else{
			weightLabel.insert({pair,weaks.size()});
			weaks.emplace_back(1,idWeightLabel);
		}
	}

//	cout<<"LEVEL "<<listOfWeak.front()->getLevelInt()<<endl;
//	for(auto& p:weaks){
//		cout<<"BLOCK"<<endl;
//		for(auto& w:p){
//			w->print();
//		}
//		cout<<endl;
//	}
	stringstream atomsId;
	stringstream weightAtomsId;
	for(unsigned i=0;i<weaks.size();i++){
		if(i!=0)atomsId<<" ";
		if(weaks[i].size()==1)
			atomsId<<get<0>(weaks[i][0]);
		else{
			vector<unsigned> aux;
			for(auto weak:weaks[i])
				aux.push_back(get<0>(weak));
			atomsId<<createMultipleRule(aux);
		}
		weightAtomsId<<" "<<get<1>(weaks[i][0]);
	}
	cout<<"6 0 "<<weaks.size()<<" 0 "<<atomsId.str()<<weightAtomsId.str()<<endl;
}

unsigned NumericOutputBuilder::rewriteBodyInAux(Rule* rule) {
	unsigned body_size=rule->getSizeBody();
	vector<Atom*> negative,positive;
	negative.reserve(body_size);
	positive.reserve(body_size);
	Atom* firstPrinted=nullptr;
	Atom *atom;
	for(unsigned i=0;i<body_size;i++){
		if(rule->isAtomToSimplifyInBody(i))continue;
		atom=rule->getAtomInBody(i);
		if(!atom->isNegative())
			positive.push_back(atom);
		else
			negative.push_back(atom);
		if(firstPrinted==nullptr)firstPrinted=atom;
	}
	if(positive.size()==1 && negative.size()==0){
		if(firstPrinted->isAggregateAtom())
			return onAggregate(firstPrinted);
		else{
			return firstPrinted->getIndex();
		}
	}

	unsigned index_head=IdGenerator::getInstance()->getNewId(1);
	cout<<"1 "<<index_head<<" ";
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
	cout<<endl;
	return index_head;
}

unsigned NumericOutputBuilder::createMultipleRule(vector<unsigned>& idatoms){
	unsigned index_head=IdGenerator::getInstance()->getNewId(1);
	for(auto id:idatoms)
		cout<<"1 "<<index_head<<" 1 0 "<<id<<endl;
	return index_head;
}

void NumericOutputBuilder::onEnd() {
	if(weakLevelConstraints.size()>0)
		printWeak();


	cout<<"0"<<endl;
//	PredicateExtTable::getInstance()->print();
	cout<<streamAtomTable.str();
	cout<<"0"<<endl<<"B+"<<endl<<"0"<<endl<<"B-"<<endl<<"1"<<endl<<"0"<<endl<<"1"<<endl;
}

void NumericOutputBuilder::appendToStreamAtomTable(Atom* atom) {
	if(predicateToPrint.size()>0 && predicateToPrint.count(atom->getPredicate()->getIndex()))
		streamAtomTable<<atom->getIndex()<<" ";ClassicalLiteral::print(atom->getPredicate(),atom->getTerms(),false,false,streamAtomTable);streamAtomTable<<endl;
}


} /* namespace grounder */
} /* namespace DLV2 */


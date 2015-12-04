/*
 * Rule.cpp
 *
 *  Created on: 03/apr/2014
 *      Author: Jessica
 */

#include "Rule.h"
#include "iostream"
#include "OrderRule.h"
#include "../table/PredicateExtension.h"

namespace DLV2{

namespace grounder{

//-------------------------------RuleInformation---------------------




// ------------------------------Rule---------------------------------

set_predicate Rule::calculatePredicate(vector<Atom*>& atoms,bool checkNegative,bool negative){
	set_predicate predicates;
	for (auto atom:atoms)
		if(!checkNegative || (atom->isNegative() == negative)){
			set_predicate atom_predicates=atom->getPredicates();
			predicates.insert(atom_predicates.begin(),atom_predicates.end());
		}

	return predicates;
}

unordered_set<index_object> Rule::calculatePredicateIndex(vector<Atom*>& atoms,bool checkNegative,bool negative){
	unordered_set<index_object> predicates;
	for (auto atom:atoms) {
		set_predicate atom_predicates=atom->getPredicates();
		for(auto predicate: atom_predicates)
			if(!checkNegative || (atom->isNegative() == negative))
				predicates.insert(predicate->getIndex());
	}
	return predicates;
}

void Rule::print(ostream& stream){

	//Print for debug
	if(!ground){printNonGround(stream);return;}
	unsigned int i=0;
	bool firstAtomPrinted=false;
	for (auto atom:head) {
		if(firstAtomPrinted && !simplifiedHead[i])
			stream<<";";
		if(!simplifiedHead[i]){
			atom->print(stream);
			if(!firstAtomPrinted)
				firstAtomPrinted=true;
		}
		i++;
	}
	firstAtomPrinted=false;
	if(areThereUndefinedAtomInBody() || isAStrongConstraint()){
		stream<<":-";
		unsigned int i=0;
		for (auto atom:body) {
			if(firstAtomPrinted && !simplifiedBody[i])
				stream<<";";
			if(!simplifiedBody[i]){
				atom->print(stream);
				if(!firstAtomPrinted)
					firstAtomPrinted=true;
			}
			i++;
		}
	}
	stream<<"."<<endl;
}

void Rule::printNonGround(ostream& stream){
	unsigned int i=0;
	for (auto atom:head) {
		atom->print(stream);
		if(i!=head.size()-1)
			stream<<";";
		i++;
	}
	if(body.size()>0 || isAStrongConstraint()){
		stream<<":-";
		unsigned int i=0;
		for (auto atom:body) {
			atom->print(stream);
			if(i!=body.size()-1)
				stream<<";";
			i++;
		}
	}
	stream<<"."<<endl;
}


bool Rule::operator ==(const Rule& r) {
	  if(getSizeBody()!=r.getSizeBody())return false;
	  if(getSizeHead()!=r.getSizeHead())return false;
	  for(auto atom:head){
		  bool find=false;
		  for(auto it=r.getBeginHead();it!=r.getEndHead();it++)
			  if(*atom==*(*it)){
				  find=true;
				  break;
			  }
		  if(!find)return false;
	  }
	  for(auto atom:body){
		  bool find=false;
		  for(auto it=r.getBeginBody();it!=r.getEndBody();it++)
			  if(*atom==*(*it)){
				  find=true;
				  break;
			  }
		  if(!find)return false;
	  }

	  return true;

}

void Rule::deleteBody(function<int(Atom*)> f) {
	for(auto atom:body){
		int result=f(atom);
		if(result==1)
			delete atom;
		if(result==2){
			atom->deleteAtoms();
			delete atom;
		}
	}
}

void Rule::deleteHead(function<int(Atom*)> f) {
	for(auto atom:head){
		int result=f(atom);
		if(result==1)
			delete atom;
		if(result==2){
			atom->deleteAtoms();
			delete atom;
		}
	}
}

void Rule::deleteGroundRule(){
	this->deleteBody([](Atom* atom){
		//Delete the given atom if is a false negative atom or is an aggregate (atoms not present in PredicateExtension)
		if(atom!=nullptr && ((atom->isClassicalLiteral() && atom->isNegative()) || atom->isAggregateAtom()))
			return 1;
		return 0;
	});
	this->deleteHead([](Atom* atom){
		if(atom!=0 && atom->isChoice())
			return 1;
		return 0;
	});
	delete this;
}

void Rule::setUnsolvedPredicates() {
	if(isChoiceRule()){
		Atom* choiceAtom=head[0];
		for(unsigned i=0;i<choiceAtom->getChoiceElementsSize();++i)
			choiceAtom->getChoiceElement(i)->getFirstAtom()->getPredicate()->setSolved(false);
	}
	if(head.size()>1){
		for(auto atom:head)
			atom->getPredicate()->setSolved(false);
	}
}


//FIXME TODO
void Rule::sortPositiveLiteralInBody(vector<vector<unsigned>>& predicate_searchInsert_table,vector<unsigned>& originalOrderMapping) {
	vector<Atom*> newBody;
	newBody.reserve(body.size());

	vector<int> sizeExtensions;
	sizeExtensions.reserve(body.size());

	for(unsigned i=0;i<body.size();++i){
		Atom* atom=body[i];
		if(atom->isClassicalLiteral() && !atom->isNegative()){
			unsigned extensionSize=INT_MAX;
			for(auto table:predicate_searchInsert_table[head.size()+i]){
				unsigned size=PredicateExtTable::getInstance()->getPredicateExt(atom->getPredicate())->getPredicateExtentionSize(table);
				if(size<extensionSize)
					extensionSize=size;
			}
//			unsigned extensionSize=0;
//			for(auto table:predicate_searchInsert_table[head.size()+i]){
//				extensionSize+=PredicateExtTable::getInstance()->getPredicateExt(atom->getPredicate())->getPredicateExtentionSize(table);
//			}
			sizeExtensions.push_back(extensionSize);
		}
		else
			sizeExtensions.push_back(-1);
		newBody.push_back(atom);
	}

	bool sort=true;
	while(sort){
		sort=false;
		for(unsigned i=0;i<body.size()-1;++i){
			Atom* atom1=newBody[i];
			Atom* atom2=newBody[i+1];
			bool atom1Positive=atom1->isClassicalLiteral() && !atom1->isNegative();
			bool atom2Positive=atom2->isClassicalLiteral() && !atom2->isNegative();
			if(atom1Positive && atom2Positive && sizeExtensions[i] > sizeExtensions[i+1]){
				newBody[i]=atom2;
				newBody[i+1]=atom1;

				unsigned otmp=originalOrderMapping[i];
				originalOrderMapping[i]=originalOrderMapping[i+1];
				originalOrderMapping[i+1]=otmp;

				int ttmp=sizeExtensions[i];
				sizeExtensions[i]=sizeExtensions[i+1];
				sizeExtensions[i+1]=ttmp;

				vector<unsigned> vtmp=predicate_searchInsert_table[head.size()+i];
				predicate_searchInsert_table[head.size()+i]=predicate_searchInsert_table[head.size()+i+1];
				predicate_searchInsert_table[head.size()+i+1]=vtmp;

				sort=true;
			}
		}
	}
	body=newBody;

//	cout<<"ORDERED BODY: ";
//	for(unsigned i=0;i<body.size();++i){
//		body[i]->print();
//		cout<<" "<<sizeExtensions[i]<<" "<<originalOrderMapping[i];
//		cout<<" --- ";
//	}
//	cout<<endl;

}

}
}



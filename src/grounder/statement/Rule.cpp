/*
 * Rule.cpp
 *
 *  Created on: 03/apr/2014
 *      Author: Jessica
 */

#include "Rule.h"
#include "iostream"
#include "OrderRule.h"

namespace DLV2{

namespace grounder{

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

void Rule::print(){

	//Print for debug
	if(!ground){printNonGround();return;}
	unsigned int i=0;
	bool firstAtomPrinted=false;
	for (auto atom:head) {
		if(firstAtomPrinted && !simplifiedHead[i])
			cout<<";";
		if(!simplifiedHead[i]){
			atom->print();
			if(!firstAtomPrinted)
				firstAtomPrinted=true;
		}
		i++;
	}
	firstAtomPrinted=false;
	if(areThereUndefinedAtomInBody() || isAStrongConstraint()){
		cout<<":-";
		unsigned int i=0;
		for (auto atom:body) {
			if(firstAtomPrinted && !simplifiedBody[i])
				cout<<";";
			if(!simplifiedBody[i]){
				atom->print();
				if(!firstAtomPrinted)
					firstAtomPrinted=true;
			}
			i++;
		}
	}
	cout<<"."<<endl;
}

void Rule::printNonGround(){
	unsigned int i=0;
	for (auto atom:head) {
		atom->print();
		if(i!=head.size()-1)
			cout<<";";
		i++;
	}
	if(body.size()>0 || isAStrongConstraint()){
		cout<<":-";
		unsigned int i=0;
		for (auto atom:body) {
			atom->print();
			if(i!=body.size()-1)
				cout<<";";
			i++;
		}
	}
	cout<<"."<<endl;
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


}}



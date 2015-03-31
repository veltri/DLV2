/*
 * Rule.cpp
 *
 *  Created on: 03/apr/2014
 *      Author: Jessica
 */

#include "Rule.h"
#include "iostream"

namespace DLV2{

namespace grounder{

set_predicate Rule::calculatePredicate(vector<Atom*>& atoms,bool checkNegative,bool negative){
	set_predicate predicates;
	for (auto atom:atoms) {
		Predicate* predicate=atom->getPredicate();
		if(predicate!=nullptr)
			if(!checkNegative || (atom->isNegative() == negative))
				predicates.insert(predicate);

	}
	return predicates;
}

unordered_set<index_object> Rule::calculatePredicateIndex(vector<Atom*>& atoms,bool checkNegative,bool negative){
	unordered_set<index_object> predicates;
	for (auto atom:atoms) {
		Predicate* predicate=atom->getPredicate();
		if(predicate!=nullptr)
			if(!checkNegative || (atom->isNegative() == negative))
				predicates.insert(predicate->getIndex());

	}
	return predicates;
}

static bool insertVariables(Atom* atom,set_term& variables,bool anonymusSafe)
{
	if(!anonymusSafe)
		if(atom->containsAnonymous())
			return false;
	set_term tempVariables=atom->getVariable();
	variables.insert(tempVariables.begin(),tempVariables.end());
	return true;

}

bool Rule::isSafe()
{
	set_term variableToCheck;
	set_term variableInPositiveAtom;
	for(auto atom:head)
		if(!insertVariables(atom,variableToCheck,false))
			return false;
	for(auto atom:body)
		if(atom->isNegative()){
			if(!insertVariables(atom,variableToCheck,false))
				return false;
		}
		else
			insertVariables(atom,variableInPositiveAtom,true);
	if(variableInPositiveAtom.size()<variableToCheck.size())
		return false;
	for(auto variable:variableToCheck)
		if(variableInPositiveAtom.count(variable)!=1)
			return false;
	return true;
}

void Rule::basicSortBody(){
	unordered_map<unsigned,set_term> builtin_negative_variable;
	//Find the variable for builtin and negative atom
	unsigned index_current_atom=0;
	for(auto current_atom:body){
		if( ( current_atom->isBuiltIn() && current_atom->getBinop()!=EQUAL ) || current_atom->isNegative() ){
			set_term variables=current_atom->getVariable();
			builtin_negative_variable.insert({index_current_atom,variables});
		}else if(current_atom->getBinop()==EQUAL ){
			//If the binop is equal insert the variable that compare in positive atom, because an assigment can have
			// variable that non compare in the positive atom
			set_term variable_in_builtin=current_atom->getVariable();

			set_term variable_to_search;
			for(auto body_atom:body){
				if(!body_atom->isBuiltIn() && !body_atom->isNegative() ){
					set_term variables=body_atom->getVariable();
					for(auto term:variables)
						if(variable_in_builtin.count(term))
							variable_to_search.insert(term);
				}
			}
			builtin_negative_variable.insert({index_current_atom,variable_to_search});

		}
		index_current_atom++;
	}

	//Remove the variable for each positive atom
	index_current_atom=0;
	vector<Atom*> body_ordered;
	for(auto current_atom:body){
		if(!(current_atom->isBuiltIn() || current_atom->isNegative())){
			body_ordered.push_back(body[index_current_atom]);
			vector<unsigned> removed_builtin_negative;
			for(auto& index_builtint_negative:builtin_negative_variable){
				for(auto term:current_atom->getVariable())index_builtint_negative.second.erase(term);
				if(index_builtint_negative.second.size()==0){
					//If all variable are erased then the position of atom have to be changed hear

					body_ordered.push_back(body[index_builtint_negative.first]);
					removed_builtin_negative.push_back(index_builtint_negative.first);
				}
			}
			for(auto builtin_negative_to_remove:removed_builtin_negative)builtin_negative_variable.erase(builtin_negative_to_remove);

		}
		index_current_atom++;
	}

	setBody(body_ordered);

}


void  Rule::print(){
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


};

};

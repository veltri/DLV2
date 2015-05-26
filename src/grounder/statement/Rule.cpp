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
	//TODO CALCULATE Z VARIABLE AND SET ASSIGNMENT
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


unordered_multimap<Term*,unsigned> Rule::findPossibleBind(){

	unordered_multimap<Term*,unsigned> possible_bind;
	int atom_counter=0;
	//First add all variable in positive atom
	for(auto atom=getBeginBody();atom!=getEndBody();++atom,++atom_counter){
		Atom* current_atom=*atom;
		if(!(current_atom->isBuiltIn() || current_atom->isNegative() || current_atom->getAggregateElementsSize()>0)) {

			for (Term *variable:current_atom->getVariable())
				possible_bind.insert({variable, atom_counter});
		}

	}

	//Second find the not cyclic assignments in built-in and aggregate atoms
	atom_counter=0;
	unordered_set<unsigned> cyclic_assignment;
	vector<unsigned> aggregates_positions;
	for(auto atom=getBeginBody();atom!=getEndBody();++atom,++atom_counter){
		Atom *current_atom = *atom;

		if (current_atom->isBuiltIn() && current_atom->getBinop() == Binop::EQUAL) {
			//If one term is ground or is in possible_bind
			Term *firstGuard = current_atom->getTerm(0);
			Term *secondGuard = current_atom->getTerm(1);


			if ( ( firstGuard->isGround() && !secondGuard->isGround() ) ||
					(possible_bind.count(firstGuard) && ! possible_bind.count(secondGuard))) {

				possible_bind.insert({secondGuard,atom_counter});
				current_atom->setAssignment(true);
			}else if ( ( !firstGuard->isGround() && secondGuard->isGround() ) ||
					(possible_bind.count(secondGuard) && ! possible_bind.count(firstGuard))) {

				possible_bind.insert({firstGuard,atom_counter});
				current_atom->setAssignment(true);

			}//Cyclic dependency
			else if(!possible_bind.count(secondGuard) && ! possible_bind.count(firstGuard))
				cyclic_assignment.insert(atom_counter);
		}//The aggregate assignment must be at the second
		else if(current_atom->getAggregateElementsSize()>0 && current_atom->getFirstBinop()==Binop::EQUAL){
			//If the guard is not in possible_bind
			if(!possible_bind.count(current_atom->getFirstGuard())){

				possible_bind.insert({current_atom->getFirstGuard(),atom_counter});
				current_atom->setAssignment(true);
				aggregates_positions.push_back(atom_counter);
			}
		}


	}

	//For cyclic dependencies, try to find the order of evaluation of cyclic built-in and remove
	// at each iteration one built-in until cyclic_assignment is empty
	while(cyclic_assignment.size()>0){
		unordered_set<unsigned> deleted_builtin;
		for(auto cyclic_builtin:cyclic_assignment){
			Atom *current_atom = body[cyclic_builtin];
			Term *firstGuard = current_atom->getTerm(0);
			Term *secondGuard = current_atom->getTerm(1);
			Term *bind_guard=nullptr;
			if ( possible_bind.count(firstGuard) && ! possible_bind.count(secondGuard))
				bind_guard=secondGuard;
			else if ( possible_bind.count(secondGuard) && ! possible_bind.count(firstGuard))
				bind_guard=firstGuard;
			if(bind_guard!=nullptr){

				possible_bind.insert({bind_guard,cyclic_builtin});
				current_atom->setAssignment(true);
				deleted_builtin.insert(cyclic_builtin);
			}
		}
		for(auto element:deleted_builtin){cyclic_assignment.erase(element);}
	}

	//If an assignment aggregate have the guard in some built-in the aggregate is not an assignment
	for(auto aggregate_position:aggregates_positions){
		auto range_term_atom=possible_bind.equal_range(body[aggregate_position]->getFirstGuard());
		for(auto it=range_term_atom.first;it!=range_term_atom.second;++it){
			if(!body[it->second]->getAggregateElementsSize()>0){
				body[aggregate_position]->setAssignment(false);
				break;
			}

		}
	}
	return possible_bind;
}

void Rule::findAtomDependency(){
}


void Rule::basicSortBody(){

	unordered_multimap<Term*,unsigned int> possible_bind=findPossibleBind();
	for(auto term_atom:possible_bind)
	{
		term_atom.first->print();cout<<" "<<term_atom.second<<endl;
	}
	for(auto atom=getBeginBody();atom!=getEndBody();++atom) {
		cout<<(*atom)->isAssignment()<<" ";
	}
	cout<<endl;

}

/*void Rule::basicSortBody(){
	if(!this->getPositivePredicateIndexInBody().empty()){
		unordered_map<unsigned,set_term> builtin_negative_variable;
		//Find the variable for builtin and negative atom
		unsigned index_current_atom=0;
		for(auto current_atom:body){
			if( (current_atom->isBuiltIn() && current_atom->getBinop()!=EQUAL ) || current_atom->isNegative() ){
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

}*/


void  Rule::print(){

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


};

};

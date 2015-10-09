/*
 * BackJumpingGrounder.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: jessica
 */

#include "BackJumpingGrounder.h"
#include "../../util/Utils.h"

namespace DLV2 {
namespace grounder {

bool BackJumpingGrounder::back() {

	direction=0;
	callFoundAssignment = false;
	if (index_current_atom <  0)
		return false;

	unsigned current_index=index_current_atom;
	switch(current_status){
		case SUCCESSFULL:
			backFromSolutionFound();
			break;
		case FIRST_MATCH:
			backFromFirstMatch();
			break;
		case NEXT_MATCH:
			backFromNextMatch();
			break;
	}

	if (index_current_atom <  0)
		return false;

	for (unsigned i=index_current_atom; i<=current_index; ++i){
		removeBindValueInAssignment(current_variables_atoms[i]);
		if(i>index_current_atom){
			for (unsigned j = 0; j < current_id_match[i].size(); ++j) {
				current_id_match[i][j].second=NO_MATCH;
			}
			current_id_match_iterator[i]=0;
			if(currentRule->getAtomInBody(i)->isAggregateAtom())
				substiteInGroundRule(i,nullptr);
		}
	}

	generateTemplateAtom();
	return true;

}

bool BackJumpingGrounder::foundAssignment() {
	current_status=SUCCESSFULL;
	return BackTrackingGrounder::foundAssignment();
}

bool BackJumpingGrounder::firstMatch() {
	current_status=FIRST_MATCH;
	return BackTrackingGrounder::firstMatch();
}

bool BackJumpingGrounder::nextMatch() {
	current_status=NEXT_MATCH;
	return BackTrackingGrounder::nextMatch();
}

void BackJumpingGrounder::inizialize(Rule* rule) {

	BackTrackingGrounder::inizialize(rule);

	closestSuccessfulBinder_it=currentRule->getBeginBody();
	closestSuccessfulBinder_index=0;
	current_status=SUCCESSFULL;

//	dependencySets.clear();
//	computeDependencySets();

	outputVariables.clear();
	for (unsigned i = 0; i < currentRule->getSizeHead(); ++i) {
		Atom* atom=currentRule->getAtomInHead(i);
		set_term variables=atom->getVariable();
		outputVariables.insert(variables.begin(),variables.end());
	}
	for (unsigned i = 0; i < currentRule->getSizeBody(); ++i) {
		Atom* atom=currentRule->getAtomInBody(i);
		if(!atom->isNegative() && atom->isClassicalLiteral() && !atom->getPredicate()->isSolved()){
			set_term variables=atom->getVariable();
			outputVariables.insert(variables.begin(),variables.end());
		}
	}

//	for (int i = 0; i < rule->getSizeBody(); ++i) {
//		set_term dep=dependencySets[i];
//		for(auto term: dep){
//			term->print(cout);
//		}
//		cout<<endl;
//	}

//	set_term var=currentRule->getAtomInHead(0)->getVariable();
//	cout<<closestBinder(2,var)<<endl;
}

void BackJumpingGrounder::closestBinder(vector<Atom*>::iterator literal_it, int literal_pos, set_term& variables,int& positionCB,vector<Atom*>::iterator& iteratorCB, bool includeCurrentLiteral) {
	iteratorCB=literal_it;
	positionCB=-1;
	int i=literal_pos;
	if(!includeCurrentLiteral){
		i--;
		iteratorCB--;
	}
	for(;i>=0;i--,iteratorCB--){
		Atom* atom=currentRule->getAtomInBody(i);
		if(!is_ground_atom[i] || (atom->isBuiltIn() && atom->isAssignment())){
			if(variables.size()==0){
				positionCB=i;
				break;
			}
			set_term literal_variables=atom->getVariable();
			if(!Utils::isDisjoint(literal_variables,variables)){
				positionCB=i;
				break;
			}
		}
		//TODO Altri tipi di atomi
	}
}

//void BackJumpingGrounder::computeDependencySets() {
//	for (unsigned i = 0; i < currentRule->getSizeBody(); ++i) {
//		Atom* atom=currentRule->getAtomInBody(i);
//		set_term dependencySet=atom->getVariable();
//		for (unsigned j = i+1; j < currentRule->getSizeBody(); ++j) {
//			Atom* atom2=currentRule->getAtomInBody(j);
//			set_term atom_variables=atom2->getVariable();
//			if(!Utils::isDisjoint(atom_variables,dependencySet))
//				dependencySet.insert(atom_variables.begin(),atom_variables.end());
//		}
//		dependencySets.push_back(dependencySet);
//	}
//}

void BackJumpingGrounder::backFromSolutionFound() {
//	cout<<"---> BACK SOLUTION FOUND"<<endl;
	current_status=NEXT_MATCH;

	vector<Atom*>::iterator closestBinder_it;
	int closestBinder_pos;
	closestBinder(current_atom_it,index_current_atom,outputVariables,closestBinder_pos,closestBinder_it,true);

	current_atom_it=closestBinder_it;
	index_current_atom=closestBinder_pos;
	closestBinder(current_atom_it,index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,false);

//	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
//	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
}

void BackJumpingGrounder::backFromFirstMatch() {
//	cout<<"---> BACK FIRST MATCH"<<endl;
//	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
//	(*current_atom_it)->print();
//	ground_rule->getAtomInBody(index_current_atom)->print();

	vector<Atom*>::iterator closestBinder_it;
	int closestBinder_pos;
	set_term variables=(*current_atom_it)->getVariable();
	closestBinder(current_atom_it,index_current_atom,variables,closestBinder_pos,closestBinder_it,false);

	current_atom_it=closestBinder_it;
	index_current_atom=closestBinder_pos;

//	for(auto var: failureSet){
//		var->print();
//	}
//	cout<<endl;
//
//	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
//	cout<<"CB "<<closestBinder_pos<<endl;
//	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
}

bool BackJumpingGrounder::match() {
	bool result = true;
	if((*current_atom_it)->isBuiltIn() && (*current_atom_it)->isAssignment() && !direction )
		result = false;

	if(result)
		result = BackTrackingGrounder::match();

	if(!result){
		set_term vars=(*current_atom_it)->getVariable();
		failureSet.insert(vars.begin(),vars.end());
	}
	else{
		set_term bindVars=current_variables_atoms[index_current_atom];
		for(auto var: bindVars){
			failureSet.erase(var);
		}
	}

	return result;
}

void BackJumpingGrounder::backFromNextMatch() {
//	cout<<"---> BACK NEXT MATCH"<<endl;

	vector<Atom*>::iterator closestBinder_it;
	int closestBinder_pos;
	closestBinder(current_atom_it,index_current_atom,failureSet,closestBinder_pos,closestBinder_it,false);

	if(closestSuccessfulBinder_it>closestBinder_it){
		current_atom_it=closestSuccessfulBinder_it;
		index_current_atom=closestSuccessfulBinder_index;
	}
	else {
		current_atom_it=closestBinder_it;
		index_current_atom=closestBinder_pos;
	}

	if(index_current_atom==closestSuccessfulBinder_index){
		closestBinder(current_atom_it,index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,false);
	}

//	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
//	cout<<"CB "<<closestBinder_pos<<endl;
//	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
}

} /* namespace grounder */
} /* namespace DLV2 */

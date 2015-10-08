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
//	bool result= BackTrackingGrounder::nextMatch();
//	if(!result && index_current_atom==currentRule->getSizeBody()-1){
//		current_status=SUCCESSFULL;
//		back();
//	}
	return BackTrackingGrounder::nextMatch();
}

void BackJumpingGrounder::inizialize(Rule* rule) {

	BackTrackingGrounder::inizialize(rule);

	closestSuccessfulBinder_it=currentRule->getBeginBody();
	closestSuccessfulBinder_index=0;
	current_status=SUCCESSFULL;

	dependencySets.clear();
	computeDependencySets();

	outputVariables.clear();
	for (unsigned i = 0; i < currentRule->getSizeHead(); ++i) {
		Atom* atom=currentRule->getAtomInHead(i);
		set_term variables=atom->getVariable();
		outputVariables.insert(variables.begin(),variables.end());
	}

//	for (int i = 0; i < rule->getSizeBody(); ++i) {
//		set_term dep=dependencySets[i];
//		for(auto term: dep){
//			term->print(cout);
//		}
//		cout<<endl;
//	}
//
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
		if(!is_ground_atom[i] && atom->isClassicalLiteral()){
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

void BackJumpingGrounder::computeDependencySets() {
	for (unsigned i = 0; i < currentRule->getSizeBody(); ++i) {
		Atom* atom=currentRule->getAtomInBody(i);
		set_term dependencySet=atom->getVariable();
		for (unsigned j = i+1; j < currentRule->getSizeBody(); ++j) {
			Atom* atom2=currentRule->getAtomInBody(j);
			set_term atom_variables=atom2->getVariable();
			if(!Utils::isDisjoint(atom_variables,dependencySet))
				dependencySet.insert(atom_variables.begin(),atom_variables.end());
		}
		dependencySets.push_back(dependencySet);
	}
}

void BackJumpingGrounder::backFromSolutionFound() {
	current_status=NEXT_MATCH;
	closestBinder(current_atom_it,index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,true);
	current_atom_it=closestSuccessfulBinder_it;
	index_current_atom=closestSuccessfulBinder_index;
}

void BackJumpingGrounder::backFromFirstMatch() {
	vector<Atom*>::iterator closestBinder_it;
	int closestBinder_pos;
	set_term variables=(*current_atom_it)->getVariable();
	closestBinder(current_atom_it,index_current_atom,variables,closestBinder_pos,closestBinder_it,false);
	if(closestBinder_pos<closestSuccessfulBinder_index){
		closestSuccessfulBinder_index=closestBinder_pos;
		closestSuccessfulBinder_it=closestBinder_it;
	}
	current_atom_it=closestBinder_it;
	index_current_atom=closestBinder_pos;
}

void BackJumpingGrounder::backFromNextMatch() {
	if(closestSuccessfulBinder_index==index_current_atom)
		closestBinder(current_atom_it,index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,false);

	vector<Atom*>::iterator closestBinder_it;
	int closestBinder_pos;
	set_term variables=dependencySets[index_current_atom];
	closestBinder(current_atom_it,index_current_atom,variables,closestBinder_pos,closestBinder_it,false);
	if(closestSuccessfulBinder_it>closestBinder_it){
		current_atom_it=closestSuccessfulBinder_it;
		index_current_atom=closestSuccessfulBinder_index;
	}
	else {
		current_atom_it=closestBinder_it;
		index_current_atom=closestBinder_pos;
	}
}

} /* namespace grounder */
} /* namespace DLV2 */

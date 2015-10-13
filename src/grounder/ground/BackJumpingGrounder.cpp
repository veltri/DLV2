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
#ifdef DEBUG_GROUNDING
	cout<<endl<<"---> INIZIALIZE"<<endl;
#endif
	BackTrackingGrounder::inizialize(rule);
	closestSuccessfulBinder_it=currentRule->getBeginBody();
	closestSuccessfulBinder_index=0;
	current_status=SUCCESSFULL;

	historyBackFromFirst.clear();
	historyBackFromSolutionFound.first=-1;
	historyBackOutputVars.clear();

	failureMap.clear();
	outputVariables.clear();
	for (unsigned i = 0; i < currentRule->getSizeHead(); ++i) {
		Atom* atom=currentRule->getAtomInHead(i);
		set_term variables=atom->getVariable();
		outputVariables.insert(variables.begin(),variables.end());
	}
	for (unsigned i = 0; i < currentRule->getSizeBody(); ++i) {
		Atom* atom=currentRule->getAtomInBody(i);
		if(atom->isClassicalLiteral() && !atom->getPredicate()->isSolved()){
			set_term variables=atom->getVariable();
			outputVariables.insert(variables.begin(),variables.end());
		}
		else if(atom->isAggregateAtom()){ //&& atom->isAssignment()
			set_term variables;
			atom->getUnsolvedPredicateVariable(variables);
			outputVariables.insert(variables.begin(),variables.end());
			if(!variables.empty()){
				set_term guards=atom->getGuardVariable();
				outputVariables.insert(guards.begin(),guards.end());
			}
		}
	}

#ifdef DEBUG_GROUNDING
	cout<<"OUTPUT VARIABLES: ";
	for(auto var: outputVariables){
		var->print();cout<<" ";
	}
	cout<<endl;
#endif

}

void BackJumpingGrounder::closestBinder(vector<Atom*>::iterator literal_it, int literal_pos, const set_term& variables,int& positionCB,vector<Atom*>::iterator& iteratorCB, bool includeCurrentLiteral) {
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
			set_term literal_variables=atom->getVariable();
			if(!Utils::isDisjoint(literal_variables,variables)){
				positionCB=i;
				break;
			}
		}
	}
}

void BackJumpingGrounder::closestBinder(vector<Atom*>::iterator literal_it, int literal_pos,int& positionCB,vector<Atom*>::iterator& iteratorCB, bool includeCurrentLiteral) {
	iteratorCB=literal_it;
	positionCB=-1;
	int i=literal_pos;
	if(!includeCurrentLiteral){
		i--;
		iteratorCB--;
	}
	bool findVariable=false;
	for(;i>=0;i--,iteratorCB--){
		Atom* atom=currentRule->getAtomInBody(i);
		if(!is_ground_atom[i] || (atom->isBuiltIn() && atom->isAssignment())){
			set_term literal_variables=atom->getVariable();
			for(auto variableInLiteral:literal_variables){
				auto value=failureMap.find(variableInLiteral);
				if(value!=failureMap.end() && (*value).second){
					positionCB=i;
					findVariable=true;
					break;
				}
			}
		}
		if(findVariable)
			break;
	}
}

void BackJumpingGrounder::backFromSolutionFound() {
#ifdef DEBUG_GROUNDING
	cout<<endl<<"---> BACK SOLUTION FOUND"<<endl;
#endif
	current_status=NEXT_MATCH;

	if(historyBackFromSolutionFound.first!=-1){
		index_current_atom=historyBackFromSolutionFound.first;
		current_atom_it=historyBackFromSolutionFound.second;
		closestSuccessfulBinder_index=historyBackOutputVars[index_current_atom].first;
		closestSuccessfulBinder_it=historyBackOutputVars[index_current_atom].second;
	}
	else{
		vector<Atom*>::iterator closestBinder_it;
		int closestBinder_pos;
		closestBinder(current_atom_it,index_current_atom,outputVariables,closestBinder_pos,closestBinder_it,true);
		historyBackFromSolutionFound.first=closestBinder_pos;
		historyBackFromSolutionFound.second=closestBinder_it;
		current_atom_it=closestBinder_it;
		index_current_atom=closestBinder_pos;
		closestBinder(current_atom_it,index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,false);
		historyBackOutputVars.insert({index_current_atom,{closestSuccessfulBinder_index,closestSuccessfulBinder_it}});
	}

#ifdef DEBUG_GROUNDING
	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
#endif
}

void BackJumpingGrounder::backFromFirstMatch() {
#ifdef DEBUG_GROUNDING
	cout<<endl<<"---> BACK FIRST MATCH"<<endl;
#endif

	auto it=historyBackFromFirst.find(index_current_atom);

	if(it!=historyBackFromFirst.end()){
		index_current_atom=((*it).second).first;
		current_atom_it=((*it).second).second;
	}
	else{
		vector<Atom*>::iterator closestBinder_it;
		int closestBinder_pos;
		set_term variables=(*current_atom_it)->getVariable();
		closestBinder(current_atom_it,index_current_atom,variables,closestBinder_pos,closestBinder_it,false);
		historyBackFromFirst.insert({index_current_atom,{closestBinder_pos,closestBinder_it}});
		current_atom_it=closestBinder_it;
		index_current_atom=closestBinder_pos;
	}

#ifdef DEBUG_GROUNDING
	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
	cout<<"CB "<<closestBinder_pos<<endl;
	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
#endif
}

bool BackJumpingGrounder::match() {
	bool result = true;
	if((*current_atom_it)->isBuiltIn() && (*current_atom_it)->isAssignment() && !direction )
		result = false;

	if(result)
		result = BackTrackingGrounder::match();

	if(!result){
		set_term vars=(*current_atom_it)->getVariable();
		for(auto variableInFailurSet:vars)
			failureMap[variableInFailurSet]=true;
	}
	else{
		set_term bindVars=current_variables_atoms[index_current_atom];
		for(auto var: bindVars){
			failureMap[var]=false;
		}
	}
#ifdef DEBUG_GROUNDING
	cout<<"MATCH RESULT: "<<result<<endl;
	cout<<"FAILURE SET: ";
	for(auto var: failureSet){
		var->print();cout<<" ";
	}
	cout<<endl;
#endif

	return result;
}

void BackJumpingGrounder::backFromNextMatch() {
#ifdef DEBUG_GROUNDING
	cout<<endl<<"---> BACK NEXT MATCH"<<endl;
#endif

	vector<Atom*>::iterator closestBinder_it;
	int closestBinder_pos;
	closestBinder(current_atom_it,index_current_atom,closestBinder_pos,closestBinder_it,false);

	if(closestSuccessfulBinder_it>closestBinder_it){
		current_atom_it=closestSuccessfulBinder_it;
		index_current_atom=closestSuccessfulBinder_index;
	}
	else {
		current_atom_it=closestBinder_it;
		index_current_atom=closestBinder_pos;
	}

	if(index_current_atom==closestSuccessfulBinder_index){
		auto it=historyBackOutputVars.find(index_current_atom);
		if(it!=historyBackOutputVars.end()){
			closestSuccessfulBinder_index=((*it).second).first;
			closestSuccessfulBinder_it=((*it).second).second;
		}
		else{
			closestBinder(current_atom_it,index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,false);
			historyBackOutputVars.insert({index_current_atom,{closestSuccessfulBinder_index,closestSuccessfulBinder_it}});
		}
	}

#ifdef DEBUG_GROUNDING
	cout<<"FAILURE SET: ";
	for(auto var: failureSet){
		var->print();cout<<" ";
	}
	cout<<endl;
	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
	cout<<"CB "<<closestBinder_pos<<endl;
	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
#endif
}

} /* namespace grounder */
} /* namespace DLV2 */

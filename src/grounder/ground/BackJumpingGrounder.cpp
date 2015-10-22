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

	int current_index=index_current_atom;
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

	for (int i=index_current_atom; i<=current_index; ++i){
		if(current_variables_atoms[i].size()>0)
			removeBindValueInAssignment(current_variables_atoms[i]);
		if(i>index_current_atom && !is_ground_atom[i]){
			Predicate *currentPredicate=currentRule->getAtomInBody(i)->getPredicate();
			for (unsigned j = 0; j < current_id_match[i].size()&&currentPredicate!=nullptr; ++j) {
				predicateExtTable->getPredicateExt(currentPredicate)->getAtomSearcher(current_id_match[i][j].first)->removeId(current_id_match[i][j].second);
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
	closestSuccessfulBinder_index=-1;
	current_status=SUCCESSFULL;

	historyBackFromFirst.clear();
	historyBackFromSolutionFound=-1;
	historyBackOutputVars.clear();

	failureMap.clear();
	outputVariables.clear();
	for (auto it=currentRule->getBeginHead();it!=currentRule->getEndHead(); ++it) {
		Atom* atom=*it;
		const set_term& variables=atom->getVariable();
		outputVariables.insert(variables.begin(),variables.end());
	}
	for (auto it=currentRule->getBeginBody();it!=currentRule->getEndBody(); ++it) {
		Atom* atom=*it;
		if(atom->isClassicalLiteral() && !atom->getPredicate()->isSolved()){
			const set_term& variables=atom->getVariable();
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
	for(auto it:variablesBinder){
		it.first->print();cout<<"\t";cout<<it.second<<endl;
	}
#endif

}

void BackJumpingGrounder::closestBinder( int literal_pos, const set_term& variables,int& positionCB,vector<Atom*>::iterator& iteratorCB, bool includeCurrentLiteral) {
	positionCB=-1;
	for(auto variable:variables){
		int binder=variablesBinder[variable];
		if(((!includeCurrentLiteral && binder<literal_pos) || (includeCurrentLiteral && binder<=literal_pos)) && binder>positionCB)
			positionCB=binder;
	}
	iteratorCB=currentRule->getBeginBody()+positionCB;
}

void BackJumpingGrounder::closestBinder( int literal_pos,int& positionCB,vector<Atom*>::iterator& iteratorCB) {
	positionCB=-1;
	for(auto pair:failureMap){
		if(!pair.second) continue;
		int binder=variablesBinder[pair.first];
		if(binder<literal_pos && binder>positionCB)
			positionCB=binder;
	}
	iteratorCB=currentRule->getBeginBody()+positionCB;
}

void BackJumpingGrounder::backFromSolutionFound() {
#ifdef DEBUG_GROUNDING
	cout<<endl<<"---> BACK SOLUTION FOUND"<<endl;
#endif
	current_status=NEXT_MATCH;

	if(historyBackFromSolutionFound!=-1){
		index_current_atom=historyBackFromSolutionFound;
		current_atom_it=currentRule->getBeginBody()+historyBackFromSolutionFound;
		closestSuccessfulBinder_index=historyBackOutputVars[index_current_atom];
		closestSuccessfulBinder_it=currentRule->getBeginBody()+historyBackOutputVars[index_current_atom];
	}
	else{
		vector<Atom*>::iterator closestBinder_it;
		int closestBinder_pos;
		closestBinder(index_current_atom,outputVariables,closestBinder_pos,closestBinder_it,true);
		historyBackFromSolutionFound=closestBinder_pos;
		current_atom_it=closestBinder_it;
		index_current_atom=closestBinder_pos;
		closestBinder(index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,false);
		historyBackOutputVars.insert({index_current_atom,closestSuccessfulBinder_index});
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
		index_current_atom=((*it).second);
		current_atom_it=currentRule->getBeginBody()+((*it).second);
	}
	else{
		vector<Atom*>::iterator closestBinder_it;
		int closestBinder_pos;
		const set_term& variables=(*current_atom_it)->getVariable();

		closestBinder(index_current_atom,variables,closestBinder_pos,closestBinder_it,false);
		historyBackFromFirst.insert({index_current_atom,closestBinder_pos});
		current_atom_it=closestBinder_it;
		index_current_atom=closestBinder_pos;
	}

#ifdef DEBUG_GROUNDING
	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
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
		const set_term& vars=(*current_atom_it)->getVariable();
		for(auto var:vars)
			failureMap[var]=true;
	}
	else{
		for(auto var: current_variables_atoms[index_current_atom])
			failureMap[var]=false;
	}

#ifdef DEBUG_GROUNDING
	cout<<"MATCH RESULT: "<<result<<endl;
	cout<<"CURRENT ATOM: "<<index_current_atom<<endl;
	cout<<"FAILURE SET: ";
	for(auto pair:failureMap){
		if(pair.second){
			pair.first->print();cout<<" ";
		}
	}
	cout<<endl;
	printAssignment();
#endif

	return result;
}

void BackJumpingGrounder::backFromNextMatch() {
#ifdef DEBUG_GROUNDING
	cout<<endl<<"---> BACK NEXT MATCH"<<endl;
	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
#endif

	vector<Atom*>::iterator closestBinder_it;
	int closestBinder_pos;
	closestBinder(index_current_atom,closestBinder_pos,closestBinder_it);

	if(closestSuccessfulBinder_index>closestBinder_pos){
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
			closestSuccessfulBinder_index=((*it).second);
			closestSuccessfulBinder_it=currentRule->getBeginBody()+((*it).second);
		}
		else{
			closestBinder(index_current_atom,outputVariables,closestSuccessfulBinder_index,closestSuccessfulBinder_it,false);
			historyBackOutputVars.insert({index_current_atom,closestSuccessfulBinder_index});
		}
	}

#ifdef DEBUG_GROUNDING
	cout<<"FAILURE SET: ";
	for(auto pair:failureMap){
		if(pair.second){
			pair.first->print();cout<<" ";
		}
	}
	cout<<endl;
	cout<<"CSB "<<closestSuccessfulBinder_index<<endl;
	cout<<"CB "<<closestBinder_pos<<endl;
	cout<<"CURRENT ATOM "<<index_current_atom<<endl;
#endif
}

} /* namespace grounder */
} /* namespace DLV2 */

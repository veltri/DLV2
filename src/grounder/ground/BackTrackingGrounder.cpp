/*
 * BackTrackingGrounder.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: davide
 */

#include "BackTrackingGrounder.h"

namespace DLV2 {
namespace grounder {

#define NO_MATCH -1

void BackTrackingGrounder::generateTemplateAtom(){
	if(templateAtom!=nullptr) delete templateAtom;
	templateAtom = (*current_atom_it)->ground(current_var_assign);
}

bool BackTrackingGrounder::match() {
	if(templateAtom->isBuiltIn() || templateAtom->isNegative() ||
				( current_variables_atoms[index_current_atom].size()==0 && !templateAtom->containsAnonymous())){

		return groundBoundAtom();

	}else{

		if(current_id_match[index_current_atom].size()==0)
			return firstMatch();
		else
			return nextMatch();

	}

}

bool BackTrackingGrounder::groundBoundAtom() {
	//  If it is a built in atom, ground it and evaluate it (Built in have not instance table, since they have not a predicate)
	if (templateAtom->isBuiltIn()) {

		return templateAtom -> evaluate(current_var_assign);
		// If there isn't instances the search fails (find equal false) and if isn't negated then the algorithm have to stop
	}
		bool find = ( predicateExtTable->getPredicateExt(templateAtom->getPredicate())
							->getGenericAtom(templateAtom) == nullptr);
		//If exist and is fact then fail the search(find equal false) else if not exist
		// or is undefined atom then continue
		if(templateAtom->isNegative())
			return !find;

		return find;

}

bool BackTrackingGrounder::firstMatch(){

	// for each table to search inizialize to no match
	vector<pair<unsigned,int>> vec;
	for(unsigned i=0;i<predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom].size();i++){
		vec.push_back({predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom][i],NO_MATCH});
	}

	current_id_match.erase(index_current_atom);
	current_id_match.insert({index_current_atom,vec}).second;

	bool find=false;
	while(current_id_match[index_current_atom].size()>0){

		unsigned tableToSearch = current_id_match[index_current_atom].back().first;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);
		unsigned id = searcher->firstMatch(templateAtom,current_var_assign,find);

		if(find){
			current_id_match[index_current_atom].back().second = id;
			return find;
		}

		current_id_match[index_current_atom].pop_back();
	}

	return false;
}

bool BackTrackingGrounder::nextMatch(){

	bool find=false;
	while(current_id_match[index_current_atom].size()>0){

		unsigned tableToSearch = current_id_match[index_current_atom].back().first;
		int current_id = current_id_match[index_current_atom].back().second;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);

		if(current_id != NO_MATCH)
			searcher->nextMatch(current_id,templateAtom,current_var_assign,find);
		else
			current_id = searcher->firstMatch(templateAtom,current_var_assign,find);


		if(find){
			current_id_match[index_current_atom].back().second = current_id;
			return find;
		}

		current_id_match[index_current_atom].pop_back();
	}

	return false;
}

bool BackTrackingGrounder::next() {
	// first next the check have to be jumped, because start with second atom else
	if(start && currentRule->getSizeBody()>0){start=false;generateTemplateAtom();return true;}

	if( index_current_atom+1>=currentRule->getSizeBody()) return false;
	current_atom_it++;
	index_current_atom++;

	generateTemplateAtom();

	return true;
}

void BackTrackingGrounder::foundAssignment() {


	Rule groundRule;
	for(auto atom=currentRule->getBeginBody();atom!=currentRule->getEndBody();atom++){

		Atom *bodyGroundAtom=(*atom)->ground(current_var_assign);

		PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(bodyGroundAtom->getPredicate());
		Atom *searchAtom=predicateExt->getGenericAtom(bodyGroundAtom);

		if(searchAtom==nullptr){
			//FATAL ERRRO ANONIMUS

		}else{
			delete bodyGroundAtom;
			if(!bodyGroundAtom->isFact())
				groundRule.addInBody(searchAtom);

		}

	}

	unsigned atom_counter=0;
	for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();atom++,atom_counter++){
		Atom *headGroundAtom=(*atom)->ground(current_var_assign);

		PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(headGroundAtom->getPredicate());
		Atom *searchAtom=predicateExt->getGenericAtom(headGroundAtom);

		if(searchAtom==nullptr){
			groundRule.addInHead(headGroundAtom);

			GenericAtom *genericGroundAtom=new GenericAtom;
			genericGroundAtom->setTerms(headGroundAtom->getTerms());
			genericGroundAtom->setFact(groundRule.getSizeBody()==0 && groundRule.getSizeHead() == 1);

			for(unsigned i=0;i<predicate_searchInsert_table[atom_counter].size();i++)
				predicateExt->addGenericAtom(predicate_searchInsert_table[atom_counter][i],genericGroundAtom);
		}else{
			delete headGroundAtom;

			if(groundRule.getSizeBody()==0 && groundRule.getSizeHead() == 1)
				searchAtom->setFact(true);

			groundRule.addInHead(searchAtom);

		}

	}

	groundRule.print();
}

bool BackTrackingGrounder::back() {
	if (index_current_atom -1 < 0)
		return false;

	current_atom_it--;
	index_current_atom--;

	do{

		if (index_current_atom -1 < 0)
			return false;

		removeBindValueInAssignment(current_variables_atoms[index_current_atom]);

		current_atom_it--;
		index_current_atom--;

	}while ((*current_atom_it)->isBuiltIn() || (*current_atom_it)->isNegative() || current_variables_atoms[index_current_atom].size()==0);

	removeBindValueInAssignment(current_variables_atoms[index_current_atom]);
	generateTemplateAtom();

	return true;
}

void BackTrackingGrounder::inizialize(Rule* rule) {
	currentRule=rule;
	current_var_assign.clear();
	current_id_match.clear();
	current_atom_it = currentRule->getBeginBody();
	index_current_atom = 0;
	templateAtom=nullptr;
	start=true;
	findBindVariablesRule();


}

void BackTrackingGrounder::findBindVariablesRule() {
	set_term total_variable;
	unsigned int index_current_atom = 0;
	current_variables_atoms.clear();

	//For each atom determines the bound and the bind variables
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); current_atom_it++) {
		Atom *current_atom = *current_atom_it;
		set_term variablesInAtom = current_atom->getVariable();
		current_variables_atoms.push_back(set_term());

		for (auto variable : variablesInAtom) {
			if (!total_variable.count(variable))
				current_variables_atoms[index_current_atom].insert(variable);
		}

		for (auto variable : variablesInAtom)
			total_variable.insert(variable);
		index_current_atom++;

	}
}

void BackTrackingGrounder::removeBindValueInAssignment(const set_term& bind_variables) {

	for (auto variable : bind_variables)
		current_var_assign.erase(variable);

}

} /* namespace grounder */
} /* namespace DLV2 */

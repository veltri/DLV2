/*
 * BackTrackingGrounder.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: davide
 */

#include "BackTrackingGrounder.h"
#include "../../util/Timer.h"


namespace DLV2 {
namespace grounder {


/// If the firstMatch on table has not been called
#define NO_MATCH -1

void BackTrackingGrounder::generateTemplateAtom(){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Generate Template");
#endif

	if(templateAtom!=nullptr) delete templateAtom;
	templateAtom = (*current_atom_it)->ground(current_var_assign);

#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Generate Template");
#endif
}

void BackTrackingGrounder::printAssignment(){

	for(auto assignment : current_var_assign){
		cout<<"VAR ";assignment.first->print();cout<<" = ";assignment.second->print();cout<<endl;
	}

}

bool BackTrackingGrounder::isGroundCurrentAtom(){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Is Ground");
	bool isGround = ((*current_atom_it)->isBuiltIn() || (*current_atom_it)->isNegative() || current_variables_atoms[index_current_atom].size()==0);
	Timer::getInstance()->stop("Is Ground");
	return isGround;
#endif

	return ((*current_atom_it)->isBuiltIn() || (*current_atom_it)->isNegative() || current_variables_atoms[index_current_atom].size()==0);

}
bool BackTrackingGrounder::match() {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Match");
#endif

	/// If match is called at the end and there isn't bind variable return false else continue
	if(index_current_atom + 1 >= currentRule->getSizeBody() && isGroundCurrentAtom()){
		if(!lastMatch)
			lastMatch = true;
		else{
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Match");
#endif
			return false;
		}

	}else
		lastMatch = false;


	if(templateAtom->isBuiltIn() ){
#ifdef DEBUG_RULE_TIME
		bool evaluate=templateAtom -> evaluate(current_var_assign);
		Timer::getInstance()->stop("Match");
		return evaluate;
#endif

		return templateAtom -> evaluate(current_var_assign);

	}else{
		bool match;
		if(current_id_match[index_current_atom].size()==0){
			match=firstMatch() == !templateAtom->isNegative();
		}else{
			match = nextMatch() == !templateAtom->isNegative();
		}
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Match");
#endif
		return match;
	}

}



bool BackTrackingGrounder::firstMatch(){
	// for each table to search inizialize to no match
	current_id_match.erase(index_current_atom);
	current_id_match.insert({index_current_atom,vector<pair<unsigned,int>>()}).second;
	for(unsigned i=0;i<predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom].size();i++){
		current_id_match[index_current_atom].push_back({predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom][i],NO_MATCH});
	}


	// For each table to search call the first match until one table return find

	bool find=false;
	while(current_id_match[index_current_atom].size()>0){

		unsigned tableToSearch = current_id_match[index_current_atom].back().first;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);
		//inizialize false for negative atom
		bool undef=false;

		unsigned id = searcher->firstMatch(templateAtom,current_var_assign,find,undef);
		atom_undef_inbody[index_current_atom]=undef;
		if(templateAtom->isNegative() && find) find=!undef;

		if(find){

			if(!isGroundCurrentAtom())
				current_id_match[index_current_atom].back().second = id;
			else
				current_id_match[index_current_atom].clear();

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
		bool undef = false;

		if(current_id != NO_MATCH)
			searcher->nextMatch(current_id,templateAtom,current_var_assign,find,undef);
		else
			current_id = searcher->firstMatch(templateAtom,current_var_assign,find,undef);

		atom_undef_inbody[index_current_atom]=undef;

		if(find){
			current_id_match[index_current_atom].back().second = current_id;
			return find;
		}

		current_id_match[index_current_atom].pop_back();
	}

	return false;
}

bool BackTrackingGrounder::next() {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Next");
#endif
	// first next the check have to be jumped, because start with second atom else
	if(start && currentRule->getSizeBody()>0){
		start=false;generateTemplateAtom();
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Next");
#endif
		return true;
	}

	if( index_current_atom+1>=currentRule->getSizeBody()){
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Next");return false;
#endif
		return false;
	}


	current_atom_it++;
	index_current_atom++;


	generateTemplateAtom();
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Next");
#endif
	return true;
}

bool BackTrackingGrounder::foundAssignment() {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Body");
#endif
	Rule* groundRule=new Rule;
	bool head_true= (currentRule->getSizeHead() <= 1 );
	unsigned index_body_atom=0;
	for(auto atom=currentRule->getBeginBody();atom!=currentRule->getEndBody();atom++,index_body_atom++){

		if(!atom_undef_inbody[index_body_atom])
			if(!((*atom)->isNegative() && StatementDependency::getInstance()->isPredicateNegativeStratified((*atom)->getPredicate()->getIndex())))
				continue;

		if((*atom)->isBuiltIn())continue;

		Atom *bodyGroundAtom=(*atom)->ground(current_var_assign);
		groundRule->addInBody(bodyGroundAtom);

	}
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Body");
		Timer::getInstance()->start("Head");
#endif
	head_true=head_true && groundRule->getSizeBody() <=0;
	bool ground_new_atom=false;
	unsigned atom_counter=0;
	for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();atom++,atom_counter++){
		Atom *headGroundAtom=(*atom)->ground(current_var_assign);

		PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(headGroundAtom->getPredicate());
		Atom *searchAtom=predicateExt->getGenericAtom(headGroundAtom);

		if(searchAtom==nullptr){
			ground_new_atom = true;
			groundRule->addInHead(headGroundAtom);

			GenericAtom *genericGroundAtom=new GenericAtom;
			genericGroundAtom->setTerms(headGroundAtom->getTerms());
			genericGroundAtom->setFact(head_true);
			for(unsigned i=0;i<predicate_searchInsert_table[atom_counter].size();i++)
				predicateExt->addGenericAtom(predicate_searchInsert_table[atom_counter][i],genericGroundAtom,false);
		}else{

			if(head_true)
				searchAtom->setFact(true);

			groundRule->addInHead(headGroundAtom);

		}

	}

	if(!(groundRule->getSizeBody()==0 && groundRule->getSizeHead()==0))
		groundRule->print();
	delete groundRule;

	if(currentRule->getSizeBody() > 0)
		removeBindValueInAssignment(current_variables_atoms[index_current_atom]);
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Head");
#endif
	return ground_new_atom;
}

bool BackTrackingGrounder::back() {



	if (index_current_atom <=  0)
		return false;

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Back");
#endif

	current_atom_it--;
	index_current_atom--;


	while (isGroundCurrentAtom()){

		if (index_current_atom <= 0){
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Back");return false;
#endif
			return false;
		}

		removeBindValueInAssignment(current_variables_atoms[index_current_atom]);

		current_atom_it--;
		index_current_atom--;

	}

	removeBindValueInAssignment(current_variables_atoms[index_current_atom]);
	generateTemplateAtom();

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Back");
#endif

	return true;
}

void BackTrackingGrounder::inizialize(Rule* rule) {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Init");
#endif
	currentRule=rule;
	current_var_assign.clear();
	current_id_match.clear();
	current_atom_it = currentRule->getBeginBody();
	index_current_atom = 0;
	if(templateAtom!=nullptr) delete templateAtom;
	templateAtom=nullptr;
	start=true;
	lastMatch=false;
	atom_undef_inbody.reserve(rule->getSizeBody());
	findBindVariablesRule();
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Init");
#endif

}

void BackTrackingGrounder::findBindVariablesRule() {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Find Bind");
#endif

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

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Find Bind");
#endif
}

void BackTrackingGrounder::removeBindValueInAssignment(const set_term& bind_variables) {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Remove Assignment");
#endif

	for (auto variable : bind_variables)
		current_var_assign.erase(variable);

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Remove Assignment");
#endif

}

} /* namespace grounder */
} /* namespace DLV2 */

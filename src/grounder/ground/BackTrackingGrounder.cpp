/*
 * BackTrackingGrounder.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: davide
 */

#include "BackTrackingGrounder.h"
#include "../../util/Timer.h"
#include <boost/lexical_cast.hpp>
#include "../atom/AggregateAtom.h"
#include "../term/ConstantTerm.h"
#include "../atom/Choice.h"


namespace DLV2 {
namespace grounder {


#ifdef TRACE_ON
void BackTrackingGrounder::printAssignment(){
	for(unsigned i=0;i<current_assignment.size();i++){
		Term *value=current_assignment[i];
		if(value!=nullptr){
			cerr<<"VAR "<<i<<" = ";
			value->print(cerr);
			cerr<<" - ";
		}
	}
	cerr<<endl;
}
#endif

bool BackTrackingGrounder::findGroundMatch(){
	trace_action_tag(grounding,1,cerr<<"FIND GROUND ATOM ON: ";templateSetAtom[index_current_atom]->print(cerr);cerr<<endl;);
	// For each table to search call the first match until one table return find
	bool find=false;
	unsigned current_table=current_id_match_iterator[index_current_atom];
	unsigned n_table=current_id_match[index_current_atom].size();
	Atom* templateAtom=templateSetAtom[index_current_atom];

	// Avoid to clone template atom for each table for negative atoms
	bool isPossibleUndef=true;
	index_object indexNegativeAtom=0;
	bool negativeToClone=false;

	while(current_table<n_table){
		unsigned tableToSearch = current_id_match[index_current_atom][current_table].first;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);
		//Initialize false for negative atom
		bool undef=false;

		Atom* atomFound=nullptr;
		atomFound=searcher->findGroundAtom(templateAtom); // (index_current_atom,templateAtom,current_assignment,atomFound);
		find=(atomFound!=nullptr);
		if(atomFound!=nullptr)
			undef=!atomFound->isFact();

		if(templateAtom->isNegative() && find)
			find=!undef;

		if(templateAtom->isNegative() && !find){
			if(atomFound!=nullptr){
				indexNegativeAtom=atomFound->getIndex();
				isPossibleUndef=false;
			}
			//We can avoid to clone the template atom for each table and do it just at the end
			negativeToClone=true;
			if(StatementDependency::getInstance()->isPredicateNotStratified(templateAtom->getPredicate()->getIndex()))
				ground_rule->setAtomToSimplifyInBody(index_current_atom,false);
			else
				ground_rule->setAtomToSimplifyInBody(index_current_atom,!undef);
		}

		if(find){
			trace_action_tag(grounding,1,cerr<<"Match OK: ";atomFound->print(cerr);cerr<<endl;);
			if(!is_bound_atom[index_current_atom]){
				current_id_match[index_current_atom][current_table].second = MATCH;
			}else{
				current_id_match[index_current_atom][current_table].second = NO_MATCH;
				current_id_match_iterator[index_current_atom]=0;
			}
			substiteInGroundRule(index_current_atom,atomFound);
			ground_rule->setAtomToSimplifyInBody(index_current_atom,!undef);

			return find;
		}
		current_id_match[index_current_atom][current_table].second = NO_MATCH;
		current_id_match_iterator[index_current_atom]=++current_table;

	}

	//If at least a possible undef atom has been found then update accordingly the vector of undef atoms of this rule
	if(negativeToClone){
		while(!atomsPossibleUndef.empty() && atomsPossibleUndef.back()>=index_current_atom)
			atomsPossibleUndef.pop_back();
		if(isPossibleUndef && !ground_rule->isAtomToSimplifyInBody(index_current_atom))
			atomsPossibleUndef.push_back(index_current_atom);
		Atom* atomFound=templateAtom->clone();
		atomFound->setIndex(indexNegativeAtom);
		substiteInGroundRule(index_current_atom,atomFound);
	}

	current_id_match_iterator[index_current_atom]=0;

	return false;
}


bool BackTrackingGrounder::match() {

	//Avoid call multiple time method match for the ground atom in the last position of the rule
	if(is_bound_atom[index_current_atom] && !direction)
 		return false;

	 if(templateSetAtom[index_current_atom]->isClassicalLiteral()){
		if(is_bound_atom[index_current_atom]){
			trace_action_tag(grounding,1,cerr<<"MATCH GROUND CLASSICAL LIT: ";templateSetAtom[index_current_atom]->print(cerr);cerr<<endl;);
			return findGroundMatch() == !templateSetAtom[index_current_atom]->isNegative();
		}
		else{
			trace_action_tag(grounding,1,cerr<<"MATCH CLASSICAL LIT: ";templateSetAtom[index_current_atom]->print(cerr);cerr<<endl;);
			bool match;
			unsigned current_table=current_id_match_iterator[index_current_atom];

			//if is the first table to visit and the id of first match is NO_MATCH
			if(current_table==0 && current_id_match[index_current_atom][current_table].second==NO_MATCH){
				match = firstMatch() == !templateSetAtom[index_current_atom]->isNegative();
			}else{
				match = nextMatch() == !templateSetAtom[index_current_atom]->isNegative();
			}

			return match;
		}

	}else if(templateSetAtom[index_current_atom]->isBuiltIn() ){
		trace_action_tag(grounding,1,cerr<<"MATCH BUILT-IN: ";templateSetAtom[index_current_atom]->print(cerr);cerr<<endl;);
		current_id_match[index_current_atom][0].second=1;
		ground_rule->setAtomToSimplifyInBody(index_current_atom);

		if(builtAlreadyEvaluated[index_current_atom])
			return true;

		return templateSetAtom[index_current_atom] -> evaluate(current_assignment);

	}else if(templateSetAtom[index_current_atom]->isAggregateAtom()){
		trace_action_tag(grounding,1,cerr<<"MATCH AGGREGATE: ";templateSetAtom[index_current_atom]->print(cerr);cerr<<endl;);
		return groundAggregate();

	}

	return false;

}



bool BackTrackingGrounder::firstMatch(){
	trace_action_tag(grounding,1,cerr<<"FIRST MATCH ON: ";templateSetAtom[index_current_atom]->print(cerr);cerr<<endl;);
	// For each table to search call the first match until one table return find
	bool find=false;
	unsigned current_table=current_id_match_iterator[index_current_atom];
	unsigned n_table=current_id_match[index_current_atom].size();
	Atom* templateAtom=templateSetAtom[index_current_atom];
	while(current_table<n_table){
		unsigned tableToSearch = current_id_match[index_current_atom][current_table].first;
//		cerr<<"TABLE: "<<tableToSearch<<endl;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);
		//Initialize false for negative atom
		bool undef=false;

		Atom* atomFound=nullptr;
		searcher->firstMatch(index_current_atom,templateAtom,current_assignment,atomFound,currentRule->getRuleInformation());
		find=(atomFound!=nullptr);
		if(atomFound!=nullptr)
			undef=!atomFound->isFact();

		if(find){
			trace_action_tag(grounding,1,cerr<<"Match OK: ";atomFound->print(cerr);cerr<<endl;);
			if(!is_bound_atom[index_current_atom]){
				current_id_match[index_current_atom][current_table].second = MATCH;
			}else{
				current_id_match[index_current_atom][current_table].second = NO_MATCH;
				current_id_match_iterator[index_current_atom]=0;
			}
			substiteInGroundRule(index_current_atom,atomFound);
			ground_rule->setAtomToSimplifyInBody(index_current_atom,!undef);

			return find;
		}
		current_id_match[index_current_atom][current_table].second = NO_MATCH;
		current_id_match_iterator[index_current_atom]=++current_table;

	}

	current_id_match_iterator[index_current_atom]=0;

	return false;
}

bool BackTrackingGrounder::nextMatch(){
	trace_action_tag(grounding,1,cerr<<"NEXT MATCH ON: ";templateSetAtom[index_current_atom]->print(cerr);cerr<<endl;);

	bool find=false;
	unsigned current_table=current_id_match_iterator[index_current_atom];
	unsigned n_table=current_id_match[index_current_atom].size();
	Atom* templateAtom=templateSetAtom[index_current_atom];
	while(current_table<n_table){

		unsigned tableToSearch = current_id_match[index_current_atom][current_table].first;
		bool match = current_id_match[index_current_atom][current_table].second;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);
		Atom* atomFound=nullptr;
		if(match != NO_MATCH){
			trace_action_tag(grounding,2,cerr<<"Invoked Next Match on table: "<<tableToSearch<<endl;);
			searcher->nextMatch(index_current_atom,templateAtom,current_assignment,atomFound,currentRule->getRuleInformation());
		}
		else{
			trace_action_tag(grounding,2,cerr<<"Invoked First Match on table: "<<tableToSearch<<endl;);
			searcher->firstMatch(index_current_atom,templateAtom,current_assignment,atomFound,currentRule->getRuleInformation());
		}

		find=(atomFound!=nullptr);
		bool undef=false;
		if(find)
			undef=!atomFound->isFact();

		if(find){
			trace_action_tag(grounding,1,cerr<<"Match OK: ";atomFound->print(cerr);cerr<<endl;);
			substiteInGroundRule(index_current_atom,atomFound);
			ground_rule->setAtomToSimplifyInBody(index_current_atom,!undef);
			current_id_match[index_current_atom][current_table].second = MATCH;
			return find;
		}
		current_id_match[index_current_atom][current_table].second = NO_MATCH;
		current_id_match_iterator[index_current_atom]=++current_table;
	}
	current_id_match_iterator[index_current_atom]=0;

	return false;
}

bool BackTrackingGrounder::next() {
	direction=1;
	callFoundAssignment = false;
	if( unsigned(index_current_atom+1)>=currentRule->getSizeBody())
		return false;

	++index_current_atom;
	generateTemplateAtom();
	return true;
}


bool BackTrackingGrounder::foundAssignment() {
	callFoundAssignment=true;
	bool isAChoiceRule=currentRule->isChoiceRule();
	bool head_true=(currentRule->getSizeHead() <= 1  && !isAChoiceRule) && (!ground_rule->areThereUndefinedAtomInBody());
	bool ground_new_atom=false;
	bool find_new_true_atom=false;
	unsigned atom_counter=0;
	Atom *searchAtom=nullptr;
	if(isAChoiceRule)
		groundChoice(find_new_true_atom,ground_new_atom);

	for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead()&&!isAChoiceRule;++atom,++atom_counter){

		Atom *headGroundAtom=nullptr;
		(*atom)->ground(current_assignment,headGroundAtom);

		PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(headGroundAtom->getPredicate());
		searchAtom=predicateExt->getAtom(headGroundAtom);

		if(searchAtom==nullptr){
			ground_new_atom = true;

			headGroundAtom->setFact(head_true);
			for(unsigned i=0;i<predicate_searchInsert_table[atom_counter].size();++i)
				predicateExt->addAtom(predicate_searchInsert_table[atom_counter][i],headGroundAtom);

			ground_rule->setAtomInHead(atom_counter,headGroundAtom);
		}else{
			delete headGroundAtom;

			//TODO If searchAtom is true ??? {a|b. a.} o {a :- b(X,Y).b(1).b(1,2)|d.}

			//Previus atom is undef and now is true
			if(head_true && !searchAtom->isFact()){
				searchAtom->setFact(true);
				find_new_true_atom=true;
			}
			//Check if previus is false now is true ground_new atom i have put true
			ground_rule->setAtomInHead(atom_counter,searchAtom);
		}
	}

	trace_action_tag(grounding,1,cerr<<"Ground Rule Produced: ";ground_rule->print(cerr);cerr<<endl;);


	// If the rule has possible undef atoms in its body its printing is postponed to the end of grounding
	// So that:
	// 	- if the printing type is numeric we give to that atoms the right indices,
	// 	- independently from the output format, we simplify that atoms.
	// In this case ground_rule content cannot be changed (for example, substituting atoms in its body),
	// so after a ground rule is saved to be processed later, the ground_rule must be reinitialized coping
	// into it, the body of the saved ground rule.
	if(!atomsPossibleUndef.empty()){
		atomsPossibleUndefPositions.push_back(atomsPossibleUndef);
		rulesWithPossibleUndefAtoms.push_back(ground_rule);
		Rule* savedRule=ground_rule;
		ground_rule=new Rule(true, currentRule->getSizeHead(), currentRule->getSizeBody());
		for(unsigned i=0;i<currentRule->getSizeBody();i++){
			Atom* atom=savedRule->getAtomInBody(i);
			if(atom!=nullptr && ((atom->isClassicalLiteral() && atom->isNegative()) || atom->isAggregateAtom()))
				substiteInGroundRule(i,atom->clone());
			else
				substiteInGroundRule(i,atom);
			ground_rule->setAtomToSimplifyInBody(i,savedRule->isAtomToSimplifyInBody(i));
		}
	}
	//Print if ground new atom, an atom changed from undef to true, the rule is a strong constraint, there are some undefined atom in body
	else if( ground_new_atom || (!ground_new_atom && !head_true) || (find_new_true_atom && head_true) || ground_rule->isAStrongConstraint() || ground_rule->areThereUndefinedAtomInBody()){
		outputBuilder->onRule(ground_rule);
	}

	if(ground_rule->isAStrongConstraint() && !ground_rule->areThereUndefinedAtomInBody()){throw ConstrainException{};};

	return ground_new_atom;
}

bool BackTrackingGrounder::back() {

	direction=0;
	if(callFoundAssignment){
		callFoundAssignment=false;
		removeBindValueFromAssignment(atoms_bind_variables[index_current_atom]);
		return true;
	}

	callFoundAssignment = false;
	if (index_current_atom <=  0)
		return false;


	--index_current_atom;

	while (is_bound_atom[index_current_atom]){
		if (index_current_atom <= 0){

			return false;
		}

		if(atoms_bind_variables[index_current_atom].size()>0)
			removeBindValueFromAssignment(atoms_bind_variables[index_current_atom]);

		--index_current_atom;

	}

	removeBindValueFromAssignment(atoms_bind_variables[index_current_atom]);
	generateTemplateAtom();
	return true;
}

void BackTrackingGrounder::inizialize(Rule* rule) {
	direction=1;
	currentRule=rule;
	index_current_atom = 0;
	callFoundAssignment = false;
	for(auto atom:templateSetAtom) {if(atom!=nullptr) atom->deleteAtoms(); delete atom;}
	templateSetAtom.resize(rule->getSizeBody());
	for(auto& atom:templateSetAtom) atom=nullptr;
	is_bound_atom.clear();
	findBindVariablesRule();
	findSearchTables();
	if(rule->getSizeBody()>0)
		generateTemplateAtom();
	findBuiltinFastEvaluated();

	if(ground_rule==0)
		ground_rule=new Rule(true, rule->getSizeHead(), rule->getSizeBody());
	else{
		ground_rule->deleteGroundRule();
		ground_rule=new Rule(true, rule->getSizeHead(), rule->getSizeBody());
	}
	atomsPossibleUndef.clear();


}

void BackTrackingGrounder::findBindVariablesRule() {

	set_term total_variable;
	unsigned int index_current_atom = 0;
	atoms_bind_variables.clear();
	atoms_bind_variables.resize(currentRule->getSizeBody());
	variablesBinder.setSize(currentRule->getVariablesSize(),0);

//	map_term<index_object> variableLocalIndex;

	//For each atom determines the bound and the bind variables
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); ++current_atom_it,++index_current_atom) {
		Atom *current_atom = *current_atom_it;

		set_term variablesInAtom =current_atom->getVariable();
//		for(auto term:variablesInAtom){
//			auto find=variableLocalIndex.find(term);
//			if(find==variableLocalIndex.end()){
//				variableLocalIndex[term]=variableLocalIndex.size()+1;
//				term->setLocalVariableIndex(variableLocalIndex[term]);
//
//				trace_action_tag(backtracking,1,
//					cerr<<"VARIABLE-INDEX : ";term->print(cerr);cerr<<" = "<<variableLocalIndex[term]<<endl;
//				);
//			}
//		}

		if(current_atom->isAggregateAtom())
			variablesInAtom=current_atom->getGuardVariable();

		atoms_bind_variables[index_current_atom].reserve(variablesInAtom.size());
		for (auto variable : variablesInAtom) {
			if (!total_variable.count(variable)){
				unsigned var=variable->getLocalVariableIndex();
				atoms_bind_variables[index_current_atom].push_back(var);
				variablesBinder[var]=index_current_atom;
			}
		}

		total_variable.insert(variablesInAtom.begin(),variablesInAtom.end());
		///Set true if is ground
		if(is_bound_atom.size()<=index_current_atom)
			is_bound_atom.push_back((current_atom->isBuiltIn() || (current_atom->isClassicalLiteral() && current_atom->isNegative()) || (atoms_bind_variables[index_current_atom].size()==0 && !current_atom->containsAnonymous()) ));

	}

	current_assignment.setSize(currentRule->getVariablesSize(),nullptr);


	trace_action_tag(backjumping,1,cerr<<"VARIABLES BINDER: ";
		for(unsigned i=0;i<currentRule->getSizeBody();++i){
			cerr<<variablesBinder[i]<<" ";
		}
		cerr<<endl;
	);


	trace_action_tag(backtracking,1,
		cerr<<"BINDER OF ATOMS: ";int i=0;
		for(auto v:atoms_bind_variables){
			cerr<<"ATOM"<<i<<"[ ";
			for(auto binder:v){
				cerr<<binder<<" ";
			}
			cerr<<"] ";
			i++;
		}
		cerr<<endl;
	);
}

void BackTrackingGrounder::findSearchTables() {
	unsigned sizeRule=currentRule->getSizeBody();
	//TODO AVOID CLEAR
	current_id_match.clear();
	current_id_match.reserve(sizeRule);
	current_id_match_iterator.reserve(sizeRule);
	for (unsigned index_current_atom = 0; index_current_atom < sizeRule; ++index_current_atom) {
		//find the table to search for each atom in the body
		current_id_match.emplace_back();
		Predicate *predicate=currentRule->getAtomInBody(index_current_atom)->getPredicate();
		if(predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom].size()==0){
			current_id_match[index_current_atom].push_back({0,NO_MATCH});
		}
		else{
			for(unsigned i=0;i<predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom].size();++i){
				if(predicate!=nullptr){
					int tableToSearch=predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom][i];
					predicateExtTable->getPredicateExt(predicate)->getAtomSearcher(tableToSearch)->setSizeResultVector(sizeRule);
				}
				current_id_match[index_current_atom].push_back({predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom][i],NO_MATCH});
			}
		}
		current_id_match_iterator[index_current_atom]=0;

	}

}

void BackTrackingGrounder::removeBindValueFromAssignment(const vector<index_object>& bind_variables) {

	for (auto variable : bind_variables)
		current_assignment[variable]=nullptr;

}

/*
 * For each atom in the body of the rule, find an a BuiltinAtom that is not an assignment. Then find the greates atom that bind some of the variable
 * in the builtin that is an a classical literal. After that the greatest binder is founded we have to find the rightmost variable ,in the classical literal, is also in the builtin.
 * Then the variable selected in the classical literal have to evaluate the built-in while do the matchTerm.
 */
void BackTrackingGrounder::findBuiltinFastEvaluated(){
	builtAlreadyEvaluated.clear();
	builtAlreadyEvaluated.resize(currentRule->getSizeBody(),false);
	matchBuiltin.clear();
	matchBuiltin.resize(currentRule->getSizeBody());
	unsigned index_current_atom=0;
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); ++current_atom_it,++index_current_atom) {
		Atom *atom=*current_atom_it;
		if(atom->isBuiltIn() && !atom->isAssignment()){
			//Find the greatest classical literal that bind some variable in the builtin
			auto varInBuiltin=atom->getVariable();
			unsigned positionAtomBinder=0;
			for(auto var:varInBuiltin)
				if(variablesBinder[var->getLocalVariableIndex()]>positionAtomBinder)
					positionAtomBinder=variablesBinder[var->getLocalVariableIndex()];
			Atom* atomBinder=currentRule->getAtomInBody(positionAtomBinder);
			if(atomBinder->isClassicalLiteral()){
				//Find the rightmost variable in the classical literal that is contained also in the builtin
				list<Term*> termsInAtom;
				for(unsigned i=0;i<atomBinder->getTermsSize();i++)
					termsInAtom.push_back(atomBinder->getTerm(i));
				while(termsInAtom.size()>0){
					Term *lastTerm=termsInAtom.back();
					termsInAtom.pop_back();
					if(lastTerm->getType()==VARIABLE && varInBuiltin.count(lastTerm)){
						//VARIABLE FINDED, then the builtin can be evaluated while matching the term in the classical literal
						builtAlreadyEvaluated[index_current_atom]=true;
						matchBuiltin[positionAtomBinder].push_back(atom);
						currentRule->addBounderBuiltin(lastTerm->getLocalVariableIndex(),atom);
						break;
					}else if(lastTerm->getType()==FUNCTION){
						//Term is function, then put in the list the term and recursively check if exist the varaible
						for(unsigned i=0;i<lastTerm->getTermsSize();i++)termsInAtom.push_back(lastTerm->getTerm(i));
					}
				}
			}
		}
	}

}


/*
 * Check if the rule contains only classical positive atoms and all the variable is bind
 */
bool BackTrackingGrounder::isCartesianProductRule(Rule *currentRule){
	unsigned index_current_atom=0;
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); ++current_atom_it,++index_current_atom) {
		Atom *current_atom = *current_atom_it;
		if(! (current_atom->isClassicalLiteral() && !current_atom->isNegative()))
			return false;
		unsigned sizeVar=0;
		for(unsigned i=0;i<current_atom->getTermsSize();i++){
			Term *term=current_atom->getTerm(i);
			if(term->getType()!=VARIABLE)return false;
			sizeVar++;
		}
		if(sizeVar==0 || sizeVar!=atoms_bind_variables[index_current_atom].size())
			return false;
	}
	return true;
}

/*
 * ground a rule with only cartesian product. tables contain a vector of the atoms to search, and two index. The first
 * is the index of the table to search and the second is the the index of the AtomVector. Thsi method simulate the groundRule procedure
 * but is more light, because we know that the atom not share variable and then we have to search in the AtomVector all the combinations
 *
 */
void BackTrackingGrounder::groundCartesian(Rule* rule){
	unsigned size=rule->getSizeBody();
	vector<tuple<vector<AtomVector*>,unsigned,unsigned>> tables;

	int i=0;
	for(i=0;i<rule->getSizeBody();i++){
		Predicate *predicate=rule->getAtomInBody(i)->getPredicate();
		vector<AtomVector*> tableToSearch;
		for(auto table:predicate_searchInsert_table[i+rule->getSizeHead()]){
			tableToSearch.push_back(predicateExtTable->getPredicateExt(predicate)->getAtomVector(table));
		}
		tables.push_back(make_tuple(tableToSearch,0,0));
	}

	i=0;
	while(true){
		if(i==-1)
			break;

		if((unsigned)i==size){
			foundAssignment();
			--i;
			continue;
		}


		if(get<1>(tables[i])>=get<0>(tables[i]).size()){
			get<1>(tables[i])=0;
			get<2>(tables[i])=0;
			--i;
			continue;
		}

		AtomVector *vec=get<0>(tables[i])[get<1>(tables[i])];
		if(get<2>(tables[i])>=vec->size()){
			get<2>(tables[i])=0;
			get<1>(tables[i])=get<1>(tables[i])+1;
			continue;
		}
		Atom * atom=(*vec)[get<2>(tables[i])];

		ground_rule->setAtomInBody(i,atom);
		ground_rule->setAtomToSimplifyInBody(i,atom->isFact());
		if(!rule->isAStrongConstraint()){
			Atom *nonGroundAtom=rule->getAtomInBody(i);
			for(unsigned j=0;j<atom->getTermsSize();j++)
				current_assignment[nonGroundAtom->getTerm(j)->getLocalVariableIndex()]=atom->getTerm(j);
		}

		get<2>(tables[i])=get<2>(tables[i])+1;
		++i;
	}


//	for(auto atom1:*predicateExtTable->getPredicateExt(rule->getAtomInBody(0)->getPredicate())->getAtomVector(NOFACT)){
//		ground_rule->setAtomInBody(0,atom1);
//		for(auto atom2:*predicateExtTable->getPredicateExt(rule->getAtomInBody(1)->getPredicate())->getAtomVector(NOFACT)){
//			ground_rule->setAtomInBody(1,atom2);
//			foundAssignment();
//		}
//	}
}

bool BackTrackingGrounder::groundAggregate() {
	Atom *aggregateAtom=templateSetAtom[index_current_atom];

	//Check if we can simplify without evaluate the aggregate
	bool alwaysTrue;
	if(aggregateAtom->checkAggregateSumCountStringGuard(alwaysTrue) || aggregateAtom->checkAggregateCountNegativeGuard(alwaysTrue)){
		substiteInGroundRule(index_current_atom,nullptr);
		ground_rule->setAtomToSimplifyInBody(index_current_atom,true);
		return alwaysTrue;
	}

	Atom *ground_aggregate;
	if(aggregateAtom->isAnAssigment() && ground_rule->getAtomInBody(index_current_atom)!=nullptr){
		//An assignment is in the lower guard
		//The atom is already grounded, just change the guard
		ground_aggregate=ground_rule->getAtomInBody(index_current_atom);
		bool finish=0;
		Term* val=ground_aggregate->generateNextCombination(finish);
		if(finish){
			substiteInGroundRule(index_current_atom,nullptr);
			return false;
		}

		ground_aggregate->setFirstGuard(val);
		current_assignment[aggregateAtom->getFirstGuard()->getLocalVariableIndex()]=val;
		return true;
	}
	//Create a ground aggregate empty and set the aggregate to not simplify
	ground_aggregate=new AggregateAtom(aggregateAtom->getFirstGuard(),aggregateAtom->getFirstBinop(),aggregateAtom->getSecondGuard(),aggregateAtom->getSecondBinop(),aggregateAtom->getAggregateFunction(),aggregateAtom->isNegative());
	ground_rule->setAtomToSimplifyInBody(index_current_atom,false);

	set_term variablesInAtom;

	ResultEvaluation result=UNDEF;
	for(unsigned i=0;i<aggregateAtom->getAggregateElementsSize()&&result==UNDEF;i++){

		// For each atom in the aggregate element (is assumed to be one because the rewriting)
		// search in the table of fact and nofact the extension and put in the ground aggregate all the extension
		// with a new aggregate element
		// For reasoning of correctness the current assignment have to be copied for maintaining the current assignment

		Atom* atom=aggregateAtom->getAggregateElement(i)->getNafLiteral(0);
		Predicate *predicate_atom=atom->getPredicate();
		vector<unsigned> tablesToSearch={FACT,NOFACT};
		variablesInAtom=atom->getVariable();

		int counter=0;
		for(unsigned j=0;j<tablesToSearch.size()&&result==UNDEF;j++){

			unsigned table=tablesToSearch[j];
			AtomSearcher *searcher=predicateExtTable->getPredicateExt(predicate_atom)->getAtomSearcher(table);
			bool find=false;
			Atom* atomFound=nullptr;

			//Each aggregate element have one atom with no relation with the other atoms in the aggregate elements, then we can
			//overwrite the general iterator in the Atom Searcher with index_current_atom
			searcher->firstMatch(index_current_atom,atom,current_assignment,atomFound,currentRule->getRuleInformation());
			find=(atomFound!=nullptr);
			while(find){
				counter++;

				AggregateElement *ground_aggregateElement=new AggregateElement;
				ground_aggregateElement->addNafLiterals(atomFound);

				//Add the id ground term in the ground aggregate element
				for(auto term_aggregateElement:aggregateAtom->getAggregateElement(i)->getTerms()){
					if(term_aggregateElement->getType()==VARIABLE)
						ground_aggregateElement->addTerm(current_assignment[term_aggregateElement->getLocalVariableIndex()]);
					else if(term_aggregateElement->getType()==FUNCTION){
						ground_aggregateElement->addTerm(term_aggregateElement->substitute(current_assignment));
					}
				}

				ground_aggregate->addAggregateElement(ground_aggregateElement);
				result=ground_aggregate->partialEvaluate();

				//Remove bind variables of template atom in the ground aggregate element
				//IF REMOVE TEMPLATE ATOM THIS NOT WORK because the variables in the template atom
				//are bind variable
				for(auto variableBind:variablesInAtom)
					current_assignment[variableBind->getLocalVariableIndex()]=nullptr;

				if(result!=UNDEF || atom->isGround())break;

				searcher->nextMatch(index_current_atom,atom,current_assignment,atomFound,currentRule->getRuleInformation());
				find=(atomFound!=nullptr);
			}
		}
	}

	if(result==UNDEF)
		result=ground_aggregate->finalEvaluate();

	//If is a first assignment set the initial value of the guard to the partial value
	if(ground_aggregate->isAnAssigment()){
		bool finish=0;
		Term* val=ground_aggregate->generateNextCombination(finish);

		current_assignment[ground_aggregate->getFirstGuard()->getLocalVariableIndex()]=val;
		ground_aggregate->setFirstGuard(val);

		if(!ground_aggregate->isUndefAssignment())
			ground_rule->setAtomToSimplifyInBody(index_current_atom);
	}

	substiteInGroundRule(index_current_atom,nullptr);

	if(( ground_aggregate->getAggregateElementsSize()==0 && !aggregateAtom->isAnAssigment() ) || result!=UNDEF)
	{
		delete ground_aggregate;
		ground_rule->setAtomToSimplifyInBody(index_current_atom);
		if(result==UNSATISFY)
			return false;

		//Aggregate is satisfy
		return true;
	}

	ground_rule->setAtomInBody(index_current_atom,ground_aggregate);
	return true;
}

void BackTrackingGrounder::groundChoice(bool& find_new_true_atom,bool& ground_new_atom){
	Atom* searchAtom=nullptr;
	Atom* ground_choice=new Choice;
	Atom *choice=currentRule->getAtomInHead(0);

	for(unsigned i=0;i<choice->getChoiceElementsSize();i++){

		Atom *atom_in_choice=choice->getChoiceElement(i)->getFirstAtom();

		Atom *headGroundAtom=nullptr;
		atom_in_choice->ground(current_assignment,headGroundAtom);
		PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(headGroundAtom->getPredicate());
		searchAtom=predicateExt->getAtom(headGroundAtom);

		if(searchAtom==nullptr){
			ground_new_atom = true;

			headGroundAtom->setFact(false);
			for(unsigned i=0;i<predicate_searchInsert_table[0].size();++i)
				predicateExt->addAtom(predicate_searchInsert_table[0][i],headGroundAtom);

			ground_choice->addSingleChoiceElement(headGroundAtom);
		}else{
			delete headGroundAtom;

			//Check if previous is false now is true ground_new atom i have put true
			ground_choice->addSingleChoiceElement(searchAtom);
		}

	}
	Atom* currentGroundChoice=ground_rule->getAtomInHead(0);
	if(currentGroundChoice!=0)
		delete currentGroundChoice;
	ground_rule->setAtomInHead(0,ground_choice);
}


} /* namespace grounder */
} /* namespace DLV2 */

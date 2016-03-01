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

		IndexingStructure *searcher=nullptr;
		Atom* atomFound=nullptr;
		if(current_table<predicate_searchInsert_atomSearcher[index_current_atom+currentRule->getSizeHead()][0].size()){
			searcher=predicate_searchInsert_atomSearcher[index_current_atom+currentRule->getSizeHead()][0][current_table];
			atomFound=searcher->find(templateAtom);
		}

		//Initialize false for negative atom
		bool undef=false;

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
		while(!atomsPossibleUndef.empty() && int(atomsPossibleUndef.back())>=index_current_atom)
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
	PredicateExtension* predicateExtension=predicateExtTable->getPredicateExt(templateAtom->getPredicate());

	while(current_table<n_table){

		unsigned predSearch=index_current_atom+currentRule->getSizeHead();

		unsigned tableToSearch = current_id_match[index_current_atom][current_table].first;
		AtomSearcher* atomSearcher=predicateExtension->getAtomSearcher(tableToSearch);
		IndexingStructure *searcher=predicate_searchInsert_atomSearcher[predSearch][0][current_table];
		//Initialize false for negative atom
		bool undef=false;

		Atom* atomFound=nullptr;
		atomSearcher->firstMatch(index_current_atom,templateAtom,current_assignment,atomFound,currentRule->getRuleInformation(),searcher,indexingArguments[index_current_atom][0],outputVariablesInAtoms[index_current_atom],{predicate_searchInsert_table[predSearch][current_table].second,iteration});
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
	PredicateExtension* predicateExtension=predicateExtTable->getPredicateExt(templateAtom->getPredicate());

	while(current_table<n_table){

		unsigned predSearch=index_current_atom+currentRule->getSizeHead();


		unsigned tableToSearch = current_id_match[index_current_atom][current_table].first;
		bool match = current_id_match[index_current_atom][current_table].second;
		AtomSearcher* atomSearcher=predicateExtension->getAtomSearcher(tableToSearch);
		IndexingStructure *searcher=predicate_searchInsert_atomSearcher[predSearch][0][current_table];
		Atom* atomFound=nullptr;
		if(match != NO_MATCH){
			trace_action_tag(grounding,2,cerr<<"Invoked Next Match on table: "<<tableToSearch<<endl;);
			atomSearcher->nextMatch(index_current_atom,templateAtom,current_assignment,atomFound,currentRule->getRuleInformation(),outputVariablesInAtoms[index_current_atom]);
		}
		else{
			trace_action_tag(grounding,2,cerr<<"Invoked First Match on table: "<<tableToSearch<<endl;);
			atomSearcher->firstMatch(index_current_atom,templateAtom,current_assignment,atomFound,currentRule->getRuleInformation(),searcher,indexingArguments[index_current_atom][0],outputVariablesInAtoms[index_current_atom],{predicate_searchInsert_table[predSearch][current_table].second,iteration});
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
	bool undefinedAtomInBody=ground_rule->areThereUndefinedAtomInBody();
	bool strongConstraint=currentRule->isAStrongConstraint();
	bool head_true=(currentRule->getSizeHead() <= 1  && !isAChoiceRule) && (!undefinedAtomInBody);
	bool ground_new_atom=false;
	bool find_new_true_atom=false;
	bool isWeak=currentRule->isWeakConstraint();
	unsigned atom_counter=0;
	Atom *searchAtom=nullptr;
	if(isAChoiceRule){
		if(Options::globalOptions()->getRewritingType()==COMPACT_NATIVE_CHOICE)
			groundChoiceNatively(find_new_true_atom,ground_new_atom);
		else
			groundChoice(find_new_true_atom,ground_new_atom);
	}

	bool foundATrueAtomInDisjuction=false;

	for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead()&&!isAChoiceRule;++atom,++atom_counter){

		// When grounding head atoms, head template atoms are used in order to avoid the creation and deletion of atoms that are already present in the predicate extensions.
		// In case an atom is not already present in the predicate extension then the corresponding grounded template atom is cloned
		// and the atom obtained in this way is stored in the predicate extension.
		Atom *headGroundAtom=groundTemplateAtomHead[atom_counter];
		(*atom)->ground(current_assignment,headGroundAtom);
		searchAtom=nullptr;
		for(auto atomSearcher:predicate_searchInsert_atomSearcher[atom_counter][0]){
			if(atomSearcher==nullptr) continue;
			searchAtom=atomSearcher->find(headGroundAtom);
			if(searchAtom!=nullptr)
				break;
		}

		if(searchAtom==nullptr){
			ground_new_atom = true;

			headGroundAtom->setFact(head_true);
			if(head_true) foundATrueAtomInDisjuction=true;
			Atom* newAtom=headGroundAtom->clone();
			PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(headGroundAtom->getPredicate());
			predicateExt->addAtom(newAtom,predicate_searchInsert_table[atom_counter][0].first,iterationToInsert);

			ground_rule->setAtomInHead(atom_counter,newAtom);


		}else{
//			clock_t start=Timer::getInstance()->getClock();
			//TODO If searchAtom is true ??? {a|b. a.} o {a :- b(X,Y).b(1,1).b(1,2)|d.}

			//Previus atom is undef and now is true
			if(head_true && !searchAtom->isFact()){
				foundATrueAtomInDisjuction=true;
				searchAtom->setFact(true);
				find_new_true_atom=true;
			}
			else if(searchAtom->isFact())
				foundATrueAtomInDisjuction=true;
			//Check if previus is false now is true ground_new atom i have put true
			ground_rule->setAtomInHead(atom_counter,searchAtom);
//			clock_t end=Timer::getInstance()->getClock();
//			Timer::getInstance()->sumTime(end-start);
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
	else if( ground_new_atom || (!ground_new_atom && !head_true) || (find_new_true_atom && head_true) || strongConstraint || undefinedAtomInBody || isWeak){
		if(isWeak)
			ground_rule->setWeightLevelLabel(currentRule->groundWeightLevel(current_assignment));

		if(!foundATrueAtomInDisjuction || head_true)
			outputBuilder->onRule(ground_rule);
	}
	if(strongConstraint && !undefinedAtomInBody){throw ConstrainException{};};


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

void BackTrackingGrounder::inizialize(Rule* rule, unordered_set<index_object>* componentPredicateInHead) {
	direction=1;
	currentRule=rule;
	index_current_atom = 0;
	callFoundAssignment = false;
	for(auto atom:templateSetAtom) {if(atom!=nullptr) atom->deleteAtoms(); delete atom;}
	templateSetAtom.resize(rule->getSizeBody());
	for(auto& atom:templateSetAtom) atom=nullptr;
	is_bound_atom.clear();
	indexingArguments.clear();
	indexingArguments.resize(rule->getSizeBody());
	findBindVariablesRule();
	findSearchTables();
	if(rule->getSizeBody()>0)
		generateTemplateAtom();
	findBuiltinFastEvaluated();

	outputVariablesInAtoms.clear();
	outputVariablesInAtoms.resize(currentRule->getSizeBody());


	if(ground_rule!=0)
		ground_rule->deleteGroundRule();
	ground_rule=(currentRule->isWeakConstraint())
			? new WeakConstraint(true,rule->getSizeBody(),currentRule->getWeight(),currentRule->getLevel(),currentRule->getLabel())
			: new Rule(true, rule->getSizeHead(), rule->getSizeBody());

	atomsPossibleUndef.clear();

	if(!currentRule->isChoiceRule()){
		/// If the current rule is not a choice rule, then the vector groundTemplateAtomHead has to be filled with placeholder atoms as follows
		for(auto& atom:groundTemplateAtomHead){
			delete atom;
			atom=0;
		}
		groundTemplateAtomHead.resize(currentRule->getSizeHead(),0);

		unsigned i=0;
		for(auto headIt=currentRule->getBeginHead();headIt!=currentRule->getEndHead();++headIt,++i){
			groundTemplateAtomHead[i]=(*headIt)->clone();
		}
	}
	setDefaultAtomSearchers(rule,componentPredicateInHead);
}

void BackTrackingGrounder::findBoundTerms(unsigned int index_current_atom, unsigned position, Atom* current_atom) {
	for (unsigned j = 0; j < current_atom->getTermsSize(); ++j) {
		Term* term = current_atom->getTerm(j);
		bool anonymous = current_atom->getTerm(j)->contain(TermType::ANONYMOUS);
		if(anonymous) continue;
		if (term->getType()==TermType::STRING_CONSTANT ||  term->getType()==TermType::NUMERIC_CONSTANT || term->getType()==TermType::SYMBOLIC_CONSTANT) {
			boundTermsInAtoms[index_current_atom][position].push_back(j);
			continue;
		}
		set_term vars;
		term->getVariable(vars);
		bool bound = true;
		for(auto v:vars){
			unsigned localIdx=v->getLocalVariableIndex();
			if(variablesBinder[localIdx]==-1 || (index_current_atom<currentRule->getSizeHead() && localIdx==0) || (index_current_atom>=currentRule->getSizeHead() && variablesBinder[localIdx]>=0 && unsigned(variablesBinder[localIdx])>=index_current_atom-currentRule->getSizeHead())){
				bound=false;
				break;
			}
		}
		if (bound){
			boundTermsInAtoms[index_current_atom][position].push_back(j);
		}
	}
}

void BackTrackingGrounder::findBindVariablesRule() {

	set_term total_variable;
	unsigned int index_current_atom = 0;
	atoms_bind_variables.clear();
	atoms_bind_variables.resize(currentRule->getSizeBody());
	variablesBinder.setSize(currentRule->getVariablesSize(),-1);
	boundTermsInAtoms.clear();
	unsigned sizeHead=currentRule->getSizeHead();
	boundTermsInAtoms.resize(currentRule->getSizeBody()+sizeHead);

	//For each atom determines the bound and the bind variables
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); ++current_atom_it,++index_current_atom) {
		Atom *current_atom = *current_atom_it;

		set_term variablesInAtom =current_atom->getVariable();

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
		if(is_bound_atom.size()<=index_current_atom){
			is_bound_atom.push_back((current_atom->isBuiltIn() || (current_atom->isClassicalLiteral() && current_atom->isNegative()) || (atoms_bind_variables[index_current_atom].size()==0 && !current_atom->containsAnonymous()) ));
		}

		if(current_atom->isClassicalLiteral()){
			indexingArguments[index_current_atom].resize(1);
			boundTermsInAtoms[index_current_atom+sizeHead].push_back(vector<unsigned>());
			boundTermsInAtoms[index_current_atom+sizeHead][0].reserve(current_atom->getTermsSize());
			findBoundTerms(index_current_atom+sizeHead, 0, current_atom);
		}
		else if(current_atom->isAggregateAtom()){
			indexingArguments[index_current_atom].resize(current_atom->getAggregateElementsSize());
			for(unsigned ag=0;ag<current_atom->getAggregateElementsSize();++ag){
				boundTermsInAtoms[index_current_atom+sizeHead].push_back(vector<unsigned>());
				boundTermsInAtoms[index_current_atom+sizeHead][ag].reserve(current_atom->getTermsSize());
				findBoundTerms(index_current_atom+sizeHead, ag, current_atom->getAggregateElement(ag)->getNafLiteral(0));
			}
		}
	}

	if(Options::globalOptions()->getRewritingType()==COMPACT_NATIVE_CHOICE){
		index_current_atom=0;
		for (auto current_atom_it = currentRule->getBeginHead(); current_atom_it != currentRule->getEndHead(); ++current_atom_it) {
			Atom *current_atom = *current_atom_it;
			if(current_atom->isChoice()){
				for(unsigned i=0;i<current_atom->getChoiceElementsSize();++i){
					Atom* atomInChoice=current_atom->getChoiceElement(i)->getAtom(1);
					if(atomInChoice!=nullptr){
						boundTermsInAtoms[index_current_atom].push_back(vector<unsigned>());
						boundTermsInAtoms[index_current_atom][i].reserve(atomInChoice->getTermsSize());
						findBoundTerms(index_current_atom, i, atomInChoice);
					}
				}
			}
		}
	}

	current_assignment.setSize(currentRule->getVariablesSize(),nullptr);


	trace_action_tag(backjumping,1,cerr<<"VARIABLES BINDER: ";
		for(unsigned i=0;i<currentRule->getVariablesSize();++i){
			cerr<<"var "<<i<<variablesBinder[i]<<endl;
		}
	);

	trace_action_tag(backtracking,1,
		cerr<<"BINDER OF ATOMS: ";
		int i=0;
		for(auto v:atoms_bind_variables){
			cerr<<"ATOM "<<i<<" [ ";
			for(auto binder:v){
				cerr<<binder<<" ";
			}
			cerr<<"] ";
			i++;
		}
		cerr<<endl;
	);

//	for(unsigned i=0;i<boundTermsInAtoms.size();++i){
//		if(i<sizeHead)
//			currentRule->getAtomInHead(i)->print();
//		else
//			currentRule->getAtomInBody(i-sizeHead)->print();
//		cout<<"\t";
//		for(auto j:boundTermsInAtoms[i])
//			for(auto a:j)
//				cout<<a<<" ";
//		cout<<endl;
//	}
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
		if(predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom].size()==0){
			current_id_match[index_current_atom].push_back({0,NO_MATCH});
		}
		else{
			for(unsigned i=0;i<predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom].size();++i){
				current_id_match[index_current_atom].push_back({predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom][i].first,NO_MATCH});
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
	currentRule->clearBounderBuiltin();
	unsigned index_current_atom=0;
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); ++current_atom_it,++index_current_atom) {
		Atom *atom=*current_atom_it;
		if(atom->isBuiltIn() && !atom->isAssignment()){
			//Find the greatest classical literal that bind some variable in the builtin
			auto varInBuiltin=atom->getVariable();
			unsigned positionAtomBinder=0;
			for(auto variable:varInBuiltin)
				if(variablesBinder[variable->getLocalVariableIndex()]>(int)positionAtomBinder)
					positionAtomBinder=variablesBinder[variable->getLocalVariableIndex()];

			Atom * possibleBinder=currentRule->getAtomInBody(positionAtomBinder);
			if(possibleBinder->isClassicalLiteral()){
				set_term variablePossibleBinder=possibleBinder->getVariable();
				if(possibleBinder->isClassicalLiteral()){
					vector<Term*> variable=possibleBinder->getVectorVariable();

					//Find the rightmost variable in the classical literal that is contained also in the builtin
					for(int i=variable.size()-1;i>=0;--i){
						Term *lastTerm=variable[i];
						if(lastTerm->getType()==VARIABLE && varInBuiltin.count(lastTerm) && variablesBinder[lastTerm->getLocalVariableIndex()]==(int)positionAtomBinder){
								//VARIABLE FINDED, then the builtin can be evaluated while matching the term in the classical literal
								builtAlreadyEvaluated[index_current_atom]=true;
								matchBuiltin[positionAtomBinder].push_back(atom);
								currentRule->addBounderBuiltin(lastTerm->getLocalVariableIndex(),atom);
								break;
							}
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
		if(current_atom->isBuiltIn() && builtAlreadyEvaluated[index_current_atom])
			continue;
		if(! (current_atom->isClassicalLiteral() && !current_atom->isNegative())){
			return false;
		}
		unsigned sizeVar=0;
		for(unsigned i=0;i<current_atom->getTermsSize();i++){
			Term *term=current_atom->getTerm(i);
			if(!(term->getType()==VARIABLE || term->getType()==ANONYMOUS)){
				return false;
			}
			if(term->getType()==VARIABLE)
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
bool BackTrackingGrounder::groundCartesian(Rule* rule){
	unsigned size=rule->getSizeBody();
	vector<tuple<vector<AtomHistoryVector*>,unsigned,unsigned>> tables(rule->getSizeBody());

	int i=0;
	for(i=0;(unsigned)i<rule->getSizeBody();i++){
		Predicate *predicate=rule->getAtomInBody(i)->getPredicate();
		if(predicate==nullptr){
			ground_rule->setAtomToSimplifyInBody(i,true);
			continue;
		}
		vector<AtomHistoryVector*> tableToSearch;
		for(auto table:predicate_searchInsert_table[i+rule->getSizeHead()]){
			tableToSearch.push_back(predicateExtTable->getPredicateExt(predicate)->getTable(table.first));
		}

		tables[i]=(make_tuple(tableToSearch,0,0));
	}

	bool ground_new_atom=false;

	i=0;
	direction=true;
	while(true){
		if(i==-1)
			break;

		if((unsigned)i==size){
			if(foundAssignment())
				ground_new_atom=true;
			--i;
			direction=false;
			continue;
		}

		if(currentRule->getAtomInBody(i)->isBuiltIn()){
			if(direction)
				++i;
			else
				--i;
			continue;
		}

		if(get<1>(tables[i])>=get<0>(tables[i]).size()){
			get<1>(tables[i])=0;
			get<2>(tables[i])=0;
			--i;
			direction=false;
			continue;
		}

		AtomHistoryVector *vec=get<0>(tables[i])[get<1>(tables[i])];
		if(get<2>(tables[i])>=vec->size()){
			get<2>(tables[i])=0;
			get<1>(tables[i])=get<1>(tables[i])+1;
			continue;
		}

		bool match=true;
		Atom * atom=(*vec)[get<2>(tables[i])];
		Atom *nonGroundAtom=rule->getAtomInBody(i);
		for(unsigned j=0;j<atom->getTermsSize();j++){
			if(atom->getTerm(j)->getType()==ANONYMOUS)continue;
			current_assignment[nonGroundAtom->getTerm(j)->getLocalVariableIndex()]=atom->getTerm(j);
			if(currentRule->getRuleInformation().isBounderBuiltin(nonGroundAtom->getTerm(j)->getLocalVariableIndex())){
				match=AtomSearcher::evaluateFastBuiltin(currentRule->getRuleInformation(),nonGroundAtom->getTerm(j)->getLocalVariableIndex(),current_assignment,atom->getTerm(j));
				if(!match)break;
			}
		}

		if(match){
			ground_rule->setAtomInBody(i,atom);
			ground_rule->setAtomToSimplifyInBody(i,atom->isFact());
			get<2>(tables[i])=get<2>(tables[i])+1;
			++i;
			direction=true;
		}else
			get<2>(tables[i])=get<2>(tables[i])+1;

	}


//	for(auto atom1:*predicateExtTable->getPredicateExt(rule->getAtomInBody(0)->getPredicate())->getAtomVector(NOFACT)){
//		ground_rule->setAtomInBody(0,atom1);
//		for(auto atom2:*predicateExtTable->getPredicateExt(rule->getAtomInBody(1)->getPredicate())->getAtomVector(NOFACT)){
//			ground_rule->setAtomInBody(1,atom2);
//			foundAssignment();
//		}
//	}

	return ground_new_atom;
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
	unsigned numTables=predicate_searchInsert_table[index_current_atom+currentRule->getSizeHead()].size();

	ResultEvaluation result=UNDEF;
	for(unsigned i=0;i<aggregateAtom->getAggregateElementsSize()&&result==UNDEF;i++){

		// For each atom in the aggregate element (is assumed to be one because the rewriting)
		// search in the table of fact and nofact the extension and put in the ground aggregate all the extension
		// with a new aggregate element
		// For reasoning of correctness the current assignment have to be copied for maintaining the current assignment

		Atom* atom=aggregateAtom->getAggregateElement(i)->getNafLiteral(0);
		variablesInAtom=atom->getVariable();

		PredicateExtension* predicateExtension=predicateExtTable->getPredicateExt(atom->getPredicate());

		int counter=0;
		for(unsigned j=0;j<numTables&&result==UNDEF;j++){

			unsigned table=predicate_searchInsert_table[index_current_atom+currentRule->getSizeHead()][j].first;
			IndexingStructure *searcher=predicate_searchInsert_atomSearcher[index_current_atom+currentRule->getSizeHead()][i][j];
			AtomSearcher* atomSearcher=predicateExtension->getAtomSearcher(table);

			if(searcher==nullptr) continue;
			bool find=false;
			Atom* atomFound=nullptr;

			//Each aggregate element have one atom with no relation with the other atoms in the aggregate elements, then we can
			//overwrite the general iterator in the Atom Searcher with index_current_atom
			atomSearcher->firstMatch(index_current_atom,atom,current_assignment,atomFound,currentRule->getRuleInformation(),searcher,indexingArguments[index_current_atom][i],vector<unsigned>());
			find=(atomFound!=nullptr);
			while(find){
				counter++;

				AggregateElement *ground_aggregateElement=new AggregateElement;
				ground_aggregateElement->addNafLiterals(atomFound);

				//Add the id ground term in the ground aggregate element
				for(auto term_aggregateElement:aggregateAtom->getAggregateElement(i)->getTerms()){
					auto termType=term_aggregateElement->getType();
					if(termType==NUMERIC_CONSTANT || termType==STRING_CONSTANT || termType==SYMBOLIC_CONSTANT)
						ground_aggregateElement->addTerm(term_aggregateElement);
					else if(termType==VARIABLE)
						ground_aggregateElement->addTerm(current_assignment[term_aggregateElement->getLocalVariableIndex()]);
					else if(termType==FUNCTION){
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

				atomSearcher->nextMatch(index_current_atom,atom,current_assignment,atomFound,currentRule->getRuleInformation(),vector<unsigned>());
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
//		searchAtom=predicateExt->getAtom(headGroundAtom);

//		for(unsigned j=i*numTables;j<(i*numTables)+numTables;j++){
		for(unsigned j=0;j<predicate_searchInsert_atomSearcher[0][i].size();++j){
			auto *searcher=predicate_searchInsert_atomSearcher[0][i][j];
			if(searcher==nullptr) continue;
			searchAtom=searcher->find(headGroundAtom);
			if(searchAtom!=nullptr){
				break;
			}
		}

		if(searchAtom==nullptr){
			ground_new_atom = true;

			headGroundAtom->setFact(false);
//			for(unsigned i=0;i<predicate_searchInsert_table[0].size();++i)
				predicateExt->addAtom(headGroundAtom,predicate_searchInsert_table[0][0].first,iterationToInsert);

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


void BackTrackingGrounder::groundChoiceNatively(bool& find_new_true_atom,bool& ground_new_atom){
	Atom* searchAtom=nullptr;
	Atom* ground_choice=new Choice;
	Atom *choice=currentRule->getAtomInHead(0);
	unsigned numChoiceElements=choice->getChoiceElementsSize();
	vector<Atom*> templateAtomsInChoice;
	templateAtomsInChoice.resize(numChoiceElements,nullptr);

	for(unsigned i=0;i<numChoiceElements;i++){
		Atom* innerAtom=choice->getChoiceElement(i)->getAtom(1);
		//TODO Se il primo atomo è un built in
		if(innerAtom!=nullptr && innerAtom->isClassicalLiteral()){
			Atom* atomFound=nullptr;
			vector<unsigned> bind_variables;
			for(unsigned a=0;a<innerAtom->getPredicate()->getArity();++a){
				bool bind=true;
				for(auto b: boundTermsInAtoms[0][i]){
					if(a==b){
						bind=false;
						break;
					}
				}
				if(bind)
					bind_variables.push_back(innerAtom->getTerm(a)->getLocalVariableIndex());
			}
			if(templateAtomsInChoice[i]==nullptr)
				innerAtom->ground(current_assignment,templateAtomsInChoice[i]);

			PredicateExtension* predicateExt=predicateExtTable->getPredicateExt(innerAtom->getPredicate());
			bool firstMatch=true;
			unsigned table=0;
			IndexingStructure* indexingStructure=0;

			while(table<=1){
				AtomSearcher* atomSearcher=predicateExt->getAtomSearcher(table);
				unsigned indexStruct=predicate_searchInsert_atomSearcher[0][i].size()-(1+table);
				indexingStructure=predicate_searchInsert_atomSearcher[0][i][indexStruct];

				if(indexingStructure==nullptr){
					table++;
					firstMatch=true;
					continue;
				}

				if(bind_variables.empty()){
					atomFound=atomSearcher->findGroundAtom(templateAtomsInChoice[i],indexingStructure);
					table++;
					if(atomFound==nullptr)
						continue;
				}
				else{
					if(firstMatch){
						atomSearcher->firstMatch(i,templateAtomsInChoice[i],current_assignment,atomFound,currentRule->getRuleInformation(),indexingStructure,0,vector<unsigned>(),{ALL,0});
						if(atomFound==nullptr){
							table++;
							continue;
						}
						else
							firstMatch=false;
					}
					else{
						atomSearcher->nextMatch(i,templateAtomsInChoice[i],current_assignment,atomFound,currentRule->getRuleInformation(),vector<unsigned>());
						if(atomFound==nullptr){
							table++;
							firstMatch=true;
							continue;
						}
					}
				}

				Atom *atom_in_choice=choice->getChoiceElement(i)->getFirstAtom();
				Atom *headGroundAtom=nullptr;
				atom_in_choice->ground(current_assignment,headGroundAtom);
				PredicateExtension* predicateExt1=predicateExtTable->getPredicateExt(headGroundAtom->getPredicate());

				for(unsigned j=0;j<predicate_searchInsert_atomSearcher[0][i].size()-2;++j){
					auto *searcher=predicate_searchInsert_atomSearcher[0][i][j];
					if(searcher==nullptr) continue;
					searchAtom=searcher->find(headGroundAtom);
					if(searchAtom!=nullptr){
						break;
					}
				}

				if(searchAtom==nullptr){
					ground_new_atom = true;

					headGroundAtom->setFact(false);
					predicateExt1->addAtom(headGroundAtom,predicate_searchInsert_table[0][0].first,iterationToInsert);

//					if(atomFound!=nullptr){
//						ChoiceElement* choiceElement=new ChoiceElement;
//						choiceElement->add(headGroundAtom);
//						choiceElement->add(atomFound);
//						ground_choice->addChoiceElement(choiceElement);
//					}
//					else
						ground_choice->addSingleChoiceElement(headGroundAtom);

				}else{
					searchAtom->print();
					delete headGroundAtom;

					//Check if previous is false now is true ground_new atom i have put true
					ground_choice->addSingleChoiceElement(searchAtom);
				}
				removeBindValueFromAssignment(bind_variables);
			}
		}
	}


	Atom* currentGroundChoice=ground_rule->getAtomInHead(0);
	if(currentGroundChoice!=0)
		delete currentGroundChoice;
	ground_rule->setAtomInHead(0,ground_choice);

	for(unsigned i=0;i<numChoiceElements;i++){
		delete templateAtomsInChoice[i];
	}

}

void BackTrackingGrounder::setIndexingStructureInHeadAndBody(unsigned position, unsigned atomPos,
		PredicateExtension* predicateExtension, Predicate* predicate,
		unordered_set<index_object>* componentPredicateInHead, unsigned table) {

		predicateExtension->getAtomSearcher(table)->setSizeResultVector(
				currentRule->getSizeBody());
		IndexingStructure* atomSearcher=nullptr;
		if (boundTermsInAtoms[position][atomPos].size()
				== predicate->getArity()) {
			auto atomSearcherMAP = predicateExtension->getIndexingStructure(
					table, MAP);
			auto atomSearcherHASH = predicateExtension->getIndexingStructure(
					table, HASHSET);
			if (atomSearcherMAP != nullptr)
				atomSearcher = atomSearcherMAP;
			else if (atomSearcherHASH != nullptr)
				atomSearcher = atomSearcherHASH;
			else {
				vector<unsigned> terms(1, 0);
				atomSearcher = predicateExtension->addAtomSearcher(table, MAP,
						&terms);
			}
		} else if (!boundTermsInAtoms[position][atomPos].empty()) {
			int indexingTermSetByUser =
					Options::globalOptions()->getPredicateIndexTerm(
							predicate->getName());
			unsigned bestArg = 0;
			unsigned bestSelectivityArg = 0;
			unsigned nextBestArg = 0;
			unsigned nextBestSelectivityArg = 0;
			PredicateInformation* predicateInfo =
					predicateExtTable->getPredicateExt(predicate)->getPredicateInformation();
			for (auto boundArg : boundTermsInAtoms[position][atomPos]) {
				if (indexingTermSetByUser >= 0
						&& boundArg == unsigned(indexingTermSetByUser)) {
					bestArg = indexingTermSetByUser;
					break;
				}
				if (predicateInfo->getSelectivity(boundArg)
						> bestSelectivityArg) {
					nextBestSelectivityArg = bestSelectivityArg;
					nextBestArg = bestArg;
					bestSelectivityArg = predicateInfo->getSelectivity(
							boundArg);
					bestArg = boundArg;
				} else if (predicateInfo->getSelectivity(boundArg)
						== bestSelectivityArg
						|| predicateInfo->getSelectivity(boundArg)
								> nextBestSelectivityArg) {
					nextBestSelectivityArg = predicateInfo->getSelectivity(
							boundArg);
					nextBestArg = boundArg;
				}
			}
			vector<unsigned> indexingTerm(2);
			indexingTerm[0] = bestArg;
			//			cout<<"---> Predicate: "<<predicate->getName()<<endl;
			//			for(auto e: indexingTerm)
			//				cout<<e<<" ";
			//			cout<<endl;
			//			For FULL INDEXING ON EACH SINGLE ARGUMENT:
			//			atomSearcher=predicateExtension->addFullIndexAtomSearcher(table,(componentPredicateInHead!=nullptr && componentPredicateInHead->count(predicate->getIndex())));
			//			indexingArguments[position-currentRule->getSizeHead()][atomPos]=bestArg;
			if (componentPredicateInHead != nullptr
					&& componentPredicateInHead->count(predicate->getIndex())) {
				if (nextBestSelectivityArg > 0) {
					indexingTerm[1] = nextBestArg;
					atomSearcher = predicateExtension->addAtomSearcher(table,
							MAP_PAIR_HISTORY_VECTOR, &indexingTerm, true);
				} else {
					atomSearcher = predicateExtension->addAtomSearcher(table,
							MAP_HISTORY_VECTOR, &indexingTerm, true);
				}
			} else {
				if (nextBestSelectivityArg > 0) {
					indexingTerm[1] = nextBestArg;
					atomSearcher = predicateExtension->addAtomSearcher(table,
							DOUBLEMAP, &indexingTerm);
				} else {
					atomSearcher = predicateExtension->addAtomSearcher(table,
							&indexingTerm);
				}
			}
		} else {
			if (componentPredicateInHead != nullptr
					&& componentPredicateInHead->count(predicate->getIndex()))
				atomSearcher = predicateExtension->addAtomSearcher(table,
						DEFAULT_RECURSIVE, nullptr, true);
			else
				atomSearcher = predicateExtension->addAtomSearcher(table,
						DEFAULT, nullptr, false);
		}
		predicate_searchInsert_atomSearcher[position][atomPos].push_back(atomSearcher);
}

void BackTrackingGrounder::createAtomSearchersForPredicateBody(unsigned position, unsigned atomPos, Predicate* predicate, unordered_set<index_object>* componentPredicateInHead){
	PredicateExtension* predicateExtension = predicateExtTable->getPredicateExt(predicate);
	if(!predicate_searchInsert_atomSearcher[position][atomPos].empty() && atomPos==0){
		for(auto tablePair:predicate_searchInsert_table[position]){
			unsigned table=tablePair.first;
			predicateExtension->getAtomSearcher(table)->setSizeResultVector(currentRule->getSizeBody());
//			indexingArguments[position-currentRule->getSizeHead()][atomPos]=??;
		}
		return;
	}
	for (auto tablePair : predicate_searchInsert_table[position]) {
		setIndexingStructureInHeadAndBody(position, atomPos, predicateExtension, predicate, componentPredicateInHead, tablePair.first);
	}
}

void BackTrackingGrounder::createAtomSearchersForPredicateHead(unsigned position, unsigned choiceElementPos, Predicate* predicate, unordered_set<index_object>* componentPredicateInHead, bool firstAtom){
	unsigned sizeRule=currentRule->getSizeBody();
	PredicateExtension* predicateExtension = predicateExtTable->getPredicateExt(predicate);

	if(!firstAtom){
		if(predicateExtension->getPredicateExtentionSize(NOFACT))
			setIndexingStructureInHeadAndBody(position, choiceElementPos, predicateExtension, predicate, componentPredicateInHead, NOFACT);
		else
			predicate_searchInsert_atomSearcher[position][choiceElementPos].push_back(0);
		if(predicateExtension->getPredicateExtentionSize(FACT))
			setIndexingStructureInHeadAndBody(position, choiceElementPos, predicateExtension, predicate, componentPredicateInHead, FACT);
		else
			predicate_searchInsert_atomSearcher[position][choiceElementPos].push_back(0);
	}
	else{
		for(unsigned i=0;i<=predicate_searchInsert_table[position][0].first;++i){
			predicateExtension->getAtomSearcher(i)->setSizeResultVector(sizeRule);
			vector<unsigned> indexing(1,0);
			auto atomSearcher=predicateExtension->addAtomSearcher(i,MAP,&indexing);
	// 		auto atomSearcher=predicateExtension->addAtomSearcher(i,HASHSET,nullptr);
			if(i==predicate_searchInsert_table[position][0].first || predicateExtension->getPredicateExtentionSize(i))
				predicate_searchInsert_atomSearcher[position][choiceElementPos].push_back(atomSearcher);
			else
				predicate_searchInsert_atomSearcher[position][choiceElementPos].push_back(0);
		}
	}
}

} /* namespace grounder */
} /* namespace DLV2 */


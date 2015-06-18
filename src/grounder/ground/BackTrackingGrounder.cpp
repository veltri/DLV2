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


namespace DLV2 {
namespace grounder {


/// If the firstMatch on table has not been called
#define NO_MATCH -1

void BackTrackingGrounder::generateTemplateAtom(){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Generate Template");
#endif

	(*current_atom_it)->ground(current_var_assign,templateSetAtom[index_current_atom]);
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
	return (is_ground_atom[index_current_atom]);

}
bool BackTrackingGrounder::match() {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Match");
#endif

	//Avoid call multiple time method match for the ground atom in the last position of the rule
	if(isGroundCurrentAtom() && callFoundAssignment){
		return false;
	}

	if(templateSetAtom[index_current_atom]->isBuiltIn() ){

#ifdef DEBUG_RULE_TIME
		bool evaluate=templateSetAtom[index_current_atom] -> evaluate(current_var_assign);
		Timer::getInstance()->stop("Match");
		return evaluate;
#endif

		current_id_match[index_current_atom][0].second=1;
		ground_rule->setAtomToSimplifyInBody(index_current_atom);
		return templateSetAtom[index_current_atom] -> evaluate(current_var_assign);

	}else if(templateSetAtom[index_current_atom]->isAggregateAtom()){
		return groundAggregate();

	}else if(templateSetAtom[index_current_atom]->isClassicalLiteral()){

		bool match;
		unsigned current_table=current_id_match_iterator[index_current_atom];
		//if is the first table to visit and the id of first match is NO_MATCH
		if(current_table==0 && current_id_match[index_current_atom][current_table].second==NO_MATCH){
			match = firstMatch() == !templateSetAtom[index_current_atom]->isNegative();
		}else{
			match = nextMatch() == !templateSetAtom[index_current_atom]->isNegative();
		}

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Match");
#endif
		return match;
	}

	return false;

}



bool BackTrackingGrounder::firstMatch(){
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("F-Match "+boost::lexical_cast<string>(index_current_atom));
#endif


	// For each table to search call the first match until one table return find
	bool find=false;
	unsigned current_table=current_id_match_iterator[index_current_atom];
	unsigned n_table=current_id_match[index_current_atom].size();
	Atom* templateAtom=templateSetAtom[index_current_atom];
	while(current_table<n_table){
		unsigned tableToSearch = current_id_match[index_current_atom][current_table].first;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);
		//Initialize false for negative atom
		bool undef=false;

		Atom* atomFound=nullptr;
		unsigned id = searcher->firstMatch(templateAtom,current_var_assign,atomFound);
		find=(atomFound!=nullptr);
		if(atomFound!=nullptr)
			undef=!atomFound->isFact();

		if(templateAtom->isNegative() && find)
			find=!undef;

		if(templateAtom->isNegative() && !find){
			atomFound=templateAtom->clone();
			substiteInGroundRule(index_current_atom,atomFound);
			if(StatementDependency::getInstance()->isPredicateNotStratified(atomFound->getPredicate()->getIndex()))
				ground_rule->setAtomToSimplifyInBody(index_current_atom,false);
			else
				ground_rule->setAtomToSimplifyInBody(index_current_atom,!undef);
		}

		if(find){
			if(!isGroundCurrentAtom()){
				current_id_match[index_current_atom][current_table].second = id;
			}else{
				current_id_match[index_current_atom][current_table].second = NO_MATCH;
				current_id_match_iterator[index_current_atom]=0;
			}
			substiteInGroundRule(index_current_atom,atomFound);
			ground_rule->setAtomToSimplifyInBody(index_current_atom,!undef);

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("F-Match "+boost::lexical_cast<string>(index_current_atom));
#endif
			return find;
		}
		current_id_match[index_current_atom][current_table].second = NO_MATCH;
		current_id_match_iterator[index_current_atom]=++current_table;

	}
	current_id_match_iterator[index_current_atom]=0;

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("F-Match "+boost::lexical_cast<string>(index_current_atom));
#endif
	return false;
}

bool BackTrackingGrounder::nextMatch(){
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("N-Match "+boost::lexical_cast<string>(index_current_atom));
#endif
	bool find=false;
	unsigned current_table=current_id_match_iterator[index_current_atom];
	unsigned n_table=current_id_match[index_current_atom].size();
	Atom* templateAtom=templateSetAtom[index_current_atom];
	while(current_table<n_table){

		unsigned tableToSearch = current_id_match[index_current_atom][current_table].first;
		int current_id = current_id_match[index_current_atom][current_table].second;
		AtomSearcher *searcher=predicateExtTable->getPredicateExt(templateAtom->getPredicate())->getAtomSearcher(tableToSearch);
		Atom* atomFound=nullptr;

		if(current_id != NO_MATCH)
			searcher->nextMatch(current_id,templateAtom,current_var_assign,atomFound);
		else
			current_id = searcher->firstMatch(templateAtom,current_var_assign,atomFound);

		find=(atomFound!=nullptr);
		bool undef=false;
		if(atomFound!=nullptr)
			undef=!atomFound->isFact();

		if(find){
			substiteInGroundRule(index_current_atom,atomFound);
			current_id_match[index_current_atom][current_table].second = current_id;
			ground_rule->setAtomToSimplifyInBody(index_current_atom,!undef);
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("N-Match "+boost::lexical_cast<string>(index_current_atom));
#endif
			return find;
		}
		current_id_match[index_current_atom][current_table].second = NO_MATCH;
		current_id_match_iterator[index_current_atom]=++current_table;
	}
	current_id_match_iterator[index_current_atom]=0;

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("N-Match "+boost::lexical_cast<string>(index_current_atom));
#endif
	return false;
}

bool BackTrackingGrounder::next() {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Next");
#endif


	callFoundAssignment = false;
	if( unsigned(index_current_atom+1)>=currentRule->getSizeBody()){
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Next");return false;
#endif
		return false;
	}


	++current_atom_it;
	++index_current_atom;


	generateTemplateAtom();
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Next");
#endif
	return true;
}

bool BackTrackingGrounder::foundAssignment() {
	callFoundAssignment=true;
	bool head_true=(currentRule->getSizeHead() <= 1) && (!ground_rule->areThereUndefinedAtomInBody());
	bool ground_new_atom=false;
	bool find_new_true_atom=false;
	unsigned atom_counter=0;
	Atom *searchAtom=0;
	for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();++atom,++atom_counter){
		Atom *headGroundAtom=nullptr;
		(*atom)->ground(current_var_assign,headGroundAtom);

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
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Head");
#endif

	//Print if ground new atom, an atom changed from undef to true, the rule is a strong constraint, there are some undefined atom in body
	if( ground_new_atom || (find_new_true_atom && head_true) || ground_rule->isAStrongConstraint() || ground_rule->areThereUndefinedAtomInBody())
		ground_rule->print();

	if(currentRule->getSizeBody() > 0)
		removeBindValueInAssignment(current_variables_atoms[index_current_atom]);
	return ground_new_atom;
}

bool BackTrackingGrounder::back() {

	callFoundAssignment = false;
	if (index_current_atom <=  0)
		return false;

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Back");
#endif

	--current_atom_it;
	--index_current_atom;

	while (isGroundCurrentAtom()){
		if (index_current_atom <= 0){
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Back");return false;
#endif
			return false;
		}

		removeBindValueInAssignment(current_variables_atoms[index_current_atom]);

		--current_atom_it;
		--index_current_atom;

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
	callFoundAssignment = false;
	for(auto atom:templateSetAtom) {if(atom!=nullptr) atom->deleteAtoms(); delete atom;}
	templateSetAtom.resize(rule->getSizeBody());
	for(auto& atom:templateSetAtom) atom=nullptr;
	is_ground_atom.clear();
	findBindVariablesRule();
	findSearchTable();
	if(rule->getSizeBody()>0)
		generateTemplateAtom();
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Init");
#endif
	if(ground_rule==0){
		ground_rule=new Rule(true, rule->getSizeHead(), rule->getSizeBody());
	}
	else{
		for(auto it=ground_rule->getBeginBody();it!=ground_rule->getEndBody();it++)
			deleteGroundAtom(*it);
		delete ground_rule;
		ground_rule=new Rule(true, rule->getSizeHead(), rule->getSizeBody());
	}
}

void BackTrackingGrounder::findBindVariablesRule() {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Find Bind");
#endif

	set_term total_variable;
	unsigned int index_current_atom = 0;
	current_variables_atoms.clear();

	//For each atom determines the bound and the bind variables
	for (auto current_atom_it = currentRule->getBeginBody(); current_atom_it != currentRule->getEndBody(); ++current_atom_it,++index_current_atom) {
		Atom *current_atom = *current_atom_it;
		set_term variablesInAtom ;

		if(current_atom->isAggregateAtom())
			variablesInAtom=current_atom->getGuardVariable();
		else
			variablesInAtom=current_atom->getVariable();

		current_variables_atoms.push_back(set_term());

		for (auto variable : variablesInAtom) {
			if (!total_variable.count(variable))
				current_variables_atoms[index_current_atom].insert(variable);
		}

		total_variable.insert(variablesInAtom.begin(),variablesInAtom.end());

		///Set true if is ground
		if(is_ground_atom.size()<=index_current_atom)
				is_ground_atom.push_back((current_atom->isBuiltIn() || (current_atom->isClassicalLiteral() && current_atom->isNegative()) || current_variables_atoms[index_current_atom].size()==0));

	}
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Find Bind");
#endif
}

void BackTrackingGrounder::findSearchTable() {
#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->start("Find Search");
#endif


	for (unsigned index_current_atom = 0; index_current_atom < currentRule->getSizeBody(); ++index_current_atom) {
		//find the table to search for each atom in the body
		current_id_match.insert({index_current_atom,vector<pair<unsigned,int>>()});
		for(unsigned i=0;i<predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom].size();++i){
			current_id_match[index_current_atom].push_back({predicate_searchInsert_table[currentRule->getSizeHead()+index_current_atom][i],NO_MATCH});
		}
		current_id_match_iterator[index_current_atom]=0;

	}

#ifdef DEBUG_RULE_TIME
		Timer::getInstance()->stop("Find Search");
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


bool BackTrackingGrounder::groundAggregate() {
	Atom *aggregateAtom=templateSetAtom[index_current_atom];
	if(aggregateAtom->getAggregateFunction()==SUM || aggregateAtom->getAggregateFunction()==COUNT){
			if((aggregateAtom->getFirstBinop()==LESS_OR_EQ || aggregateAtom->getFirstBinop()==EQUAL)
			&& aggregateAtom->getFirstGuard()->getType()!=VARIABLE && aggregateAtom->getFirstGuard()->getType()!=NUMERIC_CONSTANT){
				ground_rule->setAtomToSimplifyInBody(index_current_atom);
				substiteInGroundRule(index_current_atom,nullptr);
				return aggregateAtom->isNegative();
		}
		if(aggregateAtom->getSecondBinop()==LESS && aggregateAtom->getFirstBinop()==NONE_OP
			&& aggregateAtom->getSecondGuard()->getType()!=VARIABLE && aggregateAtom->getSecondGuard()->getType()!=NUMERIC_CONSTANT){
				cout<<"AAAAAAAAAAAAAa"<<endl;
				ground_rule->setAtomToSimplifyInBody(index_current_atom);
				substiteInGroundRule(index_current_atom,nullptr);
				return !aggregateAtom->isNegative();
		}
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
		current_var_assign.insert({aggregateAtom->getFirstGuard(),val});
		return true;
	}
	//Create a ground aggregate empty and set the aggregate to not simplify
	ground_aggregate=new AggregateAtom(aggregateAtom->getFirstGuard(),aggregateAtom->getFirstBinop(),aggregateAtom->getSecondGuard(),aggregateAtom->getSecondBinop(),aggregateAtom->getAggregateFunction(),aggregateAtom->isNegative());
	ground_rule->setAtomToSimplifyInBody(index_current_atom,false);

	ResultEvaluation result=UNDEF;
	for(unsigned i=0;i<aggregateAtom->getAggregateElementsSize()&&result==UNDEF;i++){

		// For each atom in the aggregate element (is assumed to be one because the rewriting)
		// search in the table of fact and nofact the extension and put in the ground aggregate all the extension
		// with a new aggregate element
		// For reasoning of correctness the current assignment have to be copied for maintaining the current assignment

		Atom* atom=aggregateAtom->getAggregateElement(i)->getNafLiteral(0);
		Predicate *predicate_atom=atom->getPredicate();
		vector<unsigned> tablesToSearch={FACT,NOFACT};

		int counter=0;
		for(unsigned j=0;j<tablesToSearch.size()&&result==UNDEF;j++){

			unsigned table=tablesToSearch[j];
			AtomSearcher *searcher=predicateExtTable->getPredicateExt(predicate_atom)->getAtomSearcher(table);
			bool find=false;
			Atom* atomFound=nullptr;
			map_term_term copy_current_var_assign(current_var_assign);
			unsigned id = searcher->firstMatch(atom,copy_current_var_assign,atomFound);
			find=(atomFound!=nullptr);
			while(find){
				counter++;

				AggregateElement *ground_aggregateElement=new AggregateElement;
				ground_aggregateElement->addNafLiterals(atomFound);
				//Add the id ground term in the ground aggregate element
				for(auto term_aggregateElement:aggregateAtom->getAggregateElement(i)->getTerms())
					ground_aggregateElement->addTerm(copy_current_var_assign[term_aggregateElement]);

				ground_aggregate->addAggregateElement(ground_aggregateElement);
				result=ground_aggregate->partialEvaluate();

				if(result!=UNDEF || atom->isGround())break;
				copy_current_var_assign=current_var_assign;
				searcher->nextMatch(id,atom,copy_current_var_assign,atomFound);
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

		current_var_assign.insert({ground_aggregate->getFirstGuard(),val});
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

} /* namespace grounder */
} /* namespace DLV2 */

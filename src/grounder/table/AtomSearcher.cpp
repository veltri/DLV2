/*
 * IndexAtom2.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: jessica
 */

#include "../../util/Options.h"
#include "../../util/Assert.h"
#include "AtomSearcher.h"
#include "../../util/Timer.h"
#include <boost/lexical_cast.hpp>
#include "PredicateExtension.h"

namespace DLV2{

namespace grounder{


/******************************************************* ATOM SEARCHER ***************************************************/

bool AtomSearcher::checkMatch(Atom *genericAtom, Atom *templateAtom, var_assignment& currentAssignment,const RuleInformation& ruleInformation){
	// Checks the match for each term and, if all the terms match, updates the current assignment accordingly
	var_assignment assignInTerm(currentAssignment);

	vector<index_object> variablesAdded;
	for(unsigned int i=0;i<genericAtom->getTermsSize();++i){
		Term* genericTerm=genericAtom->getTerm(i);
		Term* termToMatch=templateAtom->getTerm(i);
		if (termToMatch->getIndex() == genericTerm->getIndex()) continue;
		if(!matchTerm(genericTerm,termToMatch,assignInTerm,variablesAdded,ruleInformation))
			return false;
	}

	//TODO TEST LINEAR SCANNING THE ARRAY
	for(auto variable:variablesAdded){
		currentAssignment[variable]=assignInTerm[variable];
	}

	return true;

}

/*
 * For each builtin atom that the bind variable(with local index=index) is the last variable evaluated in the builtin, check if the builtin is satisfied. If the
 * evaluation of builtin is false the match of the term, then the match of the atom fail
 */
bool AtomSearcher::evaluateFastBuiltin(const RuleInformation& ruleInformation,index_object index, var_assignment& varAssignment, Term* genericTerm) {
	for (auto builtin : ruleInformation.getBounderBuiltin(index)) {
//		Atom* groundBuiiltin1 = nullptr;
//		builtin->ground(currentAssignment, groundBuiiltin1);
		varAssignment[index] = genericTerm;
		bool evaluation = builtin->groundAndEvaluate(varAssignment);
//		delete groundBuiiltin1;
		if (!evaluation) {
			return false;
		}
	}
	return true;
}

bool AtomSearcher::matchTerm(Term *genericTerm, Term *termToMatch, var_assignment& varAssignment,vector<index_object>& addedVariables,const RuleInformation& ruleInformation){

	TermType termToMatchType=termToMatch->getType();
	TermType genericTermType=genericTerm->getType();
	if((termToMatchType==TermType::NUMERIC_CONSTANT || termToMatchType==TermType::STRING_CONSTANT || termToMatchType==TermType::SYMBOLIC_CONSTANT))
		return false;
	else if (termToMatchType==TermType::VARIABLE) {
		index_object index=termToMatch->getLocalVariableIndex();
		if(ruleInformation.isCreatedDictionaryIntersection(index) && !ruleInformation.countInDictionaryIntersection(index,genericTerm)){
			return false;
		}
		Term* term=varAssignment[index];
		if(term!=nullptr){
			if( term->getIndex() == genericTerm->getIndex())
				return true;
			else
				return false;
		}

		if(ruleInformation.isBounderBuiltin(index)){
			if(!evaluateFastBuiltin(ruleInformation, index, varAssignment, genericTerm))
				return false;
		}

		varAssignment[index]=genericTerm;
		addedVariables.push_back(index);
		return true;
	}
	else if (termToMatchType==TermType::ANONYMOUS) return true;

	else if(termToMatchType==TermType::ARITH){
		Term *new_term=termToMatch->substitute(varAssignment);
		assert_msg(new_term->isGround(),"Arith term not safe");
		termToMatch=new_term->calculate();
	}

	else if(genericTermType==TermType::FUNCTION){

		if(termToMatchType!=TermType::FUNCTION) return false;
		if(termToMatch->getName().compare(genericTerm->getName()) != 0)return false;
		if(termToMatch->getTermsSize() != genericTerm->getTermsSize())return false;
		for(unsigned int i=0;i<genericTerm->getTermsSize();++i)
			if(!matchTerm(genericTerm->getTerm(i),termToMatch->getTerm(i),varAssignment,addedVariables,ruleInformation))
				return false;

		return true;
	}

	return false;

}

void AtomSearcher::firstMatch(unsigned id,Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation,IndexingStructure* indexingStructure) {
	GeneralIterator* currentMatch=indexingStructure->computeMatchIterator(templateAtom,ruleInformation);
	if(computeMatch(currentMatch,templateAtom,currentAssignment,atomFound,ruleInformation)){
		delete resultVector[id];
		resultVector[id]=currentMatch;
		return;
	}
	delete currentMatch;

}

bool AtomSearcher::computeMatch(GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(currentMatch->currentItem(),templateAtom,currentAssignment,ruleInformation)){
			atomFound=currentMatch->currentItem();
			return true;
		}
	}
	atomFound=nullptr;
	return false;
}

void AtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation) {
	GeneralIterator* currentMatch=resultVector[id];
	currentMatch->next();
	computeMatch(currentMatch,templateAtom,currentAssignment,atomFound,ruleInformation);

}

Atom* AtomSearcher::findGroundAtom(Atom *atom,IndexingStructure* indexingStructure){
	return indexingStructure->find(atom);
}

IndexingStructure* AtomSearcher::getIndexingStructure(unsigned type, vector<unsigned>* indexingTerms) {
	for(auto indexingStruct:indexingStructures){
		if(indexingStruct->getType()==type){
			if(indexingTerms==nullptr || indexingStruct->getIndexingTerms()==*indexingTerms)
				return indexingStruct;
		}
	}
	return nullptr;
}

}}


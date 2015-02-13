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

namespace DLV2{

namespace grounder{


/******************************************************* ATOM SEARCHER ***************************************************/

bool AtomSearcher::checkMatch(Atom *genericAtom, Atom *templateAtom, map_term_term& currentAssignment){
	// Checks the match for each term and, if all the terms match, updates the current assignment accordingly
	map_term_term assignInTerm;

	for(unsigned int i=0;i<genericAtom->getTermsSize();i++)
			if(!matchTerm(genericAtom->getTerm(i),templateAtom->getTerm(i),assignInTerm))
				return false;

	currentAssignment.insert(assignInTerm.begin(),assignInTerm.end());

	return true;

}

bool AtomSearcher::matchTerm(Term *genericTerm, Term *termToMatch, map_term_term& varAssignment){

	if (termToMatch->getType()==TermType::VARIABLE) {
		auto find_it=varAssignment.find(termToMatch);
		if(find_it!=varAssignment.end()){
		if( (*find_it).second->getIndex() == genericTerm->getIndex())
			return true;
		else
			return false;

		}
		varAssignment.insert( { termToMatch, genericTerm });
		return true;
	}


	if((genericTerm->getType()==TermType::NUMERIC_CONSTANT || genericTerm->getType()==TermType::STRING_CONSTANT )){

		if (termToMatch->getType()==TermType::ANONYMOUS) return true;
		if ((termToMatch->getType()==TermType::NUMERIC_CONSTANT || termToMatch->getType()==TermType::STRING_CONSTANT ) && termToMatch->getIndex() == genericTerm->getIndex()) return true;

	}else if(genericTerm->getType()==TermType::FUNCTION){
		if(termToMatch->getType()==TermType::ANONYMOUS) return true;
		if(termToMatch->getType()!=TermType::FUNCTION) return false;
		if(termToMatch->getName().compare(genericTerm->getName()) != 0)return false;
		if(termToMatch->getTermsSize() != genericTerm->getTermsSize())return false;
		map_term_term assignInTerm(varAssignment);
		for(unsigned int i=0;i<genericTerm->getTermsSize();i++)
			if(!matchTerm(genericTerm->getTerm(i),termToMatch->getTerm(i),assignInTerm))
				return false;

		varAssignment.insert(assignInTerm.begin(),assignInTerm.end());
		return true;
	}

	return false;

}



/****************************************************** BASE ATOM SEARCHER ***************************************************/

unsigned int BaseAtomSearcher::firstMatch(Atom *templateAtom, map_term_term& currentAssignment, bool& find,bool &undef) {
	unsigned int id = ++counter;
	GeneralIterator* currentMatch=computeGenericIterator(templateAtom);
	if(searchForFirstMatch(currentMatch, templateAtom, currentAssignment,undef)){
		find=true;
		resultMap.insert({id,currentMatch});
		return id;
	}

	delete currentMatch;
	find=false;
	return id;
}

bool BaseAtomSearcher::searchForFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment,bool &undef){
	//Call findIfAFactExist only if all the terms are bound
	if(templateAtom->isGround()){
		bool find=0;
		findIfExist(templateAtom,find,undef);
		return find;
	}

	//Compute the first match
	bool find=computeMatch(currentMatch,templateAtom,currentAssignment);
	if(find) undef=!currentMatch->currentIterm()->isFact();
	return find;
}

bool BaseAtomSearcher::computeMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(currentMatch->currentIterm(),templateAtom,currentAssignment))
			return true;
	}
	return false;
}

void BaseAtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, map_term_term& currentAssignment, bool& find, bool &undef) {
	GeneralIterator* currentMatch=resultMap.find(id)->second;
	currentMatch->next();
	computeMatch(currentMatch,templateAtom,currentAssignment);

	///Return the next matching atom retrieved from the integer identifier assigned by the firstMatch method
	if(currentMatch->isDone()){
		delete currentMatch;
		resultMap.erase(id);
		find=false;
		return;
	}
	undef=!currentMatch->currentIterm()->isFact();
	find=true;
}

Atom* BaseAtomSearcher::findAtom(Atom *atom){
	AtomTableComparator comparator;
	for(auto genericAtom:(*table)){
		if(comparator(genericAtom,atom))
			return genericAtom;
	}
	return nullptr;
}

void BaseAtomSearcher::findIfExist(Atom *templateAtom, bool& find, bool& isUndef) {
	Atom* genericAtom=findAtom(templateAtom);
	if(genericAtom!=nullptr){
		isUndef=!genericAtom->isFact();
		find=true;
		return;
	}
	find=false;
}

/****************************************************** SINGLE TERM ATOM SEARCH ***************************************************/

void SingleTermMultipleStrategiesAtomSearcher::add(Atom* atom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Add index "+predicate->getName());
#endif
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(searchingTables[i].count(termIndex))
				searchingTables[i][termIndex].insert(atom);
			else{
				searchingTables[i].emplace(termIndex,AtomTable({atom}));
			}
		}
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Add index "+predicate->getName());
#endif
}

void SingleTermMultipleStrategiesAtomSearcher::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(searchingTables[i].count(termIndex))
				searchingTables[termIndex][i].erase(atom);
		}
	}
}

Atom* SingleTermMultipleStrategiesAtomSearcher::findAtom(Atom *atom){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Find "+predicate->getName());
#endif
	int tableToSearch=manageIndex(atom);
	assert_msg(tableToSearch>-1, "Invalid index");

	index_object term = atom->getTerm(tableToSearch)->getIndex();
	AtomTable* matchingTable=&searchingTables[tableToSearch][term];

	auto atomFound_it=matchingTable->find(atom);
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Find "+predicate->getName());
#endif
	if(atomFound_it!=matchingTable->end())
		return *atomFound_it;
	return nullptr;
}

unsigned int SingleTermMultipleStrategiesAtomSearcher::selectBestIndex(const unordered_set<int>& possibleTableToSearch){
	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser] && possibleTableToSearch.count(indexingTermSetByUser))
		return indexingTermSetByUser;

	auto it=possibleTableToSearch.begin();
	unsigned tableMinSize=(*it);
	unsigned minSize=(searchingTables[(*it)]).size();
	for(it++;it!=possibleTableToSearch.end();it++){
		unsigned currentSize=(searchingTables[(*it)]).size();
		if(createdSearchingTables[*it] && minSize>currentSize){
			minSize=currentSize;
			tableMinSize=*it;
		}
	}
	return tableMinSize;
}

int SingleTermMultipleStrategiesAtomSearcher::manageIndex(Atom* templateAtom) {
	unordered_set<int> possibleTableToSearch;
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++)
		if(templateAtom->getTerm(i)->isGround())
			possibleTableToSearch.insert(i);

	int indexSelected=-1;
	if(!possibleTableToSearch.empty()){
		indexSelected=selectBestIndex(possibleTableToSearch);
		if(!createdSearchingTables[indexSelected])
			initializeIndexMaps(indexSelected);
	}
	return indexSelected;
}

GeneralIterator* SingleTermMultipleStrategiesAtomSearcher::computeGenericIterator(Atom* templateAtom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	int indexingTerm=manageIndex(templateAtom);
	GeneralIterator* currentMatch;

	//If no searching table is available (the atom is completely unbound)
	//the search is performed in the base vector
	if(indexingTerm!=-1){
		index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
		AtomTable* matchingTable=&searchingTables[indexingTerm][term];
		currentMatch=new UnorderedSetIterator(matchingTable->begin(),matchingTable->end());
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Compute iterator "+predicate->getName());
#endif
	return currentMatch;
}

void SingleTermMultipleStrategiesAtomSearcher::initializeIndexMaps(unsigned int indexingTerm){
#ifdef NDEBUG
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Create index "+predicate->getName()+" index "+boost::lexical_cast<string>(indexingTerm));
#endif
	createdSearchingTables[indexingTerm]=true;
	unordered_set<index_object> termToBeIndexedIndices;
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		if(termToBeIndexedIndices.insert(termIndex).second){
			AtomTable values;
			values.insert(a);
			searchingTables[indexingTerm].insert({termIndex,values});
		}
		else{
			searchingTables[indexingTerm][termIndex].insert(a);
		}
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Create index "+predicate->getName()+" index "+boost::lexical_cast<string>(indexingTerm));
#endif
}

/****************************************************** SINGLE TERM MULTI MAP ATOM SEARCH ***************************************************/

void SingleTermMultipleStrategiesAtomSearcherMultiMap::add(Atom* atom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Add index "+predicate->getName());
#endif
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			searchingTables[i].insert({termIndex,atom});
		}
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Add index "+predicate->getName());
#endif
}

void SingleTermMultipleStrategiesAtomSearcherMultiMap::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			AtomTableComparator comparator;
			index_object termIndex=atom->getTerm(i)->getIndex();
			auto pair=searchingTables[i].equal_range(termIndex);
			for(auto it=pair.first;it!=pair.second;it++){
				if(comparator(it->second,atom))
					searchingTables[i].erase(it);
			}
		}
	}
}

int SingleTermMultipleStrategiesAtomSearcherMultiMap::manageIndex(Atom* templateAtom) {
	unordered_set<int> possibleTableToSearch;
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++)
		if(templateAtom->getTerm(i)->isGround())
			possibleTableToSearch.insert(i);

	int indexSelected=-1;
	if(!possibleTableToSearch.empty()){
		indexSelected=selectBestIndex(possibleTableToSearch);
		if(!createdSearchingTables[indexSelected])
			initializeIndexMaps(indexSelected);
	}
	return indexSelected;
}

Atom* SingleTermMultipleStrategiesAtomSearcherMultiMap::findAtom(Atom *atom){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Find "+predicate->getName());
#endif
	int indexingTerm=manageIndex(atom);
	assert_msg(indexingTerm>-1, "Invalid index");

	index_object term = atom->getTerm(indexingTerm)->getIndex();
	AtomTableComparator comparator;
	auto pair=searchingTables[indexingTerm].equal_range(term);
	for(auto it=pair.first;it!=pair.second;it++){
		if(comparator(it->second,atom))
			return it->second;
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Find "+predicate->getName());
#endif
	return nullptr;
}

unsigned int SingleTermMultipleStrategiesAtomSearcherMultiMap::selectBestIndex(const unordered_set<int>& possibleTableToSearch){
	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser] && possibleTableToSearch.count(indexingTermSetByUser))
		return indexingTermSetByUser;

	auto it=possibleTableToSearch.begin();
	unsigned tableMinSize=(*it);
	unsigned minSize=(searchingTables[(*it)]).size();
	for(;it!=possibleTableToSearch.end();it++){
		unsigned currentSize=(searchingTables[(*it)]).size();
		if(createdSearchingTables[*it] && currentSize<minSize){
			minSize=currentSize;
			tableMinSize=*it;
		}
	}
	return tableMinSize;
}


GeneralIterator* SingleTermMultipleStrategiesAtomSearcherMultiMap::computeGenericIterator(Atom* templateAtom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	int indexingTerm=manageIndex(templateAtom);
	GeneralIterator* currentMatch;

	//If no searching table is available (the atom is completely unbound)
	//the search is performed in the base vector
	if(indexingTerm!=-1){
		index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
		auto pair=searchingTables[indexingTerm].equal_range(term);
		currentMatch=new UnorderedMultiMapIterator(pair.first,pair.second);
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
	return currentMatch;
}

void SingleTermMultipleStrategiesAtomSearcherMultiMap::initializeIndexMaps(unsigned int indexingTerm){
#ifdef NDEBUG
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	createdSearchingTables[indexingTerm]=true;
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		searchingTables[indexingTerm].insert({termIndex,a});
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Compute iterator "+predicate->getName());
#endif
}

};

};





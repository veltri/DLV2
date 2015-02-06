/*
 * IndexAtom2.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: jessica
 */

#include "../../util/Options.h"
#include "../../util/Assert.h"
#include "AtomSearcher.h"

namespace DLV2{

namespace grounder{

/******************************************************* ATOM SEARCHER ***************************************************/

bool AtomSearcher::checkMatch(Atom *genericAtom, Atom *templateAtom, map_term_term& currentAssignment){
	// Checks the match for each term and, if all the terms match, updates the current assignment accordingly
	map_term_term assignInTerm(currentAssignment);

	for(unsigned int i=0;i<genericAtom->getTermsSize();i++)
			if(!genericAtom->getTerm(i)->match(templateAtom->getTerm(i),assignInTerm))
				return false;

	for(auto assignment:assignInTerm)
		if(!currentAssignment.count(assignment.first))
			currentAssignment.insert(assignment);
	return true;

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
	bool find=computeFirstMatch(currentMatch,templateAtom,currentAssignment);
	if(find) undef=!currentMatch->currentIterm()->isFact();
	return find;
}

bool BaseAtomSearcher::computeFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(currentMatch->currentIterm(),templateAtom,currentAssignment))
			return true;
	}
	return false;
}

void BaseAtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, map_term_term& currentAssignment, bool& find, bool &undef) {
	GeneralIterator* currentMatch=resultMap.find(id)->second;
	currentMatch->next();
	computeFirstMatch(currentMatch,templateAtom,currentAssignment);

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
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(searchingTables[i].count(termIndex))
				searchingTables[i][termIndex].insert(atom);
			else{
				AtomTable values;
				values.insert(atom);
				searchingTables[i].insert({termIndex,values});
			}
		}
	}
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
	int tableToSearch=manageIndex(atom);
	assert_msg(tableToSearch>-1, "Invalid index");

	index_object term = atom->getTerm(tableToSearch)->getIndex();
	AtomTable* matchingTable=&searchingTables[tableToSearch][term];

	auto atomFound_it=matchingTable->find(atom);
	if(atomFound_it!=matchingTable->end())
		return *atomFound_it;
	return nullptr;
}

unsigned int SingleTermMultipleStrategiesAtomSearcher::selectBestIndex(const unordered_set<int>& possibleTableToSearch){
	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser] && possibleTableToSearch.count(indexingTermSetByUser))
		return indexingTermSetByUser;

	for(unsigned int i=0;i<createdSearchingTables.size();i++)
		if(possibleTableToSearch.count(i))
			return i;
	return *possibleTableToSearch.begin();
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
	return currentMatch;
}

void SingleTermMultipleStrategiesAtomSearcher::initializeIndexMaps(unsigned int indexingTerm){
#ifdef NDEBUG
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
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
}

/****************************************************** SINGLE TERM MULTI MAP ATOM SEARCH ***************************************************/

void SingleTermMultipleStrategiesAtomSearcherMultiMap::add(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			searchingTables[i].insert({termIndex,atom});
		}
	}
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
	int indexingTerm=manageIndex(atom);
	assert_msg(indexingTerm>-1, "Invalid index");

	index_object term = atom->getTerm(indexingTerm)->getIndex();
	AtomTableComparator comparator;
	auto pair=searchingTables[indexingTerm].equal_range(term);
	for(auto it=pair.first;it!=pair.second;it++){
		if(comparator(it->second,atom))
			return it->second;
	}
	return nullptr;
}

unsigned int SingleTermMultipleStrategiesAtomSearcherMultiMap::selectBestIndex(const unordered_set<int>& possibleTableToSearch){
	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser] && possibleTableToSearch.count(indexingTermSetByUser))
		return indexingTermSetByUser;

	for(unsigned int i=0;i<createdSearchingTables.size();i++)
		if(possibleTableToSearch.count(i))
			return i;
	return *possibleTableToSearch.begin();
}


GeneralIterator* SingleTermMultipleStrategiesAtomSearcherMultiMap::computeGenericIterator(Atom* templateAtom) {
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
	createdSearchingTables[indexingTerm]=true;
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		searchingTables[indexingTerm].insert({termIndex,a});
	}
}

};

};





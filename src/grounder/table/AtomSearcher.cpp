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
	// Call match for each term and if all term result true put the assignment in the current assignment
	map_term_term assignInTerm(currentAssignment);

	for(unsigned int i=0;i<genericAtom->getTermsSize();i++)
			if(!genericAtom->getTerm(i)->match(templateAtom->getTerm(i),assignInTerm))
				return false;

	for(auto assignment:assignInTerm)
		if(!currentAssignment.count(assignment.first))
			currentAssignment.insert(assignment);
	return true;

}

/****************************************************** SIMPLE ATOM SEARCHER ***************************************************/

GeneralIterator* SimpleAtomSearcher::computeGenericIterator(Atom* templateAtom) {
	GeneralIterator* currentMatch = new VectorIterator(table->begin(),table->end());
	return currentMatch;
}

unsigned int SimpleAtomSearcher::firstMatch(Atom *templateAtom, map_term_term& currentAssignment, bool& find,bool &undef) {
	unsigned int id = ++counter;
	GeneralIterator* currentMatch=computeGenericIterator(templateAtom);
	if(searchForFirstMatch(currentMatch, templateAtom, currentAssignment,undef)){
		find=true;
		resultMap.insert({id,currentMatch});
		return id;
	}

	find=false;

	return id;
}

bool SimpleAtomSearcher::searchForFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment,bool &undef){
	//Call findIfAFactExist only if all the terms are bound
	if(templateAtom->isGround()){
		bool find=0;
		findIfExist(templateAtom,find,undef);
		return find;
	}

	//Compute the first match
	bool find=computeFirstMatch(currentMatch,templateAtom,currentAssignment);
	if(find)undef=!currentMatch->currentIterm()->isFact();
	return find;
}

bool SimpleAtomSearcher::computeFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(currentMatch->currentIterm(),templateAtom,currentAssignment))
			return true;

	}
	return false;

}

void SimpleAtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, map_term_term& currentAssignment, bool& find,bool &undef) {

	auto currentMatch=resultMap.find(id)->second;
	currentMatch->next();
	computeFirstMatch(currentMatch,templateAtom,currentAssignment);

	///Return the next matching facts or no facts retrieved from the integer identifier assigned by the firstMatch method
	if(currentMatch->isDone()){
		resultMap.erase(id);
		find=false;
		return;
	}
	undef=!currentMatch->currentIterm()->isFact();
	find=true;
}

Atom* SimpleAtomSearcher::getAtom(Atom *atom){
	AtomTableComparator comparator;
	for(auto genericAtom:(*table)){
		if(comparator(genericAtom,atom))
			return genericAtom;
	}
	return nullptr;

}

void SimpleAtomSearcher::findIfExist(Atom *templateAtom,bool& find, bool& isUndef) {
	Atom* genericAtom=getAtom(templateAtom);
	if(genericAtom!=nullptr){
		isUndef=!genericAtom->isFact();
		find=true;
		return ;
	}
	find=false;
}

/****************************************************** SINGLE TERM ATOM SEARCH ***************************************************/

void SingleTermAtomSearcher::add(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdIndex[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(indexingTable[i].count(termIndex))
				indexingTable[i][termIndex].insert(atom);
			else{
				AtomTable values;
				values.insert(atom);
				indexingTable[i].insert({termIndex,values});
			}
		}
	}
}

void SingleTermAtomSearcher::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdIndex[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(indexingTable[i].count(termIndex))
				indexingTable[termIndex][i].erase(atom);
		}
	}
}

Atom* SingleTermAtomSearcher::getAtom(Atom *atom){
	int tableToSearch=manageIndex(atom);
	assert_msg(tableToSearch>-1, "Invalid index");

	index_object term = atom->getTerm(tableToSearch)->getIndex();
	AtomTable* matchingTable=&indexingTable[tableToSearch][term];

	auto atomFound_it=matchingTable->find(atom);
	if(atomFound_it!=matchingTable->end())
		return *atomFound_it;
	return nullptr;
}

unsigned int SingleTermAtomSearcher::selectBestIndex(const unordered_set<int>& possibleTableToSearch){
	if(indexSetByUser>-1 && createdIndex[indexSetByUser] && possibleTableToSearch.count(indexSetByUser))
		return indexSetByUser;

	for(unsigned int i=0;i<createdIndex.size();i++)
		if(possibleTableToSearch.count(i))
			return i;
	return *possibleTableToSearch.begin();
}

int SingleTermAtomSearcher::manageIndex(Atom* templateAtom) {
	unordered_set<int> possibleTableToSearch;
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++)
		if(templateAtom->getTerm(i)->isGround()){
			possibleTableToSearch.insert(i);
		}

	int indexSelected=-1;
	if(!possibleTableToSearch.empty()){
		indexSelected=selectBestIndex(possibleTableToSearch);
		if(!createdIndex[indexSelected])
			initializeIndexMaps(indexSelected);
	}
	return indexSelected;
}

GeneralIterator* SingleTermAtomSearcher::computeGenericIterator(Atom* templateAtom) {

	int tableIndex=manageIndex(templateAtom);

	GeneralIterator* currentMatch;
	//If no index table is available (no bound term contained) the search is performed in the original vector
	if(tableIndex!=-1){
		index_object term = templateAtom->getTerm(tableIndex)->getIndex();
		AtomTable* matchingTable=&indexingTable[tableIndex][term];
		currentMatch=new UnorderedSetIterator(matchingTable->begin(),matchingTable->end());
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
	return currentMatch;
}

void SingleTermAtomSearcher::initializeIndexMaps(unsigned int tableIndex){
	createdIndex[tableIndex]=true;
//	Timer::getInstance()->start("Creation Index Structure");
	unordered_set<index_object> termToBeIndexedIndices;
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(tableIndex)->getIndex();
		if(termToBeIndexedIndices.insert(termIndex).second){
			AtomTable values;
			values.insert(a);
			indexingTable[tableIndex].insert({termIndex,values});
		}
		else{
			indexingTable[tableIndex][termIndex].insert(a);
		}
	}
//	Timer::getInstance()->end();
}

/****************************************************** SINGLE TERM MULTI MAP ATOM SEARCH ***************************************************/

void SingleTermAtomSearcherMultiMap::add(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdIndex[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			tableIndexMap[i].insert({termIndex,atom});
		}
	}
}

void SingleTermAtomSearcherMultiMap::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdIndex[i]){
			AtomTableComparator comparator;
			index_object termIndex=atom->getTerm(i)->getIndex();
			auto pair=tableIndexMap[i].equal_range(termIndex);
			for(auto it=pair.first;it!=pair.second;it++){
				if(comparator(it->second,atom))
					tableIndexMap[i].erase(it);
			}
		}
	}
}

int SingleTermAtomSearcherMultiMap::manageIndex(Atom* templateAtom) {
	unordered_set<int> possibleTableToSearch;
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++)
		if(templateAtom->getTerm(i)->isGround())
			possibleTableToSearch.insert(i);

	int indexSelected=-1;
	if(!possibleTableToSearch.empty()){
		indexSelected=selectBestIndex(possibleTableToSearch);
		if(!createdIndex[indexSelected])
			initializeIndexMaps(indexSelected);
	}
	return indexSelected;
}

Atom* SingleTermAtomSearcherMultiMap::getAtom(Atom *atom){
	int tableToSearch=manageIndex(atom);
	assert_msg(tableToSearch>-1, "Invalid index");

	index_object term = atom->getTerm(tableToSearch)->getIndex();

	AtomTableComparator comparator;
	auto pair=tableIndexMap[tableToSearch].equal_range(term);
	for(auto it=pair.first;it!=pair.second;it++){
		if(comparator(it->second,atom))
			return it->second;
	}
	return nullptr;
}

unsigned int SingleTermAtomSearcherMultiMap::selectBestIndex(const unordered_set<int>& possibleTableToSearch){
	if(indexSetByUser>-1 && createdIndex[indexSetByUser] && possibleTableToSearch.count(indexSetByUser))
		return indexSetByUser;

	for(unsigned int i=0;i<createdIndex.size();i++)
		if(possibleTableToSearch.count(i))
			return i;
	return *possibleTableToSearch.begin();
}


GeneralIterator* SingleTermAtomSearcherMultiMap::computeGenericIterator(Atom* templateAtom) {
	int tableIndex=manageIndex(templateAtom);

	GeneralIterator* currentMatch;
	//If no index table is available (no bound term contained) the search is performed in the original vector
	if(tableIndex!=-1){
		index_object term = templateAtom->getTerm(tableIndex)->getIndex();
		auto pair=tableIndexMap[indexSetByUser].equal_range(term);
		currentMatch=new UnorderedMultiMapIterator(pair.first,pair.second);
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
	return currentMatch;
}

void SingleTermAtomSearcherMultiMap::initializeIndexMaps(unsigned int index){
	createdIndex[index]=true;
//	Timer::getInstance()->start("Creation Index Structure");
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(index)->getIndex();
		tableIndexMap[index].insert({termIndex,a});
	}
//	Timer::getInstance()->end();
}

};

};





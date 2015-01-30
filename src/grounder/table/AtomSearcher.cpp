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

unsigned int SimpleAtomSearcher::firstMatch(Atom *templateAtom, map_term_term& currentAssignment, bool& find) {
	unsigned int id = ++counter;
	GeneralIterator* currentMatch=computeGenericIterator(templateAtom);
	if(searchForFirstMatch(currentMatch, templateAtom, currentAssignment)){
		find=true;
		resultMap.insert({id,currentMatch});
		return id;
	}

	find=false;

	return id;
}

bool SimpleAtomSearcher::searchForFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment){
	//Call findIfAFactExist only if all the terms are bound
	if(templateAtom->isGround()){
		bool isUndef=0,find=0;
		findIfExist(templateAtom,find,isUndef);
		return find;
	}

	//Compute the first match
	return computeFirstMatch(currentMatch,templateAtom,currentAssignment);
}

bool SimpleAtomSearcher::computeFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(currentMatch->currentIterm(),templateAtom,currentAssignment))
			return true;

	}
	return false;

}

void SimpleAtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, map_term_term& currentAssignment, bool& find) {

	auto currentMatch=resultMap.find(id)->second;
	currentMatch->next();
	computeFirstMatch(currentMatch,templateAtom,currentAssignment);

	///Return the next matching facts or no facts retrieved from the integer identifier assigned by the firstMatch method
	if(currentMatch->isDone()){
		resultMap.erase(id);
		find=false;
		return;
	}

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
	if(createdIndex){
		index_object termIndex=atom->getTerm(indexPair.first)->getIndex();
		if(tableIndexMap.count(termIndex)){
			tableIndexMap[termIndex].insert(atom);
		}
		else{
			AtomTable values;
			values.insert(atom);
			tableIndexMap.insert({termIndex,values});
		}
	}
}

void SingleTermAtomSearcher::remove(Atom* atom) {
	if(createdIndex){
		index_object termIndex=atom->getTerm(indexPair.first)->getIndex();
		if(tableIndexMap.count(termIndex)){
			tableIndexMap[termIndex].erase(atom);
		}
	}
}

Atom* SingleTermAtomSearcher::getAtom(Atom *atom){
	if(createdIndex){
		index_object index=atom->getTerm(indexPair.first)->getIndex();
		auto atomFound_it=tableIndexMap[index].find(atom);
		if(atomFound_it!=tableIndexMap[index].end())
			return *atomFound_it;
	}
	else{
		AtomTableComparator comparator;
		for(auto genericAtom:(*table)){
			if(comparator(genericAtom,atom))
				return genericAtom;
		}
	}
	return nullptr;
}

void SingleTermAtomSearcher::createIndex(Atom* templateAtom, pair<bool, index_object>& termBoundIndex) {
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++){
		Term* t=templateAtom->getTerm(i);
		if(!indexPair.second && t->isGround()){
			indexPair.first=i;
			indexPair.second = true;
		}
		if(indexPair.second && i == indexPair.first && t->isGround()) {
			termBoundIndex.first = true;
			termBoundIndex.second = t->getIndex();
			break;
		}
	}
	if(!createdIndex && indexPair.first && table->size()>0)
		initializeIndexMaps();
}

GeneralIterator* SingleTermAtomSearcher::computeGenericIterator(Atom* templateAtom) {

	pair<bool, index_object> termBoundIndex( { false, 0 });
	createIndex(templateAtom,termBoundIndex);

	GeneralIterator* currentMatch;
	if(createdIndex && termBoundIndex.first){
		AtomTable* matchingTable=&tableIndexMap[termBoundIndex.second];
		currentMatch=new UnorderedSetIterator(matchingTable->begin(),matchingTable->end());
	}
	else{
		currentMatch=new VectorIterator(table->begin(), table->end());
	}
	return currentMatch;
}

void SingleTermAtomSearcher::initializeIndexMaps(){
//	Timer::getInstance()->start("Creation Index Structure");
	createdIndex=true;
	unordered_set<index_object> termToBeIndexedIndices;

	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexPair.first)->getIndex();
		if(termToBeIndexedIndices.insert(termIndex).second){
			AtomTable values;
			values.insert(a);
			tableIndexMap.insert({termIndex,values});
		}
		else{
			tableIndexMap[termIndex].insert(a);
		}
	}
//	Timer::getInstance()->end();
}

/****************************************************** SINGLE TERM MULTI MAP ATOM SEARCH ***************************************************/

void SingleTermAtomSearcherMultiMap::add(Atom* atom) {
	if(createdIndex){
		index_object termIndex=atom->getTerm(indexPair.first)->getIndex();
		tableIndexMap.insert({termIndex,atom});
	}
}

void SingleTermAtomSearcherMultiMap::remove(Atom* atom) {
	if(createdIndex){
		AtomTableComparator comparator;
		index_object termIndex=atom->getTerm(indexPair.first)->getIndex();
		auto pair=tableIndexMap.equal_range(termIndex);
		for(auto it=pair.first;it!=pair.second;it++){
			if(comparator(it->second,atom))
				tableIndexMap.erase(it);
		}
	}
}

Atom* SingleTermAtomSearcherMultiMap::getAtom(Atom *atom){
	if(createdIndex){
		AtomTableComparator comparator;
		index_object termIndex=atom->getTerm(indexPair.first)->getIndex();
		auto pair=tableIndexMap.equal_range(termIndex);
		for(auto it=pair.first;it!=pair.second;it++){
			if(comparator(it->second,atom))
				return it->second;
		}
	}
	else{
		AtomTableComparator comparator;
		for(auto genericAtom:(*table)){
			if(comparator(genericAtom,atom))
				return genericAtom;
		}
	}
	return nullptr;
}

void SingleTermAtomSearcherMultiMap::createIndex(Atom* templateAtom, pair<bool, index_object>& termBoundIndex) {
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++){
		Term* t=templateAtom->getTerm(i);
		if(!indexPair.second && t->isGround()){
			indexPair.first=i;
			indexPair.second = true;
		}
		if(indexPair.second && i == indexPair.first && t->isGround()) {
			termBoundIndex.first = true;
			termBoundIndex.second = t->getIndex();
			break;
		}
	}
	if(!createdIndex && indexPair.first && table->size()>0)
		initializeIndexMaps();
}

GeneralIterator* SingleTermAtomSearcherMultiMap::computeGenericIterator(Atom* templateAtom) {

	pair<bool, index_object> termBoundIndex( { false, 0 });
	createIndex(templateAtom,termBoundIndex);

	GeneralIterator* currentMatch;
	if(createdIndex && termBoundIndex.first){
		auto pair=tableIndexMap.equal_range(termBoundIndex.second);
		currentMatch=new UnorderedMultiMapIterator(pair.first,pair.second);
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
	return currentMatch;
}

void SingleTermAtomSearcherMultiMap::initializeIndexMaps(){
//	Timer::getInstance()->start("Creation Index Structure");
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexPair.first)->getIndex();
		tableIndexMap.insert({termIndex,a});
	}
//	Timer::getInstance()->end();
	createdIndex=true;
}

};

};





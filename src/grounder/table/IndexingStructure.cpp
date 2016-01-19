/*
 * IndexingStructure.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: jessica
 */

#include "IndexingStructure.h"

namespace DLV2 {
namespace grounder {

/******************************************************** Indexing Structure (Vector) **************************************************/

Atom* IndexingStructure::find(Atom* atom) {
	for(auto atom1:(*table)){
		if(*atom1==*atom){
			return atom1;
		}
	}
	return nullptr;
}

/******************************************************** Unordered Set **************************************************/

Atom* UnorderedSet::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	auto atomFound_it=indexingStructure.find(atom);
	if(atomFound_it!=indexingStructure.end())
		return *atomFound_it;
	return nullptr;
}

void UnorderedSet::update() {
	for (;lastUpdate<table->size();++lastUpdate)
		indexingStructure.insert((*table)[lastUpdate]);
}


/******************************************************** Unordered Map of Unordered Set **************************************************/

void UnorderedMapOfUnorderedSet::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	if(lastUpdate==table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		if(indexingStructure.count(termIndex))
			indexingStructure[termIndex].insert(atom);
		else{
			indexingStructure.emplace(termIndex,AtomTable({atom}));
		}
	}
}

Atom* UnorderedMapOfUnorderedSet::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();

	auto atomFound_it=indexingStructure[term].find(atom);
	if(atomFound_it!=indexingStructure[term].end()){
		return *atomFound_it;
	}
	return nullptr;
}

void UnorderedMapOfUnorderedSet::update() {
	unsigned i=indexingTerms[0];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		if(!indexingStructure.count(termIndex)){
			AtomTable values;
//			values.reserve(table->size()/PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation()->getSelectivity(indexingTerm));
			values.insert(a);
			indexingStructure.insert({termIndex,values});
		}
		else
			indexingStructure[termIndex].insert(a);
	}
}

GeneralIterator* UnorderedMapOfUnorderedSet::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation) {
	if(lastUpdate<table->size())
		update();

	int indexingTerm=indexingTerms[0];
	GeneralIterator* currentMatch;

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	AtomTable* matchingTable=&indexingStructure[term];
	currentMatch=new UnorderedSetIterator(matchingTable->begin(),matchingTable->end());
	return currentMatch;

}

/******************************************************** Unordered Map of Vector **************************************************/

void UnorderedMapOfVector::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	if(lastUpdate==table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		if(indexingStructure.count(termIndex))
			indexingStructure[termIndex].push_back(atom);
		else{
			indexingStructure.emplace(termIndex,AtomVector({atom}));
		}
	}
}

Atom* UnorderedMapOfVector::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();
	AtomVector* matchingTable=&indexingStructure[term];

	for(auto atom1:(*matchingTable)){
		if(*atom1==*atom){
			return atom1;
		}
	}
	return nullptr;
}

void UnorderedMapOfVector::update() {
	unsigned i=indexingTerms[0];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		if(!indexingStructure.count(termIndex)){
			AtomVector values;
//			values.reserve(table->size()/PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation()->getSelectivity(indexingTerm));
			values.push_back(a);
			indexingStructure.insert({termIndex,values});
		}
		else
			indexingStructure[termIndex].push_back(a);
	}
}

GeneralIterator* UnorderedMapOfVector::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation) {
	if(lastUpdate<table->size())
		update();

	int indexingTerm=indexingTerms[0];
	GeneralIterator* currentMatch;

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	AtomVector* matchingTable=&indexingStructure[term];
	currentMatch=new VectorIterator(matchingTable->begin(),matchingTable->end());

	return currentMatch;
}

/******************************************************** Unordered Multi Map **************************************************/

void UnorderedMultiMap::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	if(lastUpdate==table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		indexingStructure.insert({termIndex,atom});
	}
}

Atom* UnorderedMultiMap::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();
	auto matchingTable=indexingStructure.equal_range(term);

	for(auto it=matchingTable.first;it!=matchingTable.second;++it){
		if(*((*it).second)==*atom){
			return (*it).second;
		}
	}
	return nullptr;
}

void UnorderedMultiMap::update() {
	unsigned i=indexingTerms[0];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		indexingStructure.insert({termIndex,a});
	}
}

GeneralIterator* UnorderedMultiMap::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation) {
	if(lastUpdate<table->size())
		update();

	int indexingTerm=indexingTerms[0];
	GeneralIterator* currentMatch;

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	auto matchingTable=indexingStructure.equal_range(term);
	currentMatch=new UnorderedMultiMapIterator(matchingTable.first,matchingTable.second);

	return currentMatch;
}

/******************************************************** Unordered Map of Unordered Multi Map **************************************************/

void UnorderedMapOfUnorderedMultimap::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	if(lastUpdate<table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		int nextTermIndex=-1;
		if(i<(atom->getPredicate()->getArity()-1))
			nextTermIndex=atom->getTerm(i+1)->getIndex();
		if(indexingStructure.count(termIndex)){
			if(nextTermIndex>-1)
				indexingStructure[termIndex].insert({nextTermIndex,atom});
			else
				indexingStructure[termIndex].insert({termIndex,atom});
		}
		else{
			Multimap_Atom values;
			if(nextTermIndex>-1)
				values.insert({nextTermIndex,atom});
			else
				values.insert({termIndex,atom});
			indexingStructure.insert({termIndex,values});
		}
	}
}

Atom* UnorderedMapOfUnorderedMultimap::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();
	Multimap_Atom::iterator start;
	Multimap_Atom::iterator end;

	if(i <atom->getPredicate()->getArity()-1){
		index_object nextTerm=atom->getTerm(i+1)->getIndex();
		auto pair=indexingStructure[term].equal_range(nextTerm);
		start=pair.first;
		end=pair.second;
	}
	else{
		start=indexingStructure[term].begin();
		end=indexingStructure[term].end();
	}

	for(auto it=start;it!=end;++it){
		if(*(it->second)==*atom)
			return it->second;
	}
	return nullptr;

}

void UnorderedMapOfUnorderedMultimap::update() {
	if(table->empty()) return;
	Predicate* predicate=(*table)[0]->getPredicate();
	unsigned indexingTerm=indexingTerms[0];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom* a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		int nextTermIndex=-1;
		if(indexingTerm<(predicate->getArity()-1))
			nextTermIndex=a->getTerm(indexingTerm+1)->getIndex();
		if(indexingStructure.count(termIndex)){
			if(nextTermIndex>-1)
				indexingStructure[termIndex].insert({nextTermIndex,a});
			else
				indexingStructure[termIndex].insert({termIndex,a});
		}
		else{
			Multimap_Atom values;
			if(nextTermIndex>-1)
				values.insert({nextTermIndex,a});
			else
				values.insert({termIndex,a});
			indexingStructure.insert({termIndex,values});
		}
	}
}

GeneralIterator* UnorderedMapOfUnorderedMultimap::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation) {
	if(lastUpdate<table->size())
		update();

	unsigned indexingTerm=indexingTerms[0];

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	Multimap_Atom::iterator start;
	Multimap_Atom::iterator end;

	Term* nextTerm=templateAtom->getTerm(indexingTerm+1);
	if(indexingTerm < templateAtom->getPredicate()->getArity()-1 && nextTerm->isGround()){ //FIXME avoid to call isGround
		index_object nextTermIndex=nextTerm->getIndex();
		auto pair=indexingStructure[term].equal_range(nextTermIndex);
		start=pair.first;
		end=pair.second;
	}
	else{
		start=indexingStructure[term].begin();
		end=indexingStructure[term].end();
	}
	return new UnorderedMultiMapIterator(start,end);
}

} /* namespace grounder */
} /* namespace DLV2 */

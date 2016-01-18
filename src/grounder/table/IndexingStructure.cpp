/*
 * IndexingStructure.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: jessica
 */

#include "IndexingStructure.h"

namespace DLV2 {
namespace grounder {

Atom* IndexingStructure::find(Atom* atom) {
	for(auto atom1:(*table)){
		if(*atom1==*atom){
			return atom1;
		}
	}
	return nullptr;
}

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


void UnorderedMapOfMap::add(Atom* atom) {
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

Atom* UnorderedMapOfMap::find(Atom* atom) {
	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();
	AtomTable* matchingTable=&indexingStructure[term];

	auto atomFound_it=matchingTable->find(atom);
	if(atomFound_it!=matchingTable->end())
		return *atomFound_it;
	return nullptr;
}

void UnorderedMapOfMap::update() {
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

} /* namespace grounder */
} /* namespace DLV2 */

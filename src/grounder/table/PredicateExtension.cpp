/*
 * Instance.cpp
 *
 *  Created on: 24/mar/2014
 *      Author: Jessica
 */

#include "PredicateExtension.h"
#include "../ground/StatementDependency.h"
//#include "../utility/Timer.h"
#include <climits>

namespace DLV2{

namespace grounder{

/****************************************************** PREDICATE EXTENSION ***************************************************/

unsigned int PredicateExtension::MAX_TABLE_NUMBER = 4;

IndexingStructure* PredicateExtension::createAtomSearcher(unsigned table, unsigned indexType, vector<unsigned>* indexingTerms) {
	IndexingStructure* indexingStructure;
	switch (indexType) {
	case (MAP):
		indexingStructure = new UnorderedMapOfUnorderedSet(tables[table],*indexingTerms);
		break;
//	case (MAP_DICTIONARY_INTERSECTION):
//		atomSearcher = new SingleTermMapDictionaryAtomSearcher(tables[table],
//				predicate);
//		break;
//	case (MULTIMAP):
//		atomSearcher = new SingleTermMultiMapAtomSearcher(tables[table],
//				predicate);
//		break;
	case (HASHSET):
		indexingStructure = new UnorderedSet(tables[table]);
		break;
//	case (DOUBLEMAP):
//		atomSearcher = new DoubleTermMapAtomSearcher(tables[table], predicate);
//		break;
	case (MAP_VECTOR):
		indexingStructure = new UnorderedMapOfVector(tables[table],*indexingTerms);
		break;
	default:
		indexingStructure = new IndexingStructure(tables[table]);
		break;
	}
	return indexingStructure;
}

IndexingStructure* PredicateExtension::addAtomSearcher(unsigned table, vector<unsigned>* indexingTerms){
	// Properly set the IndexAtom type
	if(table<tables.size()){
		int indexType=Options::globalOptions()->getPredicateIndexType(predicate->getName());

		if(indexType==-1){
			if(StatementDependency::getInstance()->isOnlyInHead(predicate->getIndex()) || predicate->getArity()==1)
				indexType=HASHSET;
			else
				indexType=Options::globalOptions()->getIndexType();
		}

		if(predicate->getArity()==0)
			indexType=DEFAULT;

	#ifdef DEBUG_ATOM_SEARCHER
		cout<<"Predicate: "<<predicate->getName()<<"  Index type: "<<indexType<<endl;
	#endif

		IndexingStructure* indexingStruct=atomSearchers[table]->getIndexingStructure(indexType,indexingTerms);
		if(indexingStruct==nullptr){
			indexingStruct = createAtomSearcher(table, indexType, indexingTerms);
			atomSearchers[table]->addIndexingStructure(indexingStruct);
		}
		return indexingStruct;
	}
	return 0;
}

IndexingStructure* PredicateExtension::addAtomSearcher(unsigned table, unsigned type, vector<unsigned>* indexingTerms) {
	if(table<tables.size()){
		int indexType=type;
		if(predicate->getArity()==0)
			indexType=DEFAULT;
		if(predicate->getArity()==1)
			indexType=HASHSET;
		IndexingStructure* indexingStruct=atomSearchers[table]->getIndexingStructure(indexType,indexingTerms);
		if(indexingStruct==nullptr){
			indexingStruct = createAtomSearcher(table, indexType, indexingTerms);
			atomSearchers[table]->addIndexingStructure(indexingStruct);
		}
		return indexingStruct;
	}
	return 0;
}

PredicateExtension::~PredicateExtension() {
	for(unsigned int i=0;i<tables.size();++i){
		AtomVector* table=tables[i];
		for (auto it = table->begin(); it != table->end(); ++it){
			delete *it;
		}
		delete table;
	}

	for(unsigned int i=0;i<atomSearchers.size();++i)
		delete atomSearchers[i];

	delete predicateInformation;
}

void PredicateExtension::swapTables(unsigned tableFrom,unsigned tableTo){
	assert_msg(tableFrom<tables.size(),"The specified table doesn't exist.");
	assert_msg(tableTo<tables.size(),"The specified table doesn't exist.");

	AtomVector *table_from=tables[tableFrom];
	AtomVector *table_to=tables[tableTo];

	unsigned size=table_from->size();
	table_to->reserve(size+table_to->size());
	for (int i = size-1; i >= 0; --i) {
		Atom* currentAtom=(*table_from)[i];

		table_to->push_back(currentAtom);
		table_from->pop_back();

	}

	atomSearchers[tableFrom]->clear();
}

void PredicateExtension::swapPointersTables(unsigned tableFrom, unsigned tableTo) {
	assert_msg(tableFrom<tables.size(),"The specified table doesn't exist.");
	assert_msg(tableTo<tables.size(),"The specified table doesn't exist.");

	AtomSearcher *seacher_from=atomSearchers[tableFrom];
	AtomSearcher *seacher_to=atomSearchers[tableTo];
	AtomSearcher *searcher_tmp=seacher_from;
	atomSearchers[tableFrom]=seacher_to;
	atomSearchers[tableTo]=searcher_tmp;

	AtomVector* table_from=tables[tableFrom];
	AtomVector* table_to=tables[tableTo];
	AtomVector* table_tmp=table_from;
	tables[tableFrom]=table_to;
	tables[tableTo]=table_tmp;

}

/****************************************************** PREDICATE EXT TABLE ***************************************************/

PredicateExtTable *PredicateExtTable::predicateExtTable_;

/****************************************************** PREDICATE INFORMATION ***************************************************/

PredicateInformation::PredicateInformation(unsigned arity) : min(arity,INT_MAX), max(arity,INT_MIN) {
	min.reserve(arity);
	max.reserve(arity);
	termDictionary.resize(arity);
}

bool PredicateInformation::isOnlyPositive(unsigned index) const {
	if(min[index]>=0)
		return true;
	return false;
}

bool PredicateInformation::isOnlyNegative(unsigned index) const {
	if(max[index]<=0)
		return true;
	return false;
}

bool PredicateInformation::isOnlyPositive() const {
	for(auto n:min){
		if(n<0)
			return false;
	}
	return true;
}

bool PredicateInformation::isOnlyNegative() const {
	for(auto n:max){
		if(n>0)
			return false;
	}
	return true;
}

void PredicateInformation::update(Atom* atom) {
	for (unsigned i = 0; i < atom->getTermsSize(); ++i) {
		Term* t=atom->getTerm(i);
		if(t->getType()==TermType::NUMERIC_CONSTANT){
			int val=t->getConstantValue();
			if(t->getConstantValue()>max[i])
				max[i]=val;
			if(t->getConstantValue()<min[i])
				min[i]=val;
		}
		addInDictionary(i,t);
	}
}

int PredicateInformation::getMax(unsigned index) const {
	return max[index];
}

int PredicateInformation::getMin(unsigned index) const {
	return min[index];
}

void PredicateInformation::addInDictionary(unsigned position, Term* term) {
	termDictionary[position].insert(term);
}

bool PredicateInformation::isPresent(unsigned position, Term* term) const {
	return termDictionary[position].count(term);
}


}
}


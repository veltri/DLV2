/*
 * Instance.cpp
 *
 *  Created on: 24/mar/2014
 *      Author: Jessica
 */

#include "PredicateExtension.h"
//#include "../utility/Timer.h"


namespace DLV2{

namespace grounder{

/****************************************************** PREDICATE EXTENSION ***************************************************/

void PredicateExtension::setAtomSearchers(){


	// Properly set the IndexAtom type
	while(atomSearchers.size()<tables.size()){
		AtomSearcher* atomSearcher;
		switch (Options::globalOptions()->getIndexType()) {
		case (MAP):
			atomSearcher = new SingleTermAtomSearcher(tables[atomSearchers.size()],predicate);
			break;
		case (MULTIMAP):
			atomSearcher = new SingleTermAtomSearcherMultiMap(tables[atomSearchers.size()],predicate);
			break;
		default:
			atomSearcher = new SimpleAtomSearcher(tables[atomSearchers.size()]);
			break;
		}
		atomSearchers.push_back(atomSearcher);
	}


}

PredicateExtension::~PredicateExtension() {
	for(unsigned int i=0;i<tables.size();i++){
		AtomVector* table=tables[i];
		for (auto it = table->begin(); it != table->end(); it++){
			delete *it;
		}
		delete table;
	}

	for(unsigned int i=0;i<atomSearchers.size();i++){
		delete atomSearchers[i];
	}
}

void PredicateExtension::swapTables(unsigned tableFrom,unsigned tableTo){
	assert_msg(tableFrom<tables.size(),"The specified table doesn't exist.");
	assert_msg(tableTo<tables.size(),"The specified table doesn't exist.");

	AtomVector *table_from=tables[tableFrom];
	AtomVector *table_to=tables[tableTo];

	AtomSearcher* seacher_from=atomSearchers[tableFrom];
	AtomSearcher* seacher_to=atomSearchers[tableTo];
	unsigned size=table_from->size();
	table_to->reserve(size+table_to->size());
	for (int i = size-1; i >= 0; --i) {
		Atom* currentAtom=(*table_from)[i];

		table_to->push_back(currentAtom);
		table_from->pop_back();

		seacher_to->add(currentAtom);
	}

	seacher_from->clear();
}

/****************************************************** PREDICATE EXT TABLE ***************************************************/

PredicateExtTable *PredicateExtTable::predicateExtTable_;


PredicateExtTable* PredicateExtTable::getInstance(){
	if(predicateExtTable_== nullptr)
		predicateExtTable_= new PredicateExtTable;

	return predicateExtTable_;
}



};

};

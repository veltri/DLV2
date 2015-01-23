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

/****************************************************** INSTANCES ***************************************************/

void PredicateExtension::setAtomSearchers(){
	// Properly set the IndexAtom type
	while(atomSearchers.size()<tables.size()){
		AtomSearcher* atomSearcher;
		switch (Options::globalOptions()->getIndexType()) {
		case (MAP):
			atomSearcher = new SingleTermAtomSearcher(&tables[PredicateExtension::FACTS],&tables[PredicateExtension::NOFACTS],&tables[PredicateExtension::DELTA],predicate);
			break;
		case (MULTIMAP):
			atomSearcher = new SingleTermAtomSearcherMultiMap(&tables[PredicateExtension::FACTS],&tables[PredicateExtension::NOFACTS],&tables[PredicateExtension::DELTA],predicate);
			break;
		default:
			atomSearcher = new SimpleAtomSearcher(&tables[PredicateExtension::FACTS],&tables[PredicateExtension::NOFACTS],&tables[PredicateExtension::DELTA],predicate);
			break;
		}
		atomSearchers.push_back(atomSearcher);
	}
}

PredicateExtension::~PredicateExtension() {
	for(unsigned int i=0;i<tables.size();i++){
		AtomTable* table=&tables[i];
		for (auto it = table->begin(); it != table->end(); it++){
			delete *it;
		}
	}
	for(unsigned int i=0;i<atomSearchers.size();i++){
		delete atomSearchers[i];
	}
}

void PredicateExtension::swapTables(unsigned tableFrom,unsigned tableTo){
	assert_msg(tableFrom<tables.size(),"The specified table doesn't exist.");
	assert_msg(tableTo<tables.size(),"The specified table doesn't exist.");

	AtomTable table_from=tables[tableFrom];
	AtomTable table_to=tables[tableTo];

	unsigned size=table_from.size();
	table_to.reserve(size+table_to.size());
	for (unsigned int i = size-1; i >= 0; --i) {
		table_to.push_back(table_from[i]);
		table_from.pop_back();
	}
	//TODO fare lo stesso per i searcher
	swapSeacher(tableFrom,tableTo);
}

/****************************************************** INSTANCES TABLE ***************************************************/

PredicateExtTable *PredicateExtTable::predicateExtTable_;

PredicateExtTable::~PredicateExtTable() {
	for (auto i : predicateExtTable)
		delete (i.second);
}

PredicateExtTable* PredicateExtTable::getInstance(){
	if(predicateExtTable_== nullptr)
		predicateExtTable_= new PredicateExtTable;

	return predicateExtTable_;
}



};

};

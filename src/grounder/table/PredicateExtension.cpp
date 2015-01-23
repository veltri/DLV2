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

void PredicateExtension::setIndexAtom(){
	// Properly set the IndexAtom type
	switch (Options::globalOptions()->getIndexType()) {
	case (MAP):
		indexAtom = new SingleTermAtomSearcher(&tables[PredicateExtension::FACTS],&tables[PredicateExtension::NOFACTS],&tables[PredicateExtension::DELTA],predicate);
		break;
	case (MULTIMAP):
		indexAtom = new SingleTermAtomSearcherMultiMap(&tables[PredicateExtension::FACTS],&tables[PredicateExtension::NOFACTS],&tables[PredicateExtension::DELTA],predicate);
		break;
	default:
		indexAtom = new SimpleAtomSearcher(&tables[PredicateExtension::FACTS],&tables[PredicateExtension::NOFACTS],&tables[PredicateExtension::DELTA],predicate);
		break;
	}
}

PredicateExtension::~PredicateExtension() {
	for(unsigned int i=0;i<tables.size();i++){
		AtomTable* table=&tables[i];
		for (auto it = table->begin(); it != table->end(); it++){
			delete *it;
		}
	}
	delete (indexAtom);
}

void PredicateExtension::moveNextDeltaInDelta(){
	AtomTable* nofacts=&tables[PredicateExtension::NOFACTS];
	AtomTable* delta=&tables[PredicateExtension::DELTA];
	AtomTable* nextDelta=&tables[PredicateExtension::NEXTDELTA];
	if(delta->size()>0){
		for(GenericAtom* atom: *delta)
			nofacts->insert(atom);
		delta->clear();
	}
	if(nextDelta->size()>0){
		indexAtom->updateDelta(nextDelta);
		for(GenericAtom* atom: *nextDelta)
			delta->insert(atom);
		nextDelta->clear();
	}
}

bool PredicateExtension::isTrue(vector<Term*>& terms) {
	GenericAtom* atom=getGenericAtom(PredicateExtension::NEXTDELTA,terms,0);
	return atom->isFact();
}

void PredicateExtension::setTruth(vector<Term*>& terms, bool truth) {
	GenericAtom* atom=getGenericAtom(PredicateExtension::NEXTDELTA,terms,truth);
	atom->setFact(truth);
}

GenericAtom* PredicateExtension::getGenericAtom(unsigned int table,vector<Term*>& terms,bool truth) {
	vector<Term*> v(terms); //FIXME
	GenericAtom* atom=new GenericAtom(v,truth);
	for(unsigned int i=PredicateExtension::FACTS;i<table;i++){
		auto it=tables[i].find(atom);
		if(it!=tables[i].end()){
			GenericAtom* tmp=atom;
			atom = (*it);
			delete tmp;
			return atom;
		}
	}
	delete atom;
	return 0;
}

GenericAtom* PredicateExtension::getGenericAtom(vector<Term*>& terms,bool truth) {
	return getGenericAtom(PredicateExtension::NEXTDELTA,terms,truth);
}

bool PredicateExtension::add(unsigned int table, GenericAtom*& atomUndef, bool& updated) {
	GenericAtom* atom=getGenericAtom(table+1,atomUndef->getTerms(),atomUndef->isFact());
	if(atom==0){
		tables[table].insert(atomUndef);
		return true;
	}
	if(atomUndef->isFact() && !atom->isFact()){
		atom->setFact(true);
		updated=true;
		return false;
	}
	return false;
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

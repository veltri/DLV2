/*
 * PredicateTable.cpp
 *
 *  Created on: 13/mar/2014
 *      Author: Davide
 */

#include "PredicateTable.h"

namespace DLV2{

namespace grounder{

PredicateTable *PredicateTable::predicateTable;


void PredicateTable::getEdbPredicate(set_predicate& edb_pred) {
	for (auto p : predicate_set.flyweight_set)
		if (p->isEdb())
			edb_pred.insert(p);
}

PredicateTable* PredicateTable::getInstance() {

		if(predicateTable==nullptr)
			predicateTable=new PredicateTable;

		return predicateTable;
}

void PredicateTable::getEdbPredicate(unordered_set<index_object>& edb_pred) {
	for (auto p : predicate_set.flyweight_set)
		if (p->isEdb())
			edb_pred.insert(p->getIndex());
}

void PredicateTable::getPredicateName(unordered_set<string>& names) {
	for (auto p : predicate_set.flyweight_set)
		names.insert(p->getName());
}

};

};

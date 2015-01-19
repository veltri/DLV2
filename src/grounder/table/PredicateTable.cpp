/*
 * PredicateTable.cpp
 *
 *  Created on: 13/mar/2014
 *      Author: Davide
 */

#include "PredicateTable.h"

namespace DLV2{

namespace grounder{

void PredicateTable::getEdbPredicate(set_predicate& edb_pred) {
	for (auto p : predicate_set.flyweight_set)
		if (p->isEdb())
			edb_pred.insert(p);
}


void PredicateTable::getEdbPredicate(unordered_set<index_object>& edb_pred) {
	for (auto p : predicate_set.flyweight_set)
		if (p->isEdb())
			edb_pred.insert(p->getIndex());
}

};

};

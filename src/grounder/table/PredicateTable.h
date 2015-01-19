/*
 * PredicateTable.h
 *
 *  Created on: 13/mar/2014
 *      Author: Davide
 */

#ifndef PREDICATETABLE_H_
#define PREDICATETABLE_H_

#include <unordered_set>
#include <iostream>

#include "../atom/Predicate.h"


using namespace std;

namespace DLV2{

namespace grounder{


/**
 * Hash table of predicate
 */
class PredicateTable {
public:

	static PredicateTable* getInstance();

	/// Insert predicate in a table and return the index of the predicate
	void insertPredicate(Predicate *&p){predicate_set.insert(p);};
	/// Get the predicate
	void getPredicate(Predicate*& p){predicate_set.get(p);};
	/// Get all the Edb predicate
	void getEdbPredicate(set_predicate& edb_pred);
	/// Get all the Edb predicate index
	void getEdbPredicate(unordered_set<index_object>& edb_pred);
	~PredicateTable(){};
protected:
	static PredicateTable* predicateTable;
private:
	PredicateTable(){};

	FlyweightIndexFactory<Predicate> predicate_set;
};

};

};

#endif /* PREDICATETABLE_H_ */

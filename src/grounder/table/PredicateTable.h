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
	/// If the predicate is true negated insert also in the set predicate_true_negated
	inline void insertPredicate(Predicate *&p){
		predicate_set.insert(p);
		if(p->isTrueNegated())predicate_true_negated.insert(p);
	};
	/// Get the predicate
	void getPredicate(Predicate*& p){predicate_set.get(p);};
	/// Get all the Edb predicate
	void getEdbPredicate(set_predicate& edb_pred);
	/// Get all the Edb predicate index
	void getEdbPredicate(unordered_set<index_object>& edb_pred);
	///Get all predicates in the program
	void getPredicateName(unordered_set<string>& names);

	const set_predicate& getPredicateTrueNegated(){return predicate_true_negated;}

	Predicate* getQueryPredicate(){
		Predicate *qp=nullptr;
		for(auto predicate:predicate_set.flyweight_set){
			if(predicate->getName()==PREDNAME_QUERY)
				return predicate;
		}
		return qp;
	}

	void print(){predicate_set.print();}

	void setAllPredicateHidden(){
		for(auto predicate:predicate_set.flyweight_set){
			predicate->setHiddenForPrinting(true);
		}
	}

	~PredicateTable(){};
protected:
	static PredicateTable* predicateTable;
private:
	PredicateTable(){};

	FlyweightIndexFactory<Predicate> predicate_set;

	/// Set of predicate that have an atom true negated
	set_predicate predicate_true_negated;
};

};

};

#endif /* PREDICATETABLE_H_ */

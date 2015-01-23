/*
 * Instance.h
 *
 *  Created on: 24/mar/2014
 *      Author: Jessica
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <iostream>

#include "../../util/Options.h"
#include "../../util/Assert.h"
#include "AtomSearcher.h"

using namespace std;

namespace DLV2{

namespace grounder{

///A vector of pair of unsigned integer values and index_object values @see IndexDefinition
typedef vector<pair<unsigned int,index_object>> vec_pair_index_object;
///An unordered map with unsigned integers as keys and values
typedef unordered_multimap<unsigned int,unsigned int> map_int_int;

/**
 * This class represents the instances (the facts and the no facts) of a predicate
 */

class PredicateExtension {
public:
	///Constructors
	PredicateExtension(Predicate* predicate): predicate(predicate){};
	PredicateExtension(Predicate* predicate, unsigned tableNumber): predicate(predicate){
		for(unsigned i=0;i<tableNumber;i++)
			tables.push_back(AtomTable());
		setAtomSearchers();
	}

	///Getter for the predicate
	Predicate* getPredicate() const {return predicate;}

	//Returns the i-th AtomSeacher in atomSearchers
	AtomSearcher* getAtomSearcher(unsigned i){
		assert_msg(i<atomSearchers.size(),"The specified AtomSearche doesn't exist.");
		return atomSearchers[i];
	}

	void addTable(){
		tables.push_back(AtomTable());
		setAtomSearchers();
	}

	void addGenericAtom(unsigned table, Atom* genericAtom){
		assert_msg(i<tables.size(),"The specified table doesn't exist.");
		//Cerca in atomSearcher[i] prima di inserire
		atomSearchers[table]->find(genericAtom);
		tables[table].push_back(genericAtom);
	}

	Atom* getGenericAtom(unsigned table, Atom* genericAtom){
		assert_msg(table<tables.size(),"The specified table doesn't exist.");
		//Aggiungi in atomSearcher[i]
		atomSearchers[table]->find(genericAtom);
		return nullptr;
	}

	 //Moves the content of the tableFrom (source) to the tableTo (destination)
	 void swapTables(unsigned tableFrom,unsigned tableTo);

	///Printer method for a single table
	inline void print(unsigned table){for(auto fact:tables[table]){ClassicalLiteral::print(predicate,fact->getTerms(),false,false); cout<<"."<<endl;}}

	///Destructor
	~PredicateExtension();

private:
	///The predicate
	Predicate* predicate;

	///For each AtomTable in tables is present an AtomSeacher in atomSearchers
	///The vector of tables
	vector<AtomTable> tables;
	///The vector of  AtomSeacher
	vector<AtomSearcher*> atomSearchers;

	///This method configures the searching strategy for each table
	void setAtomSearchers();

};

/**
 * This class stores the instances for all the predicate.
 */

class PredicateExtTable {
public:


	///This method adds an Instance for a predicate
	void addInstance(Predicate* p) {
		if(!predicateExtTable.count(p->getIndex())){
			PredicateExtension* is = new PredicateExtension(p);
			predicateExtTable.insert({p->getIndex(),is});
		}
	};

	///Getter for the instances of a predicate
	PredicateExtension* getInstance(Predicate* p) {
		auto result= predicateExtTable.find(p->getIndex());
		if(result==predicateExtTable.end()) return nullptr;
		return result->second;
	};

	///Getter for the instances of a predicate index
	PredicateExtension* getInstanceIndex(index_object p) {
		auto result= predicateExtTable.find(p);
		if(result==predicateExtTable.end()) return nullptr;
		return result->second;
	};

	///This method return the size of the map of instances
	unsigned int getSize() {return predicateExtTable.size();};

	///Printer method
	void print() {for (auto i : predicateExtTable)i.second->print();	};

	///Destructor
	~PredicateExtTable();

	static PredicateExtTable* getInstance();
private:
	///Constructor
	PredicateExtTable(){}

	static PredicateExtTable *predicateExtTable_;

	///The map that stores all the Instances
	unordered_map<index_object,PredicateExtension*> predicateExtTable;
};

};

};

#endif /* INSTANCE_H_ */

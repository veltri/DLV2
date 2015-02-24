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


/**
 * This class represents the extension of each predicate (instances).
 * The class may have multiple table of atoms and for each table have an AtomSearcher associate
 */

class PredicateExtension {
public:
	///Constructors
	PredicateExtension(Predicate* predicate, unsigned tableNumber = 2): predicate(predicate){
		if(MAX_TABLE_NUMBER){
			tables.reserve(MAX_TABLE_NUMBER);
			atomSearchers.reserve(MAX_TABLE_NUMBER);
		}
		for(unsigned i=0;i<tableNumber;i++)
			tables.push_back(new AtomVector());
	}

	///Getter for the predicate
	Predicate* getPredicate() const {return predicate;}

	///Returns the i-th AtomSeacher in atomSearchers
	AtomSearcher* getAtomSearcher(unsigned i){
		setAtomSearchers();
		assert_msg(i<atomSearchers.size(),"The specified AtomSearche doesn't exist.");
		return atomSearchers[i];
	}

	/// Add table and an AtomSearcher
	void addTable(){
		tables.push_back(new AtomVector());
		setAtomSearchers();
	}

	///Add generic atom in specified table
	bool addGenericAtom(unsigned table, Atom* genericAtom, bool search = false){
		assert_msg(table<tables.size(),"The specified table doesn't exist.");
		AtomSearcher* atomSearcher=getAtomSearcher(table);
		if(search && (atomSearcher->findAtom(genericAtom))!=nullptr)
			return false;
		tables[table]->push_back(genericAtom);
		atomSearcher->add(genericAtom);
		return true;
	}

	///Get an generic atom in specified table
	Atom* getGenericAtom(unsigned table, Atom* genericAtom){
		assert_msg(table<tables.size(),"The specified table doesn't exist.");
		if(tables[table]->size()==0)return nullptr;
		AtomSearcher* atomSearcher=getAtomSearcher(table);
		Atom* atomFound=atomSearcher->findAtom(genericAtom);
		return atomFound;
	}

	///Get an generic atom searching in all table
	Atom* getGenericAtom(Atom* genericAtom){
		for(unsigned i=0;i<atomSearchers.size();i++){
			if(tables[i]->size()==0) continue;
			Atom* atomFound=getGenericAtom(i,genericAtom);
			if(atomFound!=nullptr)
				return atomFound;
		}
		return nullptr;
	}

	 //Moves the content of the tableFrom (source) to the tableTo (destination)
	 void swapTables(unsigned tableFrom,unsigned tableTo);

	///Printer method for a single table
	inline void print(unsigned table){for(auto fact:*tables[table]){ClassicalLiteral::print(predicate,fact->getTerms(),false,false); cout<<"."<<endl;}}

	///Destructor
	~PredicateExtension();

	static void setMaxTableNumber(unsigned int maxTableNumber) {MAX_TABLE_NUMBER = maxTableNumber;}

private:
	///The predicate
	Predicate* predicate;

	///For each AtomTable in tables is present an AtomSeacher in atomSearchers
	///The vector of tables
	vector<AtomVector*> tables;
	///The vector of  AtomSeacher
	vector<AtomSearcher*> atomSearchers;

	static unsigned int MAX_TABLE_NUMBER;

	///This method configures the searching strategy for each table
	void setAtomSearchers();

};

/**
 * This class stores the Predicate Extensions for all the predicate.
 * Is a Singleton.
 */

class PredicateExtTable {
public:

	///This method adds an Instance for a predicate
	void addPredicateExt(Predicate* p) {
		if(!predicateExtTable.count(p->getIndex())){
			PredicateExtension *is=new PredicateExtension(p);
			predicateExtTable.insert({p->getIndex(),is});
		}
	};

	///Getter for the instances of a predicate
	PredicateExtension* getPredicateExt(Predicate* p) {
		auto result= predicateExtTable.find(p->getIndex());
		if(result==predicateExtTable.end()) return nullptr;
		return (result->second);
	};

	///Getter for the instances of a predicate index
	PredicateExtension* getPredicateExt(index_object p) {
		auto result= predicateExtTable.find(p);
		if(result==predicateExtTable.end()) return nullptr;
		return (result->second);
	};

	///This method return the size of the map of instances
	unsigned int getSize() {return predicateExtTable.size();};

	///Printer method for the first table in Predicate Extension
	void print(unsigned table) {for (auto& i : predicateExtTable)i.second->print(table);};

	///Destructor
	~PredicateExtTable(){cout<<"aaa£"<<endl;for(auto pair_predExt:predicateExtTable) delete pair_predExt.second;};

	static PredicateExtTable* getInstance(){
		if(predicateExtTable_== nullptr)
			predicateExtTable_= new PredicateExtTable;
		return predicateExtTable_;
	}

private:
	///Constructor
	PredicateExtTable(){}

	static PredicateExtTable *predicateExtTable_;

	///The map that stores all the Predicate Extension
	unordered_map<index_object,PredicateExtension*> predicateExtTable;
};

};

};

#endif /* INSTANCE_H_ */

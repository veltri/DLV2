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
#include "IndexingStructure.h"
#include "IdGenerator.h"
#include "../output/OutputBuilder.h"
#include "../ground/StatementDependency.h"
#include "../atom/ClassicalLiteral.h"

using namespace std;

namespace DLV2{

namespace grounder{

/* Table of Predicate Extension:
 * 		FACT: Table of fact
 * 		NOFACT: Table of atom derived
 * 		DELTA, NEXTDELTA: Auxiliary table for grounding recursive rule
*/
#define FACT 0
#define NOFACT 1
#define DELTA 2
#define NEXTDELTA 3

class PredicateInformation{
public:
	PredicateInformation(unsigned arity);
	bool isOnlyPositive(unsigned index) const;
	bool isOnlyNegative(unsigned index) const;
	bool isOnlyPositive() const;
	bool isOnlyNegative() const;
	void update(Atom* atom);
	int getMax(unsigned index) const;
	int getMin(unsigned index) const;
	void addInDictionary(unsigned position,Term* term);
	unsigned getSelectivity(unsigned pos)const{return termDictionary[pos].size();}
	bool isPresent(unsigned position,Term* term)const;
	const set_term& getDictionary(unsigned i)const {return termDictionary[i];};

private:
	vector<int> min;
	vector<int> max;
	vector<set_term> termDictionary;

};


/**
 * This class represents the extension of each predicate (instances).
 * The class may have multiple table of atoms and for each table have an AtomSearcher associate
 */

class PredicateExtension {
public:
	///Constructor
	PredicateExtension(Predicate* predicate, unsigned tableNumber = 2): predicate(predicate), predicateInformation(new PredicateInformation(predicate->getArity())){
		tables.reserve(MAX_TABLE_NUMBER);
		atomSearchers.reserve(MAX_TABLE_NUMBER);
		addTables(tableNumber);
	}

	///Getter for the predicate
	inline Predicate* getPredicate() const {return predicate;}

	/// Add table and an AtomSearcher
	void addTables(unsigned numTables=1){
		for(unsigned i=0;i<numTables;++i){
			tables.push_back(new AtomHistoryVector());
			atomSearchers.push_back(new AtomSearcher(tables[i]));
		}
	}

	inline AtomHistoryVector* getTable(unsigned i)const{
		return tables[i];
	}

	///Returns the i-th AtomSeacher in atomSearchers
	inline AtomSearcher* getAtomSearcher(unsigned table)const{
		return atomSearchers[table];
	}

	IndexingStructure* getIndexingStructure(unsigned table, unsigned indexType, vector<unsigned>* indexingTerms=nullptr){
		return atomSearchers[table]->getIndexingStructure(indexType,indexingTerms);
	}

	IndexingStructure* getIndexingStructure(unsigned table, vector<unsigned>* indexingTerms=nullptr){
//		int indexType=Options::globalOptions()->getPredicateIndexType(predicate->getName());
//		if(indexType==-1){
//			if(StatementDependency::getInstance()->isOnlyInHead(predicate->getIndex()) || predicate->getArity()==1)
//				indexType=HASHSET;
//			else
//				indexType=Options::globalOptions()->getIndexType();
//		}
//		if(predicate->getArity()==0)
//			indexType=DEFAULT;
		return atomSearchers[table]->getIndexingStructure(indexingTerms);
	}

	///Set the index of the atom with new id if the atom is not yet indexed, and send it to the output builder
	void setIndexOfAtom(Atom* atom){
		atom->setIndex(IdGenerator::getInstance()->getNewId(1));
		if(!atom->getPredicate()->isHiddenForPrinting())
			OutputBuilder::getInstance()->appendToStreamAtomTable(atom);
	}

	///Search the given ground atom in all tables
	inline Atom* getGroundAtom(Atom* atom){
		for(unsigned table=0;table<tables.size();++table){
			IndexingStructure* indexingStructure=atomSearchers[table]->getDefaultIndexingStructure();
			if(indexingStructure!=nullptr){
				Atom* atomFound=indexingStructure->find(atom);
				if(atomFound!=nullptr)
					return atomFound;
			}
		}
		return nullptr;
	}

	void addAtom(Atom* atom, unsigned table){
		tables[table]->push_back(atom);
		predicateInformation->update(atom);

		if(predicate->isSolved() && !atom->isFact())
			predicate->setSolved(false);
		if(atom->getIndex()==0) setIndexOfAtom(atom);
	}

	inline void addAtom(Atom* atom, unsigned table,unsigned iteration){
		if(iteration>0)
			tables[table]->push_back_iteration(atom,iteration);
		else
			tables[table]->push_back(atom);

		predicateInformation->update(atom);

		if(predicate->isSolved() && !atom->isFact())
			predicate->setSolved(false);
		if(atom->getIndex()==0) setIndexOfAtom(atom);
	}

	//Moves the content of the tableFrom (source) to the tableTo (destination)
	void swapTables(unsigned tableFrom,unsigned tableTo);

	//Swap the pointers of the tableFrom (source) to the tableTo (destination)
	void swapPointersTables(unsigned tableFrom,unsigned tableTo);

	///Printer method for a single table
	inline void print(unsigned table){for(auto fact:*tables[table]){cout<<fact->getIndex()<<" ";ClassicalLiteral::print(predicate,fact->getTerms(),false,false,cout);cout<<endl;}}

	///Printer method for a single table
	inline void print(){for(unsigned table=0;table<tables.size();table++) print(table);}

	///Destructor
	~PredicateExtension();

	static void setMaxTableNumber(unsigned int maxTableNumber) {MAX_TABLE_NUMBER = maxTableNumber;}

	PredicateInformation* getPredicateInformation() const {return predicateInformation;}

	unsigned getPredicateExtentionSize(unsigned table) const {if(table<tables.size()) return tables[table]->size(); return 0;}
	unsigned getPredicateExtentionSize() const { unsigned size=0; for(auto table:tables) size+=table->size(); return size;}
	unsigned getPredicateExtentionSize(unsigned table,SearchType type) const {if(table<tables.size()) return tables[table]->size_iteration(type); return 0;}


	IndexingStructure* addAtomSearcher(unsigned table, vector<unsigned>* indexingTerms,bool recursive=false);
	IndexingStructure* addAtomSearcher(unsigned table, unsigned type, vector<unsigned>* indexingTerms,bool recursive=false);
	IndexingStructure* createAtomSearcher(unsigned table, unsigned indexType,  vector<unsigned>* indexingTerms,bool recursive=false);

private:
	///The predicate
	Predicate* predicate;

	///For each AtomTable in tables is present an AtomSeacher in atomSearchers
	///The vector of tables
	vector<AtomHistoryVector*> tables;
	///The vector of  AtomSeacher
	vector<AtomSearcher*> atomSearchers;

	static unsigned int MAX_TABLE_NUMBER;

	///A PredicateInformation object that stores the information about the max and the min values of each term in the instances of the predicate
	PredicateInformation* predicateInformation;

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
	void print(unsigned table) {for (auto& i : predicateExtTable) if(!(i.second->getPredicate()->isHiddenForPrinting())) i.second->print(table);};

	void print(){ for (auto& i : predicateExtTable) if(!(i.second->getPredicate()->isHiddenForPrinting())) i.second->print();}

	///Destructor
	~PredicateExtTable(){for(auto pair_predExt:predicateExtTable) delete pair_predExt.second;};

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

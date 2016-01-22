/*
 * IndexAtom.h
 *
 *  Created on: Nov 25, 2014
 *      Author: jessica
 */

#ifndef INDEXATOM_H_
#define INDEXATOM_H_

#include <algorithm>

#include "../hash/HashVecInt.h"
#include "../atom/ClassicalLiteral.h"
#include "PredicateTable.h"
#include "../statement/Rule.h"
#include "IndexingStructure.h"

using namespace std;

namespace DLV2{

namespace grounder{

/**
 * This class models a general searching strategy for a predicate's extension.
 */
class AtomSearcher {
public:
	AtomSearcher(AtomHistoryVector* table) : table(table) {resultVector.resize(ATOMS_IN_RULE,nullptr);};
	/// Given a partially ground atom, this method is meant to find all the matching atoms satisfying the variables assignment in the given atom.
	virtual void firstMatch(unsigned id,Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation, IndexingStructure* indexingStructure,const pair<SearchType,unsigned>& searchSpecification={ALL,0});
	/// Invoked after a first match iterate trough the matching atoms found one by one.
	virtual void nextMatch(unsigned id, Atom* templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation);
	/// Search a given ground atom by means of the given indexing structure
	virtual Atom* findGroundAtom(Atom *atom, IndexingStructure* indexingStructure);
	/// This method checks if the two given atoms match according to the current assignment.
	/// If they match the current assignment is update accordingly.
	bool checkMatch(Atom *genericAtom, Atom *templateAtom, var_assignment& currentAssignment,const RuleInformation& ruleInformation);
	/// Match a function with given id of term, compare the constant term and put in binds
	/// a value of the variable term present in termToMatch
	/// Return true if constant term are equal, else false
	bool matchTerm(Term *genericTerm, Term *termToMatch, var_assignment& varAssignment,vector<index_object>& addedVariables,const RuleInformation& ruleInformation);
	/// This method given an iterator increases it in order to find matching atoms with the given atom
	/// according to the current assignment.
	bool computeMatch(GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation);

	/// Erase the indexing structures
	inline virtual void clear(){indexingStructures.clear();}

	///Set the size of the result vector
	inline void setSizeResultVector(unsigned int size){	if(size>resultVector.size()) resultVector.resize(size,nullptr);}

	///Function for evaluation of builtin related with the current matching atom
	static bool evaluateFastBuiltin(const RuleInformation& ruleInformation, index_object index,	var_assignment& varAssignment, Term* genericTerm);

	///Add a specific indexing structure for the table
	void addIndexingStructure(IndexingStructure* indexingStructure){indexingStructures.push_back(indexingStructure);};
	///If present, returns an indexing structure for the table of the specified type and with the specified indexing terms
	IndexingStructure* getIndexingStructure(unsigned type, vector<unsigned>* indexingTerms);
	///If present, returns an indexing structure for the table of any type but with the specified indexing terms
	IndexingStructure* getIndexingStructure(vector<unsigned>* indexingTerms);

	///Return a default hash indexing structure
	IndexingStructure* getDefaultIndexingStructure(){
		if(indexingStructures.size()==0)
			indexingStructures.push_back(new UnorderedSet(table));

		for(auto indexingStructure: indexingStructures)
			if(indexingStructure->getType()==HASHSET || indexingStructure->getType()==MAP)
				return indexingStructure;

		return indexingStructures.front();
	}

	///Printer method. Useful mainly for debug purpose.
	virtual void print(ostream& stream=cout){for(auto atom:*table)atom->print(stream);}

	virtual ~AtomSearcher();

protected:
	///The basic data-structure that collects the atoms
	AtomHistoryVector* table;

	/// This maps stores the calls to the firstMatch method.
	/// Indeed, for each call it stores a pair with the counter and the iterator to the next matching atoms.
	vector<GeneralIterator*> resultVector;

	//This vector stores the created indexing structures for the table
	vector<IndexingStructure*> indexingStructures;

};

}}

#endif /*INDEXATOM_H_*/

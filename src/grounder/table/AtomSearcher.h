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
#include "../atom/GenericAtom.h"
#include "PredicateTable.h"

using namespace std;

namespace DLV2{

namespace grounder{

///An unordered set of generic atoms by hashAtom @see hashAtom
typedef vector<GenericAtom*> AtomTable;


/* @brief This struct contains the bind variables of an atom.
 *
 * @details During grounding process the variables of an atom are classified as bind or bound.
 * Bind variables are the ones that have no assignment yet, while the bound ones have an assignment.
 * This struct is useful in order to compare and hash atoms just by their bind variables.
 */

struct hashAtomResult {
	vector<unsigned int> bind;

	hashAtomResult(){}

	hashAtomResult(vector<unsigned int> &bind){this->bind=bind;}

	///Hash function built over bind variables
	size_t operator()(GenericAtom* atom) const {
		vector<Term*> terms;
		getTermsBind(atom,terms);
		return HashVecInt::getHashVecIntFromConfig()->computeHashTerm(terms);
	}

	///Equality comparison of two generic atoms over their bind variables
	bool operator()(GenericAtom* atom1,  GenericAtom* atom2) const {
		if(atom1->getTermsSize()!=atom2->getTermsSize())return false;
		vector<Term*> terms1;
		getTermsBind(atom1,terms1);
		vector<Term*> terms2;
		getTermsBind(atom2,terms2);
		for(unsigned i=0;i<atom1->getTermsSize();i++)
			if(atom1->getTerm(i)->getIndex()!=atom2->getTerm(i)->getIndex())
				return false;
		return true;
	}

	///This method filters the bind variables of a generic atoms and puts them in the vector given as parameters
	void getTermsBind( GenericAtom* atom, vector<Term*>& terms) const{
		for(auto t:bind)
			terms.push_back(atom->getTerm(t));
	}
};



///An unordered map of generic atoms defined by hashResultAtom @see hashResultAtom
/// A map contain the ground atom that match anda vector contains the corrispective variable bind and the value
typedef unordered_map<GenericAtom*,map_term_term, hashAtomResult, hashAtomResult> AtomResultTable;

///This struct implements an AtomResultTable (@see AtomResultTable) that represents a set of possible assignments for bind variables
struct ResultMatch {
	AtomResultTable result;
	ResultMatch(vector<unsigned int> &bind): result(AtomResultTable(0,hashAtomResult(bind),hashAtomResult(bind))){};
	/// Insert the current atom in the table if match with the template
	/// If insert the atom return true else false
	bool insert(GenericAtom* atom,Atom* templateAtom,map_term_term& currentAssignment){
		// Check if the match atom with template, if match put in result table
		map_term_term variableBindFinded;
		if (match(atom,templateAtom,currentAssignment,variableBindFinded)){
			result.insert({atom,variableBindFinded});
			return true;

		}
		return false;
	}

	/// Pop last atom in the table and put the assignment in the current assignment
	/// If the table is empty return false, else true
	bool pop(map_term_term& currentAssignment){
		if(result.size()==0)return false;
		auto it_last_atom=result.begin();
		for(auto resultValue:it_last_atom->second)currentAssignment.insert(resultValue);
		result.erase(it_last_atom);
		return true;
	}

	/// Return true if the genericAtom match with the template atom and insert in assignment the value of variable
	/// Two atom match if a constant term are equal.
	/// @param varAssignment map of assignment of the variable. If templateAtom have variable term put in
	/// varAssignment the ID of variable with the relative constant term of the genericAtom
	/// nextAssignment contains the new value of variable derived
	bool match(GenericAtom *genericAtom,Atom *templateAtom,map_term_term& currentAssignment,map_term_term& nextAssignment);
};

/**
 * This class is an abstract base class that models a general indexing strategy of a predicate's instances.
 * It is builded according to the Strategy GOF pattern.
 */
class AtomSearcher {
public:
	//Constructor for all the fields
	AtomSearcher(AtomTable* table) : table(table) {};
	///This method implementation is demanded to sub-classes.
	///It have to find all the matching atoms and return just the first of those.
	///The returned integer will be used to get the other ones through nextMatch method @see nextMatch
	virtual unsigned int firstMatch(Atom *templateAtom, map_term_term& currentAssignment, bool& find)=0;
	///This method implementation is demanded to sub-classes.
	///It is used to get the further matching atoms one by one each time it is invoked.
	virtual void nextMatch(unsigned int id, map_term_term& currentAssignment, bool& find)=0;
	///This method implementation is demanded to sub-classes.
	/// It have to find if exist the templateAtom, that have to be ground
	virtual void findIfExist(Atom *templateAtom, bool& find, bool& isUndef)=0;
	///This method implementation is demanded to sub-classes.
	///It is used to update the delta table for recursive predicates.
	virtual void swap(unsigned tableFrom,unsigned tableTo )=0;
	///Destructor
	virtual ~AtomSearcher() {};
protected:
	AtomTable* table;

};

/**
 * @brief This class is a basic and simple implementation of IndexAtom (@see IndexAtom)
 * @details Searching for match is performed over the whole tables of facts and non facts with a linear scan.
 */
class SimpleAtomSearcher: public AtomSearcher {
public:
	///Constructor
	SimpleAtomSearcher(AtomTable* facts, AtomTable* nofacts, AtomTable* delta, Predicate *p) : AtomSearcher(facts,nofacts,delta,p), counter(0), templateAtom(0), currentAssignment(0){};
	///Virtual method implementation
	virtual unsigned int firstMatch(bool searchInDelta, Atom *templateAtom, map_term_term& currentAssignment, bool& find);
	///Virtual method implementation
	virtual void nextMatch(unsigned int id,map_term_term& currentAssignment, bool& find);
	///Virtual method implementation
	virtual void findIfExist(bool searchInDelta,Atom *templateAtom, bool& find,bool& isUndef);
	///Virtual method implementation
	virtual void updateDelta(AtomTable* nextDelta){};
	///Destructor
	virtual ~SimpleAtomSearcher() {for(auto it:matches_id) delete it.second;};
protected:
	///The unordered map used to store the integer identifiers returned by the firstMach method
	unordered_map<unsigned int, ResultMatch*> matches_id;
	///The counter used to assign the integer identifiers returned by the firstMach method
	unsigned int counter;
	///Current templateAtom passed in firstMatch
	Atom *templateAtom;
	///Current assignment passed in firstMatch
	map_term_term* currentAssignment;

	///This method given an AtomTable computes the matching facts and nofacts and returns the first one of those
	void computeFirstMatch(AtomTable* collection,ResultMatch* rm);
	///This method invokes findIfAFactExists method if all the variables are bound, otherwise invokes the computeFirstMatch method
	bool searchForFirstMatch(AtomTable* table,ResultMatch* rm);
	///This method builds a ground atom using the bound variables , checks if it is true and return if is undefined or a fact
	virtual bool findIfExists(AtomTable* collection,bool& isUndef);
	virtual bool findIfExists(AtomTable* collection);
};

/**
 * @brief This class is a more advanced implementation of IndexAtom (@see IndexAtom)
 * @details Searching for match is performed over a tables of facts and no facts indexed by a single term, namely the indexing term.
 * Instead of performing the search among the whole tables it is performed among the facts and the no facts, collectively the instances,
 * that match for that term.
 * Here is used as data structure an unordered map whose keys represent the possible values of the indexing term,
 * that are mapped to unordered sets of instances in which that term appears with that value.
 * This implementation is sibling to the one with multimaps @see SingleTermIndexMultiMap,
 * since the two are implemented to be independent.
 */

class SingleTermAtomSearcher: public SimpleAtomSearcher {
public:
	/**
	 * Constructor
	 * @param facts An AtomTable of facts
	 * @param nofacts An AtomTable of no facts
	 * @param delta An AtomTable of no facts containing the result of the previous grounding iteration
	 * @param predicate The predicate corresponding to the facts and the no facts.
	 */
	SingleTermAtomSearcher(AtomTable* facts, AtomTable* nofacts,AtomTable* delta,Predicate *p) : SimpleAtomSearcher(facts,nofacts,delta,p), instantiateIndexMaps(false), positionOfIndexing(0), positionOfIndexingSetByUser(false){};
	///Overload of firstMatch method
	virtual unsigned int firstMatch(bool searchInDelta, Atom *templateAtom, map_term_term& currentAssignment, bool& find);
	///Virtual method implementation
	virtual void updateDelta(AtomTable* nextDelta);
	///Destructor
	~SingleTermAtomSearcher(){};

private:
	///Data structure for indexed facts
	unordered_map<index_object,AtomTable> factsIndexMap;
	///Data structure for indexed no facts
	unordered_map<index_object,AtomTable> nofactsIndexMap;
	///Data structure for indexed delta
	unordered_map<index_object,AtomTable> deltaIndexMap;
	///Determine whether the indexing has been filled in
	bool instantiateIndexMaps;
	///The position of the indexing term
	unsigned int positionOfIndexing;
	///Determine whether the indexing term has been established from command line arguments by the user
	bool positionOfIndexingSetByUser;

	///This method fills in the indexing data structures
	void initializeIndexMaps();

	// Set the matchingTable with the index_table if there is index else table
	bool getMatchingTable(AtomTable*& matchingTable,unordered_map<index_object,AtomTable>& index_table,AtomTable*& table, pair<bool, index_object>& termBoundIndex);

	/// This method carry out the indexing strategy, determining the indexing term with which is the actual term
	/// corresponding to position given by the user or if no position is given it is used the first admissible term as indexing term.
	/// Then filling the data structures invoking the initializeIndexMaps method.
	pair<bool, index_object> createIndex(vector<unsigned int>& bind);
};

/**
 * @brief This class is a more advanced implementation of IndexAtom (@see IndexAtom)
 * @details Searching for match is performed over a tables of facts and no facts indexed by a single term, namely the indexing term.
 * Instead of performing the search among the whole tables it is performed among the facts and the no facts, collectively the instances,
 * that match for that term.
 * Here is used as data structure an unordered multimap of pairs composed by a possible value of the indexing term
 * and an instance in which that term appears with that value.
 * This implementation is sibling to the one with maps @see SingleTermIndexAtom,
 * since the two are implemented to be independent.
 */
class SingleTermAtomSearcherMultiMap: public SimpleAtomSearcher {
public:
	/**
	 * Constructor
	 * @param facts An AtomTable of facts
	 * @param no facts An AtomTable of no facts
	 * @param delta An AtomTable of no facts containing the result of the previous grounding iteration
	 * @param predicate The predicate corresponding to the facts and the no facts.
	 */
	SingleTermAtomSearcherMultiMap(AtomTable* facts, AtomTable* nofacts,AtomTable* delta,Predicate *p) : SimpleAtomSearcher(facts,nofacts,delta,p), instantiateIndexMaps(false), positionOfIndexing(0),positionOfIndexingSetByUser(false){};
	///Overload of firstMatch method
	virtual unsigned int firstMatch(bool searchInDelta, Atom *templateAtom, map_term_term& currentAssignment, bool& find);
	//Virtual method implementation
	virtual void updateDelta(AtomTable* nextDelta);
	///Destructor
	~SingleTermAtomSearcherMultiMap(){};

private:
	///Data structure for indexed facts
	unordered_multimap<index_object,GenericAtom*> factsIndexMap;
	///Data structure for indexed no facts
	unordered_multimap<index_object,GenericAtom*> nofactsIndexMap;
	///Data structure for indexed delta
	unordered_multimap<index_object,GenericAtom*> deltaIndexMap;
	///Determine whether the indexing has been filled in
	bool instantiateIndexMaps;
	///The position of the indexing term
	unsigned int positionOfIndexing;
	///Determine whether the indexing term has been established from command line arguments by the user
	bool positionOfIndexingSetByUser;

	///This method fills in the indexing data structures
	void initializeIndexMaps();

	// Set the matchingTable with the index_table if there is index else table
	bool getMatchingTable(AtomTable*& matchingTable,unordered_multimap<index_object,GenericAtom*>& index_table,AtomTable*& table, pair<bool, index_object>& termBoundIndex);

	bool searchForFirstMatch(AtomTable* table, ResultMatch* rm);

	/// This method carry out the indexing strategy, determining the indexing term with which is the actual term
	/// corresponding to position given by the user or if no position is given it is used the first admissible term as indexing term.
	/// Then filling the data structures invoking the initializeIndexMaps method.
	pair<bool, index_object> createIndex(vector<unsigned int>& bind);
};

};

};

#endif /* INDEXATOM_H_ */

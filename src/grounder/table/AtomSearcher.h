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

/** This struct compares and hashes atoms just by their terms.
 *	It is used for the AtomTable definition (@See AtomTable)
 *	In this way, given two atom (every kind of atom) they can be compared in the same way.
 **/
struct AtomTableComparator{
	inline size_t operator()(Atom* atom) const{
		return HashVecInt::getHashVecInt()->computeHashTerm(atom->getTerms());
	}

	inline bool operator()(Atom* atom1, Atom* atom2) const{
		if(atom1->getTerms().size()!=atom2->getTermsSize())
			return false;
		for(unsigned i=0;i<atom1->getTermsSize();i++)
			if(atom1->getTerm(i)->getIndex()!=atom2->getTerm(i)->getIndex())
				return false;
		return true;
	}
};

///Vector of Atom (GenericAtom)
typedef vector<Atom*> AtomVector;
///An unordered set of Atom (GenericAtom)
typedef unordered_set<Atom*,AtomTableComparator,AtomTableComparator> AtomTable;
///An unordered multimap of Atom (GenericAtom)
typedef unordered_multimap<index_object, Atom*> Multimap_Atom;


/** This class implements a general way to access to different atom containers.
 * 	It is implemented according to the GOF pattern Iterator.
**/
class GeneralIterator {
public:
	virtual void next()=0;
	virtual bool isDone()=0;
	virtual Atom* currentIterm()=0;
	virtual ~GeneralIterator(){};
};
///This class implements and hides an iterator for atom vector
class VectorIterator : public GeneralIterator {
public:
	VectorIterator(const AtomVector::iterator& s, const AtomVector::iterator& e): start(s), end(e){};
	virtual void next(){ if(start!=end) start++;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentIterm(){return *(start);}
private:
	AtomVector::iterator start;
	AtomVector::iterator end;
};
///This class implements and hides an iterator for atom unordered set
class UnorderedSetIterator : public GeneralIterator {
public:
	UnorderedSetIterator(const AtomTable::iterator& s, const AtomTable::iterator& e): start(s), end(e){};
	virtual void next(){ if(start!=end) start++;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentIterm(){return *(start);}
private:
	AtomTable::iterator start;
	AtomTable::iterator end;
};
///This class implements and hides an iterator for atom unordered multimap
class UnorderedMultiMapIterator : public GeneralIterator {
public:
	UnorderedMultiMapIterator(const Multimap_Atom::iterator& s, const Multimap_Atom::iterator& e): start(s), end(e){};
	virtual void next(){ if(start!=end) start++;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentIterm(){return start->second;}
private:
	Multimap_Atom::iterator start;
	Multimap_Atom::iterator end;
};


/**
 * This class is an abstract base class that models a general searching strategy for a predicate's extension.
 * It is builded according to the Strategy GOF pattern.
 */
class AtomSearcher {
public:
	AtomSearcher(AtomVector* table) : table(table) {};
	/// This method implementation is demanded to sub-classes.
	/// It have to find all the matching atoms and return just the first of those.
	/// The returned integer will be used to get the other ones through nextMatch method (@See nextMatch)
	virtual unsigned int firstMatch(Atom *templateAtom, map_term_term& currentAssignment, bool& find,bool& undef)=0;
	/// This method implementation is demanded to sub-classes.
	/// It is used to get the further matching atoms one by one each time it is invoked.
	virtual void nextMatch(unsigned int id, Atom* templateAtom, map_term_term& currentAssignment, bool& find, bool &undef)=0;
	/// This method implementation is demanded to sub-classes.
	/// It have to find if the given atom exist. This atom must be ground.
	virtual void findIfExist(Atom *templateAtom, bool& find, bool& isUndef)=0;

	/// This method implementation is demanded to sub-classes.
	/// It have to find if the given atom exist and returns it, else returns nullptr.
	virtual Atom* findAtom(Atom *atom)=0;
	/// This method implementation is demanded to sub-classes.
	/// It updates the searching data-structure(s) by adding the given atom
	virtual void add(Atom* atom) = 0;
	///This method implementation is demanded to sub-classes.
	///It updates the searching data-structure(s) by removing the given atom
	virtual void remove(Atom* atom) = 0;
	///This method implementation is demanded to sub-classes.
	///It clears the searching data-structure(s).
	virtual void clear() = 0;

	///Printer method. Useful mainly for debug purpose.
	virtual void print(){};

	/// This method checks if the two given atoms match according to the current assignment.
	/// If they match the current assignment is update accordingly.
	bool checkMatch(Atom *genericAtom, Atom *templateAtom, map_term_term& currentAssignment);
	/// Match a function with given id of term, compare the constant term and put in binds
	/// a value of the variable term present in termToMatch
	/// Return true if constant term are equal, else false
	bool matchTerm(Term *genericTerm, Term *termToMatch, map_term_term& varAssignment);

	virtual ~AtomSearcher() {};

protected:
	///The basic data-structure that collects the atoms
	AtomVector* table;
};

/**
 * @brief This class is a basic implementation of AtomSearcher (@see AtomSearcher)
 * @details Searching for match is performed over the base data-structure with a linear scan, since it is a vector.
 */
class BaseAtomSearcher: public AtomSearcher {
public:
	BaseAtomSearcher(AtomVector* table) : AtomSearcher(table), counter(0) {};

	virtual unsigned int firstMatch(Atom* templateAtom, map_term_term& currentAssignment, bool& find,bool &undef);
	virtual void nextMatch(unsigned int id, Atom* templateAtom, map_term_term& currentAssignment, bool& find,bool &undef);
	virtual void findIfExist(Atom *templateAtom, bool& find, bool& isUndef);

	virtual Atom* findAtom(Atom *atom);
	virtual void add(Atom* atom){};
	virtual void remove(Atom* atom){};
	virtual void clear(){};

	virtual void print(){for(auto atom:*table)atom->print();}

	virtual ~BaseAtomSearcher() {for(auto pair:resultMap) delete pair.second;};

protected:
	/// This maps stores the calls to the firstMatch method.
	/// Indeed, for each call it stores a pair with the counter and the iterator to the next matching atoms.
	unordered_map<unsigned int, GeneralIterator*> resultMap;
	/// This is a counter used to identify the different calls to the firstMatch method.
	unsigned int counter;

	/// This method invokes findIfAFactExists method if all the variables are bound,
	/// otherwise invokes the computeFirstMatch method.
	bool searchForFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment, bool& isUndef);
	/// This method given an iterator increases it in order to find matching atoms with the given atom
	/// according to the current assignment.
	bool computeMatch(GeneralIterator* currentMatch, Atom *templateAtom, map_term_term& currentAssignment);
	/// This method computes an iterator pointing to the starting point of the search
	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom){return new VectorIterator(table->begin(),table->end());}
};

/**
 * @brief This class is a more advanced implementation of BaseAtomSearcher (@see BaseAtomSearcher )
 * @details Searching for match is performed over unordered maps indexed by a single term, namely an indexing term.
 * Instead of performing the search among the whole base vector, it is performed among the atoms,
 * that match for that term.
 * Here is used as searching data structure an unordered map whose keys represent the possible values of the indexing term,
 * that are mapped to unordered sets of atoms in which that term appears with that value.
 * Moreover is it possibly created one of this data-structure for each possible indexing term, so up the predicate arity,
 * accordingly to the searching needs during grounding.
 * This implementation is sibling to the one with multimaps @see SingleTermMultipleStrategiesAtomSearcherMultiMap,
 * since the two are implemented to be independent.
 */
class SingleTermMultipleStrategiesAtomSearcher: public BaseAtomSearcher {
public:
	SingleTermMultipleStrategiesAtomSearcher(AtomVector* table, Predicate* p) : BaseAtomSearcher(table), predicate(p) {
		searchingTables.reserve(predicate->getArity());
		createdSearchingTables.reserve(predicate->getArity());
		for(unsigned int i=0;i<predicate->getArity();i++){
			searchingTables.push_back(unordered_map<index_object,AtomTable>());
			createdSearchingTables.push_back(false);
		}
		indexingTermSetByUser = Options::globalOptions()->getPredicateIndexTerm(this->predicate->getName());
		if(indexingTermSetByUser>-1)
			assert_msg((indexingTermSetByUser>=0 && unsigned(indexingTermSetByUser)<this->predicate->getArity()), "The specified index is not valid.");
#ifdef NDEBUG
		cout<<"Predicate: "<<predicate->getName()<<"  Index Term Set By User: "<<indexingTermSetByUser<<endl;
#endif
	};

	virtual Atom* findAtom(Atom *atom);
	virtual void add(Atom* atom);
	virtual void remove(Atom* atom);
	virtual void clear(){for(auto table:searchingTables) table.clear();};

	///This method chooses the best indexing term among the one allowed.
	unsigned int selectBestIndex(const unordered_set<int>& possibleTableToSearch);

private:
	/// The predicate
	Predicate* predicate;
	///The indexing term set by user. It is -1 if not set.
	int indexingTermSetByUser;
	///A vector of chosen searching data structure for this kind of indexing strategies, one for each possible indexing term.
	vector<unordered_map<index_object,AtomTable>> searchingTables;
	/// A vector of boolean used in order to determine if the data-structure for a particular indexing terms has been created.
	vector<bool> createdSearchingTables;

	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom);

	///This method fills in the searching data structure for the given indexing term
	void initializeIndexMaps(unsigned int indexingTerm);

	/// This method determines the possible indexing terms for the given atoms.
	/// Then invokes the selectBestIndex method to determine the best one among them.
	/// If the data-structure for the best indexing term is not created, then it fills in
	/// the data structures by means of initializeIndexMaps method.
	int manageIndex(Atom* templateAtom);
};

/**
 * @brief This class is a more advanced implementation of BaseAtomSearcher (@see BaseAtomSearcher )
 * @details Searching for match is performed over unordered maps indexed by a single term, namely an indexing term.
 * Instead of performing the search among the whole base vector, it is performed among the atoms,
 * that match for that term.
 * Here is used as searching data structure an unordered multimap whose keys represent the possible values of the indexing term,
 * that are mapped to atoms in which that term appears with that value.
 * Moreover is it possibly created one of this data-structure for each possible indexing term, so up the predicate arity,
 * accordingly to the searching needs during grounding.
 * This implementation is sibling to the one with maps @see SingleTermMultipleStrategiesAtomSearcher,
 * since the two are implemented to be independent.
 */
class SingleTermMultipleStrategiesAtomSearcherMultiMap: public BaseAtomSearcher {
public:
	SingleTermMultipleStrategiesAtomSearcherMultiMap(AtomVector* table, Predicate *p) : BaseAtomSearcher(table), predicate(p) {
		searchingTables.reserve(predicate->getArity());
		createdSearchingTables.reserve(predicate->getArity());
		for(unsigned int i=0;i<predicate->getArity();i++){
			searchingTables.push_back(Multimap_Atom());
			createdSearchingTables.push_back(false);
		}
		indexingTermSetByUser = Options::globalOptions()->getPredicateIndexTerm(this->predicate->getName());
		if(indexingTermSetByUser>-1)
			assert_msg((indexingTermSetByUser>=0 && unsigned(indexingTermSetByUser)<this->predicate->getArity()), "The specified index is not valid.");
#ifdef NDEBUG
		cout<<"Predicate: "<<predicate->getName()<<"  Index Term Set By User: "<<indexingTermSetByUser<<endl;
#endif
	};

	virtual Atom* findAtom(Atom *atom);
	virtual void add(Atom* atom);
	virtual void remove(Atom* atom);
	virtual void clear(){for(auto table:searchingTables) searchingTables.clear();};

	///This method chooses the best indexing term among the one allowed.
	unsigned int selectBestIndex(const unordered_set<int>& possibleTableToSearch);

private:
	/// The predicate
	Predicate* predicate;
	/// The indexing term set by user. It is -1 if not set.
	int indexingTermSetByUser;
	/// A vector of chosen searching data structure for this kind of indexing strategies, one for each possible indexing term.
	vector<Multimap_Atom> searchingTables;
	/// A vector of boolean used in order to determine if the data-structure for a particular indexing terms has been created.
	vector<bool> createdSearchingTables;

 	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom);

 	///This method fills in the indexing data structures
	void initializeIndexMaps(unsigned int indexTable);

	/// This method determines the possible indexing terms for the given atoms.
	/// Then invokes the selectBestIndex method to determine the best one among them.
	/// If the data-structure for the best indexing term is not created, then it fills in
	/// the data structures by means of initializeIndexMaps method.
	int manageIndex(Atom* templateAtom);

};

};

};

#endif /* INDEXATOM_H_ */

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

/* @brief This struct contains the bind variables of an atom.
 *
 * @details During grounding process the variables of an atom are classified as bind or bound.
 * Bind variables are the ones that have no assignment yet, while the bound ones have an assignment.
 * This struct is useful in order to compare and hash atoms just by their bind variables.
 */
struct AtomTableComparator{

	inline size_t operator()(Atom* atom) const{
		return HashVecInt::getHashVecIntFromConfig()->computeHashTerm(atom->getTerms());
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

///An unordered set of generic atoms by hashAtom @see hashAtom
typedef vector<Atom*> AtomVector;
///An unordered set of generic atoms by hashAtom @see hashAtom
typedef unordered_set<Atom*,AtomTableComparator,AtomTableComparator> AtomTable;
typedef unordered_multimap<index_object, Atom*> Multimap_Atom;

class GeneralIterator {
public:
	virtual void next()=0;
	virtual bool isDone()=0;
	virtual Atom* currentIterm()=0;
	virtual ~GeneralIterator(){};
};

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
 * This class is an abstract base class that models a general indexing strategy of a predicate's instances.
 * It is builded according to the Strategy GOF pattern.
 */
class AtomSearcher {
public:
	AtomSearcher(AtomVector* table) : table(table) {};
	///This method implementation is demanded to sub-classes.
	///It have to find all the matching atoms and return just the first of those.
	///The returned integer will be used to get the other ones through nextMatch method @see nextMatch
	virtual unsigned int firstMatch(Atom *templateAtom, map_term_term& currentAssignment, bool& find)=0;
	///This method implementation is demanded to sub-classes.
	///It is used to get the further matching atoms one by one each time it is invoked.
	virtual void nextMatch(unsigned int id, Atom* templateAtom, map_term_term& currentAssignment, bool& find)=0;
	///This method implementation is demanded to sub-classes.
	/// It have to find if exist the templateAtom, that have to be ground
	virtual void findIfExist(Atom *templateAtom, bool& find, bool& isUndef)=0;

	///This method implementation is demanded to sub-classes.
	///It updates the searching data-structure adding the given atom
	virtual void add(Atom* atom);
	///This method implementation is demanded to sub-classes.
	///It updates the searching data-structure removing the given atom
	virtual void remove(Atom* atom);
	///This method implementation is demanded to sub-classes.
	///It updates the searching data-structure removing the given atom
	virtual void clear();

	///This method checks if the atom given matches with the templateAtom according to the current assignment
	///If they match the current assignment is update accordingly
	virtual bool checkMatch(Atom *genericAtom,Atom *templateAtom,map_term_term& currentAssignment);

	///This method implementation is demanded to sub-classes.
	/// Return the atom if exist in the table, else nullptr
	virtual Atom* getAtom(Atom *atom)=0;

	virtual ~AtomSearcher() {};
protected:
	AtomVector* table;

};

/**
 * @brief This class is a basic and simple implementation of IndexAtom (@see IndexAtom)
 * @details Searching for match is performed over the whole tables of facts and non facts with a linear scan.
 */
class SimpleAtomSearcher: public AtomSearcher {
public:
	SimpleAtomSearcher(AtomVector* table) : AtomSearcher(table), counter(0) {};

	virtual unsigned int firstMatch(Atom* templateAtom, map_term_term& currentAssignment, bool& find);
	virtual void nextMatch(unsigned int id, Atom* templateAtom, map_term_term& currentAssignment, bool& find);
	virtual void findIfExist(Atom *templateAtom, bool& find, bool& isUndef);

	virtual void add(Atom* atom){};
	virtual void remove(Atom* atom){};
	virtual void clear(){};

	virtual Atom* getAtom(Atom *atom);

protected:
	///A map in which for each call to first match the current search iterator
	unordered_map<unsigned int, GeneralIterator*> resultMap;
	///The counter used to assign the integer identifiers returned by the firstMach method
	unsigned int counter;

	///This method given an AtomTable computes the matching facts and nofacts and returns the first one of those
	void computeFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom,map_term_term& currentAssignment);
	///This method invokes findIfAFactExists method if all the variables are bound, otherwise invokes the computeFirstMatch method
	bool searchForFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom,map_term_term& currentAssignment);

	GeneralIterator* computeGenericIterator(Atom* templateAtom);
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
	SingleTermAtomSearcher(AtomVector* table, Predicate* p) : SimpleAtomSearcher(table), predicate(p), createdIndex(false) {};

	virtual unsigned int firstMatch(Atom* templateAtom, map_term_term& currentAssignment, bool& find);
	virtual void nextMatch(unsigned int id, Atom* templateAtom, map_term_term& currentAssignment, bool& find);
	virtual void findIfExist(Atom *templateAtom, bool& find,bool& isUndef);

	virtual void add(Atom* atom);
	virtual void remove(Atom* atom);
	virtual void clear(){tableIndexMap.clear();};

	virtual Atom* getAtom(Atom *atom);

private:
	///Data structure for indexed facts
	unordered_map<index_object,AtomTable> tableIndexMap;

	Predicate* predicate;
	pair<unsigned int, bool> indexPair;
	bool createdIndex;

	///This method fills in the indexing data structures
	void initializeIndexMaps();

	/// This method carry out the indexing strategy, determining the indexing term with which is the actual term
	/// corresponding to position given by the user or if no position is given it is used the first admissible term as indexing term.
	/// Then filling the data structures invoking the initializeIndexMaps method.
	void createIndex(Atom* templateAtom,pair<bool, index_object>& termBoundIndex);

	GeneralIterator* computeGenericIterator(Atom* templateAtom);
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
	SingleTermAtomSearcherMultiMap(AtomVector* table, Predicate *p) : SimpleAtomSearcher(table), predicate(p), createdIndex(false) {};

	virtual unsigned int firstMatch(Atom* templateAtom, map_term_term& currentAssignment, bool& find);
	virtual void nextMatch(unsigned int id, Atom* templateAtom, map_term_term& currentAssignment, bool& find);
	virtual void findIfExist(Atom *templateAtom, bool& find,bool& isUndef);

	virtual void add(Atom* atom);
	virtual void remove(Atom* atom);
	virtual void clear(){tableIndexMap.clear();};

	virtual Atom* getAtom(Atom *atom);

private:
	///Data structure for indexed facts
	unordered_multimap<index_object, Atom*> tableIndexMap;

	Predicate* predicate;
	pair<unsigned int, bool> indexPair;
	bool createdIndex;

	///This method fills in the indexing data structures
	void initializeIndexMaps();

	/// This method carry out the indexing strategy, determining the indexing term with which is the actual term
	/// corresponding to position given by the user or if no position is given it is used the first admissible term as indexing term.
	/// Then filling the data structures invoking the initializeIndexMaps method.
	void createIndex(Atom* templateAtom,pair<bool, index_object>& termBoundIndex);
	GeneralIterator* computeGenericIterator(Atom* templateAtom);
};

};

};

#endif /* INDEXATOM_H_ */
/*
 * IndexingStructure.h
 *
 *  Created on: Jan 15, 2016
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_TABLE_INDEXINGSTRUCTURE_H_
#define SRC_GROUNDER_TABLE_INDEXINGSTRUCTURE_H_

#include <vector>
#include "../atom/Atom.h"
#include "../../util/Constants.h"
#include "../statement/Rule.h"
using namespace std;

namespace DLV2 {
namespace grounder {

/** This class implements a general way to access to different atom containers.
 * 	It is implemented according to the GOF pattern Iterator.
 **/
class GeneralIterator {
public:
	virtual void add(GeneralIterator* g){};
	virtual void next()=0;
	virtual bool isDone()=0;
	virtual Atom* currentItem()=0;
	virtual ~GeneralIterator(){};
};
///This class implements and hides an iterator for atom vector with iterator
class VectorIterator : public GeneralIterator {
public:
	VectorIterator(const AtomHistoryVector::const_iterator& s, const AtomHistoryVector::const_iterator& e): start(s), end(e){};
	virtual void next(){ if(start!=end) ++start;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentItem(){return *(start);}
private:
	AtomHistoryVector::const_iterator start;
	AtomHistoryVector::const_iterator end;
};
///This class implements and hides an iterator for atom vector with indexing
class VectorIteratorIndex : public GeneralIterator {
public:
	VectorIteratorIndex(unsigned s,unsigned e,AtomHistoryVector* table): start(s), end(e),table(table){};
	virtual void next(){ if(start!=end) ++start;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentItem(){return (*table)[start];}
private:
	unsigned start;
	unsigned end;
	AtomHistoryVector* table;
};
///This class implements and hides an iterator for atom unordered set
class UnorderedSetIterator : public GeneralIterator {
public:
	UnorderedSetIterator(const AtomTable::const_iterator& s, const AtomTable::const_iterator& e): start(s), end(e){};
	virtual void next(){ if(start!=end) ++start;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentItem(){return *(start);}
private:
	AtomTable::const_iterator start;
	AtomTable::const_iterator end;
};
///This class implements and hides an iterator for atom unordered multimap
class UnorderedMultiMapIterator : public GeneralIterator {
public:
	UnorderedMultiMapIterator(const Multimap_Atom::const_iterator& s, const Multimap_Atom::const_iterator& e): start(s), end(e){};
	virtual void next(){ if(start!=end) ++start;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentItem(){return start->second;}
private:
	Multimap_Atom::const_iterator start;
	Multimap_Atom::const_iterator end;
};
///This class implements and hides an iterator for atom vector
class MultipleIterators : public GeneralIterator{
public:
	MultipleIterators():currentIterator(0){};
	virtual void add(GeneralIterator* g){iterators.push_back(g);}
	__attribute__ ((always_inline)) virtual void next(){
		iterators[currentIterator]->next();
		if(iterators[currentIterator]->isDone())
			currentIterator++;
	}
	virtual bool isDone(){return currentIterator>=iterators.size();}
	virtual Atom* currentItem(){return iterators[currentIterator]->currentItem();}
	virtual ~MultipleIterators(){for(auto it:iterators) delete it;};
private:
	vector<GeneralIterator*> iterators;
	unsigned currentIterator;
};

/**
 * This class represents a generic indexing data structure of atoms (@see Atom.h)
 **/
class IndexingStructure {
public:
	IndexingStructure(AtomHistoryVector* table):table(table),lastUpdate(0){};
	IndexingStructure(AtomHistoryVector* table, vector<unsigned>& indexingTerms):table(table),lastUpdate(0),indexingTerms(move(indexingTerms)){};

	///Add an atom the the indexing data structure
	virtual void add(Atom* atom){};
	///Search a (ground) atom in the indexing data structure
	virtual Atom* find(Atom* atom);
	///Erase the content of the indexing data structure
	virtual void clear(){lastUpdate=0;};
	///Update the indexing data structure by adding the atoms in the table starting from lastUpdate
	virtual void update(){};
	///Given a partially ground atom compute the matching atoms according to the variables assignment in these atom
	inline virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification){return new VectorIterator(table->begin(),table->end());};
	///Univocal label for each class implementing IndexingStructure
	virtual unsigned getType(){return DEFAULT;};

	///Get the indexing terms
	const vector<unsigned>& getIndexingTerms() const {return indexingTerms;}
	///Set the indexing terms
	void setIndexingTerms(const vector<unsigned>& indexingTerm) {this->indexingTerms = indexingTerm;}
	///Add an indexing term
	void addIndexingTerm(unsigned indexingTerm) {this->indexingTerms.push_back(indexingTerm);}

	virtual ~IndexingStructure(){}

protected:
	///Vector of atoms for which the indexing data structure is created
	AtomHistoryVector* table;
	///The position of the last atom in table to which the indexing data structure has been updated
	unsigned lastUpdate;
	///The vector of indexing terms
	vector<unsigned> indexingTerms;
};

/**
 * This class implements IndexingStructure and is used for the recursive predicate. The compute match search in the history vector
 * the elements based on the type of search and the current iteration
 **/

class IndexingStructureRecursive : public IndexingStructure{
public:
	IndexingStructureRecursive(AtomHistoryVector* table):IndexingStructure(table){};

	inline virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification){
		if(searchSpecification.first==ALL)
			return new VectorIteratorIndex(0,table->size(),table);
		auto it=table->getElements(searchSpecification.first,searchSpecification.second);
		return new VectorIteratorIndex(it.first,it.second,table);
	};
};

/**
 * This class implements IndexingStructure and provides an unordered set of atoms as indexing data structure (@see Atom.h)
 **/
class UnorderedSet : public IndexingStructure {
public:
	UnorderedSet(AtomHistoryVector* table):IndexingStructure(table){};
	void add(Atom* atom){indexingStructure.insert(atom);};
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual unsigned getType(){return HASHSET;};
private:
	AtomTable indexingStructure;
};

/**
 * This class implements IndexingStructure and provides a single term indexing data structure
 * implemented by means of an unordered map of unordered sets of atoms as indexing data structure (@see Atom.h)
 **/
class UnorderedMapOfUnorderedSet : public IndexingStructure {
public:
	UnorderedMapOfUnorderedSet(AtomHistoryVector* table, vector<unsigned>& indexingTerm): IndexingStructure(table,indexingTerm){};
	void add(Atom* atom);
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification);
	virtual unsigned getType(){return MAP;}
private:
	unordered_map<index_object,AtomTable> indexingStructure;
};

/**
 * This class implements IndexingStructure and provides a single term indexing data structure
 * implemented by means of an unordered map of vectors of atoms as indexing data structure (@see Atom.h)
 **/
class UnorderedMapOfVector : public IndexingStructure {
public:
	UnorderedMapOfVector(AtomHistoryVector* table, vector<unsigned>& indexingTerm): IndexingStructure(table,indexingTerm){};
	void add(Atom* atom);
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification);
	virtual unsigned getType(){return MAP_VECTOR;}
private:
	unordered_map<index_object,vector<Atom*>> indexingStructure;
};

/**
 * This class implements IndexingStructure and provides a single term indexing data structure
 * implemented by means of an unordered map of history vectors of atoms as indexing data structure (@see Atom.h)
 **/
class UnorderedMapOfHistoryVector : public IndexingStructure {
public:
	UnorderedMapOfHistoryVector(AtomHistoryVector* table, vector<unsigned>& indexingTerm): IndexingStructure(table,indexingTerm){};
	void add(Atom* atom);
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification);
	virtual unsigned getType(){return MAP_HISTORY_VECTOR;}
private:
	unordered_map<index_object,AtomHistoryVector> indexingStructure;
};

/**
 * This class implements IndexingStructure and provides a single term indexing data structure
 * implemented by means of an unordered multimap of atoms as indexing data structure (@see Atom.h)
 **/
class UnorderedMultiMap : public IndexingStructure {
public:
	UnorderedMultiMap(AtomHistoryVector* table, vector<unsigned>& indexingTerm): IndexingStructure(table,indexingTerm){};
	void add(Atom* atom);
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification);
	virtual unsigned getType(){return MULTIMAP;}
private:
	unordered_multimap<index_object,Atom*> indexingStructure;
};

/**
 * This class implements IndexingStructure and provides a double term indexing data structure
 * implemented by means of an unordered map of unordered multimap of atoms as indexing data structure (@see Atom.h)
 **/
class UnorderedMapOfUnorderedMultimap : public IndexingStructure {
public:
	UnorderedMapOfUnorderedMultimap(AtomHistoryVector* table, vector<unsigned>& indexingTerm): IndexingStructure(table,indexingTerm){};
	void add(Atom* atom);
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification);
	virtual unsigned getType(){return DOUBLEMAP;};
private:
	unordered_map<index_object,unordered_multimap<index_object,Atom*>> indexingStructure;
};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_TABLE_INDEXINGSTRUCTURE_H_ */

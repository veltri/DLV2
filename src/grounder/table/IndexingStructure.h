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
///This class implements and hides an iterator for atom vector
class VectorIterator : public GeneralIterator {
public:
	VectorIterator(const AtomVector::const_iterator& s, const AtomVector::const_iterator& e): start(s), end(e){};
	virtual void next(){ if(start!=end) ++start;}
	virtual bool isDone(){return start==end;}
	virtual Atom* currentItem(){return *(start);}
private:
	AtomVector::const_iterator start;
	AtomVector::const_iterator end;
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


class IndexingStructure {
public:
	IndexingStructure(AtomVector* table):table(table),lastUpdate(0){};

	virtual void add(Atom* atom){};
	virtual Atom* find(Atom* atom);
	virtual void clear(){lastUpdate=0;};
	virtual void update(){};
	virtual GeneralIterator* computeMatchIterator(Atom* templateAtom,const RuleInformation& ruleInformation){return new VectorIterator(table->begin(),table->end());};
	virtual unsigned getType(){return DEFAULT;};

	const vector<unsigned>& getIndexingTerms() const {return indexingTerms;}
	void setIndexingTerms(const vector<unsigned>& indexingTerm) {this->indexingTerms = indexingTerm;}
	void addIndexingTerm(unsigned indexingTerm) {this->indexingTerms.push_back(indexingTerm);}

	virtual ~IndexingStructure(){}

protected:
	AtomVector* table;
	unsigned lastUpdate;
	vector<unsigned> indexingTerms;
};

class UnorderedSet : public IndexingStructure {
public:
	UnorderedSet(AtomVector* table):IndexingStructure(table){};
	void add(Atom* atom){indexingStructure.insert(atom);};
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual unsigned getType(){return HASHSET;};
private:
	AtomTable indexingStructure;
};

class UnorderedMapOfMap : public IndexingStructure {
public:
	UnorderedMapOfMap(AtomVector* table):IndexingStructure(table){};
	void add(Atom* atom);
	Atom* find(Atom* atom);
	void clear(){IndexingStructure::clear(); indexingStructure.clear();};
	virtual void update();
	virtual unsigned getType(){return MAP;}
private:
	unordered_map<index_object,AtomTable> indexingStructure;
};

//class UnorderedMapOfVector : public IndexingStructure {
//public:
//	void add(Atom* atom);
//	Atom* find(Atom* atom);
//	void clear();
//	virtual void update();
//private:
//	unordered_map<index_object,AtomVector> indexingStructure;
//};
//
//class UnorderedMultimap : public IndexingStructure {
//public:
//	void add(Atom* atom);
//	Atom* find(Atom* atom);
//	void clear();
//	virtual void update();
//private:
//	unordered_multimap<index_object,AtomTable> indexingStructure;
//};
//
//class DoubleUnorderedMultimap : public IndexingStructure {
//public:
//	void add(Atom* atom);
//	Atom* find(Atom* atom);
//	void clear();
//private:
//	unordered_multimap<unsigned,unordered_multimap<index_object,AtomTable>> indexingStructure;
//};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_TABLE_INDEXINGSTRUCTURE_H_ */

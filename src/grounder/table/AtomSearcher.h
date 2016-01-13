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

using namespace std;

namespace DLV2{

namespace grounder{


///Vector of Atom (GenericAtom)
using AtomVector = vector<Atom*>;
///An unordered multimap of Atom (GenericAtom)
using Multimap_Atom = unordered_multimap<index_object, Atom*>;


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
	virtual void firstMatch(unsigned id,Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation)=0;
	/// This method implementation is demanded to sub-classes.
	/// It is used to get the further matching atoms one by one each time it is invoked.
	virtual void nextMatch(unsigned id, Atom* templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation)=0;
	/// This method implementation is demanded to sub-classes.
	/// It have to find if the given atom exist and returns it, else returns nullptr.
	virtual Atom* findGroundAtom(Atom *atom)=0;
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
	virtual void print(ostream& stream=cout){};

	/// This method checks if the two given atoms match according to the current assignment.
	/// If they match the current assignment is update accordingly.
	bool checkMatch(Atom *genericAtom, Atom *templateAtom, var_assignment& currentAssignment,const RuleInformation& ruleInformation);
	/// Match a function with given id of term, compare the constant term and put in binds
	/// a value of the variable term present in termToMatch
	/// Return true if constant term are equal, else false
	bool matchTerm(Term *genericTerm, Term *termToMatch, var_assignment& varAssignment,vector<index_object>& addedVariables,const RuleInformation& ruleInformation);

	virtual void setSizeResultVector(unsigned int size)=0;

	virtual ~AtomSearcher() {};

	virtual unsigned getType()=0;

	///Function for evaluation of builtin related with the current matching atom
	static bool evaluateFastBuiltin(const RuleInformation& ruleInformation,
			index_object index,	var_assignment& varAssignment, Term* genericTerm);

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
	BaseAtomSearcher(AtomVector* table) : AtomSearcher(table) {resultVector.resize(ATOMS_IN_RULE,nullptr);};

	virtual void setSizeResultVector(unsigned int size){
		if(size>resultVector.size())
			resultVector.resize(size,nullptr);
	};

	virtual void firstMatch(unsigned id,Atom* templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation);
	virtual void nextMatch(unsigned id, Atom* templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation);
	virtual Atom* findGroundAtom(Atom *atom);
	virtual void add(Atom* atom){};
	virtual void remove(Atom* atom){};
	virtual void clear(){};

	virtual void print(ostream& stream=cout){for(auto atom:*table)atom->print(stream);}

	virtual ~BaseAtomSearcher() {for(auto it:resultVector) delete it;};

	virtual unsigned getType(){return DEFAULT;};

protected:
	/// This maps stores the calls to the firstMatch method.
	/// Indeed, for each call it stores a pair with the counter and the iterator to the next matching atoms.
	vector<GeneralIterator*> resultVector;

	/// This method invokes findIfAFactExists method if all the variables are bound,
	/// otherwise invokes the computeFirstMatch method.
//	bool searchForFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound);
	/// This method given an iterator increases it in order to find matching atoms with the given atom
	/// according to the current assignment.
	bool computeMatch(GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation);
	/// This method computes an iterator pointing to the starting point of the search
	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation){return new VectorIterator(table->begin(),table->end());}
};

class SingleTermAtomSearcher : public BaseAtomSearcher{
public:
	SingleTermAtomSearcher(AtomVector* table, Predicate* p) : BaseAtomSearcher(table), predicate(p), defaultIndexingTerm(-1) {
		lastUpdateIndices.resize(predicate->getArity(),0);

//		indexingTermSetByUser = Options::globalOptions()->getPredicateIndexTerm(this->predicate->getName());
//		if(indexingTermSetByUser>=0)
//			assert_msg(unsigned(indexingTermSetByUser)<this->predicate->getArity(), "The specified index for the predicate \""+(this->predicate)->getName()+"\" is not valid.");
//#ifdef DEBUG_ATOM_SEARCHER
//		cout<<"Predicate: "<<predicate->getName()<<"  Index Term Set By User: "<<indexingTermSetByUser<<endl;
//#endif
		};
	///This method chooses the best indexing term among the one allowed.
	virtual unsigned int selectBestIndex(const vector<pair<int,index_object>>& possibleTableToSearch) = 0;

	inline bool isUpdatedSearchingTable(unsigned position)const{return lastUpdateIndices[position]==table->size();}

	///This method fills in the searching data structure for the given indexing term
	virtual void initializeIndexMaps(unsigned int indexingTerm) = 0;

	virtual void clear(){lastUpdateIndices.assign(lastUpdateIndices.size(),0);}

protected:
	/// The predicate
	Predicate* predicate;
	///The indexing term set by user. It is -1 if not set.
//	int indexingTermSetByUser;
	/// A vector of boolean used in order to determine if the data-structure for a particular indexing terms has been created.
	vector<unsigned> lastUpdateIndices;

	///The first indexing position for which an indexing structure is created
	int defaultIndexingTerm;

	/// This method determines the possible indexing terms for the given NOT GROUND atom.
	/// Then invokes the selectBestIndex method to determine the best one among them.
	/// If the data-structure for the best indexing term is not created, then it fills in
	/// the data structures by means of initializeIndexMaps method.
	virtual int manageIndex(Atom* templateAtom, const RuleInformation& ruleInformation);


//	int computePossibleIndexingTermTable(const vector<pair<int,index_object>>& possibleTableToSearch);

	virtual int getPositionWithBestSelectivity(const vector<pair<int,index_object>>& possibleTableToSearch);

};

/**
 * @brief This class is a more advanced implementation of SingleTermAtomSearcher (@see SingleTermAtomSearcher )
 * @details Searching for match is performed over unordered maps indexed by a single term, namely an indexing term.
 * Instead of performing the search among the whole base vector, it is performed among the atoms,
 * that match for that term.
 * Here is used as searching data structure an unordered map whose keys represent the possible values of the indexing term,
 * that are mapped to unordered sets of atoms in which that term appears with that value.
 * Moreover is it possibly created one of this data-structure for each possible indexing term, so up the predicate arity,
 * accordingly to the searching needs during grounding.
 */
class SingleTermMapAtomSearcher: public SingleTermAtomSearcher {
public:
	SingleTermMapAtomSearcher(AtomVector* table, Predicate* p) : SingleTermAtomSearcher(table,p) {
		searchingTables.reserve(predicate->getArity());
		for(unsigned int i=0;i<predicate->getArity();++i)
			searchingTables.push_back(unordered_map<index_object,AtomTable>());
	};

	virtual Atom* findGroundAtom(Atom *atom);
	virtual void add(Atom* atom);
	virtual void remove(Atom* atom);
	virtual void clear(){SingleTermAtomSearcher::clear(); for(auto& table:searchingTables)table.clear();};

	///This method chooses the best indexing term among the one allowed.
	unsigned int selectBestIndex(const vector<pair<int,index_object>>& possibleTableToSearch);

	///This method fills in the searching data structure for the given indexing term
	void initializeIndexMaps(unsigned int indexingTerm);

	virtual unsigned getType(){return MAP;};

protected:
	///A vector of chosen searching data structure for this kind of indexing strategies, one for each possible indexing term.
	vector<unordered_map<index_object,AtomTable>> searchingTables;



	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation);


};

class BinderSelector{
public:
	virtual int select(Atom* templateAtom, const RuleInformation& ruleInformation,vector<pair<int,index_object>>& possibleTableToSearch,
			vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection, SingleTermAtomSearcher* atomSearcher)=0;
	virtual ~BinderSelector(){}
protected:
};

class BinderSelector1 : public BinderSelector {
public:
	virtual int select(Atom* templateAtom, const RuleInformation& ruleInformation,vector<pair<int,index_object>>& possibleTableToSearch,
			vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection, SingleTermAtomSearcher* atomSearcher);
};

class BinderSelector2 : public BinderSelector {
public:
	virtual int select(Atom* templateAtom, const RuleInformation& ruleInformation,vector<pair<int,index_object>>& possibleTableToSearch,
			vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection, SingleTermAtomSearcher* atomSearcher);
};
class BinderSelector3 : public BinderSelector {
public:
	virtual int select(Atom* templateAtom, const RuleInformation& ruleInformation,vector<pair<int,index_object>>& possibleTableToSearch,
			vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection, SingleTermAtomSearcher* atomSearcher);
};
class BinderSelector4 : public BinderSelector {
public:
	virtual int select(Atom* templateAtom, const RuleInformation& ruleInformation,vector<pair<int,index_object>>& possibleTableToSearch,
			vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection, SingleTermAtomSearcher* atomSearcher);
};

class SingleTermMapDictionaryAtomSearcher: public SingleTermMapAtomSearcher{
public:
	SingleTermMapDictionaryAtomSearcher(AtomVector* table, Predicate* p) : SingleTermMapAtomSearcher(table,p) {setBinderSelector();};
	virtual ~SingleTermMapDictionaryAtomSearcher(){delete binderSelector;}

private:
	void setBinderSelector();
	virtual int manageIndex(Atom* templateAtom, const RuleInformation& ruleInformation);
	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation);
	BinderSelector* binderSelector;
};

/**
 * @brief This class is a more advanced implementation of SingleTermAtomSearcher (@see SingleTermAtomSearcher )
 * @details Searching for match is performed over unordered maps indexed by a single term, namely an indexing term.
 * Instead of performing the search among the whole base vector, it is performed among the atoms,
 * that match for that term.
 * Here is used as searching data structure an unordered multimap whose keys represent the possible values of the indexing term,
 * that are mapped to atoms in which that term appears with that value.
 * Moreover is it possibly created one of this data-structure for each possible indexing term, so up the predicate arity,
 * accordingly to the searching needs during grounding.
 */
class SingleTermMultiMapAtomSearcher: public SingleTermAtomSearcher {
public:
	SingleTermMultiMapAtomSearcher(AtomVector* table, Predicate *p) : SingleTermAtomSearcher(table,p) {
		searchingTables.reserve(predicate->getArity());
		for(unsigned int i=0;i<predicate->getArity();++i)
			searchingTables.push_back(Multimap_Atom());
	};

	virtual Atom* findGroundAtom(Atom *atom);
	virtual void add(Atom* atom);
	virtual void remove(Atom* atom);
	virtual void clear(){SingleTermAtomSearcher::clear(); for(auto& table:searchingTables)table.clear();};

	///This method chooses the best indexing term among the one allowed.
	unsigned int selectBestIndex(const vector<pair<int,index_object>>& possibleTableToSearch);

 	///This method fills in the indexing data structures
	void initializeIndexMaps(unsigned int indexTable);

	virtual unsigned getType(){return MULTIMAP;};

private:
	/// A vector of chosen searching data structure for this kind of indexing strategies, one for each possible indexing term.
	vector<Multimap_Atom> searchingTables;

 	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation);


};

class HashSetAtomSearcher: public BaseAtomSearcher {
public:
	HashSetAtomSearcher(AtomVector* table, Predicate *p) : BaseAtomSearcher(table), lastUpdateIndex(0) {}
	virtual Atom* findGroundAtom(Atom *atom);
	virtual void add(Atom* atom) { searchingTable.insert(atom); }
	virtual void remove(Atom* atom) { searchingTable.erase(atom); }
	virtual void clear() { lastUpdateIndex=0; searchingTable.clear(); }

	virtual unsigned getType(){return HASHSET;};

private:
	/// An unordered set of Atoms, the chosen searching data structure for this kind of indexing strategies.
	AtomTable searchingTable;

	///The HashSet contains the atoms up to the lastUpdateIndex in the vector of atoms
	unsigned lastUpdateIndex;

 	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation){
 		return new VectorIterator(table->begin(), table->end());
 	}

 	///This method fills in the indexing data structures
	void updateIndexMaps(){
		for (;lastUpdateIndex<table->size();++lastUpdateIndex)
			searchingTable.insert((*table)[lastUpdateIndex]);

	}

	void manageIndex(){
		if(lastUpdateIndex<table->size())
			updateIndexMaps();
	}

};

class DoubleTermMapAtomSearcher: public BaseAtomSearcher{
public:
	DoubleTermMapAtomSearcher(AtomVector* table, Predicate* p) : BaseAtomSearcher(table),defaultIndexingTerm(-1) {
		this->predicate=p;
		searchingTables.reserve(predicate->getArity());
		createdSearchingTables.reserve(predicate->getArity());
		for(unsigned int i=0;i<predicate->getArity();++i){
			searchingTables.push_back(unordered_map<index_object,Multimap_Atom>());
			createdSearchingTables.push_back(false);
		}
//		indexingTermSetByUser = Options::globalOptions()->getPredicateIndexTerm(this->predicate->getName());
//		if(indexingTermSetByUser>=0)
//			assert_msg(unsigned(indexingTermSetByUser)<this->predicate->getArity(), "The specified index for the predicate \""+(this->predicate)->getName()+"\" is not valid.");
//#ifdef DEBUG_ATOM_SEARCHER
//		cout<<"Predicate: "<<predicate->getName()<<"  Index Term Set By User: "<<indexingTermSetByUser<<endl;
//#endif
	};

	virtual Atom* findGroundAtom(Atom *atom);
	virtual void add(Atom* atom);
	virtual void remove(Atom* atom);
	virtual void clear(){for(auto table:searchingTables) table.clear();};

	///This method chooses the best indexing term among the one allowed.
	unsigned int selectBestIndex(const vector<pair<int,pair<index_object,int>>>& possibleTableToSearch);

	virtual unsigned getType(){return DOUBLEMAP;};

private:
	/// The predicate
	Predicate* predicate;
	///The indexing term set by user. It is -1 if not set.
//	int indexingTermSetByUser;
	/// A vector of boolean used in order to determine if the data-structure for a particular indexing terms has been created.
	vector<bool> createdSearchingTables;
	///A vector of chosen searching data structure for this kind of indexing strategies, one for each possible indexing term.
	vector<unordered_map<index_object,Multimap_Atom>> searchingTables;

	///The first indexing position for which an indexing structure is created
	int defaultIndexingTerm;


	int manageIndex(Atom* templateAtom);
	int manageIndexGround();

	virtual GeneralIterator* computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation);

	void initializeIndexMaps(unsigned int indexingTerm);

//	int computePossibleIndexingTermTable(const vector<pair<int,pair<index_object,int>>>& possibleTableToSearch);

};

}}

#endif /* INDEXATOM_H_ */

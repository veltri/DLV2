/*
 * IndexAtom2.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: jessica
 */

#include "../../util/Options.h"
#include "../../util/Assert.h"
#include "AtomSearcher.h"
#include "../../util/Timer.h"
#include <boost/lexical_cast.hpp>
#include "PredicateExtension.h"

namespace DLV2{

namespace grounder{


/******************************************************* ATOM SEARCHER ***************************************************/

bool AtomSearcher::checkMatch(Atom *genericAtom, Atom *templateAtom, var_assignment& currentAssignment){
	// Checks the match for each term and, if all the terms match, updates the current assignment accordingly
	var_assignment assignInTerm;
	assignInTerm.setSize(currentAssignment.size(),nullptr);

	vector<index_object> variablesAdded;
	for(unsigned int i=0;i<genericAtom->getTermsSize();++i){
		if(!matchTerm(genericAtom->getTerm(i),templateAtom->getTerm(i),assignInTerm,variablesAdded))
			return false;
	}

	//TODO TEST LINEAR SCANNING THE ARRAY
	for(auto variable:variablesAdded){
		currentAssignment[variable]=assignInTerm[variable];
	}

	return true;

}

bool AtomSearcher::matchTerm(Term *genericTerm, Term *termToMatch, var_assignment& varAssignment,vector<index_object>& addedVariables){

	if (termToMatch->getType()==TermType::VARIABLE) {
		index_object index=termToMatch->getLocalVariableIndex();
		Term* term=varAssignment[index];
		if(term!=nullptr){
		if( term->getIndex() == genericTerm->getIndex())
			return true;
		else
			return false;

		}
		varAssignment[index]=genericTerm;
		addedVariables.push_back(index);
		return true;
	}

	if(termToMatch->getType()==TermType::ARITH){
		Term *new_term=termToMatch->substitute(varAssignment);
		assert_msg(new_term->isGround(),"Arith term not safe");
		termToMatch=new_term->calculate();
	}

	if (termToMatch->getType()==TermType::ANONYMOUS) return true;

	if((genericTerm->getType()==TermType::NUMERIC_CONSTANT || genericTerm->getType()==TermType::STRING_CONSTANT
			 || genericTerm->getType()==TermType::SYMBOLIC_CONSTANT)){

		if (termToMatch->getIndex() == genericTerm->getIndex()) return true;

	}else if(genericTerm->getType()==TermType::FUNCTION){

		if(termToMatch->getType()!=TermType::FUNCTION) return false;
		if(termToMatch->getName().compare(genericTerm->getName()) != 0)return false;
		if(termToMatch->getTermsSize() != genericTerm->getTermsSize())return false;
		for(unsigned int i=0;i<genericTerm->getTermsSize();++i)
			if(!matchTerm(genericTerm->getTerm(i),termToMatch->getTerm(i),varAssignment,addedVariables))
				return false;

		return true;
	}

	return false;

}



/****************************************************** BASE ATOM SEARCHER ***************************************************/

void BaseAtomSearcher::firstMatch(unsigned id,Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound) {
	GeneralIterator* currentMatch=computeGenericIterator(templateAtom);
	if(searchForFirstMatch(currentMatch, templateAtom, currentAssignment,atomFound)){
		delete resultVector[id];
		resultVector[id]=currentMatch;
		return ;
	}

	delete currentMatch;
}

bool BaseAtomSearcher::searchForFirstMatch(GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound){
	//Call findIfAFactExist only if all the terms are bound
	if(templateAtom->isGround()){
		findIfExist(templateAtom,atomFound);
		return false;
	}

	//Compute the first match
	return computeMatch(currentMatch,templateAtom,currentAssignment,atomFound);
}

bool BaseAtomSearcher::computeMatch(GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(currentMatch->currentItem(),templateAtom,currentAssignment)){
			atomFound=currentMatch->currentItem();
			return true;
		}
	}
	atomFound=nullptr;
	return false;
}

void BaseAtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound) {
	GeneralIterator* currentMatch=resultVector[id];
	currentMatch->next();
	computeMatch(currentMatch,templateAtom,currentAssignment,atomFound);

}

Atom* BaseAtomSearcher::findAtom(Atom *atom){
	for(auto genericAtom:(*table)){
		if(*genericAtom==*atom){
			return genericAtom;
		}
	}
	return nullptr;
}

void BaseAtomSearcher::findIfExist(Atom *templateAtom, Atom*& atomFound) {
	atomFound=findAtom(templateAtom);
}

/****************************************************** SINGLE TERM ATOM SEARCH ***************************************************/

int SingleTermAtomSearcher::manageIndex(Atom* templateAtom) {
	vector<pair<int,index_object>> possibleTableToSearch;
	for(unsigned int i=0;i<templateAtom->getTermsSize();++i){
		Term* t=templateAtom->getTerm(i);
		if(t->isGround())
			possibleTableToSearch.push_back({i,t->getIndex()});
	}


	int indexSelected=-1;
	if(!possibleTableToSearch.empty()){
		indexSelected=selectBestIndex(possibleTableToSearch);
		if(!createdSearchingTables[indexSelected]){
			initializeIndexMaps(indexSelected);
		}
	}
	return indexSelected;
}

int SingleTermAtomSearcher::computePossibleIndexingTermTable(const vector<pair<int,index_object>>& possibleTableToSearch){
	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser])
		for(unsigned int i=0;i<possibleTableToSearch.size();++i){
			if(possibleTableToSearch[i].first==indexingTermSetByUser)
				return indexingTermSetByUser;
			if(possibleTableToSearch[i].first>indexingTermSetByUser)
				return -1;
		}
	return -1;
}

int SingleTermAtomSearcher::getPositionWithBestSelectivity(const vector<pair<int,index_object>>& possibleTableToSearch){
	int index=0;
	if(possibleTableToSearch.size()==1)
		return (*possibleTableToSearch.begin()).first;
	unsigned maxSelectivity=0;
	PredicateInformation* predInfo=PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation();
	for(auto pair:possibleTableToSearch){
		unsigned selectivity=predInfo->getSelectivity(pair.first);
		if(selectivity>maxSelectivity){
			maxSelectivity=selectivity;
			index=pair.first;
		}
	}
	return index;
}

/****************************************************** SINGLE TERM MAP ATOM SEARCH ***************************************************/

void SingleTermMapAtomSearcher::add(Atom* atom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Add index "+predicate->getName());
#endif
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(searchingTables[i].count(termIndex))
				searchingTables[i][termIndex].insert(atom);
			else{
				searchingTables[i].emplace(termIndex,AtomTable({atom}));
			}
		}
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Add index "+predicate->getName());
#endif
}

void SingleTermMapAtomSearcher::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(searchingTables[i].count(termIndex))
				searchingTables[termIndex][i].erase(atom);
		}
	}
}

Atom* SingleTermMapAtomSearcher::findAtom(Atom *atom){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Find "+predicate->getName());
#endif
	int tableToSearch=manageIndex(atom);
	assert_msg(tableToSearch>-1, "Invalid index");

	index_object term = atom->getTerm(tableToSearch)->getIndex();
	AtomTable* matchingTable=&searchingTables[tableToSearch][term];

	auto atomFound_it=matchingTable->find(atom);
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Find "+predicate->getName());
#endif
	if(atomFound_it!=matchingTable->end())
		return *atomFound_it;
	return nullptr;
}

unsigned int SingleTermMapAtomSearcher::selectBestIndex(const vector<pair<int,index_object>>& possibleTableToSearch){
	/* The choosing policy is the following:
		- if the position set by the user can be chosen, then chose that one
		- if more positions of indexing are available then chose the data structure
			with the smaller size
		- if none indexing structure has been created (among the ones allowed), then chose the position
		with the best selectivity among the position of indexing available
	*/
	int index=computePossibleIndexingTermTable(possibleTableToSearch);
	if(index!=-1) return index;

	unsigned minSize=INT_MAX;
	for(auto it=possibleTableToSearch.begin();it!=possibleTableToSearch.end();++it){
		if(createdSearchingTables[(*it).first]){
			unsigned currentSize=(searchingTables[(*it).first][(*it).second]).size();
			if(minSize>currentSize){
				minSize=currentSize;
				index=(*it).first;
			}
		}
	}
	if(index!=-1)
		return index;
	return getPositionWithBestSelectivity(possibleTableToSearch);
}

GeneralIterator* SingleTermMapAtomSearcher::computeGenericIterator(Atom* templateAtom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	int indexingTerm=manageIndex(templateAtom);
	GeneralIterator* currentMatch;

	//If no searching table is available (the atom is completely unbound)
	//the search is performed in the base vector
	if(indexingTerm!=-1){
		index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
		AtomTable* matchingTable=&searchingTables[indexingTerm][term];
		currentMatch=new UnorderedSetIterator(matchingTable->begin(),matchingTable->end());
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Compute iterator "+predicate->getName());
#endif
	return currentMatch;
}

void SingleTermMapAtomSearcher::initializeIndexMaps(unsigned int indexingTerm){
#ifdef DEBUG_ATOM_SEARCHER
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif

#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Create index "+predicate->getName()+" index "+boost::lexical_cast<string>(indexingTerm));
#endif
	createdSearchingTables[indexingTerm]=true;
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		if(!searchingTables[indexingTerm].count(termIndex)){
			AtomTable values;
			values.insert(a);
			searchingTables[indexingTerm].insert({termIndex,values}).second;
		}
		else
			searchingTables[indexingTerm][termIndex].insert(a).second;
	}

#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Create index "+predicate->getName()+" index "+boost::lexical_cast<string>(indexingTerm));
#endif
}

/****************************************************** SINGLE TERM MULTI MAP ATOM SEARCH ***************************************************/

void SingleTermMultiMapAtomSearcher::add(Atom* atom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Add index "+predicate->getName());
#endif
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			searchingTables[i].insert({termIndex,atom});
		}
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Add index "+predicate->getName());
#endif
}

void SingleTermMultiMapAtomSearcher::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			auto pair=searchingTables[i].equal_range(termIndex);
			for(auto it=pair.first;it!=pair.second;++it){
				if(*(it->second)==*atom)
					searchingTables[i].erase(it);
			}
		}
	}
}

Atom* SingleTermMultiMapAtomSearcher::findAtom(Atom *atom){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Find "+predicate->getName());
#endif
	int indexingTerm=manageIndex(atom);
	assert_msg(indexingTerm>-1, "Invalid index");

	index_object term = atom->getTerm(indexingTerm)->getIndex();
	auto pair=searchingTables[indexingTerm].equal_range(term);

	for(auto it=pair.first;it!=pair.second;++it){
		if(*(it->second)==*atom)
			return it->second;
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Find "+predicate->getName());
#endif
	return nullptr;
}

unsigned int SingleTermMultiMapAtomSearcher::selectBestIndex(const vector<pair<int,index_object>>& possibleTableToSearch){
	/* The choosing policy is the following:
		- if the position set by the user can be chosen, then chose that one
		- if more positions of indexing are available then chose the data structure
			with the smaller size
		- if none indexing structure has been created (among the ones allowed), then chose the position
		with the best selectivity among the position of indexing available
	*/
	int index=computePossibleIndexingTermTable(possibleTableToSearch);
	if(index!=-1) return index;

	unsigned minSize=INT_MAX;
	for(auto it=possibleTableToSearch.begin();it!=possibleTableToSearch.end();++it){
		if(createdSearchingTables[(*it).first]){
			unsigned currentSize=searchingTables[(*it).first].count((*it).second);
			if(minSize>currentSize){
				minSize=currentSize;
				index=(*it).first;
			}
		}
	}

	if(index!=-1)
		return index;

	return getPositionWithBestSelectivity(possibleTableToSearch);
}


GeneralIterator* SingleTermMultiMapAtomSearcher::computeGenericIterator(Atom* templateAtom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	int indexingTerm=manageIndex(templateAtom);
	GeneralIterator* currentMatch;

	//If no searching table is available (the atom is completely unbound)
	//the search is performed in the base vector
	if(indexingTerm!=-1){
		index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
		auto pair=searchingTables[indexingTerm].equal_range(term);
		currentMatch=new UnorderedMultiMapIterator(pair.first,pair.second);
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
	return currentMatch;
}

void SingleTermMultiMapAtomSearcher::initializeIndexMaps(unsigned int indexingTerm){
#ifdef DEBUG_ATOM_SEARCHER
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	createdSearchingTables[indexingTerm]=true;
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		searchingTables[indexingTerm].insert({termIndex,a});
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Compute iterator "+predicate->getName());
#endif
}

/****************************************************** HASH SET ATOM SEARCH ***************************************************/

Atom* HashSetAtomSearcher::findAtom(Atom* atom) {
	manageIndex();
	auto atomFound_it=searchingTable.find(atom);
	if(atomFound_it!=searchingTable.end())
		return *atomFound_it;
	return nullptr;
}


/****************************************************** DOUBLE TERM MAP ATOM SEARCH ***************************************************/

void DoubleTermMapAtomSearcher::add(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			int nextTermIndex=-1;
			if(i<(predicate->getArity()-1))
				nextTermIndex=atom->getTerm(i+1)->getIndex();
			if(searchingTables[i].count(termIndex)){
				if(nextTermIndex>-1)
					searchingTables[i][termIndex].insert({nextTermIndex,atom});
				else
					searchingTables[i][termIndex].insert({termIndex,atom});
			}
			else{
				Multimap_Atom values;
				if(nextTermIndex>-1)
					values.insert({nextTermIndex,atom});
				else
					values.insert({termIndex,atom});
				searchingTables[i].insert({termIndex,values});
			}
		}
	}
}

void DoubleTermMapAtomSearcher::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(createdSearchingTables[i]){
			index_object termIndex=atom->getTerm(i)->getIndex();
			int nextTermIndex=-1;
			if(i<(predicate->getArity()-1))
				nextTermIndex=atom->getTerm(i+1)->getIndex();
			if(searchingTables[i].count(termIndex)){
				if(nextTermIndex>-1)
					searchingTables[i][termIndex].erase(nextTermIndex);
				else
					searchingTables[i][termIndex].erase(termIndex);
			}

		}
	}
}

Atom* DoubleTermMapAtomSearcher::findAtom(Atom *atom){
	int tableToSearch=manageIndex(atom);
	assert_msg(tableToSearch>-1, "Invalid index");

	index_object term = atom->getTerm(tableToSearch)->getIndex();
	Multimap_Atom::iterator start;
	Multimap_Atom::iterator end;

	if(unsigned(tableToSearch) < predicate->getArity()-1){
		index_object nextTerm=atom->getTerm(tableToSearch+1)->getIndex();
		auto pair=searchingTables[tableToSearch][term].equal_range(nextTerm);
		start=pair.first;
		end=pair.second;
	}
	else{
		start=searchingTables[tableToSearch][term].begin();
		end=searchingTables[tableToSearch][term].end();
	}

	for(auto it=start;it!=end;++it){
		if(*(it->second)==*atom)
			return it->second;
	}
	return nullptr;
}

int DoubleTermMapAtomSearcher::manageIndex(Atom* templateAtom) {
	vector<pair<int,pair<index_object,int>>> possibleTableToSearch;
	unsigned termsSize=predicate->getArity();
	for(unsigned int i=0;i<termsSize;++i){
		Term* t=templateAtom->getTerm(i);
		if(t->isGround()){
			if(i<termsSize-1){
				Term* nextTerm=templateAtom->getTerm(i+1);
				if(nextTerm->isGround())
					possibleTableToSearch.push_back({i,{t->getIndex(),nextTerm->getIndex()}});
				else
					possibleTableToSearch.push_back({i,{t->getIndex(),-1}});
			}
			else
				possibleTableToSearch.push_back({i,{t->getIndex(),-1}});
		}
	}
	int indexSelected=-1;
	if(!possibleTableToSearch.empty()){
		indexSelected=selectBestIndex(possibleTableToSearch);
		if(!createdSearchingTables[indexSelected])
			initializeIndexMaps(indexSelected);
	}
	return indexSelected;
}

int DoubleTermMapAtomSearcher::computePossibleIndexingTermTable(const vector<pair<int,pair<index_object,int>>>& possibleTableToSearch){
	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser])
		for(unsigned int i=0;i<possibleTableToSearch.size();++i){
			if(possibleTableToSearch[i].first==indexingTermSetByUser)
				return indexingTermSetByUser;
			if(possibleTableToSearch[i].first>indexingTermSetByUser)
				return -1;
		}
	return -1;
}

unsigned int DoubleTermMapAtomSearcher::selectBestIndex(const vector<pair<int,pair<index_object,int>>>& possibleTableToSearch){
	/* The choosing policy is the following:
		- if the position set by the user can be chosen, then chose that one
		- if more positions of indexing are available then chose the data structure
			with the smaller size
		- if none indexing structure has been created (among the ones allowed), then chose the position
		with the best selectivity among the position of indexing available
	*/
	int index=computePossibleIndexingTermTable(possibleTableToSearch);
	if(index!=-1) return index;

	unsigned minSize=INT_MAX;
	for(auto it=possibleTableToSearch.begin();it!=possibleTableToSearch.end();++it){
		if(unsigned((*it).first)<createdSearchingTables.size() && createdSearchingTables[(*it).first]){
			unsigned termIndex=(*it).second.first;
			int nextTermIndex=(*it).second.second;
			unsigned currentSize=searchingTables[(*it).first][termIndex].size();
			if(nextTermIndex!=-1)
				currentSize=searchingTables[(*it).first][termIndex].count(nextTermIndex);
			if(minSize>currentSize){
				minSize=currentSize;
				index=(*it).first;
			}
		}
	}

	if(index!=-1)
		return index;

	index=0;
	if(possibleTableToSearch.size()==1)
		return (*possibleTableToSearch.begin()).first;
	unsigned maxSelectivity=0;
	PredicateInformation* predInfo=PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation();
	for(auto pair:possibleTableToSearch){
		unsigned selectivity=predInfo->getSelectivity(pair.first);
		if(selectivity>maxSelectivity){
			maxSelectivity=selectivity;
			index=pair.first;
		}
	}
	return index;
}

GeneralIterator* DoubleTermMapAtomSearcher::computeGenericIterator(Atom* templateAtom) {
	int indexingTerm=manageIndex(templateAtom);
	GeneralIterator* currentMatch;

	//If no searching table is available (the atom is completely unbound)
	//the search is performed in the base vector
	if(indexingTerm!=-1){
		index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
		Multimap_Atom::iterator start;
		Multimap_Atom::iterator end;

		Term* nextTerm=templateAtom->getTerm(indexingTerm+1);
		if(unsigned(indexingTerm) < predicate->getArity()-1 && nextTerm->isGround()){
			index_object nextTermIndex=nextTerm->getIndex();
			auto pair=searchingTables[indexingTerm][term].equal_range(nextTermIndex);
			start=pair.first;
			end=pair.second;
		}
		else{
			start=searchingTables[indexingTerm][term].begin();
			end=searchingTables[indexingTerm][term].end();
		}
		currentMatch=new UnorderedMultiMapIterator(start,end);
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
	return currentMatch;
}

void DoubleTermMapAtomSearcher::initializeIndexMaps(unsigned int indexingTerm){
#ifdef DEBUG_ATOM_SEARCHER
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif
	createdSearchingTables[indexingTerm]=true;
	for (Atom* a : *table) {
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		int nextTermIndex=-1;
		if(indexingTerm<(predicate->getArity()-1))
			nextTermIndex=a->getTerm(indexingTerm+1)->getIndex();
		if(searchingTables[indexingTerm].count(termIndex)){
			if(nextTermIndex>-1)
				searchingTables[indexingTerm][termIndex].insert({nextTermIndex,a});
			else
				searchingTables[indexingTerm][termIndex].insert({termIndex,a});
		}
		else{
			Multimap_Atom values;
			if(nextTermIndex>-1)
				values.insert({nextTermIndex,a});
			else
				values.insert({termIndex,a});
			searchingTables[indexingTerm].insert({termIndex,values});
		}
	}
}


};
};

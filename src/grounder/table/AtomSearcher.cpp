/*
 * IndexAtom2.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: jessica
 */

#include "../../util/Options.h"
#include "AtomSearcher.h"


namespace DLV2{

namespace grounder{

/******************************************************* RESULT MATCH ***************************************************/

bool ResultMatch::match(GenericAtom *genericAtom,Atom *templateAtom,map_term_term& currentAssignment,map_term_term& nextAssignment){
	// Call match for each term and if all term result true put the assignment in the current assignment
	map_term_term assignInTerm(currentAssignment);

	for(unsigned int i=0;i<genericAtom->getTermsSize();i++)
		if(!genericAtom->getTerm(i)->match(templateAtom->getTerm(i),assignInTerm))
			return false;
	for(auto assignment:assignInTerm)if(!currentAssignment.count(assignment.first))nextAssignment.insert(assignment);
	return true;
}

/****************************************************** SIMPLE INDEX ATOM ***************************************************/

bool SimpleAtomSearcher::findIfExists(AtomTable* collection, bool& isUndef) {
	if(collection->size()==0)return false;

	//Compute the hash of the atom
	GenericAtom *genAtom=new GenericAtom(templateAtom->getTerms(),true);

	//Look for the atom
	bool find=false;
	auto atomIterator = collection->find(genAtom);

	if(atomIterator!=collection->end()){
		find=true;
		isUndef=!(*atomIterator)->isFact();
	}

	delete genAtom;
	return find;
}

bool SimpleAtomSearcher::findIfExists(AtomTable* collection) {
	bool isUndef;
	return findIfExists(collection,isUndef);
}

unsigned int SimpleAtomSearcher::firstMatch(bool searchInDelta,Atom *templateAtom,map_term_term& currentAssignment, bool& find) {
	unsigned int id = counter;counter++;

	this->templateAtom=templateAtom;
	this->currentAssignment=&currentAssignment;

	// Hash the bind term, the variable term or term that contain variable term
	vector<unsigned int> bind;
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++)
		if(templateAtom->getTerm(i)->contain(TermType::VARIABLE))bind.push_back(i);
	ResultMatch *rm = new ResultMatch(bind);

//	    Search only in delta if searchInDelta is true
//		else search in fact or nofact if predicate is EDB
	if(( searchInDelta && searchForFirstMatch(delta,rm) ) ||
	   (!searchInDelta &&
					   (searchForFirstMatch(facts,rm) ||
					   (!predicate->isEdb() && searchForFirstMatch(nofacts,rm))))){
		find=true;
		matches_id.insert({id,rm});
		return id;
	}

	matches_id.insert({id,rm});
	nextMatch(id,currentAssignment,find);
	return id;


}

bool SimpleAtomSearcher::searchForFirstMatch(AtomTable* table, ResultMatch* rm){
	//Call findIfAFactExist only if all the terms are bound
	if(templateAtom->isGround()){
		if(findIfExists(table))
			return true;
	}
	else
		//Compute the first match
		computeFirstMatch(table,rm);
	return false;
}

void SimpleAtomSearcher::computeFirstMatch(AtomTable* collection,ResultMatch* rm){
	// If not contains variable (then there is anonymous but the other is ground)
	bool isNotVariable=templateAtom->getVariable().size()==0;
	for (GenericAtom *genericAtom : *collection) {
		if (rm->insert(genericAtom,templateAtom,*currentAssignment)) {

			//If there are no more bind variables stop.
			//Notice that the size of the bind variables vector is not always equal to the arity of the predicate.
			//Indeed, there can be anonymous variables that are not considered to be bind.
			//The same holds for bound variables.
			if(isNotVariable)break;

		}
	}
}


void SimpleAtomSearcher::nextMatch(unsigned int id,map_term_term& currentAssignment,bool& find) {
	ResultMatch *rm=matches_id.find(id)->second;

	///Return the next matching facts or no facts retrieved from the integer identifier assigned by the firstMatch method
	if(!rm->pop(currentAssignment)){
		delete rm;
		matches_id.erase(id);
		find=false;
		return ;
	}

	find=true;
}


void SimpleAtomSearcher::findIfExist(bool searchInDelta,Atom *templateAtom,bool& find, bool& isUndef) {
	this->templateAtom=templateAtom;

	if((searchInDelta && findIfExists(delta,isUndef) ) ||
	  (!searchInDelta &&
			  (findIfExists(facts,isUndef) ||
			   (!predicate->isEdb() && findIfExists(nofacts,isUndef))))){
		find=true;
		return ;
	}

	find=false;

	return ;


}

/****************************************************** SINGLE TERM INDEX ATOM ***************************************************/

void SingleTermAtomSearcher::updateDelta(AtomTable* nextDelta) {
	if(instantiateIndexMaps){
		for(GenericAtom* atom: *delta){
			index_object termIndex=atom->getTerm(positionOfIndexing)->getIndex();
			if(nofactsIndexMap.count(termIndex)){
				nofactsIndexMap[termIndex].insert(atom);
			}
			else{
				AtomTable values;
				values.insert(atom);
				nofactsIndexMap.insert({termIndex,values});
			}
		}
		deltaIndexMap.clear();
		for(GenericAtom* atom: *nextDelta){
			index_object termIndex=atom->getTerm(positionOfIndexing)->getIndex();
			if(deltaIndexMap.count(termIndex)){
				deltaIndexMap[termIndex].insert(atom);
			}
			else{
				AtomTable values;
				values.insert(atom);
				deltaIndexMap.insert({termIndex,values});
			}
		}
	}
}


pair<bool, index_object> SingleTermAtomSearcher::createIndex(vector<unsigned int>& bind) {
	// Compute the bind variables, determine the indexing term and fill the facts and no facts maps if not yet filled
	pair<bool, index_object> termBoundIndex( { false, 0 });
	if(!positionOfIndexingSetByUser){
		pair<unsigned int,bool> p = Options::globalOptions()->getIndexingTerm(this->predicate->getName());
		if(p.first>=0 && p.first<this->predicate->getArity()){
			positionOfIndexing=p.first;
			positionOfIndexingSetByUser=p.second;
		}
		else{
			positionOfIndexing=0;
			positionOfIndexingSetByUser=false;
		}
	}
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++){
		Term* t=templateAtom->getTerm(i);
		if(t->contain(TermType::VARIABLE))
			bind.push_back(i);
		if (!positionOfIndexingSetByUser && t->isGround()){
			positionOfIndexing=i;
			positionOfIndexingSetByUser = true;
		}
		if(positionOfIndexingSetByUser && i == positionOfIndexing && t->isGround()) {
			termBoundIndex.first = true;
			termBoundIndex.second = t->getIndex();
			if (!templateAtom->isGround() && !instantiateIndexMaps)
				initializeIndexMaps();
		}
	}
	return termBoundIndex;
}

bool SingleTermAtomSearcher::getMatchingTable(AtomTable*& matchingTable,unordered_map<index_object,AtomTable>& index_table,AtomTable*& table,pair<bool, index_object>& termBoundIndex){
	if(termBoundIndex.first)
		matchingTable=&index_table[termBoundIndex.second];
	else
		matchingTable=table;
	return true;
}


unsigned int SingleTermAtomSearcher::firstMatch(bool searchInDelta, Atom *templateAtom, map_term_term& currentAssignment, bool& find){

	unsigned int id = counter;counter++;

	this->templateAtom=templateAtom;
	this->currentAssignment=&currentAssignment;

	// Hash the bind term, the variable term or term that contain variable term
	vector<unsigned int> bind;

	pair<bool, index_object> termBoundIndex = createIndex(bind);

	ResultMatch *rm = new ResultMatch(bind);
	AtomTable* matchingTable;


	if(( searchInDelta && getMatchingTable(matchingTable,deltaIndexMap,delta,termBoundIndex) && searchForFirstMatch(matchingTable,rm) ) ||
	   (!searchInDelta &&
					   ( (getMatchingTable(matchingTable,factsIndexMap,facts,termBoundIndex) && searchForFirstMatch(matchingTable,rm) )  ||
					   (!predicate->isEdb() && nofacts->size()>0 && getMatchingTable(matchingTable,nofactsIndexMap,nofacts,termBoundIndex) && searchForFirstMatch(matchingTable,rm))))){
		find=true;
		matches_id.insert({id,rm});
		return id;
	}

	matches_id.insert({id,rm});
	nextMatch(id,currentAssignment,find);
	return id;

}

void SingleTermAtomSearcher::initializeIndexMaps(){
//	Timer::getInstance()->start("Creation Index Structure");
	unordered_set<index_object> termToBeIndexedIndices;

	for (GenericAtom*a : *facts) {
		index_object termIndex=a->getTerm(positionOfIndexing)->getIndex();
		if(termToBeIndexedIndices.insert(termIndex).second){
			AtomTable values;
			values.insert(a);
			factsIndexMap.insert({termIndex,values});
		}
		else{
			factsIndexMap[termIndex].insert(a);
		}
	}
	if(!predicate->isEdb()){
		termToBeIndexedIndices.clear();
		for (GenericAtom*a : *nofacts) {
			index_object termIndex=a->getTerm(positionOfIndexing)->getIndex();
			if(termToBeIndexedIndices.insert(termIndex).second){
				AtomTable values;
				values.insert(a);
				nofactsIndexMap.insert({termIndex,values});
			}
			else{
				nofactsIndexMap[termIndex].insert(a);
			}
		}
	}
//	Timer::getInstance()->end();
	instantiateIndexMaps=true;
}


/****************************************************** SINGLE TERM MULTI MAP INDEX ATOM ***************************************************/

void SingleTermAtomSearcherMultiMap::updateDelta(AtomTable* nextDelta) {
	if(instantiateIndexMaps){
		for(GenericAtom* atom: *delta){
			index_object termIndex=atom->getTerm(positionOfIndexing)->getIndex();
			nofactsIndexMap.insert({termIndex,atom});
		}
		deltaIndexMap.clear();
		for(GenericAtom* atom: *nextDelta){
			index_object termIndex=atom->getTerm(positionOfIndexing)->getIndex();
			deltaIndexMap.insert({termIndex,atom});
		}
	}
}

pair<bool, index_object> SingleTermAtomSearcherMultiMap::createIndex(vector<unsigned int>& bind) {
	// Compute the bind variables, determine the indexing term and fill the facts and no facts maps if not yet filled
	pair<bool, index_object> termBoundIndex( { false, 0 });
	if(!positionOfIndexingSetByUser){
		pair<unsigned int,bool> p = Options::globalOptions()->getIndexingTerm(this->predicate->getName());
		if(p.first>=0 && p.first<this->predicate->getArity()){
			positionOfIndexing=p.first;
			positionOfIndexingSetByUser=p.second;
		}
		else{
			positionOfIndexing=0;
			positionOfIndexingSetByUser=false;
		}
	}
	for(unsigned int i=0;i<templateAtom->getTermsSize();i++){
		Term* t=templateAtom->getTerm(i);
		if(t->contain(TermType::VARIABLE))
			bind.push_back(i);
		else if (!positionOfIndexingSetByUser && t->isGround()){
			positionOfIndexing=i;
			positionOfIndexingSetByUser = true;
		}
		if(positionOfIndexingSetByUser && i == positionOfIndexing && t->isGround()) {
			termBoundIndex.first = true;
			termBoundIndex.second = t->getIndex();
			if (!templateAtom->isGround() && !instantiateIndexMaps)
				initializeIndexMaps();
		}
	}
	return termBoundIndex;
}

bool SingleTermAtomSearcherMultiMap::getMatchingTable(AtomTable*& matchingTable,unordered_multimap<index_object,GenericAtom*>& index_table,AtomTable*& table,pair<bool, index_object>& termBoundIndex){
	if(termBoundIndex.first){
		matchingTable=new AtomTable;
		auto pair=index_table.equal_range(termBoundIndex.second);
		for(auto it=pair.first;it!=pair.second;it++)
			matchingTable->insert(it->second);
	}
	else
		matchingTable=table;
	return true;
}

bool SingleTermAtomSearcherMultiMap::searchForFirstMatch(AtomTable* table, ResultMatch* rm){
	//Call findIfAFactExist only if all the terms are bound
	if(templateAtom->isGround()){
		if(findIfExists(table))
			return true;
	}
	else{
		//Compute the first match
		computeFirstMatch(table,rm);
	}
	return false;
}

unsigned int SingleTermAtomSearcherMultiMap::firstMatch(bool searchInDelta, Atom *templateAtom, map_term_term& currentAssignment, bool& find){
	unsigned int id = counter;counter++;

	this->templateAtom=templateAtom;
	this->currentAssignment=&currentAssignment;

	AtomTable* matchingTable;

	vector<unsigned int> bind;
	pair<bool, index_object> termBoundIndex = createIndex(bind);
	ResultMatch *rm = new ResultMatch(bind);

	if(( searchInDelta && getMatchingTable(matchingTable,deltaIndexMap,delta,termBoundIndex) && searchForFirstMatch(matchingTable,rm) ) ||
	   (!searchInDelta &&
					   ( (getMatchingTable(matchingTable,factsIndexMap,facts,termBoundIndex) && searchForFirstMatch(matchingTable,rm) )  ||
					   (!predicate->isEdb() && nofacts->size()>0 && getMatchingTable(matchingTable,nofactsIndexMap,nofacts,termBoundIndex) && searchForFirstMatch(matchingTable,rm))))){
		find=true;
		matches_id.insert({id,rm});
		return id;
	}

	matches_id.insert({id,rm});
	nextMatch(id,currentAssignment,find);
	return id;
}


void SingleTermAtomSearcherMultiMap::initializeIndexMaps(){
//	Timer::getInstance()->start("Creation Index Structure");
	for (GenericAtom*a : *facts) {
		index_object termIndex=a->getTerm(positionOfIndexing)->getIndex();
		factsIndexMap.insert({termIndex,a});
	}
	if(!predicate->isEdb()){
		for (GenericAtom*a : *nofacts) {
				index_object termIndex=a->getTerm(positionOfIndexing)->getIndex();
				nofactsIndexMap.insert({termIndex,a});
		}
	}
//	Timer::getInstance()->end();
	instantiateIndexMaps=true;
}

};

};





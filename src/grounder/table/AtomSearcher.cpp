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

bool AtomSearcher::checkMatch(Atom *genericAtom, Atom *templateAtom, var_assignment& currentAssignment,const RuleInformation& ruleInformation){
	// Checks the match for each term and, if all the terms match, updates the current assignment accordingly
	var_assignment assignInTerm(currentAssignment);

	vector<index_object> variablesAdded;
	for(unsigned int i=0;i<genericAtom->getTermsSize();++i){
		Term* genericTerm=genericAtom->getTerm(i);
		Term* termToMatch=templateAtom->getTerm(i);
		if (termToMatch->getIndex() == genericTerm->getIndex()) continue;
		if(!matchTerm(genericTerm,termToMatch,assignInTerm,variablesAdded,ruleInformation))
			return false;
	}

	//TODO TEST LINEAR SCANNING THE ARRAY
	for(auto variable:variablesAdded){
		currentAssignment[variable]=assignInTerm[variable];
	}

	return true;

}

/*
 * For each builtin atom that the bind variable(with local index=index) is the last variable evaluated in the builtin, check if the builtin is satisfied. If the
 * evaluation of builtin is false the match of the term, then the match of the atom fail
 */
bool AtomSearcher::evaluateFastBuiltin(const RuleInformation& ruleInformation,index_object index, var_assignment& varAssignment, Term* genericTerm) {
	for (auto builtin : ruleInformation.getBounderBuiltin(index)) {
//		Atom* groundBuiiltin1 = nullptr;
//		builtin->ground(currentAssignment, groundBuiiltin1);
		varAssignment[index] = genericTerm;
		bool evaluation = builtin->groundAndEvaluate(varAssignment);
//		delete groundBuiiltin1;
		if (!evaluation) {
			return false;
		}
	}
	return true;
}

bool AtomSearcher::matchTerm(Term *genericTerm, Term *termToMatch, var_assignment& varAssignment,vector<index_object>& addedVariables,const RuleInformation& ruleInformation){

	TermType termToMatchType=termToMatch->getType();
	TermType genericTermType=genericTerm->getType();
	if((termToMatchType==TermType::NUMERIC_CONSTANT || termToMatchType==TermType::STRING_CONSTANT || termToMatchType==TermType::SYMBOLIC_CONSTANT))
		return false;
	else if (termToMatchType==TermType::VARIABLE) {
		index_object index=termToMatch->getLocalVariableIndex();
		if(ruleInformation.isCreatedDictionaryIntersection(index) && !ruleInformation.countInDictionaryIntersection(index,genericTerm)){
			return false;
		}
		Term* term=varAssignment[index];
		if(term!=nullptr){
			if( term->getIndex() == genericTerm->getIndex())
				return true;
			else
				return false;
		}

		if(ruleInformation.isBounderBuiltin(index)){
			if(!evaluateFastBuiltin(ruleInformation, index, varAssignment, genericTerm))
				return false;
		}

		varAssignment[index]=genericTerm;
		addedVariables.push_back(index);
		return true;
	}
	else if (termToMatchType==TermType::ANONYMOUS) return true;

	else if(termToMatchType==TermType::ARITH){
		Term *new_term=termToMatch->substitute(varAssignment);
		assert_msg(new_term->isGround(),"Arith term not safe");
		termToMatch=new_term->calculate();
	}

	else if(genericTermType==TermType::FUNCTION){

		if(termToMatchType!=TermType::FUNCTION) return false;
		if(termToMatch->getName().compare(genericTerm->getName()) != 0)return false;
		if(termToMatch->getTermsSize() != genericTerm->getTermsSize())return false;
		for(unsigned int i=0;i<genericTerm->getTermsSize();++i)
			if(!matchTerm(genericTerm->getTerm(i),termToMatch->getTerm(i),varAssignment,addedVariables,ruleInformation))
				return false;

		return true;
	}

	return false;

}



/****************************************************** BASE ATOM SEARCHER ***************************************************/

void BaseAtomSearcher::firstMatch(unsigned id,Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation) {
	GeneralIterator* currentMatch=computeGenericIterator(templateAtom,ruleInformation);
	if(computeMatch(currentMatch,templateAtom,currentAssignment,atomFound,ruleInformation)){
		delete resultVector[id];
		resultVector[id]=currentMatch;
		return;
	}
	delete currentMatch;

}

bool BaseAtomSearcher::computeMatch(GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(currentMatch->currentItem(),templateAtom,currentAssignment,ruleInformation)){
			atomFound=currentMatch->currentItem();
			return true;
		}
	}
	atomFound=nullptr;
	return false;
}

void BaseAtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation) {
	GeneralIterator* currentMatch=resultVector[id];
	currentMatch->next();
	computeMatch(currentMatch,templateAtom,currentAssignment,atomFound,ruleInformation);

}

Atom* BaseAtomSearcher::findGroundAtom(Atom *atom){
	for(auto genericAtom:(*table)){
		if(*genericAtom==*atom){
			return genericAtom;
		}
	}
	return nullptr;
}

/****************************************************** SINGLE TERM ATOM SEARCH ***************************************************/

int SingleTermAtomSearcher::manageIndex(Atom* templateAtom, const RuleInformation& ruleInformation) {
	vector<pair<int,index_object>> possibleTableToSearch;
	for(unsigned int i=0;i<templateAtom->getTermsSize();++i){
		Term* t=templateAtom->getTerm(i);
		if(t->isGround())
			possibleTableToSearch.push_back({i,t->getIndex()});
	}

	int indexSelected=-1;
	unsigned size=possibleTableToSearch.size();

	if(size==0)
		return indexSelected;

	if(size==1)
		indexSelected=possibleTableToSearch.front().first;
	else
		indexSelected=selectBestIndex(possibleTableToSearch);
	if(!isUpdatedSearchingTable(indexSelected))
		updateIndexMaps(indexSelected);
	return indexSelected;
}

//int SingleTermAtomSearcher::computePossibleIndexingTermTable(const vector<pair<int,index_object>>& possibleTableToSearch){
//	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser])
//		for(unsigned int i=0;i<possibleTableToSearch.size();++i){
//			if(possibleTableToSearch[i].first==indexingTermSetByUser)
//				return indexingTermSetByUser;
//			if(possibleTableToSearch[i].first>indexingTermSetByUser)
//				return -1;
//		}
//	return -1;
//}

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

//FIXME isUpdated
void SingleTermMapAtomSearcher::add(Atom* atom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Add index "+predicate->getName());
#endif
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(isUpdatedSearchingTable(i)){
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

//FIXME isUpdated
void SingleTermMapAtomSearcher::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(isUpdatedSearchingTable(i)){
			index_object termIndex=atom->getTerm(i)->getIndex();
			if(searchingTables[i].count(termIndex))
				searchingTables[termIndex][i].erase(atom);
		}
	}
}

Atom* SingleTermMapAtomSearcher::findGroundAtom(Atom *atom){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Find "+predicate->getName());
#endif
	if (defaultIndexingTerm==-1)
		defaultIndexingTerm=0;
	if(!isUpdatedSearchingTable(defaultIndexingTerm))
		updateIndexMaps(defaultIndexingTerm);

	index_object term = atom->getTerm(defaultIndexingTerm)->getIndex();
	AtomTable* matchingTable=&searchingTables[defaultIndexingTerm][term];

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
//	int index=computePossibleIndexingTermTable(possibleTableToSearch);
//	if(index!=-1) return index;
	int index=-1;

	unsigned minSize=INT_MAX;
	for(auto it=possibleTableToSearch.begin();it!=possibleTableToSearch.end();++it){
		if(isUpdatedSearchingTable((*it).first)){
			unsigned currentSize=(searchingTables[(*it).first][(*it).second]).size();
			if(minSize>currentSize){
				minSize=currentSize;
				index=(*it).first;
			}
		}
	}

	if(index!=-1)
		return index;
	return possibleTableToSearch.front().first;
	//return getPositionWithBestSelectivity(possibleTableToSearch);
}

GeneralIterator* SingleTermMapAtomSearcher::computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	int indexingTerm=manageIndex(templateAtom,ruleInformation);
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

void SingleTermMapAtomSearcher::updateIndexMaps(unsigned int indexingTerm){
#ifdef DEBUG_ATOM_SEARCHER
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif

#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Create index "+predicate->getName()+" index "+boost::lexical_cast<string>(indexingTerm));
#endif
	if(defaultIndexingTerm==-1)
		defaultIndexingTerm=indexingTerm;

	unsigned& lastUpdateIndex=lastUpdateIndices[indexingTerm];
	for (;lastUpdateIndex<table->size();++lastUpdateIndex) {
		Atom *a=(*table)[lastUpdateIndex];
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

int BinderSelector1::select(Atom* templateAtom,
		const RuleInformation& ruleInformation,
		vector<pair<int, index_object> >& possibleTableToSearch,
		vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection,
		SingleTermAtomSearcher* atomSearcher) {

	int indexSelected=-1;
	unsigned size=possibleTableToSearch.size();

	if(size==0){
		int min=INT_MAX;
		for(auto var:bindVariablesWithCreatedIntersection){
			int currentSize=ruleInformation.getDictionaryIntersectionSize(var.second);
			if(currentSize<min){
				min=currentSize;
				indexSelected=var.first;
			}
		}
	}
	else if(size==1)
		indexSelected=possibleTableToSearch.front().first;
	else
		indexSelected=atomSearcher->selectBestIndex(possibleTableToSearch);

	if(indexSelected>=0 && !atomSearcher->isUpdatedSearchingTable(indexSelected))
		atomSearcher->updateIndexMaps(indexSelected);
	return indexSelected;
}


int BinderSelector2::select(Atom* templateAtom,
		const RuleInformation& ruleInformation,
		vector<pair<int, index_object> >& possibleTableToSearch,
		vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection,
		SingleTermAtomSearcher* atomSearcher) {

	int indexSelected=-1;
	unsigned size=possibleTableToSearch.size();
	if(size==0){
		for(auto var:bindVariablesWithCreatedIntersection){
			if(atomSearcher->isUpdatedSearchingTable(var.first)){
				return var.first;
			}
		}
	}
	else if(size==1)
		indexSelected=possibleTableToSearch.front().first;
	else
		indexSelected=atomSearcher->selectBestIndex(possibleTableToSearch);

	if(indexSelected>=0 && !atomSearcher->isUpdatedSearchingTable(indexSelected))
		atomSearcher->updateIndexMaps(indexSelected);

	return indexSelected;

}

int BinderSelector3::select(Atom* templateAtom,
		const RuleInformation& ruleInformation,
		vector<pair<int, index_object> >& possibleTableToSearch,
		vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection,
		SingleTermAtomSearcher* atomSearcher) {

	int indexSelected=-1;
	unsigned size=possibleTableToSearch.size();
	if(size==0){
		if(bindVariablesWithCreatedIntersection.size()>0){
				auto element=bindVariablesWithCreatedIntersection.front();
				if(PredicateExtTable::getInstance()->getPredicateExt(templateAtom->getPredicate())->getPredicateInformation()->getSelectivity(element.first)
						>ruleInformation.getDictionaryIntersectionSize(element.second)){
					indexSelected=bindVariablesWithCreatedIntersection.front().first;
				}
		}
	}
	else if(size==1)
		indexSelected=possibleTableToSearch.front().first;
	else
		indexSelected=atomSearcher->selectBestIndex(possibleTableToSearch);

	if(indexSelected>=0 && !atomSearcher->isUpdatedSearchingTable(indexSelected))
		atomSearcher->updateIndexMaps(indexSelected);

	return indexSelected;
}

int BinderSelector4::select(Atom* templateAtom,
		const RuleInformation& ruleInformation,
		vector<pair<int, index_object> >& possibleTableToSearch,
		vector<pair<int,index_object>>& bindVariablesWithCreatedIntersection,
		SingleTermAtomSearcher* atomSearcher) {

	int indexSelected=-1;
	unsigned size=possibleTableToSearch.size();
	if(size==0){
		if(bindVariablesWithCreatedIntersection.size()>0){
			int min=INT_MAX;
			for(auto var:bindVariablesWithCreatedIntersection){
				int currentSize=ruleInformation.getDictionaryIntersectionSize(var.second);
				if(currentSize<min && PredicateExtTable::getInstance()->getPredicateExt(templateAtom->getPredicate())->getPredicateInformation()->getSelectivity(var.first)
						>ruleInformation.getDictionaryIntersectionSize(var.second)){
					min=currentSize;
					indexSelected=var.first;
				}
			}
		}
	}
	else if(size==1)
		indexSelected=possibleTableToSearch.front().first;
	else
		indexSelected=atomSearcher->selectBestIndex(possibleTableToSearch);

	if(indexSelected>=0 && !atomSearcher->isUpdatedSearchingTable(indexSelected))
		atomSearcher->updateIndexMaps(indexSelected);

	return indexSelected;
}

int SingleTermMapDictionaryAtomSearcher::manageIndex(Atom* templateAtom, const RuleInformation& ruleInformation) {
	vector<pair<int,index_object>> possibleTableToSearch;
	vector<pair<int,index_object>> bindVariablesWithCreatedIntersection;
	for(unsigned int i=0;i<templateAtom->getTermsSize();++i){
		Term* t=templateAtom->getTerm(i);
		if(t->isGround())
			possibleTableToSearch.push_back({i,t->getIndex()});
		else if(ruleInformation.isCreatedDictionaryIntersection(t->getLocalVariableIndex()))
			bindVariablesWithCreatedIntersection.push_back({i,t->getLocalVariableIndex()});
	}

	return binderSelector->select(templateAtom,ruleInformation,possibleTableToSearch,bindVariablesWithCreatedIntersection,this);
}

void SingleTermMapDictionaryAtomSearcher::setBinderSelector() {
	binderSelector=new BinderSelector3();
}

GeneralIterator* SingleTermMapDictionaryAtomSearcher::computeGenericIterator(Atom* templateAtom, const RuleInformation& ruleInformation) {
	int indexingTerm=manageIndex(templateAtom,ruleInformation);
	GeneralIterator* currentMatch;

	if(indexingTerm!=-1){
		if(templateAtom->getTerm(indexingTerm)->getType()==VARIABLE){
			currentMatch=new MultipleIterators();
			index_object localIndexVar=templateAtom->getTerm(indexingTerm)->getLocalVariableIndex();
			for(auto it=ruleInformation.getDictionaryIntersectionBegin(localIndexVar);it!=ruleInformation.getDictionaryIntersectionEnd(localIndexVar);++it){
				index_object term = (*it)->getIndex();
				if(!searchingTables[indexingTerm][term].empty()){
					GeneralIterator* iterator=new UnorderedSetIterator(searchingTables[indexingTerm][term].begin() ,searchingTables[indexingTerm][term].end());
					currentMatch->add(iterator);
				}
			}
		}
		else{
			index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
			AtomTable* matchingTable=&searchingTables[indexingTerm][term];
			currentMatch=new UnorderedSetIterator(matchingTable->begin(),matchingTable->end());
		}
	}
	else
		currentMatch=new VectorIterator(table->begin(), table->end());
	return currentMatch;
}


/****************************************************** SINGLE TERM MULTI MAP ATOM SEARCH ***************************************************/

void SingleTermMultiMapAtomSearcher::add(Atom* atom) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Add index "+predicate->getName());
#endif
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(isUpdatedSearchingTable(i)){
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
		if(isUpdatedSearchingTable(i)){
			index_object termIndex=atom->getTerm(i)->getIndex();
			auto pair=searchingTables[i].equal_range(termIndex);
			for(auto it=pair.first;it!=pair.second;++it){
				if(*(it->second)==*atom)
					searchingTables[i].erase(it);
			}
		}
	}
}

Atom* SingleTermMultiMapAtomSearcher::findGroundAtom(Atom *atom){
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Find "+predicate->getName());
#endif
	if (defaultIndexingTerm==-1)
		defaultIndexingTerm=0;
	if(isUpdatedSearchingTable(defaultIndexingTerm))
		updateIndexMaps(defaultIndexingTerm);


	index_object term = atom->getTerm(defaultIndexingTerm)->getIndex();
	auto pair=searchingTables[defaultIndexingTerm].equal_range(term);

	for(auto it=pair.first;it!=pair.second;++it)
		if(*(it->second)==*atom)
			return it->second;

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
//	int index=computePossibleIndexingTermTable(possibleTableToSearch);
//	if(index!=-1) return index;
	int index=-1;

	unsigned minSize=INT_MAX;
	for(auto it=possibleTableToSearch.begin();it!=possibleTableToSearch.end();++it){
		if(isUpdatedSearchingTable((*it).first)){
			unsigned currentSize=searchingTables[(*it).first].count((*it).second);
			if(minSize>currentSize){
				minSize=currentSize;
				index=(*it).first;
			}
		}
	}

	if(index!=-1)
		return index;
	return possibleTableToSearch.front().first;
//	return getPositionWithBestSelectivity(possibleTableToSearch);
}


GeneralIterator* SingleTermMultiMapAtomSearcher::computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation) {
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	int indexingTerm=manageIndex(templateAtom,ruleInformation);
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

void SingleTermMultiMapAtomSearcher::updateIndexMaps(unsigned int indexingTerm){
#ifdef DEBUG_ATOM_SEARCHER
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->start("Compute iterator "+predicate->getName());
#endif
	if(defaultIndexingTerm==-1)
		defaultIndexingTerm=indexingTerm;

	unsigned& lastUpdateIndex=lastUpdateIndices[indexingTerm];
	for (;lastUpdateIndex<table->size();++lastUpdateIndex) {
		Atom *a=(*table)[lastUpdateIndex];
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		searchingTables[indexingTerm].insert({termIndex,a});
	}
#ifdef DEBUG_RULE_TIME
	Timer::getInstance()->stop("Compute iterator "+predicate->getName());
#endif
}

/****************************************************** HASH SET ATOM SEARCH ***************************************************/

Atom* HashSetAtomSearcher::findGroundAtom(Atom* atom) {
	manageIndex();
	auto atomFound_it=searchingTable.find(atom);
	if(atomFound_it!=searchingTable.end())
		return *atomFound_it;
	return nullptr;
}


/****************************************************** DOUBLE TERM MAP ATOM SEARCH ***************************************************/

//FIXME
void DoubleTermMapAtomSearcher::add(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(isUpdatedSearchingTable(i)){
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

//FIXME
void DoubleTermMapAtomSearcher::remove(Atom* atom) {
	for (unsigned int i = 0; i < predicate->getArity(); ++i) {
		if(isUpdatedSearchingTable(i)){
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

int DoubleTermMapAtomSearcher::manageIndexGround() {
	int tableToSearch = 0;
	for (unsigned int i = 0; i < predicate->getArity(); ++i)
		if(isUpdatedSearchingTable(i)){
			tableToSearch = i;
			break;
		}
	if (!isUpdatedSearchingTable(tableToSearch))
		updateIndexMaps(tableToSearch);

	return tableToSearch;
}

Atom* DoubleTermMapAtomSearcher::findGroundAtom(Atom *atom){
	if (defaultIndexingTerm==-1)
		defaultIndexingTerm=0;

	if (!isUpdatedSearchingTable(defaultIndexingTerm))
		updateIndexMaps(defaultIndexingTerm);

	index_object term = atom->getTerm(defaultIndexingTerm)->getIndex();
	Multimap_Atom::iterator start;
	Multimap_Atom::iterator end;

	if(unsigned(defaultIndexingTerm) < predicate->getArity()-1){
		index_object nextTerm=atom->getTerm(defaultIndexingTerm+1)->getIndex();
		auto pair=searchingTables[defaultIndexingTerm][term].equal_range(nextTerm);
		start=pair.first;
		end=pair.second;
	}
	else{
		start=searchingTables[defaultIndexingTerm][term].begin();
		end=searchingTables[defaultIndexingTerm][term].end();
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
		if(!isUpdatedSearchingTable(indexSelected))
			updateIndexMaps(indexSelected);
	}
	return indexSelected;
}

//int DoubleTermMapAtomSearcher::computePossibleIndexingTermTable(const vector<pair<int,pair<index_object,int>>>& possibleTableToSearch){
//	if(indexingTermSetByUser>-1 && createdSearchingTables[indexingTermSetByUser])
//		for(unsigned int i=0;i<possibleTableToSearch.size();++i){
//			if(possibleTableToSearch[i].first==indexingTermSetByUser)
//				return indexingTermSetByUser;
//			if(possibleTableToSearch[i].first>indexingTermSetByUser)
//				return -1;
//		}
//	return -1;
//}

unsigned int DoubleTermMapAtomSearcher::selectBestIndex(const vector<pair<int,pair<index_object,int>>>& possibleTableToSearch){
	/* The choosing policy is the following:
		- if the position set by the user can be chosen, then chose that one
		- if more positions of indexing are available then chose the data structure
			with the smaller size
		- if none indexing structure has been created (among the ones allowed), then chose the position
		with the best selectivity among the position of indexing available
	*/
//	int index=computePossibleIndexingTermTable(possibleTableToSearch);
//	if(index!=-1) return index;
	int index=-1;

	unsigned minSize=INT_MAX;
	for(auto it=possibleTableToSearch.begin();it!=possibleTableToSearch.end();++it){
		if(unsigned((*it).first)<lastUpdateIndices.size() && isUpdatedSearchingTable((*it).first)){
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
	return possibleTableToSearch.front().first;

//	index=0;
//	if(possibleTableToSearch.size()==1)
//		return (*possibleTableToSearch.begin()).first;
//	unsigned maxSelectivity=0;
//	PredicateInformation* predInfo=PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation();
//	for(auto pair:possibleTableToSearch){
//		unsigned selectivity=predInfo->getSelectivity(pair.first);
//		if(selectivity>maxSelectivity){
//			maxSelectivity=selectivity;
//			index=pair.first;
//		}
//	}
//	return index;
}

GeneralIterator* DoubleTermMapAtomSearcher::computeGenericIterator(Atom* templateAtom,const RuleInformation& ruleInformation) {
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

void DoubleTermMapAtomSearcher::updateIndexMaps(unsigned int indexingTerm){
#ifdef DEBUG_ATOM_SEARCHER
	cout<<"Predicate: "<<predicate->getName()<<" Created Index on term: "<<indexingTerm<<endl;
#endif
	if(defaultIndexingTerm==-1 || defaultIndexingTerm==predicate->getArity()-1)
		defaultIndexingTerm=indexingTerm;

	unsigned& lastUpdateIndex=lastUpdateIndices[indexingTerm];
	for (;lastUpdateIndex<table->size();++lastUpdateIndex) {
		Atom* a=(*table)[lastUpdateIndex];
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


}
}


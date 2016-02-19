/*
 * IndexingStructure.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: jessica
 */

#include "IndexingStructure.h"
#include "../../util/Options.h"

namespace DLV2 {
namespace grounder {

/******************************************************* ATOM SEARCHER ***************************************************/

bool AtomSearcher::checkMatch(unsigned int id,Atom *genericAtom, Atom *templateAtom, var_assignment& currentAssignment,const RuleInformation& ruleInformation,const vector<unsigned>& outputVariables){
	// Checks the match for each term and, if all the terms match, updates the current assignment accordingly
	var_assignment assignInTerm(currentAssignment);

	vector<index_object> variablesAdded;
	for(unsigned int i=0;i<genericAtom->getTermsSize();++i){
		Term* genericTerm=genericAtom->getTerm(i);
		Term* termToMatch=templateAtom->getTerm(i);
		if(termToMatch->getIndex() == genericTerm->getIndex()) continue;
		if(!matchTerm(genericTerm,termToMatch,assignInTerm,variablesAdded,ruleInformation)){
			return false;
		}
	}

	if(!outputVariables.empty()){
		vector<unsigned> outputVariablesTerms;
		outputVariablesTerms.reserve(outputVariables.size());
		for(auto i:outputVariables){
			outputVariablesTerms.push_back(genericAtom->getTerm(i)->getIndex());
		}

		if(!outputVariablesValues[id].insert(outputVariablesTerms).second){
			return false;
		}
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
		varAssignment[index] = genericTerm;
		bool evaluation = builtin->groundAndEvaluate(varAssignment);
		if (!evaluation) {
			return false;
		}
	}
	return true;
}

bool AtomSearcher::matchTerm(Term *generic, Term *toMatch, var_assignment& varAssignment,vector<index_object>& addedVariables,const RuleInformation& ruleInformation){
	list<pair<Term*,Term*>> termsToProcess;
	termsToProcess.push_back({generic,toMatch});
	while(!termsToProcess.empty()){
		auto pair=termsToProcess.back();
		termsToProcess.pop_back();
		Term* genericTerm=pair.first;
		Term* termToMatch=pair.second;
		TermType genericTermType=genericTerm->getType();
		TermType termToMatchType=termToMatch->getType();
		if(termToMatchType==TermType::NUMERIC_CONSTANT || termToMatchType==TermType::STRING_CONSTANT || termToMatchType==TermType::SYMBOLIC_CONSTANT)
			return false;
		else if (termToMatchType==TermType::VARIABLE) {
			index_object index=termToMatch->getLocalVariableIndex();
			if(ruleInformation.isCreatedDictionaryIntersection(index) && !ruleInformation.countInDictionaryIntersection(index,genericTerm)){
				return false;
			}
			Term* term=varAssignment[index];
			if(term!=nullptr){
				if( term->getIndex() == genericTerm->getIndex())
					continue;
				return false;
			}

			if(ruleInformation.isBounderBuiltin(index)){
				if(!evaluateFastBuiltin(ruleInformation, index, varAssignment, genericTerm))
					return false;
			}

			varAssignment[index]=genericTerm;
			addedVariables.push_back(index);
			continue;
		}
		else if (termToMatchType==TermType::ANONYMOUS) continue;

		else if(termToMatchType==TermType::ARITH){
			Term *new_term=termToMatch->substitute(varAssignment);
			assert_msg(new_term->isGround(),"Arith term not safe");
			termToMatch=new_term->calculate();
			return false;
		}
		else if(genericTermType==TermType::FUNCTION){
			if(termToMatchType!=TermType::FUNCTION) return false;
			if(termToMatch->getName().compare(genericTerm->getName()) != 0)return false;
			if(termToMatch->getTermsSize() != genericTerm->getTermsSize())return false;
			for(unsigned int i=0;i<genericTerm->getTermsSize();++i){
				if(genericTerm->getTerm(i)->getIndex() == termToMatch->getTerm(i)->getIndex() )	continue;
				termsToProcess.push_back({genericTerm->getTerm(i),termToMatch->getTerm(i)});
			}
		}
		else
			return false;
	}
	return true;
}

//bool AtomSearcher::matchTerm(Term *genericTerm, Term *termToMatch, var_assignment& varAssignment,vector<index_object>& addedVariables,const RuleInformation& ruleInformation){
//	TermType termToMatchType=termToMatch->getType();
//	TermType genericTermType=genericTerm->getType();
//	if((termToMatchType==TermType::NUMERIC_CONSTANT || termToMatchType==TermType::STRING_CONSTANT || termToMatchType==TermType::SYMBOLIC_CONSTANT))
//		return false;
//	else if (termToMatchType==TermType::VARIABLE) {
//		index_object index=termToMatch->getLocalVariableIndex();
//		if(ruleInformation.isCreatedDictionaryIntersection(index) && !ruleInformation.countInDictionaryIntersection(index,genericTerm)){
//			return false;
//		}
//		Term* term=varAssignment[index];
//		if(term!=nullptr){
//			if( term->getIndex() == genericTerm->getIndex())
//				return true;
//			else
//				return false;
//		}
//
//		if(ruleInformation.isBounderBuiltin(index)){
//			if(!evaluateFastBuiltin(ruleInformation, index, varAssignment, genericTerm))
//				return false;
//		}
//
//		varAssignment[index]=genericTerm;
//		addedVariables.push_back(index);
//		return true;
//	}
//	else if (termToMatchType==TermType::ANONYMOUS) return true;
//
//	else if(termToMatchType==TermType::ARITH){
//		Term *new_term=termToMatch->substitute(varAssignment);
//		assert_msg(new_term->isGround(),"Arith term not safe");
//		termToMatch=new_term->calculate();
//	}
//
//	else if(genericTermType==TermType::FUNCTION){
//
//		if(termToMatchType!=TermType::FUNCTION) return false;
//		if(termToMatch->getName().compare(genericTerm->getName()) != 0)return false;
//		if(termToMatch->getTermsSize() != genericTerm->getTermsSize())return false;
//		for(unsigned int i=0;i<genericTerm->getTermsSize();++i){
//			if(genericTerm->getTerm(i)->getIndex() == termToMatch->getTerm(i)->getIndex() ) continue;
//			if(!matchTerm(genericTerm->getTerm(i),termToMatch->getTerm(i),varAssignment,addedVariables,ruleInformation))
//				return false;
//		}
//
//		return true;
//	}
//
//	return false;
//
//}

void AtomSearcher::firstMatch(unsigned id, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation,IndexingStructure* indexingStructure,unsigned arg,const vector<unsigned>& outputVariables,const pair<SearchType,unsigned>& searchSpecification) {
	GeneralIterator* currentMatch=indexingStructure->computeMatchIterator(templateAtom,ruleInformation,searchSpecification,arg);
	outputVariablesValues[id].clear();
	if(computeMatch(id,currentMatch,templateAtom,currentAssignment,atomFound,ruleInformation,outputVariables)){
		delete resultVector[id];
		resultVector[id]=currentMatch;
		return;
	}
	delete currentMatch;
}

bool AtomSearcher::computeMatch(unsigned int id,GeneralIterator* currentMatch, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation,const vector<unsigned>& outputVariables){
	for(;!currentMatch->isDone();currentMatch->next()){
		if (checkMatch(id,currentMatch->currentItem(),templateAtom,currentAssignment,ruleInformation,outputVariables)){
			atomFound=currentMatch->currentItem();
			return true;
		}
	}
	atomFound=nullptr;
	return false;
}

void AtomSearcher::nextMatch(unsigned int id, Atom *templateAtom, var_assignment& currentAssignment, Atom*& atomFound,const RuleInformation& ruleInformation,const vector<unsigned>& outputVariables) {
	GeneralIterator* currentMatch=resultVector[id];
	currentMatch->next();
	computeMatch(id,currentMatch,templateAtom,currentAssignment,atomFound,ruleInformation,outputVariables);

}

Atom* AtomSearcher::findGroundAtom(Atom *atom,IndexingStructure* indexingStructure){
	return indexingStructure->find(atom);
}

IndexingStructure* AtomSearcher::getIndexingStructure(unsigned type, vector<unsigned>* indexingTerms) {
	for(auto indexingStruct:indexingStructures){
		if(indexingStruct->getType()==type){
			if(indexingTerms==nullptr)
				return indexingStruct;
			else{
				vector<unsigned> indexingStructIndexingTerms=indexingStruct->getIndexingTerms();
				if(indexingStructIndexingTerms.size()!=indexingTerms->size())
					return nullptr;
				for(unsigned i=0;i<indexingTerms->size();++i){
					if(indexingStructIndexingTerms[i]!=(*indexingTerms)[i])
						return nullptr;
				}
				return indexingStruct;
			}
		}
	}
	return nullptr;
}

IndexingStructure* AtomSearcher::getIndexingStructure(vector<unsigned>* indexingTerms) {
	for(auto indexingStruct:indexingStructures){
		if(indexingTerms==nullptr)
			return indexingStruct;
		else{
			vector<unsigned> indexingStructIndexingTerms=indexingStruct->getIndexingTerms();
			if(indexingStructIndexingTerms.size()!=indexingTerms->size())
				return nullptr;
			for(unsigned i=0;i<indexingTerms->size();++i){
				if(indexingStructIndexingTerms[i]!=(*indexingTerms)[i])
					return nullptr;
			}
			return indexingStruct;
		}
	}
	return nullptr;
}

AtomSearcher::~AtomSearcher() {
	for(auto& it:resultVector)
		delete it;

	for(auto& indexingStructure: indexingStructures){
		delete indexingStructure;
		indexingStructure=0;
	}
};

/******************************************************** Indexing Structure (Vector) **************************************************/

Atom* IndexingStructure::find(Atom* atom) {
	for(auto atom1:(*table)){
		if(*atom1==*atom){
			return atom1;
		}
	}
	return nullptr;
}

/******************************************************** Unordered Set **************************************************/

Atom* UnorderedSet::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	auto atomFound_it=indexingStructure.find(atom);
	if(atomFound_it!=indexingStructure.end())
		return *atomFound_it;
	return nullptr;
}

void UnorderedSet::update() {
	for (;lastUpdate<table->size();++lastUpdate)
		indexingStructure.insert((*table)[lastUpdate]);
}


/******************************************************** Unordered Map of Unordered Set **************************************************/

void UnorderedMapOfUnorderedSet::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	if(lastUpdate==table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		if(indexingStructure.count(termIndex))
			indexingStructure[termIndex].insert(atom);
		else{
			indexingStructure.emplace(termIndex,AtomTable({atom}));
		}
	}
}

Atom* UnorderedMapOfUnorderedSet::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();

	auto atomFound_it=indexingStructure[term].find(atom);
	if(atomFound_it!=indexingStructure[term].end()){
		return *atomFound_it;
	}
	return nullptr;
}

void UnorderedMapOfUnorderedSet::update() {
	unsigned i=indexingTerms[0];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		if(!indexingStructure.count(termIndex)){
			AtomTable values;
//			values.reserve(table->size()/PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation()->getSelectivity(indexingTerm));
			values.insert(a);
			indexingStructure.insert({termIndex,values});
		}
		else
			indexingStructure[termIndex].insert(a);
	}
}

GeneralIterator* UnorderedMapOfUnorderedSet::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification,unsigned arg) {
	if(lastUpdate<table->size())
		update();

	int indexingTerm=indexingTerms[0];
	GeneralIterator* currentMatch;

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	AtomTable* matchingTable=&indexingStructure[term];
	currentMatch=new UnorderedSetIterator(matchingTable->begin(),matchingTable->end());
	return currentMatch;

}

/******************************************************** Unordered Map of Vector **************************************************/

void UnorderedMapOfVector::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	if(lastUpdate==table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		if(indexingStructure.count(termIndex))
			indexingStructure[termIndex].push_back(atom);
		else{
			indexingStructure.emplace(termIndex,vector<Atom*>({atom}));
		}
	}
}

Atom* UnorderedMapOfVector::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();
	vector<Atom*>* matchingTable=&indexingStructure[term];

	for(auto atom1:(*matchingTable)){
		if(*atom1==*atom){
			return atom1;
		}
	}
	return nullptr;
}

void UnorderedMapOfVector::update() {
	unsigned i=indexingTerms[0];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		if(!indexingStructure.count(termIndex)){
			vector<Atom*> values;
//			values.reserve(table->size()/PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation()->getSelectivity(indexingTerm));
			values.push_back(a);
			indexingStructure.insert({termIndex,values});
		}
		else
			indexingStructure[termIndex].push_back(a);
	}
}

GeneralIterator* UnorderedMapOfVector::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification,unsigned arg) {
	if(lastUpdate<table->size())
		update();

	int indexingTerm=indexingTerms[0];
	GeneralIterator* currentMatch;

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	vector<Atom*>* matchingTable=&indexingStructure[term];
	currentMatch=new VectorIterator(matchingTable->begin(),matchingTable->end());

	return currentMatch;
}

/******************************************************** Unordered Map of History Vector **************************************************/

//TODO for full index version
void UnorderedMapOfHistoryVector::add(Atom* atom) {

}

Atom* UnorderedMapOfHistoryVector::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();
	AtomHistoryVector& matchingTable=indexingStructure[term];

	for(auto atom1:matchingTable){
		if(*atom1==*atom){
			return atom1;
		}
	}
	return nullptr;
}

void UnorderedMapOfHistoryVector::update() {
	unsigned i=indexingTerms[0];
	unsigned currentIndexIteration=table->getIndexIteration();
	unsigned currentIteration=table->getCurrentIteration();
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		unsigned atomIteration=(lastUpdate<currentIndexIteration)?currentIteration-1:currentIteration;
		if(!indexingStructure.count(termIndex)){
			AtomHistoryVector values;
//			values.reserve(table->size()/PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation()->getSelectivity(indexingTerm));
			values.push_back_iteration(a,atomIteration);
			indexingStructure.insert({termIndex,values});
		}
		else
			indexingStructure[termIndex].push_back_iteration(a,atomIteration);
	}
}


GeneralIterator* UnorderedMapOfHistoryVector::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification,unsigned arg) {
	if(lastUpdate<table->size())
		update();

	GeneralIterator* currentMatch;
	int indexingTerm=indexingTerms[0];
	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	AtomHistoryVector* matchingTable=&indexingStructure[term];

	auto it=matchingTable->getElements(searchSpecification.first,searchSpecification.second);
	currentMatch=new VectorIteratorIndex(it.first,it.second,matchingTable);

	return currentMatch;
}

/******************************************************** Unordered Unordered Map Of Pair HistoryVector **************************************************/

//TODO for full index version
void UnorderedMapOfPairHistoryVector::add(Atom* atom) {

}

Atom* UnorderedMapOfPairHistoryVector::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	unsigned next=indexingTerms[1];

	index_object term = atom->getTerm(i)->getIndex();
	index_object nextTerm=atom->getTerm(next)->getIndex();

	AtomHistoryVector& matchingTable=indexingStructure[{term,nextTerm}];

	for(auto atom1:matchingTable){
		if(*atom1==*atom){
			return atom1;
		}
	}
	return nullptr;
}

void UnorderedMapOfPairHistoryVector::update() {
	unsigned i=indexingTerms[0];
	unsigned next=indexingTerms[1];
	unsigned currentIndexIteration=table->getIndexIteration();
	unsigned currentIteration=table->getCurrentIteration();
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		index_object nextTermIndex=a->getTerm(next)->getIndex();
		unsigned atomIteration=(lastUpdate<currentIndexIteration)?currentIteration-1:currentIteration;
		if(!indexingStructure.count({termIndex,nextTermIndex})){
			AtomHistoryVector values;
//			values.reserve(table->size()/PredicateExtTable::getInstance()->getPredicateExt(predicate)->getPredicateInformation()->getSelectivity(indexingTerm));
			values.push_back_iteration(a,atomIteration);
			indexingStructure.insert({{termIndex,nextTermIndex},values});
		}
		else
			indexingStructure[{termIndex,nextTermIndex}].push_back_iteration(a,atomIteration);
	}
}


GeneralIterator* UnorderedMapOfPairHistoryVector::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification,unsigned arg) {
	if(lastUpdate<table->size())
		update();

	GeneralIterator* currentMatch;
	unsigned i=indexingTerms[0];
	unsigned next=indexingTerms[1];

	index_object term = templateAtom->getTerm(i)->getIndex();
	index_object nextTerm=templateAtom->getTerm(next)->getIndex();

	AtomHistoryVector& matchingTable=indexingStructure[{term,nextTerm}];

	auto it=matchingTable.getElements(searchSpecification.first,searchSpecification.second);
	currentMatch=new VectorIteratorIndex(it.first,it.second,&matchingTable);

	return currentMatch;
}


/******************************************************** Unordered Multi Map **************************************************/

void UnorderedMultiMap::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	if(lastUpdate==table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		indexingStructure.insert({termIndex,atom});
	}
}

Atom* UnorderedMultiMap::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	index_object term = atom->getTerm(i)->getIndex();
	auto matchingTable=indexingStructure.equal_range(term);

	for(auto it=matchingTable.first;it!=matchingTable.second;++it){
		if(*((*it).second)==*atom){
			return (*it).second;
		}
	}
	return nullptr;
}

void UnorderedMultiMap::update() {
	unsigned i=indexingTerms[0];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom *a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(i)->getIndex();
		indexingStructure.insert({termIndex,a});
	}
}

GeneralIterator* UnorderedMultiMap::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification,unsigned arg) {
	if(lastUpdate<table->size())
		update();

	int indexingTerm=indexingTerms[0];
	GeneralIterator* currentMatch;

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	auto matchingTable=indexingStructure.equal_range(term);
	currentMatch=new UnorderedMultiMapIterator(matchingTable.first,matchingTable.second);

	return currentMatch;
}

/******************************************************** Unordered Map of Unordered Multi Map **************************************************/

void UnorderedMapOfUnorderedMultimap::add(Atom* atom) {
	unsigned i=indexingTerms[0];
	unsigned next=indexingTerms[1];
	if(lastUpdate<table->size()){
		index_object termIndex=atom->getTerm(i)->getIndex();
		int nextTermIndex=-1;
		if(next>0)
			nextTermIndex=atom->getTerm(next)->getIndex();
		if(indexingStructure.count(termIndex)){
			if(nextTermIndex>-1)
				indexingStructure[termIndex].insert({nextTermIndex,atom});
			else
				indexingStructure[termIndex].insert({termIndex,atom});
		}
		else{
			Multimap_Atom values;
			if(nextTermIndex>-1)
				values.insert({nextTermIndex,atom});
			else
				values.insert({termIndex,atom});
			indexingStructure.insert({termIndex,values});
		}
	}
}

Atom* UnorderedMapOfUnorderedMultimap::find(Atom* atom) {
	if(lastUpdate<table->size())
		update();

	unsigned i=indexingTerms[0];
	unsigned next=indexingTerms[1];
	index_object term = atom->getTerm(i)->getIndex();
	Multimap_Atom::iterator start;
	Multimap_Atom::iterator end;

	if(next>0){
		index_object nextTerm=atom->getTerm(next)->getIndex();
		auto pair=indexingStructure[term].equal_range(nextTerm);
		start=pair.first;
		end=pair.second;
	}
	else{
		start=indexingStructure[term].begin();
		end=indexingStructure[term].end();
	}

	for(auto it=start;it!=end;++it){
		if(*(it->second)==*atom)
			return it->second;
	}
	return nullptr;

}

void UnorderedMapOfUnorderedMultimap::update() {
	if(table->empty()) return;
	unsigned indexingTerm=indexingTerms[0];
	unsigned next=indexingTerms[1];
	for (;lastUpdate<table->size();++lastUpdate) {
		Atom* a=(*table)[lastUpdate];
		index_object termIndex=a->getTerm(indexingTerm)->getIndex();
		int nextTermIndex=-1;
		if(next>0)
			nextTermIndex=a->getTerm(next)->getIndex();
		if(indexingStructure.count(termIndex)){
			if(nextTermIndex>-1)
				indexingStructure[termIndex].insert({nextTermIndex,a});
			else
				indexingStructure[termIndex].insert({termIndex,a});
		}
		else{
			Multimap_Atom values;
			if(nextTermIndex>-1)
				values.insert({nextTermIndex,a});
			else
				values.insert({termIndex,a});
			indexingStructure.insert({termIndex,values});
		}
	}
}

GeneralIterator* UnorderedMapOfUnorderedMultimap::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation,const pair<SearchType,unsigned>& searchSpecification,unsigned arg) {
	if(lastUpdate<table->size())
		update();

	unsigned indexingTerm=indexingTerms[0];
	unsigned next=indexingTerms[1];

	index_object term = templateAtom->getTerm(indexingTerm)->getIndex();
	Multimap_Atom::iterator start;
	Multimap_Atom::iterator end;

	Term* nextTerm=templateAtom->getTerm(next);
	if(next>0 && nextTerm->isGround()){ //FIXME avoid to call isGround
		index_object nextTermIndex=nextTerm->getIndex();
		auto pair=indexingStructure[term].equal_range(nextTermIndex);
		start=pair.first;
		end=pair.second;
	}
	else{
		start=indexingStructure[term].begin();
		end=indexingStructure[term].end();
	}
	return new UnorderedMultiMapIterator(start,end);
}

/*************************************************************** Full Index on Single Argument *****************************************************************/

FullIndexingStructure::FullIndexingStructure(AtomHistoryVector* table, Predicate* predicate, AtomSearcher* atomSearcher, bool recursive, unsigned indexType): IndexingStructure(table), predicate(predicate){
    indexingStructures.reserve(predicate->getArity());
    for(unsigned i=0;i<predicate->getArity();++i){
        vector<unsigned> indexingTerm(1,i);
        if(recursive)
			indexingStructures.push_back(new UnorderedMapOfHistoryVector(table,indexingTerm));
        else{
			IndexingStructure* iS=atomSearcher->getIndexingStructure(&indexingTerm);
			if(iS!=nullptr){
				indexingStructures.push_back(iS);
			}
			else{
				if(indexType==MAP)
					indexingStructures.push_back(new UnorderedMapOfUnorderedSet(table,indexingTerm));
				else if(indexType==MAP_VECTOR)
					indexingStructures.push_back(new UnorderedMapOfVector(table,indexingTerm));
				else if(indexType==MAP_HISTORY_VECTOR)
					indexingStructures.push_back(new UnorderedMapOfHistoryVector(table,indexingTerm));

			}
        }
    }
}

void FullIndexingStructure::add(Atom* atom) {
    for(auto indexingStructure: indexingStructures)
        indexingStructure->add(atom);
}

Atom* FullIndexingStructure::find(Atom* atom) {
    return indexingStructures[0]->find(atom);
}

void FullIndexingStructure::update() {
    for (;lastUpdate<table->size();++lastUpdate) {
        Atom* a=(*table)[lastUpdate];
        add(a);
    }
}

GeneralIterator* FullIndexingStructure::computeMatchIterator(Atom* templateAtom, const RuleInformation& ruleInformation, const pair<SearchType, unsigned>& searchSpecification,unsigned arg) {
	if(lastUpdate<table->size())
		update();
	return indexingStructures[arg]->computeMatchIterator(templateAtom,ruleInformation,searchSpecification,arg);
}

} /* namespace grounder */
} /* namespace DLV2 */

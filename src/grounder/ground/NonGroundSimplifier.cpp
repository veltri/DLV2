/*
 * NonGroundSimplifier.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: davide
 */

#include "NonGroundSimplifier.h"
#include "../atom/AggregateAtom.h"

namespace DLV2 {
namespace grounder {

void NonGroundSimplifier::removeSimplifiedLiterals(Rule* r,vector<unsigned> atoms_to_delete, vector<vector<unsigned> >& predicate_searchInsert_table){
	for (auto i : atoms_to_delete) {
		Atom* atom = r->getAtomInBody(i);
		atom->deleteAtoms();
		delete atom;
	}
	sort(atoms_to_delete.begin(),atoms_to_delete.end());
	r->removeInBody(atoms_to_delete);
	for(unsigned i=0;i<atoms_to_delete.size();i++)
		predicate_searchInsert_table.erase(predicate_searchInsert_table.begin()+r->getSizeHead()+(atoms_to_delete[i]-i));
}

bool NonGroundSimplifier::simplifyRule(Rule* r,vector<vector<unsigned> >& predicate_searchInsert_table) {
	vector<unsigned> atoms_to_delete;
	bool boolean;
	int i=0;
	unsigned sizeHead=r->getSizeHead();
	for(auto it=r->getBeginBody();it!=r->getEndBody();it++,i++){
		if(checkPredicateExtensionsNotEmpty(it,i+sizeHead,predicate_searchInsert_table)==SIMPLIFY_RULE)
			return true;
		if(checkOpposite(it+1,r->getEndBody(),it))
			return true;
		if(checkDuplicate(it+1,r->getEndBody(),it))
			atoms_to_delete.push_back(i);
		if(checkFalsity(it)){
			if(!(*it)->isNegative())
				return true;
			atoms_to_delete.push_back(i);
		}
		if((*it)->isAggregateAtom()){
			if(checkAggregateSumCountStringGuard(it,boolean)){
				if(!boolean)
					return true;
				atoms_to_delete.push_back(i);
			}
			if(checkAggregateCountNegativeGuard(it,boolean)){
				if(!boolean)
					return true;
				atoms_to_delete.push_back(i);
			}
			if(checkAggregateAllAggTermShared(r,it,boolean)){
				if(!boolean)
					return true;
				atoms_to_delete.push_back(i);
			}
		}
	}

	removeSimplifiedLiterals(r,atoms_to_delete,predicate_searchInsert_table);
	return false;

}

bool NonGroundSimplifier::simplifyIfPredicateExtensionsEmpty(Rule *r,vector<vector<unsigned> >& predicate_searchInsert_table) {
	unsigned i=r->getSizeHead();
	for(auto it=r->getBeginBody();it!=r->getEndBody();it++,i++)
		if(checkPredicateExtensionsNotEmpty(it,i,predicate_searchInsert_table)==SIMPLIFY_RULE)
			return true;
	return false;
}

Simplify NonGroundSimplifier::checkPredicateExtensionsNotEmpty(vector<Atom*>::const_iterator currentIt, unsigned i,vector<vector<unsigned> >& predicate_searchInsert_table) const {
	Predicate* predicate=(*currentIt)->getPredicate();
	if(predicate==nullptr)
		return NO_SIMPLIFY;
	for(auto tableToSearch:predicate_searchInsert_table[i])
		if(predicateExtTable->getPredicateExt(predicate)->getPredicateExtentionSize(tableToSearch)>0)
			return NO_SIMPLIFY;
	if((*currentIt)->isNegative())
		return SIMPLIFY_ATOM;
	return SIMPLIFY_RULE;
}

bool NonGroundSimplifier::checkDuplicate(vector<Atom*>::const_iterator begin,vector<Atom*>::const_iterator end, vector<Atom*>::const_iterator currentIt) const {
	for(auto it=begin;it!=end;it++)
		if((*it)->equal(*(*currentIt)))
			return true;

	return false;
}

bool NonGroundSimplifier::checkOpposite(vector<Atom*>::const_iterator begin,vector<Atom*>::const_iterator end,vector<Atom*>::const_iterator currentIt) const {
	for(auto it=begin;it!=end;it++)
		if((*(*it))==(*(*currentIt)) && (*it)->isNegative()!=(*currentIt)->isNegative())
			return true;

	return false;
}

bool NonGroundSimplifier::checkFalsity(	vector<Atom*>::const_iterator currentIt) const {
	Atom* atom=*currentIt;
	if(atom->isClassicalLiteral()){
		Predicate* predicate=atom->getPredicate();
		bool isOnlyInBody=StatementDependency::getInstance()->isOnlyInBody(predicate->getIndex());
		if(isOnlyInBody && predicateExtTable->getPredicateExt(predicate)->getPredicateExtentionSize(FACT)==0)
			return true;
	}
	return false;
}

bool NonGroundSimplifier::checkAggregateSumCountStringGuard(vector<Atom*>::const_iterator currentIt,bool& alwaysTrue) const {
	return (*currentIt)->checkAggregateSumCountStringGuard(alwaysTrue);
}

bool NonGroundSimplifier::checkAggregateCountNegativeGuard(vector<Atom*>::const_iterator currentIt,bool& alwaysTrue) const {
	return (*currentIt)->checkAggregateCountNegativeGuard(alwaysTrue);
}

bool NonGroundSimplifier::checkAggregateAllAggTermShared(Rule *rule,vector<Atom*>::const_iterator currentIt, bool& alwaysTrue) const {
	return (*currentIt)->checkAggregateAllAggTermShared(rule->getBeginBody(),rule->getEndBody(),alwaysTrue);
}

} /* namespace grounder */
} /* namespace DLV2 */


























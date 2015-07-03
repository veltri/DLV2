/*
 * NonGroundSimplifier.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: davide
 */

#include "NonGroundSimplifier.h"

namespace DLV2 {
namespace grounder {

bool NonGroundSimplifier::simplifyRule(Rule* r) {

	vector<vector<Atom*>::iterator> atoms_to_delete;
	bool boolean;
	for(auto it=r->getBeginBody();it!=r->getEndBody();it++){
		if(checkDuplicate(it+1,r->getEndBody(),it))
			atoms_to_delete.push_back(it);
		if(checkOpposite(it+1,r->getEndBody(),it))
			return true;

		if(checkFalsity(it)){
			if(!(*it)->isNegative())
				return true;
			atoms_to_delete.push_back(it);
		}
		if(checkAggregateSumCountStringGuard(it,boolean)){
			if(!boolean)
				return true;
			atoms_to_delete.push_back(it);
		}
	}


	for(auto it:atoms_to_delete){
		(*it)->deleteAtoms();
		delete (*it);
		r->removeInBody(it);
	}
	return false;

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
	Atom* atom=*currentIt;
	if(atom->isAggregateAtom() && (atom->getAggregateFunction()==SUM || atom->getAggregateFunction()==COUNT) ){
		if((atom->getFirstBinop()==LESS_OR_EQ || atom->getFirstBinop()==EQUAL || atom->getFirstBinop()==LESS)
		&& atom->getFirstGuard()->getType()!=VARIABLE && atom->getFirstGuard()->getType()!=NUMERIC_CONSTANT){
			alwaysTrue= atom->isNegative();
			return true;
		}
		if((atom->getSecondBinop()==LESS || atom->getSecondBinop()==LESS_OR_EQ) && atom->getFirstBinop()==NONE_OP
			&& atom->getSecondGuard()->getType()!=VARIABLE && atom->getSecondGuard()->getType()!=NUMERIC_CONSTANT){
			alwaysTrue= !atom->isNegative();
			return true;
		}
	}
	return false;
}


} /* namespace grounder */
} /* namespace DLV2 */

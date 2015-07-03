/*
 * NonGroundSimplifier.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: davide
 */

#include "NonGroundSimplifier.h"

namespace DLV2 {
namespace grounder {


void NonGroundSimplifier::simplify() {

	vector<vector<Rule*>::iterator> rules_to_delete,constraint_to_delete;
	for(auto it=statementDependency->getBeginRules();it!=statementDependency->getEndRules();it++){
		if(simplifyRule(*it))
			rules_to_delete.push_back(it);
	}
	for(auto rule_it:rules_to_delete)statementDependency->deleteRule(rule_it);
	for(auto it=statementDependency->getBeginConstraints();it!=statementDependency->getEndConstraints();it++){
		if(simplifyRule(*it))
			constraint_to_delete.push_back(it);
	}
	for(auto rule_it:constraint_to_delete)statementDependency->deleteRuleConstraint(rule_it);
}

bool NonGroundSimplifier::simplifyRule(Rule* r) {

	vector<vector<Atom*>::iterator> atom_to_delete;
	for(auto it=r->getBeginBody();it!=r->getEndBody();it++){
		if(checkDuplicate(it+1,r->getEndBody(),it))
			atom_to_delete.push_back(it);
	}


	for(auto it:atom_to_delete){
		(*it)->deleteAtoms();
		delete (*it);
		r->removeInBody(it);
	}
	return false;

}

bool NonGroundSimplifier::checkDuplicate(vector<Atom*>::iterator begin,vector<Atom*>::iterator end, vector<Atom*>::iterator currentIt) {
	for(auto it=begin;it!=end;it++)
		if((*it)==(*currentIt))
			return true;

	return false;
}

} /* namespace grounder */
} /* namespace DLV2 */

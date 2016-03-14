/*
 * GroundingPreferences.cpp
 *
 *  Created on: Mar 10, 2016
 *      Author: jessica
 */

#include "GroundingPreferences.h"
#include "../ground/StatementDependency.h"

namespace DLV2 {
namespace grounder {

GroundingPreferences* GroundingPreferences::groundingPreferences=0;

bool GroundingPreferences::addRuleOrderingType(Rule* rule,unsigned orderingType) {
//	if(OrderRuleGroundable::isAValidOrderingType(orderingType)){
		rulesOrderingTypes.insert({rule->getIndex(),orderingType});
		return true;
//	}
	return false;
}

AnnotationsError GroundingPreferences::addRuleAtomIndexingSetting(Rule* rule, Atom* atom, vector<unsigned>& arguments) {
	vector<unsigned> positions;
	checkIfAtomIsPresentInRule(rule,atom,positions);
	if(positions.empty())
		return ATOM_NOT_PRESENT;
	for(auto p:positions)
		rulesAtomsIndexingArguments[rule->getIndex()].push_back({p,arguments});
	return OK;
}

AnnotationsError GroundingPreferences::addRulePartialOrderBefore(Rule* rule, Atom* atom) {
	vector<unsigned> positions;
	checkIfAtomIsPresentInRule(rule,atom,positions);
	if(positions.empty())
		return ATOM_NOT_PRESENT;
	ruleBeforeAtoms.push_back(positions);
	return OK;
}

AnnotationsError GroundingPreferences::addRulePartialOrderAfter(Rule* rule, Atom* atom) {
	vector<unsigned> positions;
	checkIfAtomIsPresentInRule(rule,atom,positions);
	if(positions.empty())
		return ATOM_NOT_PRESENT;
	ruleAfterAtoms.push_back(positions);
	return OK;
}

bool GroundingPreferences::addGlobalOrderingType(unsigned orderingType) {
//	if(OrderRuleGroundable::isAValidOrderingType(orderingType)){
		globalOrderingType=orderingType;
		return true;
//	}
	return false;
}

bool GroundingPreferences::addGlobalAtomIndexingSetting(Atom* atom, vector<unsigned>& arguments) {
	for(unsigned i=0;i<StatementDependency::getInstance()->getRulesSize();++i){
		Rule* rule=StatementDependency::getInstance()->getRule(i);
		addRuleAtomIndexingSetting(rule,atom,arguments);
	}
	return true;
}

bool GroundingPreferences::addGlobalPartialOrder(const vector<Atom*>& beforeAtoms, const vector<Atom*>& afterAtoms) {
	for(unsigned i=0;i<StatementDependency::getInstance()->getRulesSize();++i){
		Rule* rule=StatementDependency::getInstance()->getRule(i);
		for(auto atom:beforeAtoms)
			addRulePartialOrderBefore(rule,atom);
		for(auto atom:afterAtoms)
			addRulePartialOrderBefore(rule,atom);
		checkRulePartialOrderConflicts(rule);
	}
	return true;
}

AnnotationsError GroundingPreferences::checkRulePartialOrderConflicts(Rule* rule) {
	rulesPartialOrders.insert({rule->getIndex(),vector<vector<bool>>()});
	rulesPartialOrders[rule->getIndex()].resize(rule->getSizeBody());
	for(unsigned i=0;i<rule->getSizeBody();++i)
		rulesPartialOrders[rule->getIndex()][i].resize(rule->getSizeBody(),false);

	for(auto positionsAfter:ruleAfterAtoms)
		for(auto pA:positionsAfter)
			for(auto positionsBefore:ruleBeforeAtoms)
					for(auto pB:positionsBefore){
						if(rulesPartialOrders[rule->getIndex()][pB][pA]){
							ruleAfterAtoms.clear();
							ruleBeforeAtoms.clear();
							return CONFLICT_FOUND;
						}
						rulesPartialOrders[rule->getIndex()][pA][pB]=1;
					}
	ruleAfterAtoms.clear();
	ruleBeforeAtoms.clear();
	return OK;
}

void GroundingPreferences::checkIfAtomIsPresentInRule(Rule* rule, Atom* atom, vector<unsigned>& positions) {
	unsigned i=0;
	for(auto atomIt=rule->getBeginBody();atomIt!=rule->getEndBody();++atomIt,++i){
		if(*(*atomIt)==(*atom))
			positions.push_back(i);
	}
}

void GroundingPreferences::print(Rule* rule) const {
	cout<<"Ordering: "<<rulesOrderingTypes.at(rule->getIndex())<<endl;
	vector<pair<unsigned,vector<unsigned>>> v=rulesAtomsIndexingArguments.at(rule->getIndex());
	for(auto p:v){
		cout<<"Atom: "<<p.first<<" Indexing Arguments: ";
		for(auto a:p.second){
			cout<<a<<" ";
		}
		cout<<endl;
	}
	vector<vector<bool>> b=rulesPartialOrders.at(rule->getIndex());
	for(auto a:b){
		for(auto c:a)
			cout<<c<<" ";
		cout<<endl;
	}
	cout<<endl;
}

} /* namespace grounder */
} /* namespace DLV2 */


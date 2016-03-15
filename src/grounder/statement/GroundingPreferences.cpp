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

AnnotationsError GroundingPreferences::addRulePartialOrderAtom(Rule* rule, Atom* atom) {
	vector<unsigned> positions;
	checkIfAtomIsPresentInRule(rule,atom,positions);
	if(positions.empty())
		return ATOM_NOT_PRESENT;
	rulePartialOrderAtoms.push_back(positions);
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
			addRulePartialOrderAtom(rule,atom);
		for(auto atom:afterAtoms)
			addRulePartialOrderAtom(rule,atom);
		checkRulePartialOrderConflicts(rule);
	}
	return true;
}

AnnotationsError GroundingPreferences::checkRulePartialOrderConflicts(Rule* rule) {
	rulesPartialOrders.insert({rule->getIndex(),vector<vector<bool>>()});
	rulesPartialOrders[rule->getIndex()].resize(rule->getSizeBody());
	for(unsigned i=0;i<rule->getSizeBody();++i)
		rulesPartialOrders[rule->getIndex()][i].resize(rule->getSizeBody(),false);

	for(unsigned i=0;i<rulePartialOrderAtoms.size();++i){
		for(auto pB:rulePartialOrderAtoms[i])
			for(unsigned j=i+1;j<rulePartialOrderAtoms.size();++j){
				for(auto pA:rulePartialOrderAtoms[j]){
					if(rulesPartialOrders[rule->getIndex()][pB][pA]){
						rulePartialOrderAtoms.clear();
						return CONFLICT_FOUND;
					}
				}
			}
	}

	for(unsigned i=0;i<rulePartialOrderAtoms.size();++i){
		for(auto pB:rulePartialOrderAtoms[i])
			for(unsigned j=i+1;j<rulePartialOrderAtoms.size();++j)
				for(auto pA:rulePartialOrderAtoms[j])
					rulesPartialOrders[rule->getIndex()][pA][pB]=true;
	}
	rulePartialOrderAtoms.clear();
	return OK;
}

int GroundingPreferences::getOrderingType(Rule* r) const {
	int ruleIndex=r->getIndex();
	if(rulesOrderingTypes.count(ruleIndex))
		return rulesOrderingTypes.at(ruleIndex);
	if(globalOrderingType!=-1)
		return globalOrderingType;
	return -1;
}

bool GroundingPreferences::checkPartialOrder(unsigned ruleIndex, unsigned atomPosition, const list<unsigned>& atoms) const {
	if(rulesPartialOrders.count(ruleIndex)){
		const vector<bool>& partialOrder=rulesPartialOrders.at(ruleIndex).at(atomPosition);
		for(unsigned i=0;i<partialOrder.size();++i){
			if(partialOrder[i]){
				bool found=false;
				for(auto j:atoms){
					if(j==i){
						found=true;
						break;
					}
				}
				if(found)
					return false;
			}
		}
		return true;
	}
//	else if(){
// 	TODO global partial order
//	}
	return true;
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


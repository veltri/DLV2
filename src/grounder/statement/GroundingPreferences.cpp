/*
 * GroundingPreferences.cpp
 *
 *  Created on: Mar 10, 2016
 *      Author: jessica
 */

#include "GroundingPreferences.h"
#include "../ground/StatementDependency.h"
#include "OrderRuleGroundable.h"

namespace DLV2 {
namespace grounder {

GroundingPreferences* GroundingPreferences::groundingPreferences=0;

bool GroundingPreferences::addRuleOrderingType(Rule* rule,unsigned orderingType) {
	if(OrderRuleGroundableFactory::isAValidOrderingType(orderingType)
		&& !rulesOrderingTypes.count(rule->getIndex())){
		rulesOrderingTypes.insert({rule->getIndex(),orderingType});
		return true;
	}
	return false;
}

AnnotationsError GroundingPreferences::addRuleAtomIndexingSetting(Rule* rule, Atom* atom, vector<unsigned>& arguments) {
	vector<unsigned> positions;
	checkIfAtomIsPresentInRule(rule,atom,positions);
	if(positions.empty())
		return ATOM_NOT_PRESENT;
	rulesAtomsIndexingArguments[rule->getIndex()].push_back({rule->getAtomInBody(positions.front()),arguments});
	return OK;
}

AnnotationsError GroundingPreferences::addRulePartialOrderAtom(Rule* rule, Atom* atom) {
	vector<unsigned> positions;
	checkIfAtomIsPresentInRule(rule,atom,positions);
	if(positions.empty())
		return ATOM_NOT_PRESENT;
	rulePartialOrdersAtoms[rule->getIndex()].back().push_back(rule->getAtomInBody(positions.front()));
	return OK;
}

bool GroundingPreferences::addGlobalOrderingType(unsigned orderingType) {
	if(OrderRuleGroundableFactory::isAValidOrderingType(orderingType) && globalOrderingType!=-1){
		globalOrderingType=orderingType;
		return true;
	}
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
	rulesPartialOrders[rule->getIndex()].resize(rule->getSizeBody());
	for(unsigned i=0;i<rule->getSizeBody();++i)
		rulesPartialOrders[rule->getIndex()][i].resize(rule->getSizeBody(),false);

	for(unsigned k=0;k<rulePartialOrdersAtoms[rule->getIndex()].size();++k){
		vector<vector<unsigned>> atomsPositions;
		for(unsigned j=0;j<rulePartialOrdersAtoms[rule->getIndex()][k].size();++j){
			atomsPositions.emplace_back();
			atomsPositions.back().reserve(rule->getIndex());
			checkIfAtomIsPresentInRule(rule,rulePartialOrdersAtoms[rule->getIndex()][k][j],atomsPositions.back());
		}

		for(unsigned i=0;i<atomsPositions.size();++i){
			for(auto pB:atomsPositions[i])
				for(unsigned j=i+1;j<atomsPositions.size();++j){
					for(auto pA:atomsPositions[j]){
						if(rulesPartialOrders[rule->getIndex()][pB][pA]){
							rulesPartialOrders[rule->getIndex()].erase(rulesPartialOrders[rule->getIndex()].begin()+j);
							return CONFLICT_FOUND;
						}
					}
				}
		}

		for(unsigned i=0;i<atomsPositions.size();++i){
			for(auto pB:atomsPositions[i])
				for(unsigned j=i+1;j<atomsPositions.size();++j)
					for(auto pA:atomsPositions[j]){
						rulesPartialOrders[rule->getIndex()][pA][pB]=true;
					}
		}
	}
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
	return true;
}

bool GroundingPreferences::checkAtomIndexed(unsigned ruleIndex, unsigned atomPosition, const vector<unsigned>& possibileArgs) const {

}

void GroundingPreferences::checkIfAtomIsPresentInRule(Rule* rule, Atom* atom, vector<unsigned>& positions) {
	unsigned i=0;
	for(auto atomIt=rule->getBeginBody();atomIt!=rule->getEndBody();++atomIt,++i){
		if(*(*atomIt)==(*atom))
			positions.push_back(i);
	}
}

void GroundingPreferences::print(Rule* rule) const {
	if(rulesOrderingTypes.count(rule->getIndex()))
		cout<<"Ordering: "<<rulesOrderingTypes.at(rule->getIndex())<<endl;
	if(rulesAtomsIndexingArguments.count(rule->getIndex())){
		vector<pair<Atom*,vector<unsigned>>> v=rulesAtomsIndexingArguments.at(rule->getIndex());
		for(auto p:v){
			cout<<"Atom: ";p.first->print();cout<<" Indexing Arguments: ";
			for(auto a:p.second){
				cout<<a<<" ";
			}
			cout<<endl;
		}
	}
	if(rulesPartialOrders.count(rule->getIndex())){
		vector<vector<bool>> b=rulesPartialOrders.at(rule->getIndex());
		for(auto a:b){
			for(auto c:a)
				cout<<c<<" ";
			cout<<endl;
		}
	}
}

} /* namespace grounder */
} /* namespace DLV2 */


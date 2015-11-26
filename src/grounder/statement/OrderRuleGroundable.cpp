/*
 * OrderRuleGroundable.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: jessica
 */

#include "OrderRuleGroundable.h"
#include <list>
#include "../../util/Trace.h"
#include "../../util/Options.h"
#include "../../util/Utils.h"

namespace DLV2 {
namespace grounder {

/****************************************** OrderRuleGroundable ***********************************************/

vector<unsigned> OrderRuleGroundable::order(vector<vector<unsigned>>& predicate_searchInsert_table) {
	this->predicate_searchInsert_table=predicate_searchInsert_table;
	unsigned sizeBody=rule->getSizeBody();

	atomsVariables.resize(sizeBody);
	for(unsigned i=0;i<sizeBody;i++){
		Atom* atom=rule->getAtomInBody(i);
		if(atom->isAggregateAtom()){
			atomsVariables[i]=atom->getSharedVariable(rule->getBeginBody(),rule->getEndBody());
			set_term guards=atom->getGuardVariable();
			atomsVariables[i].insert(guards.begin(),guards.end());
		}
		else
			atomsVariables[i]=atom->getVariable();
	}

	vector<Atom*> orderedBody;
	orderedBody.reserve(sizeBody);

	vector<unsigned> orderedPositions;
	orderedPositions.reserve(sizeBody);

	vector<vector<unsigned>> orderdedPredicateSearchInsertTable;
	orderdedPredicateSearchInsertTable.reserve(predicate_searchInsert_table.size());

	unsigned sizeHead=predicate_searchInsert_table.size()-sizeBody;

	list<unsigned> atomsToInsert;
	for(unsigned i=0;i<sizeHead;++i)
		orderdedPredicateSearchInsertTable.push_back(predicate_searchInsert_table[i]);

	for(unsigned i=0;i<sizeBody;++i)
		atomsToInsert.push_back(i);

	trace_action_tag(grounding,1,
		cerr<<"Before Ordering Body and Search/Insert tables are: ";
		for(unsigned i=0;i<rule->getSizeBody();++i){
			rule->getAtomInBody(i)->print(cerr);
			for(auto j:predicate_searchInsert_table[i+sizeHead])
				cerr<<" "<<j;
			cerr<<"  ";
		}
		cerr<<endl;
	);

	while(!atomsToInsert.empty()){
		list<unsigned>::iterator bestAtom=assignWeights(atomsToInsert);
		orderdedPredicateSearchInsertTable.push_back(predicate_searchInsert_table[sizeHead+*bestAtom]);
		Atom* atom=rule->getAtomInBody((*bestAtom));
		orderedBody.push_back(atom);
		orderedPositions.push_back(*bestAtom);
		variablesInTheBody.insert(atomsVariables[*bestAtom].begin(),atomsVariables[*bestAtom].end());
		atomsToInsert.erase(bestAtom);
	}

	rule->setBody(orderedBody);
	predicate_searchInsert_table=orderdedPredicateSearchInsertTable;

	trace_action_tag(grounding,1,
		cerr<<"After Ordering Body and Search/Insert tables are: ";
		for(unsigned i=0;i<rule->getSizeBody();++i){
			rule->getAtomInBody(i)->print(cerr);
			for(auto j:orderdedPredicateSearchInsertTable[i+sizeHead])
				cerr<<" "<<j;
			cerr<<"  ";
		}
		cerr<<endl;
	);

	return orderedPositions;

}

void OrderRuleGroundable::order(vector<vector<unsigned> >& predicate_searchInsert_table, vector<unsigned>& originalOrderBody) {
	vector<unsigned> orderedPositions=order(predicate_searchInsert_table);
	vector<unsigned> newOriginalOrderBody;
	newOriginalOrderBody.resize(originalOrderBody.size());
	for(unsigned i=0;i<orderedPositions.size();++i){
		unsigned pos=orderedPositions[i];
		newOriginalOrderBody[i]=originalOrderBody[pos];
	}
	originalOrderBody=newOriginalOrderBody;
}

bool OrderRuleGroundable::isBound(Atom* atom, unsigned orginalPosition) {
	if(atom->isBuiltIn() && atom->isAssignment()){
		Term* firstTerm=atom->getTerm(0);
		set_term varsFirst;
		firstTerm->getVariable(varsFirst);

		bool firstContained;
		if(varsFirst.empty())
			firstContained=true;
		else
			firstContained = Utils::isContained(varsFirst,variablesInTheBody);
		if(varsFirst.size()>1 &&  !firstContained)
			return false;

		Term* secondTerm=atom->getTerm(1);
		set_term varsSecond;
		secondTerm->getVariable(varsSecond);
		bool secondContained;
		if(varsSecond.empty())
			secondContained=true;
		else
			secondContained = Utils::isContained(varsSecond,variablesInTheBody);
		if(firstContained && secondContained)
			atom->setAssignment(false);
		if(secondContained || firstContained)
			return true;
		return false;
	}
	else if(atom->isAggregateAtom()){
		set_term variables=atom->getSharedVariable(rule->getBeginBody(),rule->getEndBody());
		set_term guards=atom->getGuardVariable();
		if(!atom->isAssignment())
			variables.insert(guards.begin(),guards.end());
		else
			variables.erase(atom->getFirstGuard());
		return Utils::isContained(variables,variablesInTheBody);
	}
	return Utils::isContained(atomsVariables[orginalPosition],variablesInTheBody);

}

/****************************************** AllOrderRuleGroundable ***********************************************/

list<unsigned>::iterator AllOrderRuleGroundable::assignWeights(list<unsigned>& atomsToInsert) {
	double bestWeight=INT_MAX;
	list<unsigned>::iterator bestAtomIt=atomsToInsert.begin();
	for(list<unsigned>::iterator it=atomsToInsert.begin();it!=atomsToInsert.end();++it){
		Atom* atom=rule->getAtomInBody(*it);
		double weight=INT_MAX;

		if(atom->isClassicalLiteral() && !atom->isNegative()){
			weight=assignWeightPositiveClassicalLit(atom,*it);
		}
		else if(isBound(atom,*it)){
			if(atom->isClassicalLiteral() && atom->isNegative()){
				weight=assignWeightNegativeClassicalLit(atom,*it);
			}
			else if(atom->isBuiltIn()){
				weight=assignWeightBuiltInAtom(atom,*it);
			}
			else if(atom->isAggregateAtom()){
				weight=assignWeightAggregateAtom(atom,*it);
			}
		}
		else
			continue;

		if(weight<bestWeight){
			bestWeight=weight;
			bestAtomIt=it;
		}
	}
	//TODO Add all bound atoms all together and avoid the weigh update if no bind atom has been added
	update(rule->getAtomInBody(*bestAtomIt));
	return bestAtomIt;
}

/****************************************** CombinedCriterion ***********************************************/

void CombinedCriterion::computeVariablesDomains() {
	for(auto it=rule->getBeginBody();it!=rule->getEndBody();++it){
		Atom* atom=*it;
		if(atom->isClassicalLiteral() && !atom->isNegative()){
			for(unsigned i=0;i<atom->getTermsSize();++i){
				Term* term=atom->getTerm(i);
				unsigned selectivity=0;
				if(term->getType()==TermType::VARIABLE)
					selectivity=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateInformation()->getSelectivity(i);
//					else if(term==TermType::FUNCTION){ //TODO
//
//					}
				auto it=variablesDomains.find(term);
				if(it!=variablesDomains.end()){
					if(selectivity>(*it).second)
						variablesDomains[term]=selectivity;
				}
				else
					variablesDomains[term]=selectivity;
			}
		}
	}
}

void CombinedCriterion::updateVariableSelectivity(Atom* atomAdded) {
	if(atomAdded->isClassicalLiteral() && !atomAdded->isNegative()){
		for(unsigned i=0;i<atomAdded->getTermsSize();++i){
			Term* term=atomAdded->getTerm(i);
			if(term->getType()==TermType::VARIABLE){
				unsigned selectivity=predicateExtTable->getPredicateExt(atomAdded->getPredicate())->getPredicateInformation()->getSelectivity(i);
				if(variablesInTheBody.count(term))
					variablesSelectivities[term]*=selectivity/variablesDomains[term];
				else
					variablesSelectivities[term]=selectivity;
			}
//			else if(term==TermType::FUNCTION){ //TODO
//
//			}
		}
	}
}

double CombinedCriterion::assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition) {
	if(variablesDomains.empty())
		computeVariablesDomains();

	unsigned sizeTablesToSearch=0;
	for(auto j:predicate_searchInsert_table[originalPosition+rule->getSizeHead()])
		sizeTablesToSearch+=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateExtentionSize(j);

	double prodSelectivity_a=1;
	unsigned prodDomains_a=1;
	double prodSelectivity_b=1;
	unsigned prodDomains_b=1;
	for(unsigned i=0;i<atom->getTermsSize();++i){
		Term* var=atom->getTerm(i);
		if(var->getType()==TermType::VARIABLE){
			if(variablesInTheBody.count(var)){
				prodSelectivity_a*=variablesSelectivities[var]/variablesDomains[var];
				prodDomains_a*=variablesDomains[var];
				prodSelectivity_b*=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateInformation()->getSelectivity(i);
				prodDomains_b*=variablesDomains[var]*variablesDomains[var];
			}
			else{
				for(unsigned j=0;j<rule->getSizeBody();++j){
					if(j!=originalPosition && atomsVariables[j].count(var)){
						prodDomains_a*=variablesDomains[var];
						break;
					}
				}

			}
		}
//			else if(term==TermType::FUNCTION){ //TODO
//
//			}
	}

	double sel_a=sizeTablesToSearch*prodSelectivity_a/prodDomains_a;
	double sel_b=prodSelectivity_b/prodDomains_b;

	return sel_a*sel_b;

}

double CombinedCriterion::assignWeightNegativeClassicalLit(Atom* atom, unsigned originalPosition) {
	return -3;
}

double CombinedCriterion::assignWeightAggregateAtom(Atom* atom, unsigned originalPosition) {
	return -1;
}

double CombinedCriterion::assignWeightBuiltInAtom(Atom* atom, unsigned originalPosition) {
	return -2;
}

}
}



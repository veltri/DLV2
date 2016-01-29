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

vector<unsigned> OrderRuleGroundable::order(vector<vector<pair<unsigned,SearchType>>>& predicate_searchInsert_table) {
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
		if(atom->isClassicalLiteral() && !atom->isNegative()){
			for(auto v:atom->getTerms())
				v->getVariablesInArith(mapPositiveAtomsBoundVariables[i]);
		}
	}

	vector<Atom*> orderedBody;
	orderedBody.reserve(sizeBody);

	vector<unsigned> orderedPositions;
	orderedPositions.reserve(sizeBody);

	vector<vector<pair<unsigned,SearchType>>> orderdedPredicateSearchInsertTable;
	orderdedPredicateSearchInsertTable.reserve(predicate_searchInsert_table.size());

	unsigned sizeHead=predicate_searchInsert_table.size()-sizeBody;

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

	rule->clearDictionaryIntersection();
	rule->setDictionaryIntersectionSize(rule->getVariablesSize()+2);

	while(!atomsToInsert.empty()){
		list<unsigned>::iterator bestAtom=assignWeights(atomsToInsert);
		orderdedPredicateSearchInsertTable.push_back(predicate_searchInsert_table[sizeHead+*bestAtom]);
		Atom* atom=rule->getAtomInBody((*bestAtom));
		orderedBody.push_back(atom);
		orderedPositions.push_back(*bestAtom);
		if(Options::globalOptions()->isEnabledDictionaryIntersection() && atom->isClassicalLiteral() && !atom->isNegative())
			computeDictionaryIntersection(atom);
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

void OrderRuleGroundable::order(vector<vector<pair<unsigned,SearchType>> >& predicate_searchInsert_table, vector<unsigned>& originalOrderBody) {
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
	if(atom->isBuiltIn() && atom->getBinop()==Binop::EQUAL){

		if(atom->plusMinusBuiltin()){
			//If the builtin is an = and contain only + and - operatos, then we count only the total variable
			// of the builtin and if only 1 variable is free we can put this atom because even if the free variable is in
			// arithmetic operators we can calculate like an equation
			set_term variablesInAtom=atom->getVariable();
			unsigned count=0;
			for(auto var:variablesInAtom){
				if(!variablesInTheBody.count(var))
					count++;
				if(count>1)
					break;
			}
			if(count==1){
				atom->setAssignment(true);
				return true;
			}
		}else{
			// If the builtin contain also * or / operator, because ww don't have float constant we cannot solve the equation and then
			// the free variable must be alone in first or second term in the atom
			set_term varsFirst;
			atom->getTerm(0)->getVariable(varsFirst);
			if(Utils::isContained(varsFirst,variablesInTheBody) && atom->getTerm(1)->getType()==VARIABLE){
				atom->setAssignment(true);
				return true;
			}
			set_term varSecond;
			atom->getTerm(1)->getVariable(varSecond);
			if(Utils::isContained(varSecond,variablesInTheBody) && atom->getTerm(0)->getType()==VARIABLE){
				atom->setAssignment(true);
				return true;
			}
		}

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
	else if(mapPositiveAtomsBoundVariables[orginalPosition].size()>0){
		return !(atom->containsAnonymous()) && Utils::isContained(mapPositiveAtomsBoundVariables[orginalPosition],variablesInTheBody);
	}
	return !(atom->containsAnonymous()) && Utils::isContained(atomsVariables[orginalPosition],variablesInTheBody);
}

void OrderRuleGroundable::computeDictionaryIntersection(Atom* atom) {
	for(unsigned i=0;i<atom->getTermsSize();++i){
		Term* var=atom->getTerm(i);
		if(var->getType()==TermType::VARIABLE && rule->getRuleInformation().isAJoinVariable(var)){
			index_object localIndex=var->getLocalVariableIndex();
			if(variablesInTheBody.count(var)){
				for(auto it=rule->getDictionaryIntersectionBegin(localIndex);it!=rule->getDictionaryIntersectionEnd(localIndex);){
					if(predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateInformation()->isPresent(i,*it))
						it++;
					else
						rule->removeInDictionaryIntersection(it,localIndex);
				}
			}
			else{
				const set_term& set=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateInformation()->getDictionary(i);
				rule->insertInDictionaryIntersection(localIndex,set);
			}
		}
	}
}

/****************************************** AllOrderRuleGroundable ***********************************************/

unsigned AllOrderRuleGroundable::computePredicateExtensionSize(	unsigned atomPosition, Predicate* p) {
	unsigned extensionSize = 0;
	for (auto j : predicate_searchInsert_table[atomPosition + rule->getSizeHead()])
		extensionSize +=
				predicateExtTable->getInstance()->getPredicateExt(p)->getPredicateExtentionSize(j.first,j.second);
	return extensionSize;
}


list<unsigned>::iterator AllOrderRuleGroundable::assignWeights(list<unsigned>& atomsToInsert) {
	double bestWeight=LLONG_MAX;
	list<unsigned>::iterator bestAtomIt=atomsToInsert.begin();
	unsigned bestAtomExtensionSize=0;
	for(list<unsigned>::iterator it=atomsToInsert.begin();it!=atomsToInsert.end();++it){
		Atom* atom=rule->getAtomInBody(*it);
		double weight=INT_MAX;
		trace_action_tag(grounding,2,
			atom->print(cerr);
		);

		bool bound=isBound(atom,*it);
		if(atom->isClassicalLiteral() && !atom->isNegative() && ((!bound && mapPositiveAtomsBoundVariables[*it].empty()) || (bound && mapPositiveAtomsBoundVariables[*it].size()>0))){
			// If in a positive classical literal all variables that must be bound are bound then it can be safely added to the new body
			weight=assignWeightPositiveClassicalLit(atom,*it);
		}
		else if(bound){
			if(atom->isClassicalLiteral()){
				if(atom->isNegative())
					weight=assignWeightNegativeClassicalLit(atom,*it);
				else
					weight=assignWeightBoundPositiveClassicalLit(atom,*it);
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

			trace_action_tag(grounding,2,
				cerr<<" Weight: "<<weight<<endl;
			);

		if(weight<bestWeight){
			bestWeight=weight;
			bestAtomIt=it;
			Predicate* p=rule->getAtomInBody(*bestAtomIt)->getPredicate();
			if(p!=nullptr)
				bestAtomExtensionSize = computePredicateExtensionSize(*bestAtomIt, p);
			else
				bestAtomExtensionSize = 0;
		}
//		If two atoms have the same weight we prefer the one with the lower extension size
		else if(weight==bestWeight){
			Predicate* p=rule->getAtomInBody(*it)->getPredicate();
			if(p!=nullptr){
//				unsigned extensionSize = computePredicateExtensionSize(*it, p);
//				if(extensionSize<bestAtomExtensionSize)
//				{
//					bestWeight=weight;
//					bestAtomIt=it;
//					bestAtomExtensionSize=extensionSize;
//				}
				double forwardWeight=computeForwardWeight(*it);
				if(forwardWeight<bestAtomExtensionSize){
					bestWeight=weight;
					bestAtomIt=it;
					bestAtomExtensionSize=forwardWeight;
				}
			}

		}
	}
	//TODO Add all bound atoms all together and avoid the weigh update if no bind atom has been added
	update(rule->getAtomInBody(*bestAtomIt),*bestAtomIt);
	trace_action_tag(grounding,2,
		cout<<"Chosen atom: ";rule->getAtomInBody(*bestAtomIt)->print(cout);cout<<" "<<bestWeight<<endl;
	);

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
		sizeTablesToSearch+=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateExtentionSize(j.first,j.second);

	long double prodSelectivity_a=1;
	long unsigned prodDomains_a=1;
	long double prodSelectivity_b=1;
	long unsigned prodDomains_b=1;
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

double CombinedCriterion1::assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition) {
	if(variablesDomains.empty())
		computeVariablesDomains();

	unsigned sizeTablesToSearch=0;
	for(auto j:predicate_searchInsert_table[originalPosition+rule->getSizeHead()])
		sizeTablesToSearch+=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateExtentionSize(j.first,j.second);

	long double num1=1;
	long unsigned  den1=1;
	long unsigned den2=1;
	for(unsigned i=0;i<atom->getTermsSize();++i){
		Term* var=atom->getTerm(i);
		if(var->getType()==TermType::VARIABLE){
			if(variablesInTheBody.count(var)){
				num1*=variablesSelectivities[var]*predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateInformation()->getSelectivity(i);
				den1=pow(variablesDomains[var],4);
			}
			else{
				for(unsigned j=0;j<rule->getSizeBody();++j){
					if(j!=originalPosition && atomsVariables[j].count(var)){
						den2=pow(variablesDomains[var],2);
						break;
					}
				}

			}
		}
	}
	return sizeTablesToSearch*(num1/den1)*(1/den2);
}

double CombinedCriterion3::assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition) {
	double sel_c=CombinedCriterion::assignWeightPositiveClassicalLit(atom,originalPosition);
	long unsigned sel_f=1;
	for(unsigned i=0;i<atom->getTermsSize();++i){
		Term* t=atom->getTerm(i);
		if(t->getType()==TermType::FUNCTION){
			set_term variablesInFunction;
			t->getVariable(variablesInFunction);
			for(auto v:variablesInFunction){
				if(!variablesInTheBody.count(v)){
					if(variablesDomains.count(v))
						sel_f*=variablesDomains[v];
					else
						sel_f*=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateInformation()->getSelectivity(i);
				}
			}
		}
	}
	return sel_c*sel_f;
}

double CombinedCriterion4::assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition) {
	double sel_c=CombinedCriterion::assignWeightPositiveClassicalLit(atom,originalPosition);
	long unsigned sel_f=0;
	for(unsigned i=0;i<atom->getTermsSize();++i){
		Term* t=atom->getTerm(i);
		if(t->getType()==TermType::FUNCTION){
			set_term variablesInFunction;
			t->getVariable(variablesInFunction);
			for(auto v:variablesInFunction){
				if(!variablesInTheBody.count(v)){
					if(variablesDomains.count(v))
						sel_f+=variablesDomains[v];
					else
						sel_f+=predicateExtTable->getPredicateExt(atom->getPredicate())->getPredicateInformation()->getSelectivity(i);
				}
			}
		}
	}
	if(sel_f>0)
		return sel_c*sel_f;
	return sel_c;
}

double IndexingArgumentsOrderRuleGroundable::computeForwardWeight(unsigned originalPosition) {
	PredicateExtension* predicateExtension=PredicateExtTable::getInstance()->getPredicateExt(rule->getAtomInBody(originalPosition)->getPredicate());
	double forwardWeight = predicateExtension->getPredicateExtentionSize();
	for (auto j : atomsToInsert) {
		Atom* a = rule->getAtomInBody(j);
		if (j == originalPosition
				|| !(a->isClassicalLiteral() && !a->isNegative())
				|| a->getPredicate()->getArity() <= 1)
			continue;

		PredicateExtension* predicateExtension =
				PredicateExtTable::getInstance()->getPredicateExt(
						a->getPredicate());
		unsigned s = predicateExtension->getPredicateExtentionSize();
		double maxOther = 0;
		double secondMaxOther = 0;
		double bestIndex = 0;
		for (unsigned i = 0; i < a->getTermsSize(); ++i) {
			bool bound = true;
			for (auto v : variablesInTerms[j][i]) {
				if (!variablesInTheBody.count(v)) {
					if (!atomsVariables[originalPosition].count(v))
						bound = false;
				}
			}
			if (bound && boundArgumentsSelectivities[j][i] > maxOther) {
				secondMaxOther = maxOther;
				maxOther = boundArgumentsSelectivities[j][i];
			} else if (boundArgumentsSelectivities[j][i] == maxOther) {
				secondMaxOther = maxOther;
			}
		}
		if (maxOther > 0 && secondMaxOther > 0
				&& (maxOther / s) < DOUBLE_INDEX_THRESHOLD) {
			bestIndex = (1 - ((maxOther * secondMaxOther) / s));
		} else
			bestIndex = (1 - maxOther / s);

		forwardWeight *= bestIndex;
	}

	return forwardWeight;
}

double IndexingArgumentsOrderRuleGroundable::assignWeightPositiveClassicalLit(Atom* atom, unsigned originalPosition) {
	if(boundArgumentsSelectivities.empty())
		computeBoundArgumentsSelectivities();

	PredicateExtension* predicateExtension=PredicateExtTable::getInstance()->getPredicateExt(atom->getPredicate());
	unsigned size=predicateExtension->getPredicateExtentionSize();
	double max=0;
	double secondMax=0;
	double backwardWeight=currentJoinSize;
	if(currentJoinSize==0)
		backwardWeight=size;
	else{
		for(unsigned i=0;i<atom->getTermsSize();++i){
			if(Utils::isContained(variablesInTerms[originalPosition][i],variablesInTheBody)){
				if(boundArgumentsSelectivities[originalPosition][i]>max){
					secondMax=max;
					max=boundArgumentsSelectivities[originalPosition][i];
				}
				else if(boundArgumentsSelectivities[originalPosition][i]==max){
					secondMax=max;
				}
			}
		}
		if(max>0 && secondMax>0 && (max/size)<DOUBLE_INDEX_THRESHOLD){
			backwardWeight*=(1-((max*secondMax)/size));
		}
		else
			backwardWeight*=(1-max/size);
	}

	backwardWeights[originalPosition]=backwardWeight;

	return backwardWeight;

}

void IndexingArgumentsOrderRuleGroundable::update(Atom* atomAdded, unsigned originalPosition) {
	if(atomAdded->isClassicalLiteral() && !atomAdded->isNegative())
		currentJoinSize*=backwardWeights[originalPosition];
}

void IndexingArgumentsOrderRuleGroundable::computeBoundArgumentsSelectivities() {
	unsigned sizeBody=rule->getSizeBody();
	boundArgumentsSelectivities.resize(sizeBody);
	variablesInTerms.resize(sizeBody);
	backwardWeights.resize(sizeBody,0);
	unsigned atom_pos=0;
	for(auto it=rule->getBeginBody();it!=rule->getEndBody();++it,++atom_pos){
		Atom* atom=*it;
		if(!(atom->isClassicalLiteral() && !atom->isNegative())) continue;
		PredicateExtension* predicateExtension=PredicateExtTable::getInstance()->getPredicateExt(atom->getPredicate());
		unsigned termSize=atom->getTermsSize();
		variablesInTerms[atom_pos].resize(termSize);
		for(unsigned i=0;i<termSize;++i){
			Term* term=atom->getTerm(i);
			set_term variables;
			term->getVariable(variables);
			bool boundTerm=true;
			for(auto var:variables){
				bool bound=false;
				for(unsigned j=0;j<sizeBody;++j){
					if(j!=atom_pos && atomsVariables[j].count(var)){
						bound=true;
						break;
					}
				}
				if(!bound){
					boundTerm=false;
				}
				else
					variablesInTerms[atom_pos][i].insert(var);
			}
			if(boundTerm){
				double selectivity=predicateExtension->getPredicateInformation()->getSelectivity(i);
				boundArgumentsSelectivities[atom_pos].insert({i,(selectivity)});
			}
		}
	}

//	for(unsigned i=0;i<boundArgumentsSelectivities.size();++i){
//		rule->getAtomInBody(i)->print();
//		cout<<endl;
//		for(auto p:boundArgumentsSelectivities[i])
//			cout<<p.first<<" "<<p.second<<" ";
//		cout<<endl;
//	}
//
//	for(unsigned i=0;i<variablesInTerms.size();++i){
//		rule->getAtomInBody(i)->print();
//		cout<<endl;
//		for(auto p:variablesInTerms[i])
//			for(auto s:p){
//				s->print();cout<<" ";
//			}
//		cout<<endl;
//	}


}


}
}


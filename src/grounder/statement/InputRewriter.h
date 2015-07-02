/*
 * InputRewriter.h
 *
 *  Created on: 18/feb/2015
 *      Author: tesi2
 */

#ifndef INPUTREWRITER_H_
#define INPUTREWRITER_H_

#include "Rule.h"
#include "../atom/ClassicalLiteral.h"
#include "../table/PredicateExtension.h"
#include "../table/PredicateTable.h"
#include "OrderRule.h"

namespace DLV2 {
namespace grounder {

/// Abstract class that defines a choosing policy for saviors atoms
class SaviorChoosingPolicy{
public:
	virtual bool choose(Atom* atom, unsigned savior_pos, list<Atom*>& possibleAtomsBinding, vector<Atom*>& atomToAdd, bool end, const OrderRule& orderRule) = 0;
	virtual ~SaviorChoosingPolicy() {};
};

/// A concrete implementation of SaviorChoosingPolicy class that just choose the first savior
class FirstSaviorChoosingPolicy : public SaviorChoosingPolicy{
public:
	virtual bool choose(Atom* atom, unsigned savior_pos, list<Atom*>& possibleAtomsBinding, vector<Atom*>& atomToAdd, bool end, const OrderRule& orderRule);
	virtual ~FirstSaviorChoosingPolicy() {};

private:
	void getRecursiveDependencies(const OrderRule& orderRule, unsigned savior_pos, vector<Atom*>& atomToAdd);
};


/// Abstract class that defines how to rewrite the input program
class InputRewriter {
public:
	InputRewriter():predicateExtTable(PredicateExtTable::getInstance()), predicateTable(PredicateTable::getInstance()) {};
	virtual void translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited, OrderRule* orderRule=nullptr) = 0;
	virtual void translateChoice(Rule*& rule, vector<Rule*>& ruleRewrited) = 0;
	virtual void  chooseBestSaviorForAggregate(Rule* rule, AggregateElement* aggregateElement, set_term& unsafeVars, vector<Atom*>& atomToAdd, const OrderRule& orderRule) = 0;
	virtual ~InputRewriter(){};
protected:
	PredicateExtTable* predicateExtTable;
	PredicateTable* predicateTable;

	Atom* generateNewAuxiliaryAtom(string& predicate_name,vector<Term*>& terms);
};


/// A concrete implementation of InputRewriter that defines the translation of aggregates atoms using auxiliary rules
class BaseInputRewriter : public InputRewriter {
public:
	BaseInputRewriter():InputRewriter(), saviourChoosingPolicy(new FirstSaviorChoosingPolicy) {};
	/**
	 * For each aggregate element in each aggregate atom in the given rule an auxiliary rule is produced, so that:
	 * 		- its head is composed by an auxiliary atom whose terms are the variables of aggregation and the variables shared
	 * 			with the other atoms of the rule,
	 *		- its body is composed by :
	 *			- the atoms appearing in the aggregate element,
	 *			- the atoms needed to save any atom in the aggregate element.
	 * The choose of the savior(s) is delegated to the method chooseBestSaviorForAggregate
	 */
	virtual void translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited, OrderRule* orderRule=nullptr);

	/**
	 * Given a choice rule it is rewritten by means of new auxiliary rules.
	 * In particular, the rules created are:
	 * 		- One rule to factorize the body of the choice rule
	 * 		- One disjunctive rule for each choice element
	 * 		- One constraint rule with a negated count aggregate
	 *  More details are given in the method itself.
	 */
	virtual void translateChoice(Rule*& rule, vector<Rule*>& ruleRewrited);

	/**
	 * This template method searches for possible saviors of the negative atoms in the given aggregateElement.
	 * Each possible savior found is passed to the saviorChoosingPolicy object that will independently select
	 * a savior among the saviors found.
	 */
	virtual void  chooseBestSaviorForAggregate(Rule* rule, AggregateElement* aggregateElement, set_term& unsafeVars, vector<Atom*>& atomToAdd, const OrderRule& orderRule);

	virtual ~BaseInputRewriter() {delete saviourChoosingPolicy;}


protected:
	/// The savior choosing policy adopted
	SaviorChoosingPolicy* saviourChoosingPolicy;

	/// Utility method: returns the variables in the given aggregate element without the aggregation variables
	set_term getVariablesInAggregateElem(AggregateElement* aggregateElem);

	///Create an auxiliary rule for each  choice element
	virtual vector<AggregateElement*> rewriteChoiceElements(unsigned id,unsigned counter, Atom* choice, Atom* auxiliaryAtomBody,	vector<Rule*>& ruleRewrited);

	virtual void rewriteChoiceConstraint(const vector<AggregateElement*>& elements, Atom* auxiliaryAtomBody, Atom* choice, vector<Rule*>& ruleRewrited);
};

class ChoiceBaseInputRewriter : public BaseInputRewriter{
public:
	virtual vector<AggregateElement*> rewriteChoiceElements(unsigned id,unsigned counter, Atom* choice, Atom* auxiliaryAtomBody,	vector<Rule*>& ruleRewrited);
	virtual void rewriteChoiceConstraint(const vector<AggregateElement*>& elements, Atom* auxiliaryAtomBody, Atom* choice, vector<Rule*>& ruleRewrited);
protected:
	Rule* createAuxChoiceRule(const vector<Atom*>& head,const vector<Atom*>& body);
	Rule* createAuxChoiceRule(Atom* head,const vector<Atom*>& body){return createAuxChoiceRule(vector<Atom*>({head}),body);}
	Rule* createAuxChoiceRule(const vector<Atom*>& head,Atom* body){return createAuxChoiceRule(head,vector<Atom*>({body}));}
	Rule* createAuxChoiceRule(const vector<Atom*>& head){return createAuxChoiceRule(head,vector<Atom*>());}
	Rule* createAuxChoiceRule(Atom* head,Atom* body){return createAuxChoiceRule(vector<Atom*>({head}),vector<Atom*>({body}));}



};


} /* namespace grounder */
} /* namespace DLV2 */

#endif /* INPUTREWRITER_H_ */

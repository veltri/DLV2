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

namespace DLV2 {
namespace grounder {

class InputRewriter {
public:
	InputRewriter():predicateExtTable(PredicateExtTable::getInstance()), predicateTable(PredicateTable::getInstance()) {};
	virtual void translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited) = 0;
	virtual void expandEqualweightConstraint(Rule* rule, vector<Rule*>& ruleRewrited) =0;
	virtual ~InputRewriter(){};
protected:
	PredicateExtTable* predicateExtTable;
	PredicateTable* predicateTable;
};

class BaseInputRewriter : public InputRewriter {
public:
	BaseInputRewriter():InputRewriter(){};
	void translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited);
	virtual void expandEqualweightConstraint(Rule* rule, vector<Rule*>& ruleRewrited);
private:
	Predicate* createPredicate(string name,int arity);
	Rule* generateGuardRule(Atom* auxiliaryAtom,Term* guard,const vector<pair<Atom*,Term*>>& weightAtoms);

	Atom* rewriteBoundAggregateCountSum(Atom* aggregateAtom,unsigned id, vector<pair<Atom*,Term*>>& weightAtoms,vector<Rule*>& ruleRewrited);
	Atom* rewriteEqualAggregateCountSum(Atom* aggregateAtom,unsigned id, vector<pair<Atom*,Term*>>& weightAtoms,vector<Rule*>& ruleRewrited);

};


} /* namespace grounder */
} /* namespace DLV2 */

#endif /* INPUTREWRITER_H_ */

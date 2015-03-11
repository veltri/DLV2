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
	virtual ~InputRewriter(){};
protected:
	PredicateExtTable* predicateExtTable;
	PredicateTable* predicateTable;
};

class BaseInputRewriter : public InputRewriter {
public:
	BaseInputRewriter():InputRewriter(){};
	void translateAggregate(Rule* rule, vector<Rule*>& ruleRewrited);
private:
	//Get all variable in rule except the variables in the aggregate
	set_term getVariablesInClassicalLit(Rule* rule);
	//Get all variable in the aggregate element except the variables in the terms of aggregate element
	set_term getVariablesInAggregateElem(AggregateElement* aggregateElem);

};


} /* namespace grounder */
} /* namespace DLV2 */

#endif /* INPUTREWRITER_H_ */

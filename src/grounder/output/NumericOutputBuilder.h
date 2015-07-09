/*
 * NumericOutputBuilder.h
 *
 *  Created on: Jul 7, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_OUTPUT_NUMERICOUTPUTBUILDER_H_
#define SRC_GROUNDER_OUTPUT_NUMERICOUTPUTBUILDER_H_

#include "OutputBuilder.h"

namespace DLV2 {
namespace grounder {

class NumericOutputBuilder: public OutputBuilder {
public:
	NumericOutputBuilder(){};
	virtual ~NumericOutputBuilder(){};

    virtual void onRule(Rule *rule);
    virtual void onWeakConstraint();
    virtual void onQuery();
    virtual void onHeadAtom(Atom * atom);
    virtual void onDisjunctionAtom(const vector<Atom*>& head);
    virtual void onConstraint(Rule* rule);
    virtual void onHead(const vector<Atom*>& head);
    virtual void onBody(Rule *rule);
    virtual void onClassicalLiteral(Atom *atom);
    virtual void onChoiceAtom(Atom *atom);
    virtual void onAggregate(Atom *atom);
    virtual void onAggregateElement(Atom *atom);
    virtual void onFact(Atom* atom);


    virtual void onEnd();

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_OUTPUT_NUMERICOUTPUTBUILDER_H_ */

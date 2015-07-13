/*
 * TextualOutputBuilder.h
 *
 *  Created on: Jul 10, 2015
 *      Author: jessica
 */

#ifndef SRC_GROUNDER_OUTPUT_TEXTUALOUTPUTBUILDER_H_
#define SRC_GROUNDER_OUTPUT_TEXTUALOUTPUTBUILDER_H_

#include "OutputBuilder.h"

namespace DLV2 {
namespace grounder {

class TextualOutputBuilder: public OutputBuilder {
public:
	TextualOutputBuilder(){};
	virtual ~TextualOutputBuilder(){};

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
    virtual unsigned onAggregate(Atom *atom);
    virtual void onAggregateElement(Atom *atom);
    virtual void onFact(Atom* atom);

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_OUTPUT_TEXTUALOUTPUTBUILDER_H_ */

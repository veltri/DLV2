/*
 * OutputBuilder.h
 *
 *  Created on: Jul 7, 2015
 *      Author: davide
 */

#ifndef SRC_GROUNDER_OUTPUT_OUTPUTBUILDER_H_
#define SRC_GROUNDER_OUTPUT_OUTPUTBUILDER_H_


#include "../statement/Rule.h"
#include "../../util/Options.h"

using namespace std;

namespace DLV2 {
namespace grounder {


class OutputBuilder {
public:

    virtual void onRule(Rule *rule) = 0;
    virtual void onWeakConstraint() = 0;
    virtual void onQuery() = 0;
    virtual void onHeadAtom(Atom * atom) = 0;
    virtual void onDisjunctionAtom(const vector<Atom*>& head) = 0;
    virtual void onConstraint(Rule* rule)=0;
    virtual void onHead(const vector<Atom*>& head) = 0;
    virtual void onBody(Rule *rule) = 0;
    virtual void onClassicalLiteral(Atom *atom) = 0;
    virtual void onChoiceAtom(Atom *atom) = 0;
    virtual unsigned onAggregate(Atom *atom) = 0;
    virtual void onAggregateElement(Atom *atom) = 0;
    virtual void onFact(Atom* atom)=0;
    virtual void onEnd(){};

    virtual void appendToStreamAtomTable(Atom* atom, bool fact=false){};

	virtual void setAtomToFilter(Atom* atomToFilter){};

	virtual void clearStreamAtomTable(){}

    virtual ~OutputBuilder(){};

    virtual void setEnablePrint(bool enable){}

    static OutputBuilder* getInstance();
    static void freeInstance(){delete outputBuilder;}

protected:
	OutputBuilder(){};

    static OutputBuilder* outputBuilder;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_OUTPUT_OUTPUTBUILDER_H_ */

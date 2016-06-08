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
    void onWeakConstraint();
    void onQuery();
    void onHeadAtom(Atom * atom);
    void onDisjunctionAtom(const vector<Atom*>& head);
    void onConstraint(Rule* rule);
    void onHead(const vector<Atom*>& head);
    void onBody(Rule *rule);
    void onClassicalLiteral(Atom *atom);
    void onChoiceAtom(Atom *atom);
    unsigned onAggregate(Atom *atom);
    void onAggregateElement(Atom *atom);
    virtual void onFact(Atom* atom);

};

class QueryTextualOutputBuilder : public TextualOutputBuilder {
public:
	QueryTextualOutputBuilder():enablePrint(false){}

	void onRule(Rule *rule){
		if(enablePrint)
			rule->print();
	}

    void setEnablePrint(bool enable){
    	enablePrint=enable;
    }

    void onFact(Atom* atom){
    	if(enablePrint){
    		atom->print();cout<<"."<<endl;
    	}
    }


private:
    bool enablePrint;

};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_GROUNDER_OUTPUT_TEXTUALOUTPUTBUILDER_H_ */

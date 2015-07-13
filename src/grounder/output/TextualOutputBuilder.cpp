/*
 * TextualOutputBuilder.cpp
 *
 *  Created on: Jul 10, 2015
 *      Author: jessica
 */

#include "TextualOutputBuilder.h"

namespace DLV2 {
namespace grounder {

void DLV2::grounder::TextualOutputBuilder::onRule(Rule* rule) {
	rule->print();
}

void TextualOutputBuilder::onHeadAtom(Atom* atom) {
}

void TextualOutputBuilder::onDisjunctionAtom(const vector<Atom*>& head) {
}

void TextualOutputBuilder::onConstraint(Rule* rule) {
}

void TextualOutputBuilder::onHead(const vector<Atom*>& head) {
}

void TextualOutputBuilder::onBody(Rule* rule) {
}

void TextualOutputBuilder::onClassicalLiteral(Atom* atom) {
}

void TextualOutputBuilder::onChoiceAtom(Atom* atom) {
}

unsigned TextualOutputBuilder::onAggregate(Atom* atom) {
}

void TextualOutputBuilder::onAggregateElement(Atom* atom) {
}

void TextualOutputBuilder::onWeakConstraint() {
}

void TextualOutputBuilder::onQuery() {
}

void TextualOutputBuilder::onFact(Atom* atom) {
	atom->print();cout<<"."<<endl;
}

} /* namespace grounder */
} /* namespace DLV2 */

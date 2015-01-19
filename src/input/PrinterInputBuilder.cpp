/*
 * TestInputBuilder.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: david
 */

#include "PrinterInputBuilder.h"
#include <iostream>

namespace DLV2 {
namespace Grounder {

PrinterInputBuilder::PrinterInputBuilder() {
	// TODO Auto-generated constructor stub

}

PrinterInputBuilder::~PrinterInputBuilder() {
	// TODO Auto-generated destructor stub
}

void PrinterInputBuilder::onDirective(char* directiveName, char* directiveValue) {
}

void PrinterInputBuilder::onRule() {
	cout<<"FIND RULE"<<endl;
}

void PrinterInputBuilder::onConstraint() {
	cout<<"FIND CONSTRAINT"<<endl;
}

void PrinterInputBuilder::onWeakConstraint() {
}

void PrinterInputBuilder::onQuery() {
}

void PrinterInputBuilder::onHeadAtom() {
	cout<<"FIND HEAD ATOM"<<endl;
}

void PrinterInputBuilder::onHead() {
	cout<<"FIND HEAD"<<endl;
}

void PrinterInputBuilder::onBodyLiteral() {
	cout<<"FIND BODY LIT"<<endl;
}

void PrinterInputBuilder::onBody() {
	cout<<"FIND BODY"<<endl;
}

void PrinterInputBuilder::onNafLiteral(bool naf) {
	cout<<"FIND NAF "<<naf<<endl;
}

void PrinterInputBuilder::onAtom(bool isStrongNeg) {
	cout<<"FIND ATOM "<<isStrongNeg<<endl;
}

void PrinterInputBuilder::onExistentialAtom() {
}

void PrinterInputBuilder::onPredicateName(char* name) {
	cout<<"FIND PREDICATE "<<name<<endl;
}

void PrinterInputBuilder::onExistentialVariable(char* var) {
}

void PrinterInputBuilder::onEqualOperator() {
	cout<<"FIND OP"<<endl;
}

void PrinterInputBuilder::onUnequalOperator() {
	cout<<"FIND OP"<<endl;
}

void PrinterInputBuilder::onLessOperator() {
	cout<<"FIND OP"<<endl;
}

void PrinterInputBuilder::onLessOrEqualOperator() {
	cout<<"FIND OP"<<endl;
}

void PrinterInputBuilder::onGreaterOperator() {
	cout<<"FIND OP"<<endl;
}

void PrinterInputBuilder::onGreaterOrEqualOperator() {
	cout<<"FIND OP"<<endl;
}

void PrinterInputBuilder::onTerm(char* value) {
	cout<<"FIND S TERM "<<value<<endl;
}

void PrinterInputBuilder::onTerm(int value) {
	cout<<"FIND N TERM"<< value<<endl;
}

void PrinterInputBuilder::onUnknownVariable() {
	cout<<"FIND UKNOW"<<endl;
}

void PrinterInputBuilder::onFunction(char* functionSymbol, int nTerms) {
	cout<<"FIND FUNCTION "<<functionSymbol<<" "<<nTerms<<endl;
}

void PrinterInputBuilder::onTermDash() {
	cout<<"FIND DASH"<<endl;
}

void PrinterInputBuilder::onTermParams() {
	cout<<"FIND PARAMS"<<endl;
}

void PrinterInputBuilder::onTermRange(char* lowerBound, char* upperBound) {
	cout<<"FIND RANGE "<<lowerBound<<" "<<upperBound<<endl;
}

void PrinterInputBuilder::onArithmeticOperation(char arithOperator) {
	cout<<"FIND OP "<<arithOperator<<endl;
}

void PrinterInputBuilder::onWeightAtLevels(int nWeight, int nLevel, int nTerm) {
}

void PrinterInputBuilder::onChoiceLowerGuard() {
}

void PrinterInputBuilder::onChoiceUpperGuard() {
}

void PrinterInputBuilder::onChoiceElementAtom() {
}

void PrinterInputBuilder::onChoiceElementLiteral() {
}

void PrinterInputBuilder::onChoiceElement() {
}

void PrinterInputBuilder::onChoiceAtom() {
}

void PrinterInputBuilder::onBuiltinAtom() {
	cout<<"FIND BUILT"<<endl;
}

void PrinterInputBuilder::onAggregateLowerGuard() {
}

void PrinterInputBuilder::onAggregateUpperGuard() {
}

void PrinterInputBuilder::onAggregateFunction(char* functionSymbol) {
}

void PrinterInputBuilder::onAggregateGroundTerm(char* value, bool dash) {
}

void PrinterInputBuilder::onAggregateVariableTerm(char* value) {
}

void PrinterInputBuilder::onAggregateUnknownVariable() {
}

void PrinterInputBuilder::onAggregateNafLiteral() {
}

void PrinterInputBuilder::onAggregateElement() {
}

void PrinterInputBuilder::onAggregate(bool naf) {
}

}
} /* namespace DLV2_Grounder */

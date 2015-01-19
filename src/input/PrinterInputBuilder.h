/*
 * TestInputBuilder.h
 *
 *  Created on: Jan 17, 2015
 *      Author: david
 */

#ifndef TESTINPUTBUILDER_H_
#define TESTINPUTBUILDER_H_

#include "InputBuilder.h"

namespace DLV2 {
namespace grounder {

using namespace std;

class PrinterInputBuilder: public DLV2::InputBuilder {
public:
	PrinterInputBuilder();
	virtual ~PrinterInputBuilder();

    virtual void onDirective( char* directiveName, char* directiveValue );
    virtual void onRule() ;
    virtual void onConstraint() ;
    virtual void onWeakConstraint() ;
    virtual void onQuery() ;
    virtual void onHeadAtom() ;
    virtual void onHead() ;
    virtual void onBodyLiteral() ;
    virtual void onBody() ;
    virtual void onNafLiteral( bool naf = false ) ;
    virtual void onAtom( bool isStrongNeg = false ) ;
    virtual void onExistentialAtom() ;
    virtual void onPredicateName( char* name ) ;
    virtual void onExistentialVariable( char* var ) ;
    virtual void onEqualOperator() ;
    virtual void onUnequalOperator() ;
    virtual void onLessOperator() ;
    virtual void onLessOrEqualOperator() ;
    virtual void onGreaterOperator() ;
    virtual void onGreaterOrEqualOperator() ;
    virtual void onTerm( char* value ) ;
    virtual void onTerm( int value ) ;
    virtual void onUnknownVariable() ;
    virtual void onFunction( char* functionSymbol, int nTerms ) ;
    virtual void onTermDash() ;
    virtual void onTermParams() ;
    virtual void onTermRange( char* lowerBound, char* upperBound ) ;
    virtual void onArithmeticOperation( char arithOperator ) ;
    virtual void onWeightAtLevels( int nWeight, int nLevel, int nTerm ) ;
    virtual void onChoiceLowerGuard() ;
    virtual void onChoiceUpperGuard() ;
    virtual void onChoiceElementAtom() ;
    virtual void onChoiceElementLiteral() ;
    virtual void onChoiceElement() ;
    virtual void onChoiceAtom() ;
    virtual void onBuiltinAtom() ;
    virtual void onAggregateLowerGuard() ;
    virtual void onAggregateUpperGuard() ;
    virtual void onAggregateFunction( char* functionSymbol ) ;
    virtual void onAggregateGroundTerm( char* value, bool dash = false ) ;
    virtual void onAggregateVariableTerm( char* value ) ;
    virtual void onAggregateUnknownVariable() ;
    virtual void onAggregateNafLiteral() ;
    virtual void onAggregateElement() ;
    virtual void onAggregate( bool naf = false ) ;
};

}

}
/* namespace DLV2_Grounder */
#endif /* TESTINPUTBUILDER_H_ */

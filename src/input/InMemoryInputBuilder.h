/*
 * InMemoryInputBuilder.h
 *
 *  Created on: Jan 19, 2015
 *      Author: davide
 */

#ifndef SRC_INPUT_INMEMORYINPUTBUILDER_H_
#define SRC_INPUT_INMEMORYINPUTBUILDER_H_

#include <list>

#include "InputBuilder.h"
#include "../grounder/table/TermTable.h"
#include "../grounder/table/PredicateTable.h"
#include "../grounder/atom/Atom.h"
#include "../grounder/statement/Rule.h"
#include "../grounder/term/ConstantTerm.h"
#include "../grounder/term/VariableTerm.h"
#include "../grounder/term/ArithTerm.h"
#include "../grounder/term/FunctionTerm.h"
#include "../grounder/ground/StatementDependency.h"
#include "../grounder/table/Instance.h"

using namespace std;

namespace DLV2 {
namespace grounder {

class InMemoryInputBuilder: public InputBuilder {
public:
	InMemoryInputBuilder();
	virtual ~InMemoryInputBuilder();

    virtual void onDirective( char* directiveName, char* directiveValue ) ;
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

    void newTerm(char*);


private:

    TermTable *termTable;

    PredicateTable *predicateTable;

    StatementDependency* statementDependency;

    InstanceTable* instancesTable;

    vector<Term*> terms_parsered;

    Atom *currentAtom;

	Rule *currentRule;

	Binop currentBinop;


};

} /* namespace grounder */
} /* namespace DLV2 */

#endif /* SRC_INPUT_INMEMORYINPUTBUILDER_H_ */

/*
 *
 *  Copyright 2014 Mario Alviano, Carmine Dodaro, Francesco Ricca and
 *                 Pierfrancesco Veltri.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "DBInputBuilder.h"
#include "../../util/Utils.h"

namespace DLV2{ namespace DB{

using namespace std;    
    
DBInputBuilder::DBInputBuilder(
    DBConnection& con ):
        currentAtom(NULL),    
        currentLiteral(NULL),
        query(NULL),
        nTermsForWeight(0),
        nTermsForLevel(0),
        nTermsAfterLevel(0),
        lowerGuard(NULL),
        upperGuard(NULL)
{
    program = new Program(con);
    graph = new LabeledDependencyGraph<>();
}
    

void 
DBInputBuilder::onRule()
{
    program->createAndAddRule(head,body);
    head.clear();
    body.clear();
}

void
DBInputBuilder::onConstraint()
{
    // TODO 
    // How to handle constraints?
    
    body.clear();
}

void
DBInputBuilder::onWeakConstraint()
{
    // TODO
    // How to handle weak constraints?
    
    // At the moment we are simply deleting the terms from the stack which are 
    // involved in the current weak constraint.
    assert_msg( nTermsForWeight +
            nTermsForLevel +
            nTermsAfterLevel <= 
            termStack.size(),
            "The terms' stack has not a sufficient number of terms "
            "for building weight, level and terms of the current "
            "weak constraint.");
    // On top of the terms' stack there should be the list of terms 
    // in the reverse order.
    if( nTermsAfterLevel > 0 )
    {
        unsigned stackSize = termStack.size();
        for( unsigned i=0; i<nTermsAfterLevel; i++ )
        {
            delete termStack[stackSize-nTermsAfterLevel+i];
        }
        termStack.erase(termStack.begin()+(stackSize-nTermsAfterLevel),termStack.end());
    }
    // Then, we should have the level.
    if( nTermsForLevel )
    {
        delete termStack.back();
        termStack.pop_back();
    }
    // Finally, the weight.
    if( nTermsForWeight )
    {
        delete termStack.back();
        termStack.pop_back();
    }
    body.clear();
}

void
DBInputBuilder::onQuery()
{
    assert_msg( currentAtom, "Trying to adding a null query atom" );
    if( query != NULL )
    {
        cout << "Query " << (*currentAtom) << " replaces " << query << endl;
        delete query;
    }
    query = currentAtom;
}

void
DBInputBuilder::onHeadAtom()
{
    assert_msg( currentAtom, "Trying to adding a null atom" );
    head.push_back(currentAtom);
}

void 
DBInputBuilder::onHead()
{
    
}

void
DBInputBuilder::onBodyLiteral()
{
    assert_msg( currentLiteral, "Trying to adding a null literal" );
    body.push_back(currentLiteral);
}

void
DBInputBuilder::onBody()
{
    
}

void
DBInputBuilder::onNafLiteral( 
    bool naf )
{
    assert_msg( currentAtom, "Trying to finalize a literal without any atom" );
    currentLiteral = program->createLiteral(currentAtom,naf);
}

void
DBInputBuilder::onAtom( 
    bool isStrongNeg )
{
    assert_msg( predName.length() > 0, 
            "Trying to finalize an atom with a null predicate name" );
    
    currentAtom = program->createAtom(predName, termStack, isStrongNeg);
    termStack.clear();
    predName = "";
}

void
DBInputBuilder::onExistentialAtom()
{
    // TODO
}

void
DBInputBuilder::onPredicateName( 
    char* name )
{
    assert_msg( name, "Trying to create an atom with a null predicate name" );
    predName.assign(name);
}

void
DBInputBuilder::onExistentialVariable( 
    char* var )
{
    // TODO
}

void
DBInputBuilder::onEqualOperator()
{
    binop.assign("=");
}

void
DBInputBuilder::onUnequalOperator()
{
    binop.assign("<>");
}

void
DBInputBuilder::onLessOperator()
{
    binop.assign("<");
}

void
DBInputBuilder::onLessOrEqualOperator()
{
    binop.assign("<=");
}

void
DBInputBuilder::onGreaterOperator()
{
    binop.assign(">");
}

void
DBInputBuilder::onGreaterOrEqualOperator()
{
    binop.assign(">=");
}

void
DBInputBuilder::onTerm( 
    char* value )
{
    newTerm(value,termStack);
}

void
DBInputBuilder::onTerm( 
    int value )
{
    Term* currentTerm = NULL;
    
    currentTerm = program->createIntegerConstant(value);
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        termStack.push_back(currentTerm);
    }
}

void
DBInputBuilder::onUnknownVariable()
{
    Term* currentTerm = NULL;
    
    currentTerm = program->createVariable(string("_"));
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        termStack.push_back(currentTerm);
    }
}

void 
DBInputBuilder::onFunction( 
    char* functionSymbol, 
    int nTerms )
{
    // TODO
    // How to handle functions?
    
    // Consume nTerms from the stack.
    unsigned newSize = termStack.size()-nTerms;
    termStack.erase(termStack.begin()+newSize,termStack.end());
}

void 
DBInputBuilder::onTermDash()
{
    // TODO 
    // How to handle dashed terms?
    
    // Consume one term from the stack.
    termStack.pop_back();
}

void 
DBInputBuilder::onTermParams()
{
    // TODO 
    // How to handle parametric terms?
    
    // Consume one term from the stack.
    termStack.pop_back();
}

void 
DBInputBuilder::onTermRange( 
    char* lowerBound, 
    char* upperBound )
{
    // TODO
    // How to handle a terms range?
}

void 
DBInputBuilder::onArithmeticOperation( 
    char arithOperator )
{
    // TODO
    // How to handle arithmetic operations?
    
    // The right and left operands are on top of the stack.
    termStack.pop_back();
    termStack.pop_back();
}

void 
DBInputBuilder::onWeightAtLevels( 
    int nWeight, 
    int nLevel, 
    int nTerm )
{
    nTermsForWeight = nWeight; 
    nTermsForLevel = nLevel;
    nTermsAfterLevel = nTerm;
}

void 
DBInputBuilder::onChoiceLowerGuard()
{
    // TODO
}

void 
DBInputBuilder::onChoiceUpperGuard()
{
    // TODO
}

void 
DBInputBuilder::onChoiceElementAtom()
{
    // TODO
}

void 
DBInputBuilder::onChoiceElementLiteral()
{
    // TODO
}

void 
DBInputBuilder::onChoiceElement()
{
    // TODO
}

void 
DBInputBuilder::onChoiceAtom()
{
    // TODO
}
    
void 
DBInputBuilder::onBuiltinAtom()
{
    // The operands should be on top of the terms' stack.
    assert_msg( termStack.size() > 1,
            "Trying to create an invalid builtin atom" );
    Term* rightOperand = termStack.back();
    termStack.pop_back();
    Term* leftOperand = termStack.back();
    termStack.pop_back();
    
    currentAtom = program->createBuiltinAtom(leftOperand,binop,rightOperand);
    termStack.clear();
    predName = "";
}
 
void 
DBInputBuilder::onAggregateLowerGuard() 
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null aggregate lower guard" );
    lowerGuard = termStack.back();
    termStack.pop_back();
    lowerBinop.assign(binop);
}

void 
DBInputBuilder::onAggregateUpperGuard()
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null choice-right term" );
    upperGuard = termStack.back();
    termStack.pop_back();
    upperBinop.assign(binop);
}
    
void 
DBInputBuilder::onAggregateFunction( 
    char* functionSymbol )
{
    assert_msg( functionSymbol, "Trying to create an aggregate with a null function" );
    aggregateFunction.assign(functionSymbol);
}
    
void 
DBInputBuilder::onAggregateGroundTerm( 
    char* value, 
    bool dash )
{
    newTerm(value,aggregateElementTerms,dash);
}
    
void 
DBInputBuilder::onAggregateVariableTerm( 
    char* value )
{
    newTerm(value,aggregateElementTerms);
}
    
void 
DBInputBuilder::onAggregateUnknownVariable()
{
    aggregateElementTerms.push_back(program->createVariable(string("_")));
}
    
void 
DBInputBuilder::onAggregateNafLiteral()
{
    // The current literal should be pointed 
    // by currentLiteral;
    assert_msg( currentLiteral, "Trying to adding a null literal" );
    aggregateElementLiterals.push_back(currentLiteral);
}

void 
DBInputBuilder::onAggregateElement()
{
    assert_msg( (aggregateElementTerms.size() > 0 
            && aggregateElementLiterals.size() > 0),
            "Invalid aggregate element.");
    AggregateElement* element = 
            program->createAggregateElement(aggregateElementTerms,aggregateElementLiterals);
    aggregateElements.push_back(element);
    aggregateElementTerms.clear();
    aggregateElementLiterals.clear();
}
    
void 
DBInputBuilder::onAggregate( 
    bool naf )
{
    assert_msg( aggregateFunction.length() > 0, 
            "Trying to finalize an aggregate with a null function symbol" );
    assert_msg( aggregateElements.size() > 0, 
            "Trying to finalize an aggregate without elements" );
    assert_msg( lowerGuard || upperGuard, 
            "Trying to finalize an aggregate without any guards" );

    currentLiteral = program->createAggregateLiteral(
            lowerGuard,
            lowerBinop,
            upperGuard,
            upperBinop,
            aggregateFunction,
            aggregateElements,
            naf);
    aggregateElements.clear();
    lowerBinop = "";
    lowerGuard = NULL;
    upperBinop = "";
    upperGuard = NULL;
    aggregateFunction = "";
}
    
void 
DBInputBuilder::newTerm( 
    char* value,
    vector<Term*>& target,
    bool dash )
{
    Term* currentTerm = NULL;
    
    if( value[0] >= 'A' && value[0] <='Z' ) // Variable
    {
        currentTerm = program->createVariable(value);
    }
    else if( Utils::isNumeric(value,10) ) // Numeric constant
    {
        int val = atoi(value);
        if( dash )
            val = 0 - val;
        currentTerm = program->createIntegerConstant(val);
    }
    else // String
    {
        currentTerm = program->createStringConstant(value);
    }
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        target.push_back(currentTerm);
    }
}

};};

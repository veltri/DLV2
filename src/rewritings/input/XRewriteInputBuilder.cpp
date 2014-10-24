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

/* 
 * File:   XRewriteInputBuilder.cpp
 * Author: pierfrancesco
 *
 * Created on 21 ottobre 2014, 16.01
 */

#include "XRewriteInputBuilder.h"

using namespace std;
using namespace DLV2::REWRITERS;

void
XRewriteInputBuilder::onRule()
{
}

void
XRewriteInputBuilder::onConstraint()
{
}

void
XRewriteInputBuilder::onWeakConstraint()
{
}

void
XRewriteInputBuilder::onQuery()
{
}

void
XRewriteInputBuilder::onHeadAtom()
{
}

void
XRewriteInputBuilder::onHead()
{
}

void
XRewriteInputBuilder::onBodyLiteral()
{
}

void
XRewriteInputBuilder::onBody()
{
}

void
XRewriteInputBuilder::onNafLiteral(
    bool naf )
{
}

void
XRewriteInputBuilder::onAtom(
    bool isStrongNeg )
{
}

void
XRewriteInputBuilder::onExistentialAtom()
{
}

void
XRewriteInputBuilder::onPredicateName(
    char* name )
{
}

void
XRewriteInputBuilder::onExistentialVariable(
    char* var )
{
}

void
XRewriteInputBuilder::onEqualOperator()
{
}

void
XRewriteInputBuilder::onUnequalOperator()
{
}

void
XRewriteInputBuilder::onLessOperator()
{
}

void
XRewriteInputBuilder::onLessOrEqualOperator()
{
}

void
XRewriteInputBuilder::onGreaterOperator()
{
}

void
XRewriteInputBuilder::onGreaterOrEqualOperator()
{
}

void
XRewriteInputBuilder::onTerm(
    char* value )
{
}

void
XRewriteInputBuilder::onTerm(
    int value )
{
}

void
XRewriteInputBuilder::onUnknownVariable()
{
}

void
XRewriteInputBuilder::onFunction(
    char* functionSymbol,
    int nTerms )
{
}

void
XRewriteInputBuilder::onTermDash()
{
}

void
XRewriteInputBuilder::onTermParams()
{
}

void
XRewriteInputBuilder::onTermRange(
    char* lowerBound,
    char* upperBound )
{
}

void
XRewriteInputBuilder::onArithmeticOperation(
    char arithOperator )
{
}

void
XRewriteInputBuilder::onWeightAtLevels(
    int nWeight,
    int nLevel,
    int nTerm )
{
}

void
XRewriteInputBuilder::onChoiceLowerGuard()
{
}

void
XRewriteInputBuilder::onChoiceUpperGuard()
{
}

void
XRewriteInputBuilder::onChoiceElementAtom()
{
}

void
XRewriteInputBuilder::onChoiceElementLiteral()
{
}

void
XRewriteInputBuilder::onChoiceElement()
{
}

void
XRewriteInputBuilder::onChoiceAtom()
{
}

void
XRewriteInputBuilder::onBuiltinAtom()
{
}

void
XRewriteInputBuilder::onAggregateLowerGuard()
{
}

void
XRewriteInputBuilder::onAggregateUpperGuard()
{
}

void
XRewriteInputBuilder::onAggregateFunction(
    char* functionSymbol )
{
}

void
XRewriteInputBuilder::onAggregateGroundTerm(
    char* value,
    bool dash )
{
}

void
XRewriteInputBuilder::onAggregateVariableTerm(
    char* value )
{
}

void
XRewriteInputBuilder::onAggregateUnknownVariable()
{
}

void
XRewriteInputBuilder::onAggregateNafLiteral()
{
}

void
XRewriteInputBuilder::onAggregateElement()
{
}

void
XRewriteInputBuilder::onAggregate(
    bool naf )
{
}

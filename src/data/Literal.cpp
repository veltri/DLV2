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

#include "Literal.h"

Literal::Literal( 
    const Atom& a, 
    bool neg ): 
        isNegative(neg),
        isAggregate(false),
        lowerGuard(NULL),
        lowerBinop(""),
        upperGuard(NULL),
        upperBinop(""),
        aggregateFunction("")
{
    atom = new Atom(a);
}

// Aggregate's constructor
Literal::Literal( 
    Term* lGuard, 
    string lOp, 
    Term* uGuard,
    string uOp,
    string function,
    vector<AggregateElement> aElements,
    bool naf):
        atom(NULL),
        isNegative(naf),
        isAggregate(true),
        lowerBinop(lOp),
        upperBinop(uOp),
        aggregateFunction(function),
        aggregateElements(aElements)
{
    if( lGuard != NULL )
        lowerGuard = new Term(*lGuard);
    else
        lowerGuard = NULL;
    if( uGuard != NULL )
        upperGuard = new Term(*uGuard);
    else
        upperGuard = NULL;
}

Literal::Literal( 
    const Literal& l ): 
        isNegative(l.isNegative),
        isAggregate(l.isAggregate),
        lowerBinop(l.lowerBinop),
        upperBinop(l.upperBinop),
        aggregateFunction(l.aggregateFunction),
        aggregateElements(l.aggregateElements)
{ 
    if( l.atom != NULL )
        atom = new Atom(*l.atom);
    else 
        atom = NULL;
    if( l.lowerGuard != NULL )
        lowerGuard = new Term(*l.lowerGuard);
    else
        lowerGuard = NULL;
    if( l.upperGuard != NULL )
        upperGuard = new Term(*l.upperGuard);
    else
        upperGuard = NULL;
}

Literal::~Literal() 
{
    if( lowerGuard )
        delete lowerGuard;
    if( upperGuard )
        delete upperGuard;
    if( atom )
        delete atom;
}

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
    Atom a, 
    bool neg ): 
        atom(a), 
        isNegative(neg),
        isAggregate(false),
        lowerGuard(NULL),
        lowerBinop(""),
        upperGuard(NULL),
        upperBinop(""),
        aggregateFunction("")
{
    
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
        isNegative(naf),
        isAggregate(true),
        lowerGuard(lGuard),
        lowerBinop(lOp),
        upperGuard(uGuard),
        upperBinop(uOp),
        aggregateFunction(function),
        aggregateElements(aElements)
{
    
}

Literal::Literal( 
    const Literal& l ): 
        atom(l.atom), 
        isNegative(l.isNegative),
        isAggregate(l.isAggregate),
        lowerGuard(l.lowerGuard),
        lowerBinop(l.lowerBinop),
        upperGuard(l.upperGuard),
        upperBinop(l.upperBinop),
        aggregateFunction(l.aggregateFunction),
        aggregateElements(l.aggregateElements)
{ 

}
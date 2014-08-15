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

#include "DBLiteral.h"

using namespace std;
using namespace DLV2::DB;
    
DBLiteral::DBLiteral( 
    DBAtom* a, 
    bool neg ):
        atom(a),
        isNegative(neg),
        aggregate(false),
        lowerGuard(NULL),
        lowerBinop(""),
        upperGuard(NULL),
        upperBinop(""),
        aggregateFunction("")
{
}

// Aggregates' constructor
DBLiteral::DBLiteral( 
    DBTerm* lGuard, 
    const string& lOp, 
    DBTerm* uGuard,
    const string& uOp,
    const string& function,
    const vector<DBAggregateElement*>& aElements,
    bool naf):
        atom(NULL),
        isNegative(naf),
        aggregate(true),
        lowerGuard(lGuard),
        lowerBinop(lOp),
        upperGuard(uGuard),
        upperBinop(uOp),
        aggregateFunction(function),
        aggregateElements(aElements)
{
}

DBLiteral::DBLiteral( 
    const DBLiteral& l ): 
        isNegative(l.isNegative),
        aggregate(l.aggregate),
        lowerBinop(l.lowerBinop),
        upperBinop(l.upperBinop),
        aggregateFunction(l.aggregateFunction),
        aggregateElements(l.aggregateElements)
{ 
    if( l.atom != NULL )
        atom = new DBAtom(*l.atom);
    else 
        atom = NULL;
    if( l.lowerGuard != NULL )
        lowerGuard = new DBTerm(*l.lowerGuard);
    else
        lowerGuard = NULL;
    if( l.upperGuard != NULL )
        upperGuard = new DBTerm(*l.upperGuard);
    else
        upperGuard = NULL;
}

DBLiteral::~DBLiteral() 
{
    if( lowerGuard != NULL )
        delete lowerGuard;
    if( upperGuard != NULL )
        delete upperGuard;
    if( atom != NULL )
        delete atom;
    for( unsigned i=0; i<aggregateElements.size(); i++ )
        if( aggregateElements[i] != NULL )
            delete aggregateElements[i];
}
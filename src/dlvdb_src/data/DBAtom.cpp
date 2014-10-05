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

#include "DBAtom.h"
#include "DBProgram.h"

using namespace std;
using namespace DLV2::DB;
    
// Classical atoms
DBAtom::DBAtom(
    const DBProgram& ownerProgr,
    index_t predIdx, 
    const vector<DBTerm*>& tList, 
    bool tNeg ):
        ownerProgram(ownerProgr),
        predIndex(predIdx),
        trueNegated(tNeg),
        terms(tList),
        builtin(false),
        leftOp(NULL),
        binOp(""),
        rightOp(NULL),
        aggregate(false),
        lowerGuard(NULL),
        lowerBinop(""),
        upperGuard(NULL),
        upperBinop(""),
        aggregateFunction("")
{
}

// Builtins
DBAtom::DBAtom(
    const DBProgram& ownerProgr,
    DBTerm* left,
    const string& binop,
    DBTerm* right):
        ownerProgram(ownerProgr),
        trueNegated(false),
        builtin(true),
        leftOp(left),
        binOp(binop),
        rightOp(right),
        aggregate(false),
        lowerGuard(NULL),
        lowerBinop(""),
        upperGuard(NULL),
        upperBinop(""),
        aggregateFunction("")
{
    assert_msg( (left != NULL && right != NULL), "Builtin operands not valid.");
}

// Aggregates' constructor
DBAtom::DBAtom( 
    const DBProgram& ownerProgr,
    index_t predIdx,
    DBTerm* lGuard, 
    const string& lOp, 
    DBTerm* uGuard,
    const string& uOp,
    const string& function,
    const vector< DBAggregateElement* >& aElements ):
        ownerProgram(ownerProgr),
        predIndex(predIdx),
        trueNegated(false),
        builtin(false),
        leftOp(NULL),
        binOp(""),
        rightOp(NULL),
        aggregate(true),
        lowerGuard(lGuard),
        lowerBinop(lOp),
        upperGuard(uGuard),
        upperBinop(uOp),
        aggregateFunction(function),
        aggregateElements(aElements)
{
}

// Copy constructor
DBAtom::DBAtom(
    const DBAtom& a ):
        ownerProgram(a.ownerProgram),
        predIndex(a.predIndex),
        trueNegated(a.trueNegated),
        terms(a.terms),
        builtin(a.builtin),
        binOp(a.binOp),
        aggregate(a.aggregate),
        lowerBinop(a.lowerBinop),
        upperBinop(a.upperBinop),
        aggregateFunction(a.aggregateFunction),
        aggregateElements(a.aggregateElements)
{
    if( a.builtin )
    {
        assert_msg( (a.leftOp != NULL && a.rightOp != NULL), "Builtin operands not valid.");
        leftOp = new DBTerm(*a.leftOp);
        rightOp = new DBTerm(*a.rightOp);
        lowerGuard = NULL;
        upperGuard = NULL;
    }
    else if( a.aggregate )
    {
        leftOp = NULL;
        rightOp = NULL;
        if( a.lowerGuard != NULL )
            lowerGuard = new DBTerm(*a.lowerGuard);
        else
            lowerGuard = NULL;
        if( a.upperGuard != NULL )
            upperGuard = new DBTerm(*a.upperGuard);
        else
            upperGuard = NULL;
    }
    else
    {
        leftOp = NULL;
        rightOp = NULL;
        lowerGuard = NULL;
        upperGuard = NULL;
    }
}

DBAtom::~DBAtom()
{
    if( lowerGuard != NULL )
        delete lowerGuard;
    if( upperGuard != NULL )
        delete upperGuard;
    for( unsigned i=0; i<aggregateElements.size(); i++ )
    {
        assert_msg( aggregateElements[i] != NULL, "Trying to destroy an aggregate literal with a null element." );
        delete aggregateElements[i];
    }
    if( leftOp != NULL )
        delete leftOp;
    if( rightOp != NULL )
        delete rightOp;
    for( unsigned i=0; i<terms.size(); i++ )
    {
        assert_msg( terms[i] != NULL, "Trying to destroy an atom with a null term." );
        delete terms[i];
    }
}

const std::string& 
DBAtom::getPredicateName() const 
{
    assert_msg( !isBuiltin(), "Builtin atoms have no names" );
    return ownerProgram.getPredicateNamesTable().getName(predIndex);
}

unsigned
DBAtom::getArity() const
{
    assert_msg( (!isBuiltin() && !isAggregate()), "Builtin and aggregate atoms have no arities" );
    return ownerProgram.getPredicateNamesTable().getArity(predIndex);
}

bool
DBAtom::isAssignmentAggregate() const
{
    if( isAggregate() &&
            lowerGuard != NULL && 
            upperGuard != NULL && 
            lowerBinop == "<=" &&
            upperBinop == "<=" &&
            *lowerGuard == *upperGuard )
        return true;
            
    return false;
}


bool
DBAtom::isAssignmentBuiltin() const
{
    // Assert: isBuiltin()  <--> (leftOp && rightOp)
    assert_msg( (!isBuiltin() || (leftOp != NULL && rightOp != NULL) ), "Not a valid builtin" );
    assert_msg( (!(leftOp != NULL && rightOp != NULL) || isBuiltin()), "Not a valid builtin" );
    // By means of the above assert we are sure that if
    // the current atom is a builtin (an equality one,
    // in this case), then its operands are not null.
    if( isEqualityBuiltin() &&
            ( leftOp->isConst() ||
              leftOp->isInt() ||
              rightOp->isConst() ||
              rightOp->isInt() ) )
        return true;
    return false;
}

const std::string&
DBAtom::getAggregateName() const
{
    assert_msg( isAggregate(), "The atom is not an aggregate" );
    return ownerProgram.getPredicateNamesTable().getName(predIndex);
}

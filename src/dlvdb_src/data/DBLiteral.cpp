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
        isNegative(neg)
{
    assert_msg( a != NULL, "Null atom" );
}

DBLiteral::DBLiteral( 
    const DBLiteral& l ): 
        isNegative(l.isNegative)
{ 
    assert_msg( l.atom != NULL, "Null atom" );
    atom = new DBAtom(*l.atom);
}

DBLiteral::~DBLiteral() 
{
    assert_msg( atom != NULL, "Null atom" );
    delete atom;
}

bool
DBLiteral::isRegularAtom()
const
{
    assert_msg( atom != NULL, "Null atom" );
    return atom->isRegularAtom();
}

bool
DBLiteral::isPropositional()
const
{
    assert_msg( atom != NULL, "Null atom" );
    return atom->isPropositional();
}

bool
DBLiteral::isBuiltin() 
const
{
    assert_msg( atom != NULL, "Null atom" );
    return atom->isBuiltin();
}

bool
DBLiteral::isAssignmentBuiltin() const
{
    assert_msg( atom != NULL, "Null atom" );
    return atom->isAssignmentBuiltin();
}

bool
DBLiteral::isAggregate() const
{ 
    assert_msg( atom != NULL, "Null atom" );
    return atom->isAggregate();
}

bool
DBLiteral::isAssignmentAggregate() const
{
    assert_msg( atom != NULL, "Null atom" );
    return atom->isAssignmentAggregate();
}

bool
DBLiteral::isSaviour() const
{
    // A saviour literal is a positive literal which is neither
    // builtin nor aggregate (except assignment aggregates, i.e.,
    // aggregates of the form: X <= aggregate( Vars : Conjunction ) <= X;
    // because this kind of aggregates fixes a value for X).
    assert_msg( atom != NULL, "Null atom" );
    return !isNaf() &&
            ( !isBuiltin() || isAssignmentBuiltin() ) &&
            ( !isAggregate() || isAssignmentAggregate() );
}

bool
DBLiteral::safetyMustBeChecked() const
{
    // For assignment aggregates you must check safety of their aggregate set.
    return isNaf() || ( isBuiltin() && !isAssignmentBuiltin() )  || isAggregate();
}

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
DBLiteral::isBuiltin() 
const
{
    assert_msg( atom != NULL, "Null atom" );
    return atom->isBuiltin();
}

bool
DBLiteral::isAggregate() const
{ 
    assert_msg( atom != NULL, "Null atom" );
    return atom->isAggregate();
}
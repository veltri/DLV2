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

#include "Atom.h"

namespace DLV2{ namespace DB{

using namespace std;
    
// Builtins
Atom::Atom(
    Term* left,
    const string& binop,
    Term* right):
        predicateName(""),
        arity(0),
        trueNegated(false),
        builtin(true),
        leftOp(left),
        binOp(binop),
        rightOp(right)
{
}

// Classical atoms
Atom::Atom(
    const string& name, 
    const vector<Term*>& tList, 
    bool tNeg ):
        predicateName(name),
        arity(tList.size()),
        trueNegated(tNeg),
        terms(tList),
        builtin(false),
        leftOp(NULL),
        binOp(""),
        rightOp(NULL)
{
}

// Classical atoms
Atom::Atom(
    char* name, 
    const vector<Term*>& tList, 
    bool tNeg ):
        predicateName(name),
        arity(tList.size()),
        trueNegated(tNeg),
        terms(tList),
        builtin(false),
        leftOp(NULL),
        binOp(""),
        rightOp(NULL)
{
}

// Copy constructor
Atom::Atom(
    const Atom& a ):
        predicateName(a.predicateName),
        arity(a.arity),
        trueNegated(a.trueNegated),
        terms(a.terms),
        builtin(a.builtin),
        binOp(a.binOp)
{
    if( a.builtin )
    {
        assert_msg( (a.leftOp != NULL && a.rightOp != NULL), "Builtin operands not valid.");
        leftOp = new Term(*a.leftOp);
        rightOp = new Term(*a.rightOp);
    }
    else
    {
        leftOp = NULL;
        rightOp = NULL;
    }
}

Atom::~Atom()
{
    if( leftOp != NULL )
        delete leftOp;
    if( rightOp != NULL )
        delete rightOp;
    for( unsigned i=0; i<terms.size(); i++ )
        delete terms[i];
}
    
};};

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
#include "../util/Assert.h"
#include <climits>

using namespace std;
using namespace DLV2::MOCK;

// Classical atoms' constructor
Atom::Atom(  
    string name, 
    unsigned arit, 
    vector<Term> termsList,
    bool tNeg ):
        predIndex(Names::addPredicateName(name)),
        arity(arit),
        trueNegated(tNeg),
        terms(termsList),
        isBuiltin(false),
        bLeft(NULL),
        binop(""),
        bRight(NULL)
{
    
}

// Existential atoms' constructor
Atom::Atom( 
    string name, 
    unsigned arit, 
    vector<Term> termsList, 
    vector<Term> existVars ):
        predIndex(Names::addPredicateName(name)),
        arity(arit),
        trueNegated(false),
        terms(termsList),
        existentialVars(existVars),
        isBuiltin(false),
        bLeft(NULL),
        binop(""),
        bRight(NULL)
{

}
    
// Builtin atoms' constructor
Atom::Atom( 
    Term* left, 
    string bop, 
    Term* right ):
        predIndex(UINT_MAX),
        arity(0),
        trueNegated(false),
        isBuiltin(true),
        binop(bop)
{
    if( left != NULL )
        bLeft = new Term(*left);
    else
        bLeft = NULL;
    if( right != NULL )
        bRight = new Term(*right);
    else
        bRight = NULL;
}

Atom::Atom( 
    const Atom& a ): 
        predIndex(a.predIndex), 
        arity(a.arity),
        trueNegated(a.trueNegated), 
        terms(a.terms),
        existentialVars(a.existentialVars),
        isBuiltin(a.isBuiltin),
        binop(a.binop)
{
    if( a.bLeft != NULL )
        bLeft = new Term(*a.bLeft);
    else
        bLeft = NULL;
    if( a.bRight != NULL )
        bRight = new Term(*a.bRight);
    else
        bRight = NULL;
}

Atom::~Atom()
{
    if( bLeft != NULL )
        delete bLeft;
    if( bRight != NULL )
        delete bRight;
}

string 
Atom::getPredName() const 
{ 
    assert_msg( !isBuiltin, "This atom is a builtin, it has not a predicate name." );
    return Names::getPredicateName(predIndex); 
}
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

vector<string> Atom::predicateNames;
vector<unsigned> Atom::arities;
vector<string> Atom::stringConstants;
vector<int> Atom::integerConstants;

// Classical atoms' constructor
Atom::Atom(  
    string name, 
    unsigned arity, 
    vector<Term*> termsList,
    bool tNeg ):
        predIndex(Atom::addPredicateName(name,arity)),
        trueNegated(tNeg),
        terms(termsList)
{

}

// Existential atoms' constructor
Atom::Atom( 
    string name, 
    unsigned arity, 
    vector<Term*> termsList, 
    vector<Variable> existVars ):
        predIndex(Atom::addPredicateName(name,arity)),
        trueNegated(false),
        terms(termsList),
        existentialVars(existVars)
{

}

Atom::Atom( 
    const Atom& a ): 
        predIndex(a.predIndex), 
        trueNegated(a.trueNegated), 
        terms(a.terms),
        existentialVars(a.existentialVars)
{
    
}

unsigned 
Atom::addPredicateName( 
    string name,
    unsigned arity )
{
    bool found = false;
    unsigned index;
    for( unsigned i=0; i<Atom::predicateNames.size() && !found; i++ )
        if( Atom::predicateNames[i] == name )
        {
            index = i;
            found = true;
        }
    if( !found )
    {
        Atom::predicateNames.push_back(name);
        Atom::arities.push_back(arity);
        return Atom::predicateNames.size()-1;
    }
    else 
    {
        if( Atom::arities[index] != arity )
            cout << name << ": first used with arity " 
                    << arities[index]
                    << ", now seen with arity " 
                    << arity
                    << "." << endl;
        return index;
    }
}

string 
Atom::getPredicateName( 
    unsigned index )
{
    assert_msg( (index >= 0 && index < Atom::predicateNames.size()),
            "The index " << index << " is not valid." );
    return Atom::predicateNames[index];
}

unsigned 
Atom::getPredicateArity( 
    unsigned index )
{
    assert_msg( (index >= 0 && index < Atom::predicateNames.size()),
            "The index " << index << " is not valid." );
    return Atom::arities[index];
}

unsigned 
Atom::addStringConstant( 
    string constant )
{
    unsigned index;
    bool found = false;
    for( unsigned i=0; i<Atom::stringConstants.size() && !found; i++ )
        if( Atom::stringConstants[i] == constant )
        {
            index = i;
            found = true;
        }
    if( !found )
    {
        Atom::stringConstants.push_back(constant);
        return Atom::stringConstants.size()-1;
    }
    else 
        return index;
}

string 
Atom::getStringConstant( 
    unsigned index )
{
    assert_msg( (index >= 0 && index <Atom::stringConstants.size()),
            "The index " << index << " is not valid." );
    return Atom::stringConstants[index];
}

unsigned 
Atom::addIntegerConstant( 
    int constant )
{
    unsigned index;
    bool found = false;
    for( unsigned i=0; i<Atom::integerConstants.size() && !found; i++ )
        if( Atom::integerConstants[i] == constant )
        {
            index = i;
            found = true;
        }
    if( !found )
    {
        Atom::integerConstants.push_back(constant);
        return Atom::integerConstants.size()-1;
    }
    else 
        return index;
}
    
int
Atom::getIntegerConstant( 
    unsigned index )
{
    assert_msg( (index >= 0 && index < Atom::integerConstants.size()),
            "The index " << index << " is not valid." );
    return Atom::integerConstants[index];
}

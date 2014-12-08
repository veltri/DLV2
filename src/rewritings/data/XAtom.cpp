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

#include "XAtom.h"
#include "XProgram.h"

using namespace std;
using namespace DLV2::REWRITERS;

XAtom::XAtom(
    const XProgram& ownerProgr,
    index_t predIdx,
    const vector< XTerm >& tList,
    bool tNeg ):
        ownerProgram(ownerProgr),
        predIndex(predIdx),
        trueNegated(tNeg),
        terms(tList)
{
    assert_msg( ownerProgr.getPredicateNamesTable().isValidIndex(predIdx), "Predicate index not valid" );
    assert_msg( ( !tNeg || ownerProgr.getPredicateNamesTable().getItem(predIdx).isNegative() ),
            "Adding a negative predicate name like a non-negated atom" );
    for( unsigned i=0; i<terms.size(); i++ )
    {
        type.addToSchema(terms[i].getType());
        if( terms[i].isConst() )
            type.addToConstantPositions(i);
        else if( terms[i].isVar() )
            type.addToVariablePositions(i);
        else
            type.addToNullPositions(i);
    }
}

// Copy constructor
XAtom::XAtom(
    const XAtom& a ):
        ownerProgram(a.ownerProgram),
        predIndex(a.predIndex),
        trueNegated(a.trueNegated),
        terms(a.terms),
        type(a.type)
{
}

XAtom::~XAtom()
{
}

const std::string&
XAtom::getPredicateName() const
{
    return ownerProgram.getPredicateName(predIndex);
}

unsigned
XAtom::getArity() const
{
    return ownerProgram.getPredicateArity(predIndex);
}

bool
XAtom::isGround() const
{
    for( unsigned i=0; i<terms.size(); i++ )
        if( terms[i].isVar() )
            return false;
    return true;
}

bool
XAtom::operator==(
    const XAtom& atom ) const
{
    if( predIndex != atom.predIndex )
        return false;
    if( trueNegated != atom.trueNegated )
        return false;
    if( terms.size() != atom.terms.size() )
        return false;
    for( unsigned i=0; i<terms.size(); i++ )
        if( terms[i] != atom.terms[i] )
            return false;
    return true;
}

bool
XAtom::operator!=(
    const XAtom& atom ) const
{
    return !(*this == atom);
}

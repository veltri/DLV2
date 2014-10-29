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
        terms(tList),
        builtin(false),
        aggregate(false)
{
    assert_msg( ( !tNeg || ownerProgr.getPredicateNamesTable().getItem(predIdx).isNegative() ),
            "Adding a negative predicate name like a non-negated atom" );
}

// Copy constructor
XAtom::XAtom(
    const XAtom& a ):
        ownerProgram(a.ownerProgram),
        predIndex(a.predIndex),
        trueNegated(a.trueNegated),
        terms(a.terms),
        builtin(a.builtin),
        aggregate(a.aggregate)
{
}

XAtom::~XAtom()
{
}

const std::string&
XAtom::getPredicateName() const
{
    assert_msg( !isBuiltin(), "Builtin atoms have no names" );
    return ownerProgram.getPredicateNamesTable().getName(predIndex);
}

unsigned
XAtom::getArity() const
{
    assert_msg( (!isBuiltin() && !isAggregate()), "Builtin and aggregate atoms have no arities" );
    return ownerProgram.getPredicateNamesTable().getArity(predIndex);
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
    if( builtin != atom.builtin )
        return false;
    if( aggregate != atom.aggregate )
        return false;
    return true;
}

bool
XAtom::operator!=(
    const XAtom& atom ) const
{
    return !(*this == atom);
}

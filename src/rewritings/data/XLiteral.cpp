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

/* 
 * File:   XLiteral.cpp
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 12.53
 */

#include "XLiteral.h"

using namespace std;
using namespace DLV2::REWRITERS;

XLiteral::XLiteral(
    const XAtom& a,
    bool neg ):
        atom(a),
        isNegative(neg)
{
}

XLiteral::XLiteral(
    const XLiteral& l ):
        atom(l.atom),
        isNegative(l.isNegative)
{
}

XLiteral::~XLiteral()
{
}

bool
XLiteral::isSaviour() const
{
    // A saviour literal is a positive literal which is neither
    // builtin nor aggregate (except assignment aggregates, i.e.,
    // aggregates of the form: X <= aggregate( Vars : Conjunction ) <= X;
    // because this kind of aggregates fixes a value for X).
    return !isNaf();
//           && ( !isBuiltin() || isAssignmentBuiltin() )
//           && ( !isAggregate() || isAssignmentAggregate() );
}

bool
XLiteral::operator==(
    const XLiteral& literal ) const
{
    if( atom != literal.atom )
        return false;
    if( isNegative != literal.isNegative )
        return false;
    return true;
}

bool
XLiteral::operator!=(
    const XLiteral& literal ) const
{
    return !(*this == literal);
}

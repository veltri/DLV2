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
 * File:   XBody.cpp
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 17.23
 */

#include "XBody.h"

using namespace std;
using namespace DLV2::REWRITERS;

XBody::XBody(
    const unordered_set< XLiteral >& literals2 )
{
    for( const_iterator it=literals2.begin(); it!=literals2.end(); it++ )
    {
        addLiteral(*it);
    }
}

XBody::XBody(
    const XBody& body )
{
    for( const_iterator it=body.literals.begin(); it!=body.literals.end(); it++ )
    {
        addLiteral(*it);
    }
}

XBody::~XBody()
{
    literalPtrs.clear();
    literals.clear();
}

const XLiteral&
XBody::operator[](
    index_t index ) const
{
    assert_msg( (0 < index && index < literalPtrs.size()), "Index out of range" );
    return *literalPtrs[index];
}

void
XBody::addLiteral(
    const XLiteral& literal )
{
    pair< const_iterator, bool > ret = literals.insert(literal);
    if( ret.second )
    {
        literalPtrs.push_back(ret.first);
    }
}

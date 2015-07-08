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
 * File:   XNullsetTable.cpp
 * Author: cesco
 *
 * Created on 26/giu/2015, 19:21:52
 */

#include "XNullsetTable.h"
#include "XProgram.h"

using namespace DLV2::REWRITERS;
using namespace std;

XPredicateNullsets&
XNullsetTable::operator[](
    index_t predIdx )
{
    iterator it = nullsetsMap.find(predIdx);
    if( it == nullsetsMap.end() )
    {
        pair< iterator, bool > res = insert(predIdx,XPredicateNullsets(program.getPredicateArity(predIdx)));
        it = res.first;
    }
    return it->second;
}

const XPredicateNullsets&
XNullsetTable::at(
    index_t predIdx ) const
{
    const_iterator it = nullsetsMap.find(predIdx);
    assert_msg( it != nullsetsMap.end(), "Index out of range" );
    return it->second;
}

pair< XNullsetTable::iterator, bool >
XNullsetTable::insert(
    index_t predIdx,
    const XPredicateNullsets& predNullsets )
{
    return nullsetsMap.insert(pair< index_t, XPredicateNullsets >(predIdx,predNullsets));
}

bool
XNullsetTable::isEmpty(
    index_t predIdx,
    unsigned pos ) const
{
    const_iterator it = nullsetsMap.find(predIdx);
    if( it == nullsetsMap.end() )
        return true;
    else
        return it->second.at(pos).empty();
}

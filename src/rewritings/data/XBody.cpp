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
#include "../../util/Assert.h"

using namespace std;
using namespace DLV2::REWRITERS;

const XLiteral&
XBody::operator[](
    index_t index ) const
{
    assert_msg( index < literals.size(), "Index out of range" );
    return literals[index];
}

const XLiteral&
XBody::at(
    index_t index ) const
{
    assert_msg( index < literals.size(), "Index out of range" );
    return literals.at(index);
}

bool
XBody::isGround() const
{
    for( unsigned i=0; i<literals.size(); i++ )
        if( !literals[i].isGround() )
            return false;
    return true;
}

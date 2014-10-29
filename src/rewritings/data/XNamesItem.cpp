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
 * File:   XNamesItem.cpp
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 17.37
 */

#include "XNamesItem.h"

using namespace DLV2::REWRITERS;

XNamesItem::XNamesItem(
    const XNamesItem &item2 )
{
    assert_msg( this != &item2, "Cannot copy the same object" );

    name = item2.name;
    arity = item2.arity;
}

bool
XNamesItem::operator==(
    const XNamesItem &n ) const
{
    return ( arity == n.arity ) ? strcmp(getName(),n.getName()) == 0 : false;
}

bool
XNamesItem::operator!=(
    const XNamesItem &n ) const
{
    return ( arity != n.arity || strcmp(getName(),n.getName()) != 0 );
}

const char*
XNamesItem::getPositiveName() const
{
    if (isNegative())
        return getName()+1;
    else
        return getName();
}

const char*
XNamesItem::getNegativeName() const
{
    char* temp;

    if (isPositive())
    {
        temp = new char[name.length()+2];
        temp[0] = '-';
        strcpy(temp+1,name.c_str());
    }
    else
    {
        temp = new char[name.length()+1];
        strcpy(temp,name.c_str());
    }
    return temp;
}

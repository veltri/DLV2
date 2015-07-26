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
 * File:   XTerm.cpp
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 17.09
 */

#include "XTerm.h"

#include <sstream>

using namespace std;
using namespace DLV2::REWRITERS;

XTerm::XTerm(
    Type t,
    const string& txt ):
        value(-1),
        text(txt),
        type(t)
{
    assert_msg( type != Integer, "Wrong constructor" );
}

XTerm::XTerm(
    Type t,
    char* txt ):
        value(-1),
        text(txt),
        type(t)
{
    assert_msg( type != Integer, "Wrong constructor" );
}

bool
XTerm::operator==(
    const XTerm& term ) const
{
    if( getType() != term.getType() )
        return false;

    if( isInt() )
        return value == term.value;
    else
        return text == term.text;
}

bool
XTerm::operator!=(
    const XTerm& term ) const
{
    return !(*this == term);
}

XTerm&
XTerm::operator=(
    const XTerm& term )
{
    value = term.value;
    text = term.text;
    type = term.type;
    return *this;
}

bool
XTerm::operator<(
    const XTerm& term ) const
{
    stringstream t1;
    stringstream t2;
    if( getType() == Integer )
        t1 << value;
    else
        t1 << text;
    if( term.getType() == Integer )
        t2 << term.value;
    else
        t2 << term.text;

    return t1.str() < t2.str();
}

bool
XTerm::operator<=(
    const XTerm& term ) const
{
    stringstream t1;
    stringstream t2;
    if( getType() == Integer )
        t1 << value;
    else
        t1 << text;
    if( term.getType() == Integer )
        t2 << term.value;
    else
        t2 << term.text;

    return t1.str() <= t2.str();
}

bool
XTerm::operator >(
    const XTerm& term ) const
{
    return !( *this <= term );
}

bool
XTerm::operator>=(
    const XTerm& term ) const
{
    return !( *this < term );
}
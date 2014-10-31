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
 * File:   XHead.cpp
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 13.35
 */

#include "XHead.h"

using namespace std;
using namespace DLV2::REWRITERS;

XHead::XHead(
    const vector< XAtom >& atoms2 ):
        atoms(atoms2)
{
}

XHead::XHead(
    const XHead& head ):
        atoms(head.atoms)
{
}

XHead::~XHead()
{
}

const XAtom&
XHead::operator[](
    index_t index ) const
{
    assert_msg( (0 < index && index < atoms.size()), "Index out of range" );
    return atoms[index];
}

void
XHead::addAtom(
    const XAtom& atom )
{
    atoms.push_back(atom);
}

bool
XHead::isGround() const
{
    for( unsigned i=0; i<atoms.size(); i++ )
        if( !atoms[i].isGround() )
            return false;
    return true;
}

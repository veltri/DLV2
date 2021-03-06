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

#include "DBAggregateElement.h"

using namespace DLV2::DB;
   
DBAggregateElement::~DBAggregateElement()
{
    for( unsigned i=0;i<terms.size(); i++ )
    {
        assert_msg( terms[i] != NULL, "Trying to destroy an aggregate element with a null term." );
        delete terms[i];
    }
    for( unsigned i=0;i<literals.size(); i++ )
    {
        assert_msg( literals[i] != NULL, "Trying to destroy an aggregate element with a null literal." );
        delete literals[i];
    }
}
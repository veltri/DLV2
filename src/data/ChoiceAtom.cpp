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

#include "ChoiceAtom.h"

ChoiceAtom::ChoiceAtom(
    Term* lb, 
    string lo, 
    vector<ChoiceElement> ce, 
    string ro, 
    Term* rb ) :
        lowerBinop(lo),
        choices(ce),
        upperBinop(ro)        
{
    if( lb != NULL )
        lowerGuard = new Term(*lb);
    else
        lowerGuard = NULL;
    if( rb != NULL )
        upperGuard = new Term(*rb);
    else
        upperGuard = NULL;
}

ChoiceAtom::ChoiceAtom(
    const ChoiceAtom& ca ) :
        lowerBinop(ca.lowerBinop),
        choices(ca.choices),
        upperBinop(ca.upperBinop)        
{
    if( ca.lowerGuard != NULL )
        lowerGuard = new Term(*ca.lowerGuard);
    else
        lowerGuard = NULL;
    if( ca.upperGuard != NULL )
        upperGuard = new Term(*ca.upperGuard);
    else
        upperGuard = NULL;
}

ChoiceAtom::~ChoiceAtom()
{
    if( lowerGuard )
        delete lowerGuard;
    if( upperGuard )
        delete upperGuard;
}
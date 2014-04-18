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
        lowerGuard(lb),
        lowerBinop(lo),
        choices(ce),
        upperBinop(ro),
        upperGuard(rb)
        
{
    
}

ChoiceAtom::ChoiceAtom(
    const ChoiceAtom& ca ) :
       lowerGuard(ca.lowerGuard),
       lowerBinop(ca.lowerBinop),
        choices(ca.choices),
        upperBinop(ca.upperBinop),
        upperGuard(ca.upperGuard)
        
{
    
}
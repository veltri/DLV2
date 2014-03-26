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

#include "IntegerConstant.h"

IntegerConstant::IntegerConstant(
    int i ):
        Term(Atom::addIntegerConstant(i))
{
    
}

IntegerConstant::IntegerConstant(
    const IntegerConstant& i ): 
        Term(Atom::addIntegerConstant(i.index)) {
    
}

string 
IntegerConstant::toString() const
{ 
    ostringstream oss;
    oss << Atom::getIntegerConstant(index);
    return oss.str();
}

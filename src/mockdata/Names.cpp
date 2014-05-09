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

#include "Names.h"
#include "../util/Assert.h"

using namespace std;

namespace DLV2
{

vector<string> Names::predicateNames;
vector<string> Names::stringConstants;
vector<int> Names::integerConstants;

unsigned 
Names::addPredicateName( 
    string name )
{
    unsigned index = 0;
    bool found = false;
    for( unsigned i=0; i<Names::predicateNames.size() && !found; i++ )
        if( Names::predicateNames[i] == name )
        {
            index = i;
            found = true;
        }
    if( !found )
    {
        Names::predicateNames.push_back(name);
        return Names::predicateNames.size()-1;
    }
    else 
        return index;
}

string 
Names::getPredicateName( 
    unsigned index )
{
    assert_msg( (index >= 0 && index < Names::predicateNames.size()),
            "The index " << index << " is not valid." );
    return Names::predicateNames[index];
}

unsigned 
Names::addStringConstant( 
    string constant )
{
    unsigned index = 0;
    bool found = false;
    for( unsigned i=0; i<Names::stringConstants.size() && !found; i++ )
        if( Names::stringConstants[i] == constant )
        {
            index = i;
            found = true;
        }
    if( !found )
    {
        Names::stringConstants.push_back(constant);
        return Names::stringConstants.size()-1;
    }
    else 
        return index;
}

string 
Names::getStringConstant( 
    unsigned index )
{
    assert_msg( (index >= 0 && index < Names::stringConstants.size()),
            "The index " << index << " is not valid." );
    return Names::stringConstants[index];
}

unsigned 
Names::addIntegerConstant( 
    int constant )
{
    unsigned index = 0;
    bool found = false;
    for( unsigned i=0; i<Names::integerConstants.size() && !found; i++ )
        if( Names::integerConstants[i] == constant )
        {
            index = i;
            found = true;
        }
    if( !found )
    {
        Names::integerConstants.push_back(constant);
        return Names::integerConstants.size()-1;
    }
    else 
        return index;
}
    
int
Names::getIntegerConstant( 
    unsigned index )
{
    assert_msg( (index >= 0 && index < Names::integerConstants.size()),
            "The index " << index << " is not valid." );
    return Names::integerConstants[index];
}

};
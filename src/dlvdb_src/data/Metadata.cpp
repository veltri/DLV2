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

#include "Metadata.h"
#include "../../util/Assert.h"
#include <vector>
#include <bits/unordered_map.h>

namespace DLV2{ namespace DB{

using namespace std;

bool 
Metadata::pushAttribute(
    const string& name, 
    const string& type )
{
    // No need to check whether "name" has been already indexed,
    // because every attribute name is stored only once.
    attributeNames.push_back(name);
    attributeIndexes[name] = attributeNames.size()-1;
    attributeTypes.push_back(type);
    return true;
}

const string&
Metadata::getAttributeName(
    unsigned index )
{
    assert_msg( index > 0 && index <attributeNames.size(), "Attribute index out of range." );
    return attributeNames[index];
}

unsigned
Metadata::getAttributeIndex(
    const string& name )
{
    unordered_map<string,double>::const_iterator ok = attributeIndexes.find(name);
    assert_msg( ok != attributeIndexes.end(), "Attribute name not valid." );
    return ok->second;
}

unsigned
Metadata::getAttributeType(
    unsigned index )
{
    assert_msg( index > 0 && index <attributeTypes.size(), "Attribute index out of range." );
    return attributeTypes[index];
}

};};

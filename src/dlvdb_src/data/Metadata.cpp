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

namespace DLV2{ namespace DB{

using namespace std;

Metadata::Metadata(
    const string& pred, 
    unsigned a, 
    vector<string>* attrs ):
        predicateName(pred),
        arity(a)
{
    assert_msg( attrs != NULL, "Null attribute list");
    attributeNames = attrs;
    for( unsigned i=0; i<attributeNames->size(); i++ )
        attributeIndexes[(*attributeNames)[i]] = i;
}

Metadata::Metadata(
    char* pred, 
    unsigned a, 
    vector<string>* attrs ):
        predicateName(pred),
        arity(a)
{
    assert_msg( attrs != NULL, "Null attribute list");
    attributeNames = attrs;
    for( unsigned i=0; i<attributeNames->size(); i++ )
        attributeIndexes[(*attributeNames)[i]] = i;
}

Metadata::Metadata(
    const Metadata& m ):
        predicateName(m.predicateName),
        arity(m.arity),
        attributeNames(m.attributeNames),
        attributeIndexes(m.attributeIndexes)
{
}

const string&
Metadata::getAttributeName(
    unsigned index ) const
{
    assert_msg( (attributeNames != NULL && index > 0 && index <attributeNames->size()), 
            "Attribute index out of range." );
    return (*attributeNames)[index];
}

unsigned
Metadata::getAttributeIndex(
    const string& name ) const
{
    unordered_map<string,unsigned>::const_iterator ok = attributeIndexes.find(name);
    assert_msg( ok != attributeIndexes.end(), "Attribute name not valid." );
    return ok->second;
}

};};

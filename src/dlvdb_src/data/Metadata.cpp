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
#include "DBProgram.h"
#include "../../util/Assert.h"

using namespace std;
using namespace DLV2::DB;

Metadata::Metadata(
    index_t predIdx,
    string* tName,
    vector< string >* attrs ):
        predIndex(predIdx)
{
    assert_msg( tName != NULL, "Null table name");
    assert_msg( attrs != NULL, "Null attribute list");
    tableName = tName;
    attributeNames = attrs;
    for( unsigned i=0; i<attributeNames->size(); i++ )
        attributePositions[(*attributeNames)[i]] = i;
}

Metadata::Metadata(
    const Metadata& m ):
        predIndex(m.predIndex),
        attributePositions(m.attributePositions)
{
    assert_msg( m.tableName != NULL, "Null table name" );
    assert_msg( m.attributeNames != NULL, "Null attribute names vector" );
    tableName = new string(*m.tableName);
    attributeNames = new vector< string >(*m.attributeNames);
}

Metadata::~Metadata() 
{ 
    assert_msg( attributeNames != NULL, "Trying to destroy metadata with null attribute names." );
    assert_msg( tableName != NULL, "Trying to destroy metadata with null table name." );
    delete tableName;
    delete attributeNames;
}

const string&
Metadata::getTableName() const
{
    assert_msg( tableName != NULL, "Null table name" );
    return *tableName;
}

const string&
Metadata::getAttributeName(
    unsigned index ) const
{
    assert_msg( (attributeNames != NULL && index < attributeNames->size()), 
            "Attribute index out of range." );
    return attributeNames->at(index);
}

unsigned
Metadata::getAttributePosition(
    const string& name ) const
{
    unordered_map< string, unsigned >::const_iterator ok = attributePositions.find(name);
    assert_msg( ok != attributePositions.end(), "Attribute name not valid." );
    return ok->second;
}
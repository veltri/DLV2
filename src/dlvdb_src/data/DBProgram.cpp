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

#include "DBProgram.h"
#include "Metadata.h"
#include "../../util/DBConnection.h"
    
using namespace std;
using namespace DLV2::DB;

DBProgram::DBProgram( 
    const DBProgram& p ): 
        rules(p.rules), 
        schemaMapping(p.schemaMapping),
        subProgramsMapping(p.subProgramsMapping),
        connection(p.connection)
{
}

DBProgram::~DBProgram()
{
    for( SCHEMAMAP::iterator it = schemaMapping.begin();
            it != schemaMapping.end();
            it++ )
    {
        delete it->second;
    }
    schemaMapping.clear();
    for( SUBPROGRAMSMAP::iterator it = subProgramsMapping.begin();
            it != subProgramsMapping.end();
            it++ )
    {
        delete it->second;
    }
    subProgramsMapping.clear();
    for( unsigned i=0; i<rules.size(); i++ )
        delete rules[i];
}
    
DBTerm*
DBProgram::createIntegerConstant( 
    int val )
{
    return new DBTerm(val);
}

DBTerm*
DBProgram::createStringConstant( 
    const string& val )
{
    return new DBTerm(val);
}

DBTerm*
DBProgram::createStringConstant( 
    char* val )
{
    return new DBTerm(val);
}

DBTerm*
DBProgram::createVariable( 
    const string& name )
{
    return new DBTerm(0,name);
}

DBTerm*
DBProgram::createVariable( 
    char* name )
{
    return new DBTerm(0,name);
}

DBAtom*
DBProgram::createAtom( 
    const string& predName, 
    const vector<DBTerm*>& terms, 
    bool tNeg )
{
    return new DBAtom(predName,terms,tNeg);
}

DBAtom*
DBProgram::createAtom( 
    char* predName, 
    const vector<DBTerm*>& terms, 
    bool tNeg )
{
    return new DBAtom(predName,terms,tNeg);
}

DBAtom*
DBProgram::createBuiltinAtom(
    DBTerm* leftOp, 
    const string& binOp, 
    DBTerm* rightOp )
{
    return new DBAtom(leftOp,binOp,rightOp);
}

DBLiteral*
DBProgram::createLiteral(
    DBAtom* a, 
    bool naf )
{
    return new DBLiteral(a,naf);
}

DBLiteral*
DBProgram::createAggregateLiteral(
    DBTerm* lowerGuard,
    const string& lowerBinop,
    DBTerm* upperGuard, 
    const string& upperBinop, 
    const string& aggregateFunction, 
    const vector<DBAggregateElement*>& aggregateSet,
    bool isNegative )
{
    return new DBLiteral(
            lowerGuard,
            lowerBinop,
            upperGuard,
            upperBinop,
            aggregateFunction,
            aggregateSet,
            isNegative);
}

DBAggregateElement*
DBProgram::createAggregateElement( 
    const vector<DBTerm*>& terms,
    const vector<DBLiteral*>& lits )
{
    return new DBAggregateElement(terms,lits);
}

DBRule*
DBProgram::createRule( 
    const vector<DBAtom*>& head,
    const vector<DBLiteral*>& body )
{
    return new DBRule(head,body);
}

void
DBProgram::createAndAddRule( 
    const vector<DBAtom*>& head,
    const std::vector<DBLiteral*>& body )
{
    addRule(new DBRule(head,body));
}

void
DBProgram::addRule(
    DBRule* r )
{
    // Add the index of r to the set of rules having
    // p in the head for each predicate p in the head.
    const std::vector<DBAtom*>& head = r->getHead();
    for( unsigned i = 0; i < head.size(); i++ )
    {
        const DBAtom* a = head[i];//static_cast<const DBAtom*>(head[i]);
        assert_msg( a != NULL, "Null head atom." );
        // Only standard atoms can be found in the head. 
        // Thus, this control is not necessary.
        if( !a->isBuiltin() )
            addToPredicateSubProgram(a->getPredicateName(),a->getArity(),rules.size());
    }
    rules.push_back(r);
}

Metadata*
DBProgram::getMetadata(
    const std::string& predName )
{
    SCHEMAMAP::iterator it = schemaMapping.find(predName);
    if( it != schemaMapping.end() )
        return it->second;
    else
        return NULL;
}

set<unsigned>*
DBProgram::getSubProgram(
    const std::string& predName )
{
    SUBPROGRAMSMAP::iterator it = subProgramsMapping.find(predName);
    if( it != subProgramsMapping.end() )
        return it->second;
    else
        return NULL;
}

bool
DBProgram::addPredicateName(
    const string& name,
    unsigned arity )
{
    SCHEMAMAP::const_iterator it = schemaMapping.find(name);
    if( it == schemaMapping.end() )
    {
        // Retrieve the attribute list of table "name".
        vector<string>* attributeNames = NULL;
        attributeNames = getDBConnection().retrieveTableSchema(name);
        if( attributeNames != NULL && attributeNames->size() > 0 )
        {
            Metadata* data = new Metadata(name,arity,attributeNames);
            schemaMapping[name] = data; 
            return true;
        }
    }
    return false;
}
    
bool
DBProgram::addToPredicateSubProgram(
    const string& name,
    unsigned arity,
    unsigned ruleIndex )
{
    SUBPROGRAMSMAP::const_iterator it = subProgramsMapping.find(name);
    if( it == subProgramsMapping.end() )
    {
        set<unsigned>* subProgram = new set<unsigned>();
        subProgram->insert(ruleIndex);
        subProgramsMapping[name] = subProgram;
        return true;
    }
    else
    {
        pair<set<unsigned>::iterator,bool> res = it->second->insert(ruleIndex);
        return res.second;
    }
}
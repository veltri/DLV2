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

#include "Program.h"
#include "Metadata.h"
#include "../../util/DBConnection.h"

namespace DLV2{ namespace DB{
    
using namespace std;

Program::Program( 
    const Program& p ): 
        rules(p.rules), 
        schemaMapping(p.schemaMapping),
        subProgramsMapping(p.subProgramsMapping),
        connection(p.connection)
{
}

Program::~Program()
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
    
Term*
Program::createIntegerConstant( 
    int val )
{
    return new Term(val);
}

Term*
Program::createStringConstant( 
    const string& val )
{
    return new Term(val);
}

Term*
Program::createStringConstant( 
    char* val )
{
    return new Term(val);
}

Term*
Program::createVariable( 
    const string& name )
{
    return new Term(0,name);
}

Term*
Program::createVariable( 
    char* name )
{
    return new Term(0,name);
}

Atom*
Program::createAtom( 
    const string& predName, 
    const vector<Term*>& terms, 
    bool tNeg )
{
    return new Atom(predName,terms,tNeg);
}

Atom*
Program::createAtom( 
    char* predName, 
    const vector<Term*>& terms, 
    bool tNeg )
{
    return new Atom(predName,terms,tNeg);
}

Atom*
Program::createBuiltinAtom(
    Term* leftOp, 
    const string& binOp, 
    Term* rightOp )
{
    return new Atom(leftOp,binOp,rightOp);
}

Literal*
Program::createLiteral(
    Atom* a, 
    bool naf )
{
    return new Literal(a,naf);
}

Literal*
Program::createAggregateLiteral(
    Term* lowerGuard,
    const string& lowerBinop,
    Term* upperGuard, 
    const string& upperBinop, 
    const string& aggregateFunction, 
    const vector<AggregateElement*>& aggregateSet,
    bool isNegative )
{
    return new Literal(
            lowerGuard,
            lowerBinop,
            upperGuard,
            upperBinop,
            aggregateFunction,
            aggregateSet,
            isNegative);
}

AggregateElement*
Program::createAggregateElement( 
    const vector<Term*>& terms,
    const vector<Literal*>& lits )
{
    return new AggregateElement(terms,lits);
}

Rule*
Program::createRule( 
    const vector<Atom*>& head,
    const vector<Literal*>& body )
{
    return new Rule(head,body);
}

void
Program::createAndAddRule( 
    const vector<Atom*>& head,
    const std::vector<Literal*>& body )
{
    addRule(new Rule(head,body));
}

void
Program::addRule(
    Rule* r )
{
    // Retrieve table schema for each predicate in r.
    // Moreover, for each predicate p in the head, 
    // add the index of r to the set of rules 
    // having p in the head.
    const std::vector<Atom*>& head = r->getHead();
    const std::vector<Literal*>& body = r->getBody();
    for( unsigned i = 0; i < head.size(); i++ )
    {
        const Atom* a = static_cast<const Atom*>(head[i]);
        addHeadPredicate(a->getPredicateName(),a->getArity(),rules.size());
    }
    for( unsigned i = 0; i < body.size(); i++ )
    {
        const Literal* l = static_cast<const Literal*>(body[i]);
        addPredicate(l->getAtom().getPredicateName(),l->getAtom().getArity());
    }   
    rules.push_back(r);
}

Metadata*
Program::getMetadata(
    const std::string& predName )
{
    SCHEMAMAP::iterator it = schemaMapping.find(predName);
    if( it != schemaMapping.end() )
        return it->second;
    else
        return NULL;
}

set<unsigned>*
Program::getSubProgram(
    const std::string& predName )
{
    SUBPROGRAMSMAP::iterator it = subProgramsMapping.find(predName);
    if( it != subProgramsMapping.end() )
        return it->second;
    else
        return NULL;
}

bool
Program::addPredicate(
    const string& name,
    unsigned arity )
{
    SCHEMAMAP::const_iterator it = schemaMapping.find(name);
    if( it == schemaMapping.end() )
    {
        // Retrieve the attribute list of table "name".
        Metadata* data = new Metadata(name,arity,getDBConnection().retrieveTableSchema(name));   
        schemaMapping[name] = data; 
        return true;
    }
    return false;
}
    
bool
Program::addHeadPredicate(
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
    }
    else
        it->second->insert(ruleIndex);
    
    return addPredicate(name,arity);
}

};};

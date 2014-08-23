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

#include "QueryBuilder.h"
#include "../../util/Assert.h"
#include "QueryObject.h"
#include "../data/DBProgram.h"

using namespace std;
using namespace DLV2::DB;

QueryBuilder::QueryBuilder(
    DBProgram* p ):
        query(NULL),
        program(p)
{
    assert_msg( p != NULL, "The program is null." );
}


void
QueryBuilder::rewriteNonRecursiveRule(
    DBRule* rule )
{
    assert_msg( rule != NULL, "The rule is null." );
    assert_msg( rule->getHead().size() == 1, "Only or-free programs are allowed." );
    query = new QueryObject();
    if( rule->hasNegation() )
        rewriteRuleWithNegation(rule);
    else
        rewritePositiveRule(rule);
    reset();
}

void
QueryBuilder::rewriteRecursiveRule( 
    DBRule* rule )
{
    // TODO
    assert(0);
}

void
QueryBuilder::rewritePositiveRule(
    DBRule* rule )
{
    assert_msg( rule != NULL, "The rule is null." );
    if( rule->hasAggregates() )
    {
        // TODO
        assert(0);
    }
    if( rule->hasBuiltins() )
    {
        // TODO
        assert(0);
    }
    for( unsigned i=0; i<rule->getHead().size(); i++ )
        addInHead(rule->getHead().at(i));
    for( unsigned i=0; i<rule->getBody().size(); i++ )
        addInPositiveBody(rule->getBody().at(i));
}

void
QueryBuilder::rewriteRuleWithNegation(
    DBRule* rule )
{
    // TODO
    assert(0);    
}

void
QueryBuilder::rewriteRuleWithBuiltins(
    DBRule* rule )
{
    // TODO
    assert(0);
}

void
QueryBuilder::rewriteRuleWithAggregates( 
    DBRule* rule )
{
    // TODO
    assert(0);   
}


void
QueryBuilder::addInHead( 
    DBAtom* headAtom )
{
    assert_msg( headAtom != NULL, "Null head atom" );
    assert_msg( headVariablesMap.empty(), "Only or-free programs are allowed" );
    assert_msg( headAtom->getTerms().size() > 0, "Propositional atoms are not allowed" );
    query->targetPredicate = headAtom->getPredicateName();
    // The number of attributes which has to be selected 
    // by the output query is given by the arity of the head predicate.
    // The vector is resized because in the following we will need 
    // to access directly to single locations.
    query->attributesToSelect.resize(headAtom->getTerms().size());
    for( unsigned i=0; i<headAtom->getTerms().size(); i++ )
    {
        DBTerm* headTerm = headAtom->getTerms().at(i);
        COORDINATES termCoordinates;
        // The head predicate has index 0.
        termCoordinates.predIndex = 0;
        termCoordinates.termIndex = i;
        assert_msg( headTerm != NULL, "Null term" );
        assert_msg( headTerm->getType() == DBTerm::Variable, "Not variable term in head" );
        // Check whether it is a self-join.
        VARIABLEMAP::iterator it = headVariablesMap.find(headTerm->getText());
        if( it == headVariablesMap.end() )
        {
            vector<COORDINATES> v;
            v.push_back(termCoordinates);
            headVariablesMap[headTerm->getText()] = v;
        }
        else
        {
            it->second.push_back(termCoordinates);
        }
        // Check whether it appears in the body.
        // If the body literals' stack were filled out 
        // after the head, this control would be unnecessary.
        it = bodyVariablesMap.find(headTerm->getText());
        if( it != bodyVariablesMap.end() )
        {
            assert_msg( it->second.size() > 0, 
                    "A term without any locations has been added" );
            // Consider only the first location where it appears.
            unsigned predIndex = it->second.at(0).predIndex;
            unsigned termIndex = it->second.at(0).termIndex;
            assert_msg( predIndex < query->sourcePredicates.size(),
                    "Index out of range" );
            string attribute(
                query->sourcePredicates[predIndex]+
                "."+
                getAttributeName(query->sourcePredicates[predIndex],termIndex));
            query->attributesToSelect[i] = attribute;
        }
    }
}

void
QueryBuilder::addInPositiveBody(
    DBLiteral* literal )
{
    assert_msg( literal != NULL, "Null body literal" );
    assert_msg( !literal->isAggregate(), 
            "Call addAggregateIn(Positive|Negative)Body to add aggregate literals" );
    assert_msg( !literal->isBuiltin(), 
            "Call addBuiltin to add builtins" );
    assert_msg( !literal->isNaf(), 
            "Call addInNegativeBody to add negative literals" );
    DBAtom* currentAtom = literal->getAtom();
    assert_msg( currentAtom != NULL, "Null body atom" );
    assert_msg( currentAtom->getTerms().size() > 0, 
            "Propositional atoms are not allowed" );

    unsigned currentPredIndex = addSourcePredicate(currentAtom->getPredicateName());    
    for( unsigned i=0; i<currentAtom->getTerms().size(); i++ )
    {
        DBTerm* currentTerm = currentAtom->getTerms().at(i);
        assert_msg( currentTerm != NULL, "Null term" );
        const string& currentAttributeName =
            getAttributeName(currentAtom->getPredicateName(),i);
        if( currentTerm->getType() == DBTerm::Variable &&
                currentTerm->getText() != "_" )
        {
            // First check whether currentTerm appears in the head
            VARIABLEMAP::const_iterator it = 
                    headVariablesMap.find(currentTerm->getText());
            if( it != headVariablesMap.end() )
            {
                // Repeat the current attribute name for each location 
                // of the head where currentTerm appears. Note that the 
                // locations that have to be considered are stored 
                // in vector it->second.
                string attribute(
                    currentAtom->getPredicateName()+
                    "."+
                    currentAttributeName);
                for( unsigned j=0; j<it->second.size(); j++ )
                {
                    unsigned targetTermIndex = it->second.at(j).termIndex;
                    assert_msg( targetTermIndex < query->attributesToSelect.size(),
                        "Index out of range" );
                    query->attributesToSelect[targetTermIndex] = attribute;
                }
            }
            // Once we have done with the current attribute we erase the record 
            // from the map in order to avoid that one can write
            // attributes (to select) in the same location more than once.
            headVariablesMap.erase(it);
            
            // Then, check whether currentTerm has been already seen in the body.
            it = bodyVariablesMap.find(currentTerm->getText());
            if( it != bodyVariablesMap.end() )
            {
                assert_msg( it->second.size() > 0, 
                    "A term without any locations has been added" );
                // There should be only one location in it->second.                
                unsigned targetPredIndex = it->second.at(0).predIndex;
                unsigned targetTermIndex = it->second.at(0).termIndex;
                assert_msg( targetPredIndex < query->sourcePredicates.size(),
                    "Index out of range" );
                const string& targetAttributeName =
                    getAttributeName(query->sourcePredicates[targetPredIndex],targetTermIndex);
                QCondition condition(
                    currentAtom->getPredicateName()+
                    "."+
                    currentAttributeName,
                    query->sourcePredicates[targetPredIndex]+
                    "."+
                    targetAttributeName);
                query->conditions.push_back(condition);    
            }
            
            // Finally, add the current variable to the map of the body variables
            COORDINATES currentCoordinates;
            currentCoordinates.predIndex = currentPredIndex;
            currentCoordinates.termIndex = i;
            vector<COORDINATES> v;
            v.push_back(currentCoordinates);
            bodyVariablesMap[currentTerm->getText()] = v;
        }
        else if( currentTerm->getType() == DBTerm::String )
        {
            QCondition condition(
                currentAtom->getPredicateName()+
                "."+
                currentAttributeName,
                "\""+currentTerm->getText()+"\"");
            query->conditions.push_back(condition);
        }
        else if( currentTerm->getType() == DBTerm::Integer )
        {
            QCondition condition(
                currentAtom->getPredicateName()+
                "."+
                currentAttributeName,
                currentTerm->getText());
            query->conditions.push_back(condition);
        }
    }
}
    
void 
QueryBuilder::addInNegativeBody( 
    DBLiteral* literal )
{
    
}

void
QueryBuilder::addAggregateInPositiveBody( 
    DBLiteral* literal )
{
    
}
    
void 
QueryBuilder::addAggregateInNegativeBody( 
    DBLiteral* literal )
{
    
}
    
void 
QueryBuilder::addBuiltin( 
    DBLiteral* literal )
{
    
}

void 
QueryBuilder::reset()
{
    headVariablesMap.clear();
    bodyVariablesMap.clear();
}

unsigned
QueryBuilder::addSourcePredicate(
    const std::string& pred )
{
    assert_msg( query, "The query is null" );
    for( unsigned i=0; i<query->sourcePredicates.size(); i++ )
        if( query->sourcePredicates[i] == pred )
            return i;
    query->sourcePredicates.push_back(pred);
    return query->sourcePredicates.size()-1;
}

const string&
QueryBuilder::getAttributeName(
    const std::string& predName, 
    unsigned termIndex)
{
    assert_msg( program != NULL, "Null program" );
    Metadata* meta = program->getMetadata(predName);
    assert_msg( meta != NULL, "Null metadata" );
    return meta->getAttributeName(termIndex);
}
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

/* 
 * File:   SQLStrategy.cpp
 * Author: pierfrancesco
 *
 * Created on 23/ott/2014, 20:41:41
 */

#include "SQLStrategy.h"

using namespace std;
using namespace DLV2::DB;


SQLStrategy::SQLStrategy(
    DBProgram* p ):
        program(p)
{
    assert_msg( p != NULL, "The program is null." );
}

SQLStrategy::SQLStrategy(
    const SQLStrategy& ss ):
        program(ss.program)
{
    assert_msg( ss.program != NULL, "The program is null." );
}

void
SQLStrategy::rewriteRule(
    const DBRule& rule,
    string& sqlOutput )
{
    assert_msg( (headVariablesMap.empty() &&
            bodyVariablesMap.empty() &&
            bodyPredicates.empty() &&
            targetTable.empty() &&
            attributesToSelect.empty() &&
            sourceTables.empty() &&
            conditions.empty()),
            "Not null data structures" );

    if( rule.isRecursive() )
        rewriteRecursiveRule(rule);
    else
        rewriteNonRecursiveRule(rule);

    getRuleInSQL(sqlOutput);

    reset();
}

void
SQLStrategy::rewriteFact(
    const DBRule& rule,
    string& sql )
{
    // TODO
}

void
SQLStrategy::rewriteNonRecursiveRule(
    const DBRule& rule )
{
    assert_msg( rule.getHead().size() == 1, "Only or-free programs are allowed." );
    if( rule.hasNegation() )
        rewriteNegativeRule(rule);
    else
        rewritePositiveRule(rule);
}

void
SQLStrategy::rewriteRecursiveRule(
    const DBRule& rule )
{
    // TODO
    assert_msg( 0, "Sorry, we aren't able to handle recursion" );
}

void
SQLStrategy::rewritePositiveRule(
    const DBRule& rule )
{
    if( rule.hasAggregates() )
    {
        // TODO
        assert_msg( 0, "Sorry, we aren't able to handle aggregate atoms" );
    }
    if( rule.hasBuiltins() )
    {
        // TODO
        assert_msg( 0, "Sorry, we aren't able to handle builtins" );
    }
    for( unsigned i=0; i<rule.getHead().size(); i++ )
    {
        DBAtom* headAtom = rule.getHead().at(i);
        assert_msg( headAtom != NULL, "Null heat atom" );
        addInHead(*headAtom);
    }
    for( unsigned i=0; i<rule.getBody().size(); i++ )
    {
        DBLiteral* bodyLit = rule.getBody().at(i);
        assert_msg( bodyLit != NULL, "Null body literal" );
        addInPositiveBody(*bodyLit);
    }
}

void
SQLStrategy::rewriteNegativeRule(
    const DBRule& rule )
{
    // TODO
    assert_msg( 0, "Sorry, we aren't able to handle negation as failure" );
}

void
SQLStrategy::rewriteRuleWithBuiltins(
    const DBRule& rule )
{
    // TODO
    assert_msg( 0, "Sorry, we aren't able to handle builtins" );
}

void
SQLStrategy::rewriteRuleWithAggregates(
    const DBRule& rule )
{
    // TODO
    assert_msg( 0, "Sorry, we aren't able to handle aggregate atoms" );
}

void
SQLStrategy::addInHead(
    const DBAtom& headAtom )
{
    assert_msg( !headAtom.isBuiltin(), "A builtin atom occurs in the head" );
    assert_msg( !headAtom.isAggregate(), "An aggregate atom occurs in the head" );
    assert_msg( headVariablesMap.empty(), "Only or-free programs are allowed" );
    assert_msg( headAtom.getTerms().size() > 0, "Propositional atoms are not allowed" );
    targetTable = getTableName(headAtom.getPredIndex());
    // The number of attributes which has to be selected
    // by the output query is given by the arity of the head predicate.
    // The vector is resized because in the following we will need
    // to access directly to single locations.
    attributesToSelect.resize(headAtom.getTerms().size());
    for( unsigned i=0; i<headAtom.getTerms().size(); i++ )
    {
        DBTerm* headTerm = headAtom.getTerms().at(i);
        Coordinates termCoordinates;
        // The head predicate has index 0.
        termCoordinates.predPos = 0;
        termCoordinates.termPos = i;
        assert_msg( headTerm != NULL, "Null term" );
        assert_msg( headTerm->isVar(), "Not variable term in the head" );
        // Check whether it deals with a self-join.
        VariableMap::iterator it = headVariablesMap.find(headTerm->getText());
        if( it == headVariablesMap.end() )
        {
            vector< Coordinates > v;
            v.push_back(termCoordinates);
            headVariablesMap[headTerm->getText()] = v;
        }
        else
        {
            it->second.push_back(termCoordinates);
        }
        // Check whether it appears in the body.
        // If the body literals' stack were filled
        // after the head, this control would be unnecessary.
        it = bodyVariablesMap.find(headTerm->getText());
        if( it != bodyVariablesMap.end() )
        {
            assert_msg( it->second.size() > 0,
                    "A term without any locations has been added" );
            // Consider only the first location where it appears.
            unsigned predPos = it->second.at(0).predPos;
            unsigned termPos = it->second.at(0).termPos;
            assert_msg( predPos < bodyPredicates.size(),
                    "Index out of range" );
            string attribute(
                getTableAlias(predPos)+
                "."+
                getAttributeName(predPos,termPos));
            attributesToSelect[i] = attribute;
        }
    }
}

void
SQLStrategy::addInPositiveBody(
    const DBLiteral& literal )
{
    assert_msg( !literal.isNaf(),
            "Call addInNegativeBody to add negative literals" );
    DBAtom* currentAtom = literal.getAtom();
    assert_msg( currentAtom != NULL, "Null body atom" );
    assert_msg( !currentAtom->isAggregate(),
            "Call addAggregateIn(Positive|Negative)Body to add aggregate atoms" );
    assert_msg( !currentAtom->isBuiltin(),
            "Call addBuiltin to add builtins" );
    assert_msg( currentAtom->getTerms().size() > 0,
            "Propositional atoms are not allowed" );
    // Add the predicate and retrieve the position where
    // it appears in the bodyPredicates vector.
    unsigned currentPredPos = addSource(*currentAtom);
    for( unsigned i=0; i<currentAtom->getTerms().size(); i++ )
    {
        DBTerm* currentTerm = currentAtom->getTerms().at(i);
        assert_msg( currentTerm != NULL, "Null term" );
        const string& currentAttributeName =
            getAttributeName(currentPredPos,i);
        string currentTableAlias =
            getTableAlias(currentPredPos);
        if( currentTerm->isVar() && !currentTerm->isUnknownVar() )
        {
            // First check whether currentTerm appears in the head
            VariableMap::const_iterator it =
                    headVariablesMap.find(currentTerm->getText());
            if( it != headVariablesMap.end() )
            {
                // Repeat the current attribute name for each location
                // of the head where currentTerm appears. Note that the
                // locations that have to be considered are stored
                // in vector it->second.
                string attribute(
                    currentTableAlias+
                    "."+
                    currentAttributeName);
                for( unsigned j=0; j<it->second.size(); j++ )
                {
                    unsigned targetTermPos = it->second.at(j).termPos;
                    assert_msg( targetTermPos < attributesToSelect.size(),
                        "Index out of range" );
                    attributesToSelect[targetTermPos] = attribute;
                }

                // Once we have done with the current attribute we erase the record
                // from the map in order to avoid that one could write
                // attributes (to select) in the same location more than once.
                headVariablesMap.erase(it);
            }

            // Then, check whether currentTerm has been already seen in the body.
            it = bodyVariablesMap.find(currentTerm->getText());
            if( it != bodyVariablesMap.end() )
            {
                assert_msg( it->second.size() > 0,
                    "A term without any locations has been added" );
                // There should be only one location in it->second,
                // because we insert only the last location of each
                // body variable into the map. Indeed, you can consider
                // only the last location of a variable in order to catch
                // a join.
                unsigned targetPredPos = it->second.at(0).predPos;
                unsigned targetTermPos = it->second.at(0).termPos;
                const string& targetAttributeName =
                    getAttributeName(targetPredPos,targetTermPos);
                QCondition condition(
                    currentTableAlias+
                    "."+
                    currentAttributeName,
                    getTableAlias(targetPredPos)+
                    "."+
                    targetAttributeName);
                conditions.push_back(condition);
            }

            // Finally, add the current variable to the map of the body variables
            Coordinates currentCoordinates;
            currentCoordinates.predPos = currentPredPos;
            currentCoordinates.termPos = i;
            vector< Coordinates > v;
            v.push_back(currentCoordinates);
            bodyVariablesMap[currentTerm->getText()] = v;
        }
        else if( currentTerm->isConst() )
        {
            QCondition condition(
                currentTableAlias+
                "."+
                currentAttributeName,
                "'"+currentTerm->getText()+"'");
            conditions.push_back(condition);
        }
        else if( currentTerm->isInt() )
        {
            QCondition condition(
                currentTableAlias+
                "."+
                currentAttributeName,
                currentTerm->getText());
            conditions.push_back(condition);
        }
    }
}

void
SQLStrategy::addInNegativeBody(
    const DBLiteral& literal )
{

}

void
SQLStrategy::addAggregateInPositiveBody(
    const DBLiteral& literal )
{

}

void
SQLStrategy::addAggregateInNegativeBody(
    const DBLiteral& literal )
{

}

void
SQLStrategy::addBuiltin(
    const DBLiteral& literal )
{

}

unsigned
SQLStrategy::addSource(
    const DBAtom& sourceAtom )
{
    // Return the position where the predicate is going to be located.
    bodyPredicates.push_back(sourceAtom.getPredIndex());
    sourceTables.push_back(
        getTableName(sourceAtom.getPredIndex())+
        " AS "+
        getTableAlias(bodyPredicates.size()-1));
    return bodyPredicates.size()-1;
}

const string&
SQLStrategy::getTableName(
    index_t predIndex ) const
{
    assert_msg( program != NULL, "Null program" );
    const Metadata* meta = program->getMetadata(predIndex);
    assert_msg( meta != NULL, "Null metadata" );
    return meta->getTableName();
}

string
SQLStrategy::getTableAlias(
    unsigned pos ) const
{
    return string("t"+to_string(pos));
}

const string&
SQLStrategy::getAttributeName(
    unsigned predPos,
    unsigned termPos ) const
{
    assert_msg( predPos < bodyPredicates.size(), "Index out of range" );
    assert_msg( program != NULL, "Null program" );
    const Metadata* meta = program->getMetadata(bodyPredicates[predPos]);
    assert_msg( meta != NULL, "Null metadata" );
    return meta->getAttributeName(termPos);
}

void
SQLStrategy::reset()
{
    headVariablesMap.clear();
    bodyVariablesMap.clear();
    bodyPredicates.clear();
    targetTable.clear();
    attributesToSelect.clear();
    sourceTables.clear();
    conditions.clear();
}

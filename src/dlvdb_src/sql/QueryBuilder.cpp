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
    query->targetPredicate = rule->getHead().at(0)->getPredicateName();
    if( rule->hasNegation() )
        rewriteRuleWithNegation(rule);
    else
        rewritePositiveRule(rule);
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
    // Fill Select clause
    fillAttributesToSelect(rule);
    // Here, the body is composed of positive standard atoms
    for( unsigned i=0; i<rule->getBody().size(); i++ )
    {
        DBLiteral* literal = rule->getBody().at(i);
        assert_msg( literal != NULL, "Null literal." );
        DBAtom* atom = literal->getAtom();
        assert_msg( atom != NULL, "Null atom." );
        addSourcePredicate(atom->getPredicateName());
        
        for( unsigned j=0; j<atom->getTerms().size(); j++ )
        {
            Metadata* meta = program->getMetadata(atom->getPredicateName());
            assert_msg( meta != NULL, "Null metadata for "+atom->getPredicateName() );
            DBTerm* term = atom->getTerms().at(j);
            assert_msg( term != NULL, "Null term." );
            if( term->getType() == DBTerm::Variable )
            {
                // Check for self-joins
                for( unsigned k=j+1; k<atom->getTerms().size(); k++ )
                {
                    DBTerm* term1 = atom->getTerms().at(k);
                    assert_msg( term1 != NULL, "Null term." );                    
                    if( term1->getType() == DBTerm::Variable &&
                            term1->getText() == term->getText() )
                    {
                        QCondition condition(
                            atom->getPredicateName()+"."+meta->getAttributeName(j),    
                            atom->getPredicateName()+"."+meta->getAttributeName(k)
                            );
                        query->conditions.push_back(condition);
                    }
                }
                // Check for joins
                for( unsigned x=i+1; x<rule->getBody().size(); x++ )
                {
                    DBLiteral* literal1 = rule->getBody().at(x);
                    assert_msg( literal1 != NULL, "Null literal." );
                    DBAtom* atom1 = literal1->getAtom();
                    assert_msg( atom1 != NULL, "Null atom." );
                    for( unsigned y=0; y<atom1->getTerms().size(); y++ )
                    {
                        Metadata* meta1 = program->getMetadata(atom1->getPredicateName());
                        assert_msg( meta1 != NULL, "Null metadata for "+atom1->getPredicateName() );
                        DBTerm* term1 = atom1->getTerms().at(y);
                        assert_msg( term1 != NULL, "Null term." );
                        if( term1->getType() == DBTerm::Variable && 
                                term1->getText() == term->getText() )
                        {
                            QCondition condition(
                                atom->getPredicateName()+"."+meta->getAttributeName(j),
                                atom1->getPredicateName()+"."+meta1->getAttributeName(y));
                            query->conditions.push_back(condition);    
                        }
                    }
                }
            }
            else if( term->getType() == DBTerm::String )
            {
                QCondition condition(
                    atom->getPredicateName()+"."+meta->getAttributeName(j),
                    term->getText());
                query->conditions.push_back(condition);
            }
            else
            {
                assert_msg( 0, "Only variables and strings are allowed." );
            }
        }
    }
}

void
QueryBuilder::rewriteRuleWithNegation(
    DBRule* rule )
{
    
}

//void
//QueryBuilder::rewriteRuleWithBuiltins(
//    DBRule* rule )
//{
//    
//}
//
//void
//QueryBuilder::rewriteRuleWithAggregates( 
//    DBRule* rule )
//{
//    
//}

void 
QueryBuilder::reset()
{
}

bool
QueryBuilder::occursVariable(
    DBAtom* atom,
    DBTerm* var )
{
    assert_msg( var != NULL, "Null term" );
    assert_msg( var->getType() == DBTerm::Variable, "Non variable term" );
    assert_msg( atom != NULL, "Null atom" );
    for( unsigned i=0; i<atom->getTerms().size(); i++ )
    {
        if( atom->getTerms().at(i)->getType() == DBTerm::Variable && 
               atom->getTerms().at(i)->getText() == var->getText() )
            return true;
    }
    return false;
}

void
QueryBuilder::fillAttributesToSelect(
    DBRule* rule )
{
    assert_msg( rule->getHead().size() == 1, "Only or-free programs are allowed" );
    assert_msg( query, "The query is null" );
    DBAtom* head = rule->getHead().at(0);
    assert_msg( head != NULL, "Null head atom" );
    for( unsigned i=0; i<head->getTerms().size(); i++ )
    {
        DBTerm* term = head->getTerms().at(i);
        assert_msg( term != NULL, "Null term" );
        assert_msg( term->getType() == DBTerm::Variable, "Not variable term in the head" );
        // Add only one attribute for each term of the head.
        bool found = false;
        for( unsigned j=0; j<rule->getBody().size() && !found; j++ )
        {
            DBLiteral* literal = rule->getBody().at(j);
            assert_msg( literal != NULL, "Null literal." );
            DBAtom* atom = literal->getAtom();
            assert_msg( atom != NULL, "Null atom." );
            for( unsigned k=0; k<atom->getTerms().size() && !found; k++ )
            {    
                DBTerm* term1 = atom->getTerms().at(k);
                assert_msg( term1 != NULL, "Null term." );
                if( term1->getType() == DBTerm::Variable &&
                        term->getText() == term1->getText() )
                {
                    found = true;
                    Metadata* meta = program->getMetadata(atom->getPredicateName());
                    query->attributesToSelect.push_back(
                        string(meta->getPredicateName())+"."+meta->getAttributeName(k));
                }
            }
        }
    }
}

void
QueryBuilder::addSourcePredicate(
    const std::string& pred )
{
    assert_msg( query, "The query is null" );
    bool found = false;
    for( unsigned i=0; i<query->sourcePredicates.size() && !found; i++ )
        if( query->sourcePredicates[i] == pred )
            found = true;
    if( !found )
        query->sourcePredicates.push_back(pred);
}
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
 * File:   XProgram.cpp
 * Author: pierfrancesco
 *
 * Created on 30 ottobre 2014, 12.30
 */

#include "XProgram.h"

#include "XAtomicHead.h"
#include "XDisjunctiveHead.h"
#include "XConjunctiveHead.h"
#include "XStickyLabel.h"
#include "XStickyExpandedRule.h"
#include "XPartition.h"
#include "XPieceUnifier.h"
#include "../../util/ErrorMessage.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"

using namespace std;
using namespace DLV2::REWRITERS;

XProgram::XProgram():
        predicates(),
        rules(),
        facts(),
        hasDisjunction(false),
        hasConjunction(false),
        predicateToRulesMapping(),
        varsCounter(0),
        query(NULL),
        queryRules(),
        propagationGraph(),
        nonTemporaryRulesSize(-1)
{
}

XProgram::XProgram(
    const XProgram& program ):
        predicates(program.predicates),
        rules(program.rules),
        facts(program.facts),
        hasDisjunction(program.hasDisjunction),
        hasConjunction(program.hasConjunction),
        predicateToRulesMapping(program.predicateToRulesMapping),
        varsCounter(program.varsCounter),
        queryRules(program.queryRules),
        propagationGraph(program.propagationGraph),
        nonTemporaryRulesSize(program.nonTemporaryRulesSize)
{
    if( program.query != NULL )
    {
        query = createAtom(program.query->getPredIndex(),program.query->getTerms(),program.query->isTrueNegated());
    }
}

XProgram::~XProgram()
{
    if( query != NULL )
        delete query;
}

XTerm*
XProgram::createIntegerConstant(
    int val ) const
{
    return new XTerm(val);
}

XTerm*
XProgram::createStringConstant(
    const string& val ) const
{
    return new XTerm(XTerm::String,val);
}

XTerm*
XProgram::createStringConstant(
    char* val ) const
{
    return new XTerm(XTerm::String,val);
}

XTerm*
XProgram::createStandardVariable(
    const string& name ) const
{
    return new XTerm(XTerm::Variable,name);
}

XTerm*
XProgram::createStandardVariable(
    char* name ) const
{
    return new XTerm(XTerm::Variable,name);
}

XTerm*
XProgram::createUnknownVariable() const
{
    return new XTerm(XTerm::Variable,string("_"));
}

XTerm*
XProgram::createNull(
    const std::string& name ) const
{
    return new XTerm(XTerm::Null,name);
}

XTerm*
XProgram::createNull(
    char* name ) const
{
    return new XTerm(XTerm::Null,name);
}

XAtom*
XProgram::createAtom(
    index_t predIndex,
    const vector< XTerm >& terms,
    bool trueNegated ) const
{
    return new XAtom(*this,predIndex,terms,trueNegated);
}

XLiteral*
XProgram::createLiteral(
    const XAtom& a,
    bool naf ) const
{
    return new XLiteral(a,naf);
}

XHead*
XProgram::createAtomicHead(
    const XAtom& a ) const
{
    return new XAtomicHead(a);
}

XHead*
XProgram::createDisjunctiveHead(
    const vector< XAtom >& atoms ) const
{
    return new XDisjunctiveHead(atoms);
}

XHead*
XProgram::createConjunctiveHead(
    const vector< XAtom >& atoms ) const
{
    return new XConjunctiveHead(atoms);
}

XBody*
XProgram::createBody(
    const XRandomAccessSet< XLiteral >& lits ) const
{
    return new XBody(lits);
}

XBody*
XProgram::createBody(
    const vector< XLiteral >& lits ) const
{
    return new XBody(lits);
}

XRule*
XProgram::createRule(
    XHead* head,
    XBody* body ) const
{
    return new XRule(head,body);
}

XStickyLabel*
XProgram::createStickyLabel(
    index_t expRuleIndex,
    const XAtom& atom ) const
{
    return new XStickyLabel(expRuleIndex,atom);
}

XTermMetadata*
XProgram::createStickyTermMetadata(
    const XTerm& term ) const
{
    return new XTermMetadata(term);
}

XStickyExpandedRule*
XProgram::createStickyExpandedRule(
    const XRule& rule ) const
{
    return new XStickyExpandedRule(rule);
}

XStickyUnifier*
XProgram::createStickyUnifier(
    const XAtom& headAt,
    const XAtom& bodyAt,
    const XMapping& subst ) const
{
    return new XStickyUnifier(headAt,bodyAt,subst);
}

XEquivalenceClass*
XProgram::createEquivalenceClass()
{
    return new XEquivalenceClass(*this);
}

XPartition*
XProgram::createPartition()
{
    return new XPartition(*this);
}

XPieceUnifier*
XProgram::createPieceUnifier(
    const std::vector< XAtom >& q,
    const std::vector< XAtom >& h,
    XPartition* p,
    const XRule& query,
    const XRule& rule,
    const std::unordered_set< unsigned >& subQueryAtomPos ) const
{
    return new XPieceUnifier(q,h,p,query,rule,subQueryAtomPos);
}

void
XProgram::addRule(
    const XRule& r )
{
    // First of all, check its safety!!!
    try
    {
        checkSafety(r);
    }
    catch( XSafetyException& exc )
    {
        ErrorMessage::errorDuringParsing(exc.what());
    }

    if( r.hasAtomicHead() && r.getBody() == NULL && r.isGround() )
    {
        facts.push_back(r);
    }
    else
    {
        iterator rIt = rules.insert(rules.end(),r);

        // Add the current rule to the ruleSets of its head predicates
        const XHead* head = r.getHead();
        assert_msg( head != NULL, "Heads must not be null" );
        for( unsigned i=0; i<head->size(); i++ )
        {
            addToPredicateRuleSet((*head)[i].getPredIndex(),rIt);
        }
        if( r.hasDisjunctiveHead() )
            hasDisjunction = true;
        else if( r.hasConjunctiveHead() )
            hasConjunction = true;
    }
}

XProgram::const_iterator
XProgram::addTemporaryRule(
    const XRule& r )
{
    trace_msg( rewriting, 3, "Adding temporary rule: " << r );
    if( nonTemporaryRulesSize == -1 )
    {
        trace_msg( rewriting, 3, "Old rules size was " << rules.size() );
        nonTemporaryRulesSize = rules.size();
    }

    // First of all, check its safety!!!
    try
    {
        checkSafety(r);
    }
    catch( XSafetyException& exc )
    {
        ErrorMessage::errorDuringParsing(exc.what());
    }
    assert_msg( !(r.hasAtomicHead() && r.getBody() == NULL && r.isGround()), "Temporary facts not allowed" );
    const_iterator rIt = rules.insert(rules.end(),r);
    trace_msg( rewriting, 3, "New rules size is: " << rules.size() );
    return rIt;
}

void
XProgram::eraseTemporaryRules()
{
    // How many rules are to be erased?
    if( nonTemporaryRulesSize != -1 )
    {
        unsigned rulesToBeErased = rules.size()-nonTemporaryRulesSize;
        trace_msg( rewriting, 3, "Erasing temporary rules, rules size = " << rules.size()
                << ", rulesToBeErased = " << rulesToBeErased );
        for( unsigned i=0; i<rulesToBeErased; i++ )
            rules.pop_back();
        nonTemporaryRulesSize = -1;
    }
}

void
XProgram::addQuery(
    const XAtom& q )
{
    if( query != NULL )
    {
        cout << "Query " << q << " replaces " << *query << endl;
        delete query;
    }
    query = new XAtom(q);
}

pair< index_t, bool >
XProgram::addPredicate(
    const string& name,
    unsigned arity,
    bool internal )
{
//    assert_msg( arity > 0, "Propositional atoms are not allowed" );
    pair< index_t, bool > res = predicates.add(name,arity,internal);
    return res;
}

void
XProgram::computeQueryRules()
{
    if( query != NULL && queryRulesSize() == 0 )
    {
        // Look up rules with the query predicate in their atomic head.
        // Every of these should be considered as query rule, so they
        // are not part of the input program.
        bool ok = true;
        vector< iterator > rulesToBeMoved;
        for( iterator it=rules.begin(); it!=rules.end() && ok; it++ )
        {
            assert_msg( it->getHead() != NULL, "Null head" );
            if( it->hasAtomicHead() )
            {
                if( it->getHead()->at(0).getPredIndex() == query->getPredIndex() )
                    rulesToBeMoved.push_back(it);
            }
            else
            {
                // If the query predicate appears in the non-atomic
                // head of a rule, the query will be considered as atomic.
                for( unsigned i=0; i<it->getHead()->size() && ok; i++ )
                    if( it->getHead()->at(i).getPredIndex() == query->getPredIndex() )
                        ok = false;
            }
            // If the query predicate appears in any body atom
            // of a rule, the query will be considered as atomic.
            if( it->getBody() != NULL )
                for( unsigned i=0; i<it->getBody()->size() && ok; i++ )
                    if( it->getBody()->at(i).getAtom().getPredIndex() == query->getPredIndex() )
                        ok = false;
        }
        // If the query predicate appears only in atomic rule heads,
        // move such rules to 'queryRules' because they are not part
        // of the input program (they might be non-sticky, non-linear, and so on).
        if( ok )
        {
            // Erase pointers to rules stored in 'rules' (those whose head predicate
            // is equal to the new query predicate), because such rules are about to be
            // moved to 'queryRules', so their pointers will be invalidated.
            XPredicateToXRulesetMap::iterator it = predicateToRulesMapping.find(query->getPredIndex());
            if( it != predicateToRulesMapping.end() )
                it->second.clear();
            // Move rules to 'queryRules'.
            for( unsigned i=0; i<rulesToBeMoved.size(); i++ )
            {
                iterator qIt = queryRules.insert(queryRules.end(),*rulesToBeMoved[i]);
                rules.erase(rulesToBeMoved[i]);
                addToPredicateRuleSet(query->getPredIndex(),qIt);
            }
        }
        else
            cout << "Warning: added an atomic query whose predicate appears either "
                    "in the non-atomic head or in the body of a rule" << endl;
    }
    computePropagationGraph();
}

const string&
XProgram::getPredicateName(
    index_t predIndex ) const
{
    return predicates.getName(predIndex);
}

unsigned
XProgram::getPredicateArity(
    index_t predIndex ) const
{
    return predicates.getArity(predIndex);
}

const XProgram::XRulePointers&
XProgram::getPredicateRulePointers(
    index_t predIndex ) const
{
    XPredicateToXRulesetMap::const_iterator it = predicateToRulesMapping.find(predIndex);
    assert_msg( it != predicateToRulesMapping.end(), "Predicate index not valid" );
    return it->second;
}

bool
XProgram::addToPredicateRuleSet(
    index_t predIndex,
    const_iterator ruleIt )
{
    XPredicateToXRulesetMap::iterator it = predicateToRulesMapping.find(predIndex);
    if( it == predicateToRulesMapping.end() )
    {
        XRulePointers rulePointers;
        rulePointers.pushItem(ruleIt);
        pair< index_t, const XRulePointers& > newMapping(predIndex,rulePointers);
        pair< XPredicateToXRulesetMap::const_iterator, bool > insResult =
                predicateToRulesMapping.insert(newMapping);
        return insResult.second;
    }
    else
    {
        return it->second.pushItem(ruleIt);
    }
}

void
XProgram::checkSafety(
    const XRule& rule ) const
        throw (XSafetyException)
{
    unordered_set< XTerm > safeVars;
    unordered_set< XTerm > unsafeVars;
    const XHead* head = rule.getHead();
    assert_msg( head != NULL, "Null head" );
    for( unsigned i=0; i<head->size(); i++ )
    {
        const vector< XTerm >& terms = head->at(i).getTerms();
        for( unsigned j=0; j<terms.size(); j++ )
        {
            if( terms[j].isUnknownVar() )
                throw XSafetyException(rule);
            else if( terms[j].isVar() && !rule.isExistential(terms[j]) )
                unsafeVars.insert(terms[j]);
        }
    }
    if( rule.getBody() != NULL )
    {
        const XBody* body = rule.getBody();
        for( unsigned i=0; i<body->size(); i++ )
        {
            const vector< XTerm >& terms = body->at(i).getAtom().getTerms();
            for( unsigned j=0; j<terms.size(); j++ )
            {
                if( body->at(i).isSaviour() )
                {
                    if( terms[j].isStandardVar() )
                    {
                        unsafeVars.erase(terms[j]);
                        safeVars.insert(terms[j]);
                    }
                }
                else
                {
                    if( terms[j].isUnknownVar() )
                        throw XSafetyException(rule);
                    else if( terms[j].isVar() && safeVars.find(terms[j]) == safeVars.end() )
                        unsafeVars.insert(terms[j]);
                }
            }
        }
    }
}

void
XProgram::updatePropagationGraph(
    const_iterator ruleIt,
    index_t ruleIndex )
{
    const XHead* head = ruleIt->getHead();
    assert_msg( head != NULL, "Null head" );
    const XBody* body = ruleIt->getBody();
    if( body != NULL )
    {
        for( unsigned i=0; i<head->size(); i++ )
        {
            const XAtom& currAtom = head->at(i);
            for( unsigned j=0; j<currAtom.getTerms().size(); j++ )
            {
                const XTerm& currTerm = currAtom.getTerms().at(j);
                stringstream sDest;
                sDest << currAtom.getPredicateName() << "_" << j;
                const vector< XCoordinates >& bodyPositions = ruleIt->getBodyPositions(currTerm);
                for( unsigned k=0; k<bodyPositions.size(); k++ )
                {
                    unsigned atomCoord = bodyPositions[k].atomPos;
                    unsigned termCoord = bodyPositions[k].termPos;
                    assert_msg( atomCoord < body->size(), "Index out of range" );
                    assert_msg( termCoord < body->at(atomCoord).getAtom().getTerms().size(), "Index out of range" );
                    stringstream sSrc;
                    sSrc << body->at(atomCoord).getAtom().getPredicateName() << "_" << termCoord;
                    propagationGraph.addEdge(sSrc.str(),sDest.str(),ruleIndex);
                }
            }
        }
    }
}

void
XProgram::computePropagationGraph()
{
    index_t ruleIdx = 0;
    for( const_iterator rIt = beginRules(); rIt != endRules(); rIt++ )
        updatePropagationGraph(rIt,ruleIdx++);
//    // Add a noose with the same label to each vertex. Notice that such a label does not match any rule index.
//    propagationGraph.addNooses(ruleIdx);
}

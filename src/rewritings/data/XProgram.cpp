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
#include "../../util/ErrorMessage.h"

using namespace std;
using namespace DLV2::REWRITERS;

XProgram::XProgram():
        predicates(),
        rules(),
        facts(),
        hasDisjunction(false),
        hasConjunction(false),
        predicateToRulesMapping()
{
}

XProgram::XProgram(
    const XProgram& program ):
        predicates(program.predicates),
        rules(program.rules),
        facts(program.facts),
        hasDisjunction(program.hasDisjunction),
        hasConjunction(program.hasConjunction),
        predicateToRulesMapping(program.predicateToRulesMapping)
{

}

XProgram::~XProgram()
{
}

XTerm*
XProgram::createIntegerConstant(
    int val )
{
    return new XTerm(val);
}

XTerm*
XProgram::createStringConstant(
    const string& val )
{
    return new XTerm(XTerm::String,val);
}

XTerm*
XProgram::createStringConstant(
    char* val )
{
    return new XTerm(XTerm::String,val);
}

XTerm*
XProgram::createVariable(
    const string& name )
{
    return new XTerm(XTerm::Variable,name);
}

XTerm*
XProgram::createVariable(
    char* name )
{
    return new XTerm(XTerm::Variable,name);
}

XTerm*
XProgram::createNull(
    const std::string& name )
{
    return new XTerm(XTerm::Null,name);
}

XTerm*
XProgram::createNull(
    char* name )
{
    return new XTerm(XTerm::Null,name);
}

XAtom*
XProgram::createAtom(
    index_t predIndex,
    const vector< XTerm >& terms,
    bool trueNegated )
{
    return new XAtom(*this,predIndex,terms,trueNegated);
}

XLiteral*
XProgram::createLiteral(
    const XAtom& a,
    bool naf )
{
    return new XLiteral(a,naf);
}

XHead*
XProgram::createAtomicHead(
    const XAtom& a )
{
    return new XAtomicHead(a);
}

XHead*
XProgram::createDisjunctiveHead(
    const vector< XAtom >& atoms )
{
    return new XDisjunctiveHead(atoms);
}

XHead*
XProgram::createConjunctiveHead(
    const vector< XAtom >& atoms )
{
    return new XConjunctiveHead(atoms);
}

XBody*
XProgram::createBody(
    const XRandomAccessSet< XLiteral >& lits )
{
    return new XBody(lits);
}

XRule*
XProgram::createRule(
    XHead* head,
    XBody* body )
{
    return new XRule(head,body);
}

void
XProgram::addRule(
    const XRule& r )
{
    // First of all, check its safety!!!
    try
    {
        assertIsRuleSafe(r);
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
        rules.push_back(r);

        // Add the current rule to the ruleSets of its head predicates
        XRuleIndex rIndex = rules.size()-1;
        const XHead* head = r.getHead();
        assert_msg( head != NULL, "Heads must not be null" );
        for( unsigned i=0; i<head->size(); i++ )
        {
            addToPredicateRuleSet((*head)[i].getPredIndex(),rIndex);
        }
        if( r.hasDisjunctiveHead() )
            hasDisjunction = true;
        else if( r.hasConjunctiveHead() )
            hasConjunction = true;
    }
}

pair< index_t, bool >
XProgram::addPredicate(
    const string& name,
    unsigned arity )
{
    assert_msg( arity > 0, "Propositional atoms are not allowed" );
    pair< index_t, bool > res = predicates.add(name,arity);
    return res;
}

bool
XProgram::addToPredicateRuleSet(
    index_t predIndex,
    XRuleIndex ruleIndex )
{
    XPredicateToXRulesetMap::iterator it = predicateToRulesMapping.find(predIndex);
    if( it == predicateToRulesMapping.end() )
    {
        XRuleIndicesCollection ruleIndices;
        ruleIndices.pushRuleIndex(ruleIndex);
        pair< index_t, XRuleIndicesCollection > newMapping(predIndex,ruleIndices);
        pair< XPredicateToXRulesetMap::const_iterator, bool > insResult =
                predicateToRulesMapping.insert(newMapping);
        return insResult.second;
    }
    else
    {
        return it->second.pushRuleIndex(ruleIndex);
    }
}

void
XProgram::assertIsRuleSafe(
    const XRule& rule ) const throw (XSafetyException)
{
    // TODO
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

const XRule&
XProgram::getRule(
    XRuleIndex ruleIndex ) const
{
    assert_msg( ( 0 <= ruleIndex && ruleIndex < rules.size() ), "Index out of range" );
    return rules[ruleIndex];

}

const XRule&
XProgram::getFact(
    index_t factIndex ) const
{
    assert_msg( ( 0 <= factIndex && factIndex < facts.size() ), "Index out of range" );
    return facts[factIndex];
}

const XRuleIndicesCollection&
XProgram::getPredicateRuleIndices(
    index_t predIndex ) const
{
    XPredicateToXRulesetMap::const_iterator it = predicateToRulesMapping.find(predIndex);
    assert_msg( it != predicateToRulesMapping.end(), "Predicate index not valid" );
    return it->second;
}

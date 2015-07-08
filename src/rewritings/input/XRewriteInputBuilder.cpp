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
 * File:   XRewriteInputBuilder.cpp
 * Author: pierfrancesco
 *
 * Created on 21 ottobre 2014, 16.01
 */

#include "XRewriteInputBuilder.h"
#include "../../util/Utils.h"
#include <sstream>

using namespace std;
using namespace DLV2::REWRITERS;

XRewriteInputBuilder::XRewriteInputBuilder():
        termStack(),
        predName(),
        atomStack(),
        literalStack(),
        literalActuallyAddedToLiteralStack(false),
        currentBodyLiterals(0),
        currentHeadAtoms(0),
        isDisjunctiveCurrentHead(false),
        isConjunctiveCurrentHead(false),
        nTermsForWeight(0),
        nTermsForLevel(0),
        nTermsAfterLevel(0),
        hasNegation(false),
        hasDisjunction(false),
        hasConjunction(false),
        varsRenaming()
{
    program = new XProgram();
}

XRewriteInputBuilder::~XRewriteInputBuilder()
{
}

void
XRewriteInputBuilder::onRule()
{
    assert_msg( atomStack.size() > 0, "Not valid head" );
    XHead* currentHead = NULL;
    XBody* currentBody = NULL;

    if( isDisjunctiveCurrentHead )
    {
        assert_msg( ( atomStack.size() == currentHeadAtoms && currentHeadAtoms > 1 ),
                "Not valid disjunctive head" );
        currentHead = program->createDisjunctiveHead(atomStack);
    }
    else if( isConjunctiveCurrentHead )
    {
        assert_msg( ( atomStack.size() == currentHeadAtoms && currentHeadAtoms > 1 ),
                "Not valid conjunctive head" );
        currentHead = program->createConjunctiveHead(atomStack);
    }
    else
    {
        assert_msg( ( atomStack.size() == currentHeadAtoms && currentHeadAtoms == 1 ),
                "Not valid atomic head" );
        currentHead = program->createAtomicHead(atomStack.back());
    }

    assert_msg( literalStack.size() == currentBodyLiterals, "Not valid body" );
    if( currentBodyLiterals > 0 )
        currentBody = program->createBody(literalStack);

    XRule* rule = program->createRule(currentHead,currentBody);
    program->addRule(*rule);

    // The destructor of XRule destroys also currentHead and currentBody.
    delete rule;
    atomStack.clear();
    literalStack.clear();
    currentBodyLiterals = 0;
    currentHeadAtoms = 0;
    isDisjunctiveCurrentHead = false;
    isConjunctiveCurrentHead = false;
    nTermsForWeight = 0;
    nTermsForLevel = 0;
    nTermsAfterLevel = 0;
    varsRenaming.clear();
}

void
XRewriteInputBuilder::onConstraint()
{
    assert_msg( 0, "At the moment, constraints are not supported" );
    // TODO
    // How to handle constraints?

    assert_msg( atomStack.size() == 0, "A constraint does not have an head" );
    assert_msg( literalStack.size() == currentBodyLiterals, "Not valid body constraint" );
    literalStack.clear();
    currentBodyLiterals = 0;
    nTermsForWeight = 0;
    nTermsForLevel = 0;
    nTermsAfterLevel = 0;
    varsRenaming.clear();
}

void
XRewriteInputBuilder::onWeakConstraint()
{
    assert_msg( 0, "At the moment, weak constraints are not supported" );
    // TODO
    // How to handle weak constraints?

    // At the moment we are simply deleting the terms which are
    // involved in the current weak constraint.
    assert_msg( nTermsForWeight +
            nTermsForLevel +
            nTermsAfterLevel <=
            termStack.size(),
            "The terms' stack has not a sufficient number of terms "
            "for building weight, level and terms of the current "
            "weak constraint.");
    // On top of the terms' stack there should be the list of terms
    // in the reverse order.
    if( nTermsAfterLevel > 0 )
    {
        unsigned stackSize = termStack.size();
        termStack.erase(termStack.begin()+(stackSize-nTermsAfterLevel),termStack.end());
    }
    // Then, we should have the level.
    if( nTermsForLevel )
    {
        termStack.pop_back();
    }
    // Finally, the weight.
    if( nTermsForWeight )
    {
        termStack.pop_back();
    }
    assert_msg( atomStack.size() == 0, "A constraint does not have an head" );
    assert_msg( literalStack.size() == currentBodyLiterals, "Not valid body constraint" );
    literalStack.clear();
    currentBodyLiterals = 0;
    nTermsForWeight = 0;
    nTermsForLevel = 0;
    nTermsAfterLevel = 0;
    varsRenaming.clear();
}

void
XRewriteInputBuilder::onQuery()
{
    assert_msg( atomStack.size() > 0, "Trying to adding a null query atom" );
    program->addQuery(atomStack.back());
    atomStack.pop_back();
    varsRenaming.clear();
}

void
XRewriteInputBuilder::onHeadAtom()
{
    currentHeadAtoms++;
}

void
XRewriteInputBuilder::onAtomicHead()
{
    isDisjunctiveCurrentHead = false;
    isConjunctiveCurrentHead = false;
}

void
XRewriteInputBuilder::onDisjunctiveHead()
{
    isDisjunctiveCurrentHead = true;
    isConjunctiveCurrentHead = false;
    hasDisjunction = true;
}

void
XRewriteInputBuilder::onConjunctiveHead()
{
    isDisjunctiveCurrentHead = false;
    isConjunctiveCurrentHead = true;
    hasConjunction = true;
}

void
XRewriteInputBuilder::onHead()
{
}

void
XRewriteInputBuilder::onBodyLiteral()
{
    if( literalActuallyAddedToLiteralStack )
        currentBodyLiterals++;
}

void
XRewriteInputBuilder::onBody()
{
}

void
XRewriteInputBuilder::onNafLiteral(
    bool naf )
{
    assert_msg( atomStack.size() > 0, "Trying to finalize a literal without any atom" );
    XLiteral* currentLiteral = program->createLiteral(atomStack.back(),naf);
    assert_msg( currentLiteral, "Trying to finalize a literal without any atom" );

    literalActuallyAddedToLiteralStack = literalStack.pushItem(*currentLiteral);

    if( naf )
        hasNegation = true;
    atomStack.pop_back();
    delete currentLiteral;
}

void
XRewriteInputBuilder::onAtom(
    bool isStrongNeg )
{
    assert_msg( predName.length() > 0,
            "Trying to finalize an atom with a null predicate name" );

    XAtom* currentAtom = NULL;

    if( isStrongNeg )
    {
        const char* negName = Utils::getNegativeName(predName);
        pair< index_t, bool > res = program->addPredicate(negName,termStack.size());
        delete negName;
        currentAtom = program->createAtom(res.first,termStack,true);
    }
    else
    {
        pair< index_t, bool > res = program->addPredicate(predName,termStack.size());
        currentAtom = program->createAtom(res.first,termStack);
    }

    assert_msg( currentAtom != NULL, "The atom has not been created" );
    atomStack.push_back(*currentAtom);
    termStack.clear();
    predName = "";
    delete currentAtom;
}

void
XRewriteInputBuilder::onExistentialAtom()
{
    assert_msg( 0, "At the moment, a different syntax for existential atoms is supported" );
}

void
XRewriteInputBuilder::onPredicateName(
    char* name )
{
    assert_msg( name, "Trying to create an atom with a null predicate name" );
    predName.assign(name);
}

void
XRewriteInputBuilder::onExistentialVariable(
    char* var )
{
    assert_msg( 0, "At the moment, a different syntax for existential atoms is supported" );
}

void
XRewriteInputBuilder::onEqualOperator()
{
}

void
XRewriteInputBuilder::onUnequalOperator()
{
}

void
XRewriteInputBuilder::onLessOperator()
{
}

void
XRewriteInputBuilder::onLessOrEqualOperator()
{
}

void
XRewriteInputBuilder::onGreaterOperator()
{
}

void
XRewriteInputBuilder::onGreaterOrEqualOperator()
{
}

void
XRewriteInputBuilder::onTerm(
    char* value )
{
    newTerm(value,termStack);
}

void
XRewriteInputBuilder::onTerm(
    int value )
{
    XTerm* currentTerm = program->createIntegerConstant(value);

    // Push currentTerm into the stack.
    assert_msg( currentTerm != NULL, "The term has not been created" );
    termStack.push_back(*currentTerm);
    delete currentTerm;
}

void
XRewriteInputBuilder::onUnknownVariable()
{
    XTerm* currentTerm = program->createUnknownVariable();

    // Push currentTerm into the stack.
    assert_msg( currentTerm != NULL, "The term has not been created" );
    termStack.push_back(*currentTerm);
    delete currentTerm;
}

void
XRewriteInputBuilder::onFunction(
    char* functionSymbol,
    int nTerms )
{
    assert_msg( 0, "At the moment, functions are not supported" );
    // TODO
    // How to handle functions?

    // Consume nTerms from the stack.
//    unsigned newSize = termStack.size()-nTerms;
//    termStack.erase(termStack.begin()+newSize,termStack.end());
}

void
XRewriteInputBuilder::onTermDash()
{
    assert_msg( 0, "At the moment, dashed terms are not supported" );
    // TODO
    // How to handle dashed terms?

    // Consume one term from the stack.
//    termStack.pop_back();
}

void
XRewriteInputBuilder::onTermParams()
{
    assert_msg( 0, "At the moment, parenthesized terms are not supported" );
    // TODO
    // How to handle parametric terms?

    // Consume one term from the stack.
//    termStack.pop_back();
}

void
XRewriteInputBuilder::onTermRange(
    char* lowerBound,
    char* upperBound )
{
    assert_msg( 0, "At the moment, range facts are not supported" );
    // TODO
    // How to handle a terms range?
}

void
XRewriteInputBuilder::onArithmeticOperation(
    char arithOperator )
{
    assert_msg( 0, "At the moment, arithmetic operations are not supported" );
    // TODO
    // How to handle arithmetic operations?

    // The right and left operands are on top of the stack.
//    termStack.pop_back();
//    termStack.pop_back();
}

void
XRewriteInputBuilder::onWeightAtLevels(
    int nWeight,
    int nLevel,
    int nTerm )
{
    nTermsForWeight = nWeight;
    nTermsForLevel = nLevel;
    nTermsAfterLevel = nTerm;
}

void
XRewriteInputBuilder::onChoiceLowerGuard()
{
    assert_msg( 0, "At the moment, choice atoms are not supported" );
    // TODO
    // How to handle choice atoms?
}

void
XRewriteInputBuilder::onChoiceUpperGuard()
{
    assert_msg( 0, "At the moment, choice atoms are not supported" );
    // TODO
    // How to handle choice atoms?
}

void
XRewriteInputBuilder::onChoiceElementAtom()
{
    assert_msg( 0, "At the moment, choice atoms are not supported" );
    // TODO
    // How to handle choice atoms?
}

void
XRewriteInputBuilder::onChoiceElementLiteral()
{
    assert_msg( 0, "At the moment, choice atoms are not supported" );
    // TODO
    // How to handle choice atoms?
}

void
XRewriteInputBuilder::onChoiceElement()
{
    assert_msg( 0, "At the moment, choice atoms are not supported" );
    // TODO
    // How to handle choice atoms?
}

void
XRewriteInputBuilder::onChoiceAtom()
{
    assert_msg( 0, "At the moment, choice atoms are not supported" );
    // TODO
    // How to handle choice atoms?

    // REMINDER... add this statement to function createExistentialAtom
    // that you're going to add to the XProgram interface:
//    pair< index_t, bool > res = program->addPredicate(predName,termStack.size());
}

void
XRewriteInputBuilder::onBuiltinAtom()
{
    assert_msg( 0, "At the moment, built-in atoms are not supported" );
    // TODO
    // How to handle built-in atoms?

//    termStack.clear();
//    predName = "";
}

void
XRewriteInputBuilder::onAggregateLowerGuard()
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?

    // The lower guard should be on top of the stack.
//    termStack.pop_back();
}

void
XRewriteInputBuilder::onAggregateUpperGuard()
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?

    // The lower guard should be on top of the stack.
//    termStack.pop_back();
}

void
XRewriteInputBuilder::onAggregateFunction(
    char* functionSymbol )
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?
}

void
XRewriteInputBuilder::onAggregateGroundTerm(
    char* value,
    bool dash )
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?
}

void
XRewriteInputBuilder::onAggregateVariableTerm(
    char* value )
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?
}

void
XRewriteInputBuilder::onAggregateUnknownVariable()
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?
}

void
XRewriteInputBuilder::onAggregateNafLiteral()
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?

//    assert_msg( currentLiteral, "Trying to adding a null literal" );
//    delete currentLiteral;
}

void
XRewriteInputBuilder::onAggregateElement()
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?
}

void
XRewriteInputBuilder::onAggregate(
    bool naf )
{
    assert_msg( 0, "At the moment, aggregate atoms are not supported" );
    // TODO
    // How to handle aggregate atoms?
}

XProgram*
XRewriteInputBuilder::getProgram()
{
    assert_msg( program != NULL, "Null program" );
    program->computeQueryRules();
    return program;
}

void
XRewriteInputBuilder::newTerm(
    char* value,
    vector< XTerm >& target,
    bool dash )
{
    XTerm* currentTerm = NULL;

    if( value[0] >= 'A' && value[0] <='Z' ) // Variable
    {
        string varName(value);
        unordered_map< string, string >::const_iterator it = varsRenaming.find(varName);
        if( it != varsRenaming.end() )
        {
            currentTerm = program->createStandardVariable(it->second);
        }
        else
        {
            stringstream ss;
            ss << "X" << program->incrementVariablesCounter();
            varsRenaming.insert(pair< const string&, const string& >(varName,ss.str()));
            currentTerm = program->createStandardVariable(ss.str());

        }
    }
    else if( Utils::isNumeric(value,10) ) // Numeric constant
    {
        int val = atoi(value);
        if( dash )
            val = 0 - val;
        currentTerm = program->createIntegerConstant(val);
    }
    else // String
    {
        currentTerm = program->createStringConstant(value);
    }

    // Push currentTerm into the stack.
    assert_msg( currentTerm != NULL, "The term has not been created" );
    target.push_back(*currentTerm);
    delete currentTerm;
}

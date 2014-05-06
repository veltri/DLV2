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

#include <sstream>
#include <cstring>
#include <cstdlib>
#include "SimpleInputBuilder.h"
#include "../util/Assert.h"

using namespace std;

namespace DLV2
{

SimpleInputBuilder::SimpleInputBuilder():
        program(new Program()), 
        currentLiteral(NULL),
        currentAtom(NULL), 
        varCounter(0), 
        query(NULL),
        nTermsForWeight(0), 
        nTermsForLevel(0), 
        nTermsAfterLevel(0),
        lowerGuard(NULL), 
        upperGuard(NULL),
        currentChoiceElement(NULL),
        currentChoiceAtom(NULL)
{ 
    
}

SimpleInputBuilder::~SimpleInputBuilder()
{
    if( program != NULL )
        delete program;
    if( query != NULL )
        delete query;
    if( currentLiteral != NULL )
        delete currentLiteral;
    if( currentAtom != NULL )
        delete currentAtom;
    if( lowerGuard != NULL )
        delete lowerGuard;
    if( upperGuard != NULL )
        delete upperGuard;
    if( currentChoiceElement != NULL )
        delete currentChoiceElement;
    if( currentChoiceAtom != NULL )
        delete currentChoiceAtom;
}

Program&
SimpleInputBuilder::getProgram()
{ 
    // It should be not null;
    assert_msg( program, "The program is null!" );
    return *program; 
}

Atom* 
SimpleInputBuilder::getQuery() 
{
    // It could be null;
    return query; 
}

void 
SimpleInputBuilder::onRule()
{
    if( currentChoiceAtom != NULL )
    {
        ChoiceRule currentRule(*currentChoiceAtom,body);
        program->addChoiceRule(currentRule);
        delete currentChoiceAtom;
        currentChoiceAtom = NULL;
    }
    else
    {
        Rule currentRule(head,body);
        program->addRule(currentRule);
        head.clear();
    }
    body.clear();
    localVariables.clear();
    varCounter = 0;
}

void 
SimpleInputBuilder::onConstraint()
{
    Constraint currentConstraint(body);
    program->addConstraint(currentConstraint);
    head.clear();
    body.clear();
    localVariables.clear();
    varCounter = 0;
}
    
void 
SimpleInputBuilder::onWeakConstraint()
{
    assert_msg( nTermsForWeight +
            nTermsForLevel +
            nTermsAfterLevel <= 
            termStack.size(),
            "The terms' stack has not a sufficient number of terms "
            "for building weight, level and terms of the current "
            "weak constraint.");
    // On top of the terms' stack 
    // there should be the list of terms 
    // in the reverse order.
    vector<Term> terms;
    if( nTermsAfterLevel > 0 )
    {
        unsigned stackSize = termStack.size();
        for( unsigned i=0; i<nTermsAfterLevel; i++ )
        {
            terms.push_back(termStack[stackSize-nTermsAfterLevel+i]);
        }
        termStack.erase(termStack.begin()+(stackSize-nTermsAfterLevel),termStack.end());
    }
    // Then, we should have the level.
    Term* level = NULL;
    if( nTermsForLevel )
    {
        level = new Term(termStack.back());
        termStack.pop_back();
    }
    // Finally, the weight.
    Term* weight = NULL;
    if( nTermsForWeight )
    {
        weight = new Term(termStack.back());
        termStack.pop_back();
    }
    WeakConstraint wc(body,weight,level,terms);
    program->addWeakConstraint(wc);
    body.clear();
    localVariables.clear();
    varCounter = 0;
    if( weight != NULL )
        delete weight;
    if( level != NULL )
        delete level;
}

void 
SimpleInputBuilder::onQuery()
{
    assert_msg( currentAtom, "Trying to adding a null query atom" );
    if( query != NULL )
    {
        cout << "Query " << (*currentAtom) << " replaces " << query << endl;
        delete query;
    }
    query = new Atom(*currentAtom);
    if( currentAtom )
    {
        delete currentAtom;
        currentAtom = NULL;
    }
}
    
// Finalize an atom; destroy all of its properties.
void 
SimpleInputBuilder::onHeadAtom() 
{
    assert_msg( currentAtom, "Trying to adding a null atom" );
    head.push_back(*currentAtom);
    if( currentAtom )
    {
        delete currentAtom;
        currentAtom = NULL;
    }
}
 
// Finalize a literal; destroy all of its properties.
void 
SimpleInputBuilder::onBodyLiteral()
{
    assert_msg( currentLiteral, "Trying to adding a null literal" );
    body.push_back(*currentLiteral);
    if( currentLiteral )
    {
        delete currentLiteral;    
        currentLiteral = NULL;
    }
}
    
void 
SimpleInputBuilder::onNafLiteral( 
    bool naf )
{
    assert_msg( currentAtom, "Trying to finalize a literal without any atom" );
    if( currentLiteral != NULL )
    {
        delete currentLiteral;
        currentLiteral = NULL;
    }
    currentLiteral = new Literal(*currentAtom,naf);
    if( currentAtom )
    {
        delete currentAtom;   
        currentAtom = NULL;
    }
}
    
void 
SimpleInputBuilder::onAtom( 
    bool isStrongNeg )
{
    assert_msg( predName.length() > 0, 
            "Trying to finalize an atom with a null predicate name" );
    if( currentAtom != NULL )
    {
        delete currentAtom;
        currentAtom = NULL;
    }
    currentAtom = new Atom(predName, termStack.size(), 
            termStack, isStrongNeg);
    termStack.clear();
    predName = "";
}

void 
SimpleInputBuilder::onExistentialAtom()
{
    assert_msg( predName.length() > 0, 
            "Trying to finalize an atom with a null predicate name" );
    if( currentAtom != NULL )
    {
        delete currentAtom;
        currentAtom = NULL;
    }
    currentAtom = new Atom(predName, termStack.size(), 
            termStack, existVars);
    termStack.clear();
    existVars.clear();
    predName = "";
}
    
void 
SimpleInputBuilder::onPredicateName( 
    char* name )
{
    assert_msg( name, "Trying to create an atom with a null predicate name" );
    predName = string(name);
}
    
void 
SimpleInputBuilder::onExistentialVariable(
    char* var )
{
    // Looking for other instances of 
    // the variable in the current rule
    bool found = false;
    for( unsigned i=0; i<localVariables.size() && !found; i++ )
        if( localVariables[i].varName == var )
        {
            existVars.push_back(Term(localVariables[i].varIndex,string(var)));
            found = true;
        }
    if( !found )
    {
        existVars.push_back(Term(varCounter,string(var)));
        VariableIndex ind;
        ind.varIndex = varCounter++;
        ind.varName = string(var);
        localVariables.push_back( ind );
    }       
}

void 
SimpleInputBuilder::onTerm( 
    char* value )
{
    newTerm(value,termStack);
}
    
void 
SimpleInputBuilder::onTerm( 
    int value )
{
    termStack.push_back(Term(value));
}
    
void 
SimpleInputBuilder::onFunction( 
    char* functionSymbol, 
    int nTerms )
{
    // Pop nTerms elements from the stack and 
    // create a function term with them. 
    // Afterward, push the function into the stack.
    assert_msg( (functionSymbol && strlen(functionSymbol) > 0), 
            "Trying to create a function with a null symbol" );
    
    // FIXME
    stringstream ss;
    ss << functionSymbol << "(";
    // Consume nTerms from the stack
    for( unsigned i=termStack.size()-nTerms; i<termStack.size(); i++ )
    {
        ss << termStack[i];
        if( i < termStack.size()-1 )
            ss << ",";
    }
    ss << ")";
    // Consume nTerms from the stack.
    unsigned newSize = termStack.size()-nTerms;
    termStack.erase(termStack.begin()+newSize,termStack.end());
    // Push the function into the stack.
    termStack.push_back(Term(ss.str()));
}
    
void 
SimpleInputBuilder::onTermDash()
{
    // Pop nTerms elements from the stack and put "-" in front of them. 
    // Afterward, push the obtained complex term into the stack.

    // FIXME
    stringstream ss;
    ss << "-";
    ss << termStack.back();
    // Consume one term from the stack.
    termStack.pop_back();
    // Push the function into the stack.
    termStack.push_back(Term(ss.str()));
}
    
void 
SimpleInputBuilder::onTermParams()
{
    // Pop one element from the stack and enclose it in parentheses. 
    // Afterward, push the obtained complex term into the stack.

    // FIXME
    stringstream ss;
    ss << "(";
    ss << termStack.back();
    ss << ")";
    // Consume one term from the stack.
    termStack.pop_back();
    // Push the function into the stack.
    termStack.push_back(Term(ss.str()));
}

void 
SimpleInputBuilder::onArithmeticOperation( char arithOperator )
{
    // The right and left operands are on top of the stack.
    Term rightOperand(termStack.back());
    termStack.pop_back();
    Term leftOperand(termStack.back());
    termStack.pop_back();
    // Build a new term by that arithmetic expression.
    // FIXME
    stringstream ss;
    ss << leftOperand;
    ss << arithOperator;
    ss << rightOperand;
    // Push the function into the stack.
    termStack.push_back(Term(ss.str()));
}

void 
SimpleInputBuilder::onWeightAtLevels( 
    int nWeight, 
    int nLevel, 
    int nTerms )
{
    nTermsForWeight = nWeight; 
    nTermsForLevel = nLevel;
    nTermsAfterLevel = nTerms;
}
    
void 
SimpleInputBuilder::onChoiceLowerGuard( 
    char* binop ) 
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null choice-left term" );
    if( lowerGuard != NULL )
    {
        delete lowerGuard;
        lowerGuard = NULL;
    }
    lowerGuard = new Term(termStack.back());
    termStack.pop_back();
    lowerBinop = string(binop);
}

void 
SimpleInputBuilder::onChoiceUpperGuard(
    char* binop ) 
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null choice-right term" );
    if( upperGuard != NULL )
    {
        delete upperGuard;
        upperGuard = NULL;
    }
    upperGuard = new Term(termStack.back());
    termStack.pop_back();
    upperBinop = string(binop);
}

void 
SimpleInputBuilder::onChoiceElementAtom()
{
    assert_msg( predName.length() > 0, 
            "Trying to finalize an atom with a null predicate name" );
    if( currentAtom != NULL )
    {
        delete currentAtom;
        currentAtom = NULL;
    }
    currentAtom = new Atom(predName, termStack.size(), 
            termStack, false);
    termStack.clear();
    predName = "";
    if( currentChoiceElement != NULL )
    {
        delete currentChoiceElement;
        currentChoiceElement = NULL;
    }
    currentChoiceElement = new ChoiceElement(*currentAtom,vector<Literal>());
    if( currentAtom != NULL )
    {
        delete currentAtom;
        currentAtom = NULL;
    }
}
    
void 
SimpleInputBuilder::onChoiceElementLiteral()
{
    assert_msg( currentChoiceElement, 
            "Trying to add a literal to a null choice element" );
    assert_msg( currentLiteral, 
            "Trying to finalize a null choice literal" );
    currentChoiceElement->addLiteral(*currentLiteral);
    if( currentLiteral )
    {
        delete currentLiteral;    
        currentLiteral = NULL;
    }
}
    
void 
SimpleInputBuilder::onChoiceElement()
{
    assert_msg( currentChoiceElement, 
            "Trying to finalize a null choice element" );
    choiceElements.push_back(*currentChoiceElement);
    if( currentChoiceElement )
    {
        delete currentChoiceElement;
        currentChoiceElement = NULL;
    }
}

void 
SimpleInputBuilder::onChoiceAtom()
{
    if( currentChoiceAtom != NULL )
    {
        delete currentChoiceAtom;
        currentChoiceAtom = NULL;
    }
    currentChoiceAtom = 
            new ChoiceAtom(lowerGuard,lowerBinop,choiceElements,
            upperBinop,upperGuard);
    
    if( lowerGuard )
    {
        delete lowerGuard;
        lowerGuard = NULL;
    }
    if( upperGuard )
    {
        delete upperGuard;
        upperGuard = NULL;
    }
    lowerBinop = "";
    upperBinop = "";
    choiceElements.clear();
}

void 
SimpleInputBuilder::onBuiltinAtom( 
    char* binop )
{
    // The operands should be on top of the terms' stack.
    assert_msg( (termStack.size() > 1 && binop != NULL), 
            "Trying to create an invalid builtin atom" );
    Term* rightOperand = new Term(termStack.back());
    termStack.pop_back();
    Term* leftOperand = new Term(termStack.back());
    termStack.pop_back();
    string op(binop);
    
    if( currentAtom != NULL )
    {
        delete currentAtom;
        currentAtom = NULL;
    }
    currentAtom = new Atom(leftOperand,op,rightOperand);
    termStack.clear();
    predName = "";
    if( leftOperand != NULL )
        delete leftOperand;
    if( rightOperand != NULL )
        delete rightOperand;
}

void 
SimpleInputBuilder::onAggregateLowerGuard( 
    char* op )
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null aggregate lower guard" );
    if( lowerGuard != NULL )
    {
        delete lowerGuard;
        lowerGuard = NULL;
    }
    lowerGuard = new Term(termStack.back());
    termStack.pop_back();
    lowerBinop = string(op);
}

void 
SimpleInputBuilder::onAggregateUpperGuard( 
    char* op )
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null choice-right term" );
    if( upperGuard != NULL )
    {
        delete upperGuard;
        upperGuard = NULL;
    }
    upperGuard = new Term(termStack.back());
    termStack.pop_back();
    upperBinop = string(op);
}

void 
SimpleInputBuilder::onAggregateFunction( 
    char* f )
{
    assert_msg( f, "Trying to create an aggregate with a null function" );
    aggregateFunction = string(f);
}

void 
SimpleInputBuilder::onAggregateGroundTerm( 
    char* value, 
    bool dash )
{
    newTerm(value,aggregateElementTerms,dash);
}
    
void 
SimpleInputBuilder::onAggregateVariableTerm( 
    char* value )
{
    newTerm(value,aggregateElementTerms);
}

void 
SimpleInputBuilder::onAggregateNafLiteral()
{
    // The current literal should be pointed 
    // by currentLiteral;
    assert_msg( currentLiteral, "Trying to adding a null literal" );
    aggregateElementLiterals.push_back(*currentLiteral);
    if( currentLiteral )
    {
        delete currentLiteral;    
        currentLiteral = NULL;
    }
}

void 
SimpleInputBuilder::onAggregateElement()
{
    assert_msg( (aggregateElementTerms.size() > 0 
            && aggregateElementLiterals.size() > 0),
            "Invalid aggregate element.");
    AggregateElement element(aggregateElementTerms,aggregateElementLiterals);
    aggregateElements.push_back(element);
    aggregateElementTerms.clear();
    aggregateElementLiterals.clear();
}

void 
SimpleInputBuilder::onAggregate(
    bool naf )
{
    assert_msg( aggregateFunction.length() > 0, 
            "Trying to finalize an aggregate with a null function symbol" );
    assert_msg( aggregateElements.size() > 0, 
            "Trying to finalize an aggregate without elements" );
    assert_msg( lowerGuard || upperGuard, 
            "Trying to finalize an aggregate without any guards" );
    if( currentLiteral != NULL )
    {
        delete currentLiteral;
        currentLiteral = NULL;
    }
    currentLiteral = new Literal(lowerGuard,lowerBinop,upperGuard,upperBinop,
            aggregateFunction,aggregateElements,naf);
    aggregateElements.clear();
    if( lowerGuard )
    {
        delete lowerGuard;
        lowerGuard = NULL;
    }
    lowerBinop = "";
    if( upperGuard )
    {
        delete upperGuard;
        upperGuard = NULL;
    }
    upperBinop = "";
    aggregateFunction = "";
}

bool 
SimpleInputBuilder::isNumeric( 
    const char* pszInput, 
    int nNumberBase )
{
    istringstream iss( pszInput );
 
    if ( nNumberBase == 10 )
    {
        double dTestSink;
        iss >> dTestSink;
    }
    else if ( nNumberBase == 8 || nNumberBase == 16 )
    {
        int nTestSink;
        iss >> ( ( nNumberBase == 8 ) ? oct : hex ) >> nTestSink;
    }
    else
        return false;
 
    // was any input successfully consumed/converted?
    if ( ! iss )
        return false;
 
    // was all the input successfully consumed/converted?
    return ( iss.rdbuf()->in_avail() == 0 );
}

void 
SimpleInputBuilder::newTerm( 
    char* value,
    vector<Term>& target,
    bool dash )
{
    Term* currentTerm = NULL;
    assert_msg( (value && strlen(value) > 0), 
            "Trying to create a term with a null value" );

    if( value[0] >= 'A' && value[0] <='Z' ) // Variable
    {
        // Looking for other instances of 
        // the variable in the current rule
        for( unsigned i=0; i<localVariables.size() && !currentTerm; i++ )
            if( localVariables[i].varName == value )
                currentTerm = new Term(localVariables[i].varIndex,string(value));
        if( !currentTerm )
        {
            currentTerm = new Term(varCounter,string(value));
            VariableIndex ind;
            ind.varIndex = varCounter++;
            ind.varName = string(value);
            localVariables.push_back( ind );
        }   
    }
    else if( value[0] == '_' && strlen(value) == 1 ) // Unknow variable;
    { 
        currentTerm = new Term(varCounter++,string(value));  
    }
    else if( (value[0] == '\"' && value[strlen(value)-1] == '\"') ||  
            (value[0] >= 'a' && value[0] <='z') )   // String constant
    {
        currentTerm = new Term(value);
    }
    else if( isNumeric( value, 10 ) ) // Numeric constant
    {
        int val = atoi(value);
        if( dash )
            val = 0 - val;
        currentTerm = new Term(val);
    }
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        target.push_back(*currentTerm);
        delete currentTerm;
    }
}

};
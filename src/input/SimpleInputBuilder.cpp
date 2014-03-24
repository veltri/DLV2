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
#include "../data/Variable.h"
#include "../data/StringConstant.h"
#include "../data/IntegerConstant.h"

SimpleInputBuilder::SimpleInputBuilder(): 
        InputBuilder()
{ 
    program = new Program(); 
    currentRule = NULL;
    currentLiteral = NULL;
    currentAtom = NULL;
    currentTerm = NULL;
    varCounter = 0;
    query = NULL;
}

SimpleInputBuilder::~SimpleInputBuilder()
{
    // Delete all terms of the program, 
    // because they are instantiated dinamically.
    for( unsigned i=0; i<allTerms.size(); i++ )
        delete allTerms[i];
    if( program != NULL )
        delete program;
    if( query != NULL )
        delete query;
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
    if( currentRule != NULL )
    {
        delete currentRule;
        currentRule = NULL;
    }
    currentRule = new Rule(head,body);
    
    program->addRule(*currentRule);
    delete currentRule;
    currentRule = NULL;
    head.clear();
    body.clear();
    localVariables.clear();
    varCounter = 0;
}

void 
SimpleInputBuilder::onConstraint()
{
    if( currentRule != NULL )
    {
        delete currentRule;
        currentRule = NULL;
    }
    currentRule = new Rule(head,body);
    
    program->addRule(*currentRule);
    delete currentRule;
    currentRule = NULL;
    head.clear();
    body.clear();
    localVariables.clear();
    varCounter = 0;
}
    
void 
SimpleInputBuilder::onWeakConstraint()
{
    // TODO
}

void 
SimpleInputBuilder::onQuery()
{
    assert_msg( currentAtom, "Trying to adding a null query atom" );
    if( query != NULL )
    {
        cout << "Query " << (*currentAtom) << " replaces " << query << endl;
        delete query;
        query = NULL;
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
SimpleInputBuilder::addToHead() 
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
SimpleInputBuilder::addToBody()
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
    // Before emptying the stack, we store its content.
    // We need these pointers to delete all the terms  
    // of the program, because they are instantiated
    // dinamically.
    allTerms.insert(allTerms.end(),termStack.begin(),termStack.end());
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
    // Before emptying the stack, we store its content.
    // We need these pointers to delete all the terms  
    // of the program, because they are instantiated
    // dinamically.
    allTerms.insert(allTerms.end(),termStack.begin(),termStack.end());
    termStack.clear();
    existVars.clear();
    predName = "";
}
    
void 
SimpleInputBuilder::predicateName( 
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
            existVars.push_back(Variable(localVariables[i].varIndex));
            found = true;
        }
    if( !found )
    {
        existVars.push_back(Variable(varCounter));
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
    if( currentTerm != NULL )
        currentTerm = NULL;
    assert_msg( (value && strlen(value) > 0), 
            "Trying to create a term with a null value" );

    if( value[0] >= 'A' && value[0] <='Z' ) // Variable
    {
        // Looking for other instances of 
        // the variable in the current rule
        for( unsigned i=0; i<localVariables.size() && !currentTerm; i++ )
            if( localVariables[i].varName == value )
                currentTerm = new Variable(localVariables[i].varIndex);
        if( !currentTerm )
        {
            currentTerm = new Variable(varCounter);
            VariableIndex ind;
            ind.varIndex = varCounter++;
            ind.varName = string(value);
            localVariables.push_back( ind );
        }   
    }
    else if( value[0] == '_' && strlen(value) == 1 ) // Unknow variable;
    { 
        currentTerm = new Variable(varCounter++);  
    }
    else if( (value[0] == '\"' && value[strlen(value)-1] == '\"') ||  
            (value[0] >= 'a' && value[0] <='z') )   // String constant
    {
        currentTerm = new StringConstant(value);
    }
    else if( isNumeric( value, 10 ) ) // Numeric constant
    {
        currentTerm = new IntegerConstant( atoi(value) );
    }
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        termStack.push_back(currentTerm);
        currentTerm = NULL;
    }
    
}
    
void 
SimpleInputBuilder::onTerm( 
    int value )
{
    if( currentTerm != NULL )
        currentTerm = NULL;
    currentTerm = new IntegerConstant( value );
    termStack.push_back(currentTerm);
    currentTerm = NULL;
}
    
void 
SimpleInputBuilder::onFunction( 
    char* functionSymbol, 
    int nTerms )
{
    // Pop nTerms elements from the stack and 
    // create a function term with them. 
    // Afterward, push the function into the stack.
    if( currentTerm != NULL )
        currentTerm = NULL;
    assert_msg( (functionSymbol && strlen(functionSymbol) > 0), 
            "Trying to create a function with a null symbol" );
    
    // FIXME
    stringstream ss;
    ss << functionSymbol << "(";
    // Consume nTerms from the stack
    for( unsigned i=termStack.size()-nTerms; i<termStack.size(); i++ )
    {
        ss << termStack[i]->toString();
        // Before popping #nTerms pointers from the stack
        // delete the pointed terms.
        delete termStack[i];
    }
    ss << ")";
    currentTerm = new StringConstant(ss.str());
    // Consume nTerms from the stack.
    unsigned newSize = termStack.size()-nTerms;
    termStack.resize(newSize);
    // Push the function into the stack.
    termStack.push_back(currentTerm);
    currentTerm = NULL;
}
    
void 
SimpleInputBuilder::onTermDash( 
    int nTerms )
{
    // Pop nTerms elements from the stack and put "-" in front of them. 
    // Afterward, push the obtained complex term into the stack.
    if( currentTerm != NULL )
        currentTerm = NULL;
    
    // FIXME
    stringstream ss;
    ss << "-";
    // Consume nTerms from the stack
    for( unsigned i=termStack.size()-nTerms; i<termStack.size(); i++ )
    {
        ss << termStack[i]->toString();
        // Before popping #nTerms pointers from the stack
        // delete the pointed terms.
        delete termStack[i];
    }
    ss << ")";
    currentTerm = new StringConstant(ss.str());
    // Consume nTerms from the stack.
    unsigned newSize = termStack.size()-nTerms;
    termStack.resize(newSize);
    // Push the function into the stack.
    termStack.push_back(currentTerm);
    currentTerm = NULL;
}
    
void 
SimpleInputBuilder::onTermParams( 
    int nTerms )
{
    // Pop nTerms elements from the stack and enclose them in parentheses. 
    // Afterward, push the obtained complex term into the stack.
    if( currentTerm != NULL )
        currentTerm = NULL;
    
    // FIXME
    stringstream ss;
    ss << "(";
    // Consume nTerms from the stack
    for( unsigned i=termStack.size()-nTerms; i<termStack.size(); i++ )
    {
        ss << termStack[i]->toString();
        if( i < termStack.size()-1 )
            ss << ",";
        // Before popping #nTerms pointers from the stack
        // delete the pointed terms.
        delete termStack[i];
    }
    ss << ")";
    currentTerm = new StringConstant(ss.str());
    // Consume nTerms from the stack.
    unsigned newSize = termStack.size()-nTerms;
    termStack.resize(newSize);
    // Push the function into the stack.
    termStack.push_back(currentTerm);
    currentTerm = NULL;
}

void 
SimpleInputBuilder::onArithmeticOperation( char arithOperator )
{
    // The right and left operands are on top of the stack.
    Term* rightOperand = termStack.back();
    termStack.pop_back();
    Term* leftOperand = termStack.back();
    termStack.pop_back();
    // Build a new term by that arithmetic expression.
    // FIXME
    stringstream ss;
    ss << leftOperand->toString();
    ss << arithOperator;
    ss << rightOperand->toString();
    currentTerm = new StringConstant(ss.str());
    // Push the function into the stack.
    termStack.push_back(currentTerm);
    delete leftOperand;
    delete rightOperand;
    currentTerm = NULL;
}

void 
SimpleInputBuilder::onWeight( 
    int nTerms )
{
    
}
    
void 
SimpleInputBuilder::onLevel( 
    int nTerms )
{
    
}
    
void 
SimpleInputBuilder::onLevelsAndTerms( 
    int nTermsForLevel, 
    int nTerms )
{
    
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
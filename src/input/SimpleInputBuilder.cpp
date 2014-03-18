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
}

SimpleInputBuilder::~SimpleInputBuilder()
{
    if( program != NULL )
    {
        delete program;
        program = NULL;
    }
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
}
    
void 
SimpleInputBuilder::onQuery()
{
    
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
SimpleInputBuilder::onNafLiteral( bool naf )
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
SimpleInputBuilder::onAtom( bool isStrongNeg )
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
SimpleInputBuilder::predicateName( char* name )
{
    assert_msg( name, "Trying to create an atom with a null predicate name" );
    predName = string(name);
}
    
void 
SimpleInputBuilder::onTerm( char* value )
{
    if( currentTerm != NULL )
        currentTerm = NULL;
    assert_msg( (value && strlen(value) > 0), 
            "Trying to create a term with a null value" );

    if( value[0] >= 'A' && value[0] <='Z' ) // Variable
    {
        // Looking for other instances of 
        // the variable in the current rule
        for( unsigned i=0; i<localVariables.size(); i++ )
            if( localVariables[i] == value )
                currentTerm = new Variable(i);
        if( !currentTerm )
        {
            localVariables.push_back( string(value) );
            currentTerm = new Variable(localVariables.size());
        }   
    }
    else if( value[0] == '_' && strlen(value) == 1 ) // Unknow variable;
    { 
        currentTerm = new Variable(222);  // FIXME
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
SimpleInputBuilder::onTerm( int value )
{
    if( currentTerm != NULL )
        currentTerm = NULL;
    currentTerm = new IntegerConstant( value );
    termStack.push_back(currentTerm);
    currentTerm = NULL;
}
    
void 
SimpleInputBuilder::onFunction( char* functionSymbol, int nTerms )
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
        if( i < termStack.size()-1 )
            ss << ",";
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
SimpleInputBuilder::onTermDash()
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
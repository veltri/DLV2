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

SimpleInputBuilder::SimpleInputBuilder() :
    program(new Program()), currentLiteral(NULL),
    currentAtom(NULL), varCounter(0), query(NULL),
    nTermsForWeight(0), nTermsForLevel(0), nTermsAfterLevel(0),
    lowerGuard(NULL), upperGuard(NULL),
    currentChoiceElement(NULL),currentChoiceAtom(NULL)

{ 
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
    vector<Term*> terms;
    if( nTermsAfterLevel > 0 )
    {
        unsigned stackSize = termStack.size();
        for( unsigned i=0; i<nTermsAfterLevel; i++ )
        {
            terms.push_back(termStack[stackSize-nTermsAfterLevel+i]);
            allTerms.push_back(termStack[stackSize-nTermsAfterLevel+i]);
        }
        termStack.resize(stackSize-nTermsAfterLevel);
    }
    // Then, we should have the level.
    Term* level = NULL;
    if( nTermsForLevel )
    {
        level = termStack.back();
        allTerms.push_back(termStack.back());
        termStack.pop_back();
    }
    // Finally, the weight.
    Term* weight = NULL;
    if( nTermsForWeight )
    {
        weight = termStack.back();
        allTerms.push_back(termStack.back());
        termStack.pop_back();
    }
    WeakConstraint wc(body,weight,level,terms);
    program->addWeakConstraint(wc);
    body.clear();
    localVariables.clear();
    varCounter = 0;
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
    // Before emptying the terms' stack, we store its content.
    // We need to keep these pointers in memory to delete all the 
    // terms of the program, because they are instantiated
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
            existVars.push_back(Variable(localVariables[i].varIndex,string(var)));
            found = true;
        }
    if( !found )
    {
        existVars.push_back(Variable(varCounter,string(var)));
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
    Term* currentTerm = new IntegerConstant( value );
    termStack.push_back(currentTerm);
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
        ss << termStack[i]->toString();
        if( i < termStack.size()-1 )
            ss << ",";
        // Before popping #nTerms pointers from the stack
        // delete the pointed terms.
        delete termStack[i];
    }
    ss << ")";
    Term* currentTerm = new StringConstant(ss.str());
    // Consume nTerms from the stack.
    unsigned newSize = termStack.size()-nTerms;
    termStack.resize(newSize);
    // Push the function into the stack.
    termStack.push_back(currentTerm);
}
    
void 
SimpleInputBuilder::onTermDash()
{
    // Pop nTerms elements from the stack and put "-" in front of them. 
    // Afterward, push the obtained complex term into the stack.

    // FIXME
    stringstream ss;
    ss << "-";
    ss << termStack.back()->toString();
    // Before popping the pointer from the stack
    // delete the pointed term.
    delete termStack.back();
    // Consume one term from the stack.
    termStack.pop_back();
    Term* currentTerm = new StringConstant(ss.str());
    // Push the function into the stack.
    termStack.push_back(currentTerm);
}
    
void 
SimpleInputBuilder::onTermParams()
{
    // Pop one element from the stack and enclose it in parentheses. 
    // Afterward, push the obtained complex term into the stack.

    // FIXME
    stringstream ss;
    ss << "(";
    ss << termStack.back()->toString();
    ss << ")";
    // Before popping the pointer from the stack
    // delete the pointed term.
    delete termStack.back();
        // Consume one term from the stack.
    termStack.pop_back();
    Term* currentTerm = new StringConstant(ss.str());
    // Push the function into the stack.
    termStack.push_back(currentTerm);
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
    Term* currentTerm = new StringConstant(ss.str());
    // Push the function into the stack.
    termStack.push_back(currentTerm);
    delete leftOperand;
    delete rightOperand;
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
    lowerGuard = termStack.back();
    allTerms.push_back(lowerGuard);
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
    upperGuard = termStack.back();
    allTerms.push_back(upperGuard);
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
    // Before emptying the stack, we store its content.
    // We need these pointers to delete all the terms  
    // of the program, because they are instantiated
    // dinamically.
    allTerms.insert(allTerms.end(),termStack.begin(),termStack.end());
    termStack.clear();
    predName = "";
    if( currentChoiceElement != NULL )
    {
        delete currentChoiceElement;
        currentChoiceElement = NULL;
    }
    vector<Literal> lits;
    currentChoiceElement = new ChoiceElement(*currentAtom,lits);
    if( currentAtom )
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
    lowerGuard = NULL;
    upperGuard = NULL;
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
    Term* rightOperand = termStack.back();
    allTerms.push_back(rightOperand);
    termStack.pop_back();
    Term* leftOperand = termStack.back();
    allTerms.push_back(leftOperand);
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
}

void 
SimpleInputBuilder::onAggregateLowerGuard( 
    char* op )
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null aggregate lower guard" );
    lowerGuard = termStack.back();
    allTerms.push_back(lowerGuard);
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
    upperGuard = termStack.back();
    allTerms.push_back(upperGuard);
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
    // Before emptying the terms' stack, we store its content.
    // We need to keep these pointers in memory to delete all the 
    // terms of the program, because they are instantiated
    // dinamically.
    allTerms.insert(allTerms.end(),aggregateElementTerms.begin(),
            aggregateElementTerms.end());
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
    lowerGuard = NULL;
    lowerBinop = "";
    upperGuard = NULL;
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
    vector<Term*>& target,
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
                currentTerm = new Variable(localVariables[i].varIndex,string(value));
        if( !currentTerm )
        {
            currentTerm = new Variable(varCounter,string(value));
            VariableIndex ind;
            ind.varIndex = varCounter++;
            ind.varName = string(value);
            localVariables.push_back( ind );
        }   
    }
    else if( value[0] == '_' && strlen(value) == 1 ) // Unknow variable;
    { 
        currentTerm = new Variable(varCounter++,string(value));  
    }
    else if( (value[0] == '\"' && value[strlen(value)-1] == '\"') ||  
            (value[0] >= 'a' && value[0] <='z') )   // String constant
    {
        currentTerm = new StringConstant(value);
    }
    else if( isNumeric( value, 10 ) ) // Numeric constant
    {
        int val = atoi(value);
        if( dash )
            val = 0 - val;
        currentTerm = new IntegerConstant(val);
    }
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        target.push_back(currentTerm);
    }
}
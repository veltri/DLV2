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

#include <cstring>
#include <cstdlib>
#include "SelectorBuilder.h"
#include "../util/Assert.h"

SelectorBuilder::SelectorBuilder():
        InputBuilder()
{}

void SelectorBuilder::onRule() { cout << "rule" << endl;
}

void SelectorBuilder::onConstraint() {
}

void SelectorBuilder::onWeakConstraint() { cout << "weak" << endl;
}

void SelectorBuilder::onQuery() { cout << "query" << endl;
}

void SelectorBuilder::onHeadAtom() { cout << "head" << endl;
}

void SelectorBuilder::onBodyLiteral() { cout << "body" << endl;
}

void SelectorBuilder::onNafLiteral(bool naf) { cout << "neg lit" << endl;
}

void SelectorBuilder::onAtom(bool isStrongNeg) { cout << "atom" << endl;
}

void SelectorBuilder::onExistentialAtom() {
}

void SelectorBuilder::onPredicateName(char* p) { cout << "pred"<< p << endl;
}

void SelectorBuilder::onExistentialVariable(char*) {
}

void SelectorBuilder::onTerm(char*) {
}

void SelectorBuilder::onTerm(int int1) {
}

void SelectorBuilder::onFunction(char*, int int1) {
}

void SelectorBuilder::onTermDash() {
}

void SelectorBuilder::onTermParams() {
}

void SelectorBuilder::onArithmeticOperation(char char1) {
}

void SelectorBuilder::onWeightAtLevels(int int1, int int2, int int3) {
}

void SelectorBuilder::onChoiceLowerGuard(char*) {
}

void SelectorBuilder::onChoiceUpperGuard(char*) {
}

void SelectorBuilder::onChoiceElementAtom() { cout << "choice" << endl;
}

void SelectorBuilder::onChoiceElementLiteral() {
}

void SelectorBuilder::onChoiceElement() {
}

void SelectorBuilder::onChoiceAtom() {
}

void SelectorBuilder::onBuiltinAtom(char*) {
}

void SelectorBuilder::onAggregateLowerGuard(char*) {
}

void SelectorBuilder::onAggregateUpperGuard(char*) {
}

void SelectorBuilder::onAggregateFunction(char*) {
}

void SelectorBuilder::onAggregateGroundTerm(char*, bool dash) {
}

void SelectorBuilder::onAggregateVariableTerm(char*) {
}

void SelectorBuilder::onAggregateNafLiteral() { cout << "aggneg" << endl;
}

void SelectorBuilder::onAggregateElement() { cout << "aggpos" << endl;
}

void SelectorBuilder::onAggregate(bool naf) { cout << "agg" << endl;
}

unsigned
SelectorBuilder::getSolverToCall()
{
 return 0;
}



SelectorBuilder::~SelectorBuilder()
{

}

 /*
SelectorBuilder::~SelectorBuilder()
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
SelectorBuilder::getProgram()
{ 
    // It should be not null;
    assert_msg( program, "The program is null!" );
    return *program; 
}

Atom* 
SelectorBuilder::getQuery()
{
    // It could be null;
    return query; 
}

void 
SelectorBuilder::onRule()
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
SelectorBuilder::onConstraint()
{
    Constraint currentConstraint(body);
    program->addConstraint(currentConstraint);
    head.clear();
    body.clear();
    localVariables.clear();
    varCounter = 0;
}
    
void 
SelectorBuilder::onWeakConstraint()
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
SelectorBuilder::onQuery()
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
SelectorBuilder::onHeadAtom()
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
SelectorBuilder::onBodyLiteral()
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
SelectorBuilder::onNafLiteral(
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
SelectorBuilder::onAtom(
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
SelectorBuilder::onExistentialAtom()
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
SelectorBuilder::onPredicateName(
    char* name )
{
    assert_msg( name, "Trying to create an atom with a null predicate name" );
    predName = string(name);
}
    
void 
SelectorBuilder::onExistentialVariable(
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
SelectorBuilder::onTerm(
    char* value )
{
    newTerm(value,termStack);
}
    
void 
SelectorBuilder::onTerm(
    int value )
{
    Term* currentTerm = new IntegerConstant( value );
    termStack.push_back(currentTerm);
}
    
void 
SelectorBuilder::onFunction(
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
SelectorBuilder::onTermDash()
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
SelectorBuilder::onTermParams()
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
SelectorBuilder::onArithmeticOperation( char arithOperator )
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
SelectorBuilder::onWeightAtLevels(
    int nWeight, 
    int nLevel, 
    int nTerms )
{
    nTermsForWeight = nWeight; 
    nTermsForLevel = nLevel;
    nTermsAfterLevel = nTerms;
}
    
void 
SelectorBuilder::onChoiceLowerGuard(
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
SelectorBuilder::onChoiceUpperGuard(
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
SelectorBuilder::onChoiceElementAtom()
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
SelectorBuilder::onChoiceElementLiteral()
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
SelectorBuilder::onChoiceElement()
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
SelectorBuilder::onChoiceAtom()
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
SelectorBuilder::onBuiltinAtom(
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
SelectorBuilder::onAggregateLowerGuard(
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
SelectorBuilder::onAggregateUpperGuard(
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
SelectorBuilder::onAggregateFunction(
    char* f )
{
    assert_msg( f, "Trying to create an aggregate with a null function" );
    aggregateFunction = string(f);
}

void 
SelectorBuilder::onAggregateGroundTerm(
    char* value, 
    bool dash )
{
    newTerm(value,aggregateElementTerms,dash);
}
    
void 
SelectorBuilder::onAggregateVariableTerm(
    char* value )
{
    newTerm(value,aggregateElementTerms);
}

void 
SelectorBuilder::onAggregateNafLiteral()
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
SelectorBuilder::onAggregateElement()
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
SelectorBuilder::onAggregate(
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
SelectorBuilder::isNumeric(
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
SelectorBuilder::newTerm(
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
*/

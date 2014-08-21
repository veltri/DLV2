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

#include "DBInputBuilder.h"
#include "../../util/Utils.h"
#include "../sql/QueryBuilder.h"

using namespace std;
using namespace DLV2::DB;
    
DBInputBuilder::DBInputBuilder(
    DBConnection& con ):
        currentAtom(NULL),
        isChoice(false),
        currentLiteral(NULL),
        query(NULL),
        nTermsForWeight(0),
        nTermsForLevel(0),
        nTermsAfterLevel(0),
        lowerGuard(NULL),
        upperGuard(NULL),
        hasNegation(false),
        hasAggregates(false),
        hasBuiltins(false)
{
    program = new DBProgram(con);
    queryBuilder = new QueryBuilder(program);
    program->setQueryBuilder(queryBuilder);
    graph = new LabeledDependencyGraph<>();
}
    
DBInputBuilder::~DBInputBuilder()
{
    if( queryBuilder != NULL )
        delete queryBuilder;
}

void 
DBInputBuilder::onRule()
{
    program->createAndAddRule(head,body,hasNegation,hasAggregates,hasBuiltins);
    // Add an edge from each body literal to each head atom.
    for( unsigned i=0; i<head.size(); i++ )
    {
        for( unsigned j=0; j<body.size(); j++ )
        {
            assert_msg( head[i] != NULL, "Trying to create a rule with a null head atom." );
            assert_msg( body[j] != NULL, "Trying to create a rule with a null body literal." );
            // An head atom cannot be a builtin.
            if( head[i]->isTrueNegated() )
                addEdgeToDepGraph(string("-").append(head[i]->getPredicateName()),body[j]);
            else
                addEdgeToDepGraph(head[i]->getPredicateName(),body[j]);
        }   
    }
    head.clear();
    body.clear();
    hasNegation = false;
    hasAggregates = false;
    hasBuiltins = false;
}

void
DBInputBuilder::onConstraint()
{
    // TODO 
    // How to handle constraints?
    
    body.clear();
}

void
DBInputBuilder::onWeakConstraint()
{
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
        for( unsigned i=0; i<nTermsAfterLevel; i++ )
        {
            delete termStack[stackSize-nTermsAfterLevel+i];
        }
        termStack.erase(termStack.begin()+(stackSize-nTermsAfterLevel),termStack.end());
    }
    // Then, we should have the level.
    if( nTermsForLevel )
    {
        delete termStack.back();
        termStack.pop_back();
    }
    // Finally, the weight.
    if( nTermsForWeight )
    {
        delete termStack.back();
        termStack.pop_back();
    }
    body.clear();
}

void
DBInputBuilder::onQuery()
{
    assert_msg( currentAtom, "Trying to adding a null query atom" );
    if( query != NULL )
    {
        cout << "Query " << (*currentAtom) << " replaces " << query << endl;
        delete query;
    }
    query = currentAtom;
}

void
DBInputBuilder::onHeadAtom()
{
    assert_msg( currentAtom, "Trying to adding a null atom" );
    head.push_back(currentAtom);
}

void 
DBInputBuilder::onHead()
{
    vector<unsigned> headVertices;
    // Add head atoms to the graph in order to keep track of atoms which appear
    // only in heads of rules without body.
    for( unsigned i=0; i<head.size(); i++ )
    {
        assert_msg( head[i] != NULL, "Null head atom." );
        headVertices.push_back(
            graph->addVertex(
                head[i]->getPredicateName()));
    }
    if( !isChoice && head.size() > 1 )
    {
        graph->addDisjunctiveHead(headVertices);
    }
    isChoice = false;    
}

void
DBInputBuilder::onBodyLiteral()
{
    assert_msg( currentLiteral, "Trying to adding a null literal" );
    body.push_back(currentLiteral);
}

void
DBInputBuilder::onBody()
{
    
}

void
DBInputBuilder::onNafLiteral( 
    bool naf )
{
    assert_msg( currentAtom, "Trying to finalize a literal without any atom" );
    currentLiteral = program->createLiteral(currentAtom,naf);
    if( naf )
        hasNegation = true;
}

void
DBInputBuilder::onAtom( 
    bool isStrongNeg )
{
    assert_msg( predName.length() > 0, 
            "Trying to finalize an atom with a null predicate name" );

    program->addPredicateName(predName,termStack.size());
    currentAtom = program->createAtom(predName, termStack, isStrongNeg);
    termStack.clear();
    predName = "";
}

void
DBInputBuilder::onExistentialAtom()
{
    // TODO
    program->addPredicateName(predName,termStack.size());
}

void
DBInputBuilder::onPredicateName( 
    char* name )
{
    assert_msg( name, "Trying to create an atom with a null predicate name" );
    predName.assign(name);
}

void
DBInputBuilder::onExistentialVariable( 
    char* var )
{
    // TODO
}

void
DBInputBuilder::onEqualOperator()
{
    binop.assign("=");
}

void
DBInputBuilder::onUnequalOperator()
{
    binop.assign("<>");
}

void
DBInputBuilder::onLessOperator()
{
    binop.assign("<");
}

void
DBInputBuilder::onLessOrEqualOperator()
{
    binop.assign("<=");
}

void
DBInputBuilder::onGreaterOperator()
{
    binop.assign(">");
}

void
DBInputBuilder::onGreaterOrEqualOperator()
{
    binop.assign(">=");
}

void
DBInputBuilder::onTerm( 
    char* value )
{
    newTerm(value,termStack);
}

void
DBInputBuilder::onTerm( 
    int value )
{
    DBTerm* currentTerm = NULL;
    
    currentTerm = program->createIntegerConstant(value);
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        termStack.push_back(currentTerm);
    }
}

void
DBInputBuilder::onUnknownVariable()
{
    DBTerm* currentTerm = NULL;
    
    currentTerm = program->createVariable(string("_"));
    
    // Push currentTerm into the stack.
    if( currentTerm != NULL )
    {
        termStack.push_back(currentTerm);
    }
}

void 
DBInputBuilder::onFunction( 
    char* functionSymbol, 
    int nTerms )
{
    // TODO
    // How to handle functions?
    
    // Consume nTerms from the stack.
    unsigned newSize = termStack.size()-nTerms;
    termStack.erase(termStack.begin()+newSize,termStack.end());
}

void 
DBInputBuilder::onTermDash()
{
    // TODO 
    // How to handle dashed terms?
    
    // Consume one term from the stack.
    termStack.pop_back();
}

void 
DBInputBuilder::onTermParams()
{
    // TODO 
    // How to handle parametric terms?
    
    // Consume one term from the stack.
    termStack.pop_back();
}

void 
DBInputBuilder::onTermRange( 
    char* lowerBound, 
    char* upperBound )
{
    // TODO
    // How to handle a terms range?
}

void 
DBInputBuilder::onArithmeticOperation( 
    char arithOperator )
{
    // TODO
    // How to handle arithmetic operations?
    
    // The right and left operands are on top of the stack.
    termStack.pop_back();
    termStack.pop_back();
}

void 
DBInputBuilder::onWeightAtLevels( 
    int nWeight, 
    int nLevel, 
    int nTerm )
{
    nTermsForWeight = nWeight; 
    nTermsForLevel = nLevel;
    nTermsAfterLevel = nTerm;
}

void 
DBInputBuilder::onChoiceLowerGuard()
{
    // TODO
}

void 
DBInputBuilder::onChoiceUpperGuard()
{
    // TODO
}

void 
DBInputBuilder::onChoiceElementAtom()
{
    // TODO
    program->addPredicateName(predName,termStack.size());
}

void 
DBInputBuilder::onChoiceElementLiteral()
{
    // TODO
}

void 
DBInputBuilder::onChoiceElement()
{
    // TODO
}

void 
DBInputBuilder::onChoiceAtom()
{
    // TODO
    isChoice = true;
}
    
void 
DBInputBuilder::onBuiltinAtom()
{
    // FIXME : a builtin is likely to be composed of more than two terms. 
    // The operands should be on top of the terms' stack.
    assert_msg( termStack.size() > 1,
            "Trying to create an invalid builtin atom" );
    DBTerm* rightOperand = termStack.back();
    termStack.pop_back();
    DBTerm* leftOperand = termStack.back();
    termStack.pop_back();
    
    currentAtom = program->createBuiltinAtom(leftOperand,binop,rightOperand);
    termStack.clear();
    predName = "";
    hasBuiltins = true;
}
 
void 
DBInputBuilder::onAggregateLowerGuard() 
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null aggregate lower guard" );
    lowerGuard = termStack.back();
    termStack.pop_back();
    lowerBinop.assign(binop);
}

void 
DBInputBuilder::onAggregateUpperGuard()
{
    // It should be on top of the stack.
    assert_msg( termStack.size() > 0, 
            "Trying to create a null choice-right term" );
    upperGuard = termStack.back();
    termStack.pop_back();
    upperBinop.assign(binop);
}
    
void 
DBInputBuilder::onAggregateFunction( 
    char* functionSymbol )
{
    assert_msg( functionSymbol, "Trying to create an aggregate with a null function" );
    aggregateFunction.assign(functionSymbol);
    aggregateLabel << aggregateFunction << "{";
}
    
void 
DBInputBuilder::onAggregateGroundTerm( 
    char* value, 
    bool dash )
{
    newTerm(value,aggregateElementTerms,dash);
}
    
void 
DBInputBuilder::onAggregateVariableTerm( 
    char* value )
{
    newTerm(value,aggregateElementTerms);
}
    
void 
DBInputBuilder::onAggregateUnknownVariable()
{
    aggregateElementTerms.push_back(program->createVariable(string("_")));
}
    
void 
DBInputBuilder::onAggregateNafLiteral()
{
    // The current literal should be pointed 
    // by currentLiteral;
    assert_msg( currentLiteral, "Trying to adding a null literal" );
    aggregateElementLiterals.push_back(currentLiteral);
}

void 
DBInputBuilder::onAggregateElement()
{
    assert_msg( (aggregateElementTerms.size() > 0 
            && aggregateElementLiterals.size() > 0),
            "Invalid aggregate element.");
    DBAggregateElement* element = 
            program->createAggregateElement(aggregateElementTerms,aggregateElementLiterals);
    aggregateElements.push_back(element);
    // Create the aggregate set string that will be used
    // during the creation of the dependency graph.
    if( aggregateLabel.str().at(aggregateLabel.str().length()-1) != '{' )
        aggregateLabel << ";";
    for( unsigned i=0; i<aggregateElementTerms.size(); i++ )
    {
        assert_msg( aggregateElementTerms[i] != NULL, "Null term in an aggregate set." );
        aggregateLabel << *aggregateElementTerms[i];
        if( i < aggregateElementTerms.size()-1 )
            aggregateLabel << ",";
    }
    aggregateLabel << ":";
    for( unsigned i=0; i<aggregateElementLiterals.size(); i++ )
    {
        assert_msg( aggregateElementLiterals[i] != NULL, "Null literal in an aggregate set." );
        aggregateLabel << *aggregateElementLiterals[i];
        
        if( i < aggregateElementLiterals.size()-1 )
            aggregateLabel << ",";
    }
    aggregateElementTerms.clear();
    aggregateElementLiterals.clear();
}
    
void 
DBInputBuilder::onAggregate( 
    bool naf )
{
    assert_msg( aggregateFunction.length() > 0, 
            "Trying to finalize an aggregate with a null function symbol" );
    assert_msg( aggregateElements.size() > 0, 
            "Trying to finalize an aggregate without elements" );
    assert_msg( lowerGuard || upperGuard, 
            "Trying to finalize an aggregate without any guards" );
    
    // Create the name that is going to be added to the depgraph for this aggregate atom.
    aggregateLabel << "}";
    
    currentLiteral = program->createAggregateLiteral(
            lowerGuard,
            lowerBinop,
            upperGuard,
            upperBinop,
            aggregateFunction,
            aggregateElements,
            naf,
            aggregateLabel.str());
    
    // Add an edge from each literal in the aggregate set to the aggregate atom.
    for( unsigned i=0; i<aggregateElements.size(); i++ )
    {
        assert_msg( aggregateElements[i] != NULL, "Null element in an aggregate set." );
        for( unsigned j=0; j<aggregateElements[i]->getLiterals().size(); j++ )
        {
            DBLiteral* l = aggregateElements[i]->getLiterals().at(j);
            assert_msg( l != NULL, "Null literal in an aggregate set." );
            // An aggregate atom cannot be true negated.
            addEdgeToDepGraph(aggregateLabel.str(),l);
        }
    }
    aggregateLabel.clear();
    aggregateElements.clear();
    lowerBinop = "";
    lowerGuard = NULL;
    upperBinop = "";
    upperGuard = NULL;
    aggregateFunction = "";
    hasAggregates = true;
}
    
void 
DBInputBuilder::newTerm( 
    char* value,
    vector<DBTerm*>& target,
    bool dash )
{
    DBTerm* currentTerm = NULL;
    
    if( value[0] >= 'A' && value[0] <='Z' ) // Variable
    {
        currentTerm = program->createVariable(value);
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
    if( currentTerm != NULL )
    {
        target.push_back(currentTerm);
    }
}

void
DBInputBuilder::addEdgeToDepGraph(
    const string& targetLabel, 
    DBLiteral* source )
{
    assert_msg( source != NULL, "Trying to add an edge from a null literal." );
    if( !source->isBuiltin() )
    {
        string sourceLabel;
        if( source->isAggregate() )
            sourceLabel = source->getAggregateName();
        else
        {
            assert_msg( source->getAtom() != NULL, "Trying to add an edge from a null atom." );
            if( source->getAtom()->isTrueNegated() )
                sourceLabel.append("-").append(source->getAtom()->getPredicateName());
            else
                sourceLabel = source->getAtom()->getPredicateName();
        }
        if( source->isNaf() )
            graph->addNegativeEdge(sourceLabel,targetLabel);
        else
            graph->addPositiveEdge(sourceLabel,targetLabel);
    }
}
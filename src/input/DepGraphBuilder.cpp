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

#include "DepGraphBuilder.h"
#include "../directives/DirectiveFactory.h"

namespace DLV2
{

void 
DepGraphBuilder::onDirective( 
    char* directiveName, 
    char* directiveValue )
{
    Directive* dir = DirectiveFactory::createDirective(directiveName,directiveValue);
    std::cout << *dir << std::endl;
    delete dir;
}
        
void DepGraphBuilder::onRule()
{
    // Add an edge from each body literal to each head atom.
    for( unsigned i=0; i<literalStack.size(); i++ )
        for( unsigned j=0; j<atomStack.size(); j++ )
            if( literalStack[i].second )
                graph.addNegativeEdge(literalStack[i].first,atomStack[j]);
            else
                graph.addPositiveEdge(literalStack[i].first,atomStack[j]);
        
    atomStack.clear();
    literalStack.clear();
}
    
void 
DepGraphBuilder::onConstraint()
{
    literalStack.clear();
}
    
void 
DepGraphBuilder::onWeakConstraint()
{
    literalStack.clear();
}
    
void 
DepGraphBuilder::onQuery()
{
}
    
void 
DepGraphBuilder::onHeadAtom()
{
    atomStack.push_back(predName);
}
    
void 
DepGraphBuilder::onHead()
{
    // Add head atoms to the graph in order to keep track of atoms which appear
    // only in heads of rules without body.
    for( unsigned i=0; i<atomStack.size(); i++ )
        graph.addVertex(atomStack[i]);
}
    
void 
DepGraphBuilder::onBodyLiteral()
{
    if( !isBuiltin )
    {
        DepGraphLiteral literal(predName,isNaf);
        literalStack.push_back(literal);
    }
    // Reset to recognize the next literal.
    isNaf = false;
    isBuiltin = false;
}
    
void 
DepGraphBuilder::onBody()
{   
}
    
void 
DepGraphBuilder::onNafLiteral( 
    bool naf )
{
    isNaf = naf;
}
    
void 
DepGraphBuilder::onAtom( 
    bool isStrongNeg )
{
    // Add "-" at the beginning of the predicate name if the atom is strongly negated.
    if( isStrongNeg )
        predName.insert(0,1,'-');
}
    
void 
DepGraphBuilder::onExistentialAtom()
{    
}
    
void 
DepGraphBuilder::onPredicateName( 
    char* name )
{
    assert_msg( name, "Trying to create an atom with a null predicate name" );
    predName.assign(name);
}
        
void 
DepGraphBuilder::onExistentialVariable( 
    char* var )
{   
}
    
void 
DepGraphBuilder::onTerm( 
    char* value )
{   
}
    
void 
DepGraphBuilder::onTerm( 
    int value )
{   
}
    
void 
DepGraphBuilder::onFunction( 
    char* functionSymbol, 
    int nTerms )
{   
}

void 
DepGraphBuilder::onTermDash()
{
}
    
void 
DepGraphBuilder::onTermParams()
{
}

void 
DepGraphBuilder::onTermRange( 
    char* lowerBound, 
    char* upperBound )
{
}

void 
DepGraphBuilder::onArithmeticOperation( char arithOperator )
{
}

void 
DepGraphBuilder::onWeightAtLevels( 
    int nWeight, 
    int nLevel, 
    int nTerms )
{
}
    
void 
DepGraphBuilder::onChoiceLowerGuard( 
    char* binop ) 
{
}

void 
DepGraphBuilder::onChoiceUpperGuard(
    char* binop ) 
{
}

void 
DepGraphBuilder::onChoiceElementAtom()
{
    currentChoiceElementAtom.assign(predName);
}
    
void 
DepGraphBuilder::onChoiceElementLiteral()
{
    if( !isBuiltin )
    {
        DepGraphLiteral literal(predName,isNaf);
        currentChoiceElementLiterals.push_back(literal);
    }
    // Reset to recognize the next literal.
    isNaf = false;
    isBuiltin = false;
}
    
void 
DepGraphBuilder::onChoiceElement()
{
    // Add an edge from each literal to the atom of the current element.
    for( unsigned i=0; i<currentChoiceElementLiterals.size(); i++ )
    {
        if( currentChoiceElementLiterals[i].second )
            graph.addNegativeEdge(currentChoiceElementLiterals[i].first,
                    currentChoiceElementAtom);
        else
            graph.addPositiveEdge(currentChoiceElementLiterals[i].first,
                    currentChoiceElementAtom);
    }
    currentChoiceElementLiterals.clear();
    // Finally, add the atom of the current element to the set of head atoms.
    atomStack.push_back(currentChoiceElementAtom);
}

void 
DepGraphBuilder::onChoiceAtom()
{
}

void 
DepGraphBuilder::onBuiltinAtom( 
    char* binop )
{
    isBuiltin = true;
}

void 
DepGraphBuilder::onAggregateLowerGuard( 
    char* op )
{
}

void 
DepGraphBuilder::onAggregateUpperGuard( 
    char* op )
{
}

void 
DepGraphBuilder::onAggregateFunction( 
    char* f )
{
    assert_msg( f, "Trying to create an aggregate function with a null symbol" );
    aggregateFunction.assign(f);
}

void 
DepGraphBuilder::onAggregateGroundTerm( 
    char* value, 
    bool dash )
{
    assert_msg( value, "Trying to create an aggregate function with a null ground term" );
    std::string term(value);
    if( dash )
        term.insert(0,1,'-');
    currentAggregateElementTerms.push_back(term);
}
    
void 
DepGraphBuilder::onAggregateVariableTerm( 
    char* value )
{
    assert_msg( value, "Trying to create an aggregate function with a null variable term" );
    currentAggregateElementTerms.push_back(std::string(value));
}

void 
DepGraphBuilder::onAggregateNafLiteral()
{
    if( !isBuiltin )
    {
        DepGraphLiteral literal(predName,isNaf);
        aggregateLiteralStack.push_back(literal);
    }
    // Reset to recognize the next literal.
    isNaf = false;
    isBuiltin = false;
}

void 
DepGraphBuilder::onAggregateElement()
{
    std::string aggregateElement;
    for( unsigned i=0; i<currentAggregateElementTerms.size(); i++ )
    {
        aggregateElement.append(currentAggregateElementTerms[i]);
        if( i < currentAggregateElementTerms.size()-1 )
            aggregateElement.append(",");
    }
    aggregateElement.append(":");
    for( unsigned i=aggregateLiteralPlaceholder; i<aggregateLiteralStack.size(); i++ )
    {
        if( aggregateLiteralStack[i].second )
            aggregateElement.append("not ");
        aggregateElement.append(aggregateLiteralStack[i].first);
        
        if( i < aggregateLiteralStack.size()-1 )
            aggregateElement.append(",");
    }
    // Push the aggregate element into the aggregate set.
    if( aggregateSet.empty() )
        // It's the firt element in the set.
        aggregateSet.append("{");
    else
        aggregateSet.append(";");
    aggregateSet.append(aggregateElement);
    
    currentAggregateElementTerms.clear();
    // Literals of the next element will be pushed into the stack 
    // without removing literals of the previous element. Thus, mark the 
    // current size of the stack as the position of the first literal of the 
    // next element.
    aggregateLiteralPlaceholder = aggregateLiteralStack.size();
}

void 
DepGraphBuilder::onAggregate(
    bool naf )
{
    aggregateSet.append("}");
    // Create the name that is going to be added to the graph for that aggregate atom.
    predName.clear();
    predName.append(aggregateFunction);
    predName.append(aggregateSet);
    aggregateFunction.clear();
    aggregateSet.clear();
    aggregateLiteralPlaceholder = 0;
    // Add an edge from each literal in the aggregate set to the aggregate atom.
    for( unsigned i=0; i<aggregateLiteralStack.size(); i++ )
    {
        if( aggregateLiteralStack[i].second )
            graph.addNegativeEdge(aggregateLiteralStack[i].first,predName);
        else
            graph.addPositiveEdge(aggregateLiteralStack[i].first,predName);
    }
    aggregateLiteralStack.clear();
    // After this function it will be called onBodyLiteral, where 
    // that aggregate atom will be added to body literals' stack.
    isNaf = naf;
}

};
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

#include "DependencyGraph.h"
#include "../util/Assert.h"
#include "Graph.h"

#include <cstring>

namespace DLV2
{

DependencyGraph::DependencyGraph():
    graph( new Graph() )
{
}

DependencyGraph::~DependencyGraph() 
{
    delete graph;
}

void
DependencyGraph::addEdge(
    const char* p1,
    const char* p2,
    unsigned label )
{
    assert_msg( strcmp(p1,p2) != 0, "Adding a noose to the depgraph." );
    // Retrieve the vertex_descriptors.
    unsigned v1 = addVertex(p1);
    unsigned v2 = addVertex(p2);
    if( !graph->isEdge(v1,v2,label) )
        graph->addEdge(v1,v2,label);
}

void
DependencyGraph::computeStronglyConnectedComponents()
{
    graph->computeStronglyConnectedComponents();
}

bool 
DependencyGraph::isHCF(
    unsigned componentIdx)
{
    return graph->isHCF(componentIdx);
}

bool
DependencyGraph::isHCF()
{
    return graph->isHCF();
}

bool 
DependencyGraph::isStratified(
    unsigned componentIdx)
{
    return graph->isStratified(componentIdx);
}

bool
DependencyGraph::isStratified()
{
    return graph->isStratified();
}

bool
DependencyGraph::isCyclic(
    unsigned componentIdx)
{
    return graph->isCyclic(componentIdx);
}

bool
DependencyGraph::isCyclic()
{
    return graph->isCyclic();
}

bool
DependencyGraph::isTight()
{
    return graph->isTight();
}

unsigned
DependencyGraph::addVertex(
    const char* p )
{
    std::unordered_map<const char*, unsigned>::const_iterator it = predsMap.find(p);
    if( it == predsMap.end() )
    {
        unsigned descriptor = graph->addVertex();
        predsMap.insert({p,descriptor});        
        return descriptor;
    }
    else 
        return it->second;
}

};

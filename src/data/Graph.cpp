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

#include "Graph.h"
#include "../util/Assert.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace boost;

namespace DLV2 
{

typedef property<edge_name_t, unsigned> EdgeProperty;
    
class DirectedGraph: public adjacency_list<vecS,vecS,directedS,no_property,EdgeProperty> 
{
};

typedef DirectedGraph::vertex_descriptor Vertex;
typedef DirectedGraph::edge_descriptor Edge;

Graph::Graph():
    graph( *new DirectedGraph() ),
    numberOfStronglyConnectedComponents(0)
{
    
}

Graph::~Graph()
{
    graph.clear();
    assert_msg( graph.vertex_set().empty(), "The depgraph is not empty." );
    delete &graph;
}
    
unsigned 
Graph::addVertex() 
{
    return add_vertex(graph);
}

void 
Graph::addEdge( 
    unsigned v1,
    unsigned v2,
    unsigned label )
{
    assert_msg( v1 != v2, "Adding a noose to the depgraph." );
    add_edge(v1,v2,label,graph);
}

bool 
Graph::isEdge(
    unsigned v1, 
    unsigned v2, 
    unsigned label )
{
    std::pair<Edge,bool> alreadyExists = edge(v1,v2,graph);
    if( alreadyExists.second )
    {
        unsigned lab = get(edge_name,graph,alreadyExists.first);
        return label == lab;
    }
    else 
        return false;
}

void
Graph::computeStronglyConnectedComponents()
{
    assert_msg( stronglyConnectedComponents.size() == 0, 
            "Strongly connected components have been already computed." );
    
    stronglyConnectedComponents.reserve( num_vertices( graph ) );
    std::vector< unsigned int > discover_time( num_vertices( graph ) );
    std::vector< default_color_type > color( num_vertices( graph ) );
    std::vector< Vertex > root( num_vertices( graph ) );
    numberOfStronglyConnectedComponents = strong_components( graph, 
        &stronglyConnectedComponents[ 0 ], 
        root_map( &root[ 0 ] ).
        color_map( &color[ 0 ] ).
        discover_time_map( &discover_time[ 0 ] ) );
    
    assert_msg( numberOfStronglyConnectedComponents > 0, 
            "No strongly connected components in the depgraph." );
}

bool
Graph::isHCF(
    unsigned componentIdx )
{
    // TODO
    return true;
}

bool
Graph::isHCF()
{
    // TODO
    return true;
}

bool 
Graph::isStratified(
    unsigned componentIdx )
{
    // TODO
    return true;
}

bool 
Graph::isStratified()
{
    // TODO
    return true;
}

bool 
Graph::isCyclic(
    unsigned componentIdx )
{
    assert_msg( numberOfStronglyConnectedComponents > 0, 
            "Strongly connencted components have not been computed." );
    assert_msg( componentIdx < numberOfStronglyConnectedComponents, 
            "The component id is out of range." );
    
    unsigned nVerticesInComponent = 0;
    for( unsigned i=0; i<stronglyConnectedComponents.size(); i++ )
        if( stronglyConnectedComponents[i] == componentIdx )
            nVerticesInComponent++;
    return nVerticesInComponent > 1;
}

bool 
Graph::isCyclic()
{
    assert_msg( numberOfStronglyConnectedComponents > 0, 
            "Strongly connencted components have not been computed." );
    
    for( unsigned i=0; i<numberOfStronglyConnectedComponents; i++ )
        if( isCyclic(i) )
            return true;
    return false;
}
    
bool 
Graph::isTight()
{
    // TODO
    return true;
}

};

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
 * File:   Graph.h
 * Author: cesco
 *
 * Created on 6 maggio 2014, 18.14
 */

#ifndef DEPENDENCYGRAPH_H
#define	DEPENDENCYGRAPH_H

#include "DepGraphNoStrategy.h"
#include "../util/Constants.h"

#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

namespace DLV2
{
    typedef boost::property< boost::edge_name_t, unsigned > EdgeProperty;
    
    class DirectedGraph: public boost::adjacency_list<
            boost::vecS,
            boost::vecS,
            boost::directedS,
            boost::no_property,
            EdgeProperty >
    {
    };

    typedef DirectedGraph::vertex_descriptor Vertex;
    typedef DirectedGraph::edge_descriptor Edge;
    typedef DirectedGraph::vertex_iterator VertexIterator;
    typedef DirectedGraph::edge_iterator EdgeIterator;
    typedef DirectedGraph::out_edge_iterator OutEdgeIterator;
    
    typedef std::vector< unsigned > Component;
    typedef std::vector< Component > Components;
        
    template< typename ControlStrategy = DepGraphNoStrategy >
    class DependencyGraph {
    public:
        DependencyGraph();
        DependencyGraph( const DependencyGraph& dg );
        ~DependencyGraph();
        
        unsigned addVertex();
        void addEdge( unsigned src, unsigned dest, unsigned label = POSITIVE_EDGE );
        bool isEdge( unsigned src, unsigned dest, unsigned label = POSITIVE_EDGE ) const;
        bool isAnyEdge( unsigned src, unsigned dest ) const;
        unsigned numOfVertices() const { return boost::num_vertices(graph); }
        void computeStronglyConnectedComponents();
        unsigned getAtomComponent( unsigned vertexIdx ) const;
        const Component& getComponent( unsigned componentIdx ) const;
        const Components& getComponentList() const;
        unsigned numberOfComponents() const;
        
        void addDisjunctiveHead( std::vector< unsigned > head );
        
        bool isHCF( unsigned componentIdx ) const;
        bool isHCF() const;
        bool isStratified( unsigned componentIdx );
        bool isStratified();
        bool isCyclic( unsigned componentIdx ) const;
        bool isCyclic() const;
        bool isTight() const;
        
    private:        
        void computeLabeledEdges();
           
        ControlStrategy controller;
        DirectedGraph& graph;
        // It represents vertices by components
        Components stronglyConnectedComponents;
        // It represents components by vertices
        std::vector< unsigned int > vertexComponents;
        // It represents negated edges in components
        std::vector< bool > componentHasNegations;
        // It represents disjunctive heads
        std::vector< Component > disjunctiveHeads;
        
        template < typename T > 
        friend inline std::ostream& operator<<( std::ostream&, DependencyGraph< T >& );
        
    };
    
    template < typename ControlStrategy >
    std::ostream&
    operator<<( 
        std::ostream& out,
        DependencyGraph< ControlStrategy >& g )
    {
        out << "DEPGRAPH: (" << g.numOfVertices() << " atoms, " 
            << g.numberOfComponents() << " components)"
            << ((g.isCyclic()) ? " cyclic" : " acyclic")
            << ((g.isHCF()) ? " hcf" : " not_hcf")
            << ((g.isStratified()) ? " stratified" : " not_stratified")
            << ((g.isTight()) ? " tight" : " not_tight")
            << std::endl << std::endl;
        // Print the adjacency list.
        VertexIterator vi, viEnd;
        for (boost::tie(vi, viEnd) = boost::vertices(g.graph); vi != viEnd; ++vi)
        {
            out << *vi << " -->";
            OutEdgeIterator ei, eiEnd;
            for (boost::tie(ei, eiEnd) = boost::out_edges(*vi,g.graph); ei != eiEnd; ++ei)
            {
                Vertex target = boost::target(*ei, g.graph);
                out << " " << target;
            }
            out << std::endl;
        }
        out << std::endl << std::endl;
        
        for( unsigned i=0; i<g.getComponentList().size(); i++ )
        {
            out << "COMPONENT " << i << ":"
                << (g.isCyclic(i) ? " cyclic" : " acyclic")
                << (g.isHCF(i) ? " hcf" : " not_hcf")
                << (g.isStratified(i) ? " stratified" : " not_stratified")      
                << std::endl << "{";
            for( unsigned j=0; j<g.getComponent(i).size(); j++ )
                out << " " << g.getComponent(i)[j];
                
            out << " }" << std::endl;
        }
        
        return out;
    }
};
    
template < typename ControlStrategy >
DLV2::DependencyGraph< ControlStrategy >::DependencyGraph():
        graph( *new DirectedGraph() )
{
}

template < typename ControlStrategy >
DLV2::DependencyGraph< ControlStrategy >::DependencyGraph(
    const DLV2::DependencyGraph< ControlStrategy >& dg ):
        controller(dg.controller),
        graph( *new DirectedGraph(dg.graph) ),
        stronglyConnectedComponents(dg.stronglyConnectedComponents),
        vertexComponents(dg.vertexComponents),
        componentHasNegations(dg.componentHasNegations),
        disjunctiveHeads(dg.disjunctiveHeads)
{
    
}

template < typename ControlStrategy >
DLV2::DependencyGraph< ControlStrategy >::~DependencyGraph()
{
    graph.clear();
    assert_msg( graph.vertex_set().empty(), "The depgraph is not empty." );
    delete &graph;
}

template < typename ControlStrategy >
unsigned 
DLV2::DependencyGraph< ControlStrategy >::addVertex() 
{
    return boost::add_vertex(graph);
}

template < typename ControlStrategy >
void 
DLV2::DependencyGraph< ControlStrategy >::addEdge( 
    unsigned v1,
    unsigned v2,
    unsigned label )
{
    //assert_msg( v1 != v2, "Adding a noose to the depgraph." );
    assert_msg( (label >= POSITIVE_EDGE && label <= NEGATIVE_EDGE), 
            "Not a valid label for the new edge." );
    controller.edge(label);

    boost::add_edge(v1,v2,label,graph);
}

template < typename ControlStrategy >
bool 
DLV2::DependencyGraph< ControlStrategy >::isEdge(
    unsigned v1, 
    unsigned v2, 
    unsigned label ) const
{
    assert_msg( (label >= POSITIVE_EDGE && label <= NEGATIVE_EDGE), 
            "Not a valid label for the edge in input." );
    controller.edge(label);

    std::pair< Edge, bool > alreadyExists = boost::edge(v1,v2,graph);
    if( alreadyExists.second )
    {
        unsigned lab = boost::get(boost::edge_name,graph,alreadyExists.first);
        return label == lab;
    }
    else 
        return false;
}

template < typename ControlStrategy >
bool 
DLV2::DependencyGraph< ControlStrategy >::isAnyEdge(
    unsigned v1, 
    unsigned v2 ) const
{
    std::pair< Edge, bool > alreadyExists = boost::edge(v1,v2,graph);
    return alreadyExists.second;
}

template < typename ControlStrategy >
void
DLV2::DependencyGraph< ControlStrategy >::computeStronglyConnectedComponents()
{
    assert_msg( stronglyConnectedComponents.size() == 0, 
            "Strongly connected components have been already computed." );

    vertexComponents.resize( boost::num_vertices( graph ) );
    std::vector< unsigned int > discoverTime( boost::num_vertices( graph ) );
    std::vector< boost::default_color_type > color( boost::num_vertices( graph ) );
    std::vector< Vertex > root( boost::num_vertices( graph ) );
    unsigned numberOfStronglyConnectedComponents = boost::strong_components( graph, 
        &vertexComponents[ 0 ], 
        boost::root_map( &root[ 0 ] ).
        color_map( &color[ 0 ] ).
        discover_time_map( &discoverTime[ 0 ] ) );

    assert_msg( numberOfStronglyConnectedComponents > 0, 
            "No strongly connected components in the depgraph." );

    stronglyConnectedComponents.resize( numberOfStronglyConnectedComponents );
    for( std::vector< int >::size_type i = 0; i != vertexComponents.size(); ++i )
    {
        unsigned currentComponentId = vertexComponents[ i ];
        assert_msg( currentComponentId < stronglyConnectedComponents.size(),
                "The current component id is out of range." );
        stronglyConnectedComponents[ currentComponentId ].push_back( i );
    }

}

template < typename ControlStrategy >
unsigned
DLV2::DependencyGraph< ControlStrategy >::getAtomComponent(
    unsigned vertexId ) const
{
    assert_msg( vertexComponents.size() > 0, 
            "Strongly connected components have not been computed." );
    assert_msg( vertexId < vertexComponents.size(), 
            "The component id is out of range." );

    return vertexComponents[vertexId];
}

template < typename ControlStrategy >
const DLV2::Component&
DLV2::DependencyGraph< ControlStrategy >::getComponent(
    unsigned componentIdx ) const
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connected components have not been computed." );
    assert_msg( componentIdx < stronglyConnectedComponents.size(), 
            "The component id is out of range." );

    return stronglyConnectedComponents[componentIdx];
}

template < typename ControlStrategy >
const DLV2::Components&
DLV2::DependencyGraph< ControlStrategy >::getComponentList() const
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connected components have not been computed." );

    return stronglyConnectedComponents;
}

template < typename ControlStrategy >
unsigned
DLV2::DependencyGraph< ControlStrategy >::numberOfComponents() const
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connected components have not been computed." );

    return stronglyConnectedComponents.size();
}

template < typename ControlStrategy >
void
DLV2::DependencyGraph< ControlStrategy >::addDisjunctiveHead(
    std::vector< unsigned > head )
{
    assert_msg( head.size() > 0, "The head is empty." );
    disjunctiveHeads.push_back(head); 
}

template < typename ControlStrategy >
bool
DLV2::DependencyGraph< ControlStrategy >::isHCF(
    unsigned componentIdx ) const
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connected components have not been computed." );
    assert_msg( componentIdx < stronglyConnectedComponents.size(), 
            "The component id is out of range." );

    if( !isCyclic(componentIdx) )
        return true;

    for( unsigned i=0; i<disjunctiveHeads.size(); i++ )
        for( unsigned j=0; j<disjunctiveHeads[i].size(); j++ )
            for( unsigned k=j+1; k<disjunctiveHeads[i].size(); k++ )
            {
                unsigned v1 = disjunctiveHeads[i][j];
                unsigned v2 = disjunctiveHeads[i][k];
                assert_msg( (v1 < vertexComponents.size() && 
                        v2<vertexComponents.size()),
                        "Vertex id out of range" );
                if( vertexComponents[v1] == vertexComponents[v2] &&
                        vertexComponents[v1] == componentIdx )
                    return false;
            }
    return true;
}

template < typename ControlStrategy >
bool
DLV2::DependencyGraph< ControlStrategy >::isHCF() const
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connected components have not been computed." );

    if( !isCyclic() )
        return true; 

    for( unsigned i=0; i<disjunctiveHeads.size(); i++ )
        for( unsigned j=0; j<disjunctiveHeads[i].size(); j++ )
            for( unsigned k=j+1; k<disjunctiveHeads[i].size(); k++ )
            {
                unsigned v1 = disjunctiveHeads[i][j];
                unsigned v2 = disjunctiveHeads[i][k];
                assert_msg( (v1 < vertexComponents.size() && 
                        v2<vertexComponents.size()),
                        "Vertex id out of range" );
                if( vertexComponents[v1] == vertexComponents[v2] )
                    return false;
            }
    return true;
}

template < typename ControlStrategy >
bool 
DLV2::DependencyGraph< ControlStrategy >::isStratified(
    unsigned componentIdx )
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connected components have not been computed." );
    assert_msg( componentIdx < stronglyConnectedComponents.size(), 
            "The component id is out of range." );

    if( controller.isPositive() )
        return true;

    if( componentHasNegations.size() == 0 )
    {
        computeLabeledEdges(); 
    }
    return !componentHasNegations[componentIdx];
}

template < typename ControlStrategy >
bool 
DLV2::DependencyGraph< ControlStrategy >::isStratified()
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connencted components have not been computed." );

    if( controller.isPositive() )
        return true;

    for( unsigned i=0; i<stronglyConnectedComponents.size(); i++ )
        if( !isStratified(i) )
            return false;
    return true;
}

template < typename ControlStrategy >
bool 
DLV2::DependencyGraph< ControlStrategy >::isCyclic(
    unsigned componentIdx ) const
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connencted components have not been computed." );
    assert_msg( componentIdx < stronglyConnectedComponents.size(), 
            "The component id is out of range." );

    return ( stronglyConnectedComponents[componentIdx].size() > 1 ||
               ( stronglyConnectedComponents[componentIdx].size() == 1 &&
                isAnyEdge(stronglyConnectedComponents[componentIdx][0],
                    stronglyConnectedComponents[componentIdx][0]) ) );
}

template < typename ControlStrategy >
bool 
DLV2::DependencyGraph< ControlStrategy >::isCyclic() const
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connencted components have not been computed." );

    for( unsigned i=0; i<stronglyConnectedComponents.size(); i++ )
        if( isCyclic(i) )
            return true;
    return false;
}

template < typename ControlStrategy >
bool 
DLV2::DependencyGraph< ControlStrategy >::isTight() const
{
    return !isCyclic();
}

template < typename ControlStrategy >
void
DLV2::DependencyGraph< ControlStrategy >::computeLabeledEdges()
{
    assert_msg( stronglyConnectedComponents.size() > 0, 
            "Strongly connencted components have not been computed." );

    componentHasNegations.resize(stronglyConnectedComponents.size());
    for( unsigned i = 0; i<stronglyConnectedComponents.size(); i++ )
        componentHasNegations[i] = false;

    // Scan for negated edges
    // if components of the connected nodes are equal, not stratified
    EdgeIterator i, iEnd;
    for( tie(i,iEnd) = boost::edges(graph); i != iEnd; ++i )
    {
        unsigned label = boost::get(boost::edge_name,graph,*i);
        if( label == NEGATIVE_EDGE )
        {
            Vertex src = source(*i,graph);
            Vertex trgt = target(*i,graph);
            assert_msg( (src < vertexComponents.size() &&  
                    trgt < vertexComponents.size()),
                    "Vertex id out of range" );
            if( vertexComponents[src] == vertexComponents[trgt] )
                componentHasNegations[vertexComponents[src]] = true;
        }
    }
}



#endif	/* DEPENDENCYGRAPH_H */


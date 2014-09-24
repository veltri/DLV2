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
 * File:   DependencyGraph.h
 * Author: cesco
 *
 * Created on 28 aprile 2014, 17.37
 */

#ifndef LABELEDDEPENDENCYGRAPH_H
#define LABELEDDEPENDENCYGRAPH_H

#include "DependencyGraph.h"
#include <unordered_map>

namespace DLV2
{    
    template < typename ControlStrategy = DepGraphNoStrategy, 
               typename Label = std::string >
    class LabeledDependencyGraph {
    public:
        LabeledDependencyGraph() {}
        LabeledDependencyGraph( const LabeledDependencyGraph< ControlStrategy, Label >& ldg );
        ~LabeledDependencyGraph() {}
        
        unsigned addVertex( Label name );
        void addPositiveEdge( Label src, Label dest ) { addEdge(src,dest,POSITIVE_EDGE); }
        void addNegativeEdge( Label src, Label dest ) { addEdge(src,dest,NEGATIVE_EDGE); }
        bool isPositiveEdge( Label src, Label dest ) const { return isEdge(src,dest,POSITIVE_EDGE); }
        bool isNegativeEdge( Label src, Label dest ) const { return isEdge(src,dest,NEGATIVE_EDGE); }
        bool isAnyEdge( Label src, Label dest ) const;
        unsigned numOfVertices() const { return graph.numOfVertices(); }
        void computeStronglyConnectedComponents() { graph.computeStronglyConnectedComponents(); }
        unsigned getAtomComponent( Label name ) const;
        const Component& getComponent( unsigned id ) const { return graph.getComponent(id); }
        const Components& getComponentList() const { return graph.getComponentList(); }
        unsigned numberOfComponents() const { return graph.numberOfComponents(); }
        
        void addDisjunctiveHead( std::vector< Label > head );
        void addDisjunctiveHead( std::vector< unsigned > head );

        unsigned getVertexDescriptor( Label label );
        const Label& getLabelOfVertex( unsigned vertexDescriptor );
        
        // Returns true iff the component with the index componentidx is 
        // head-cycle free (HCF). A component is HCF if it contains no 
        // disjunctions or if it is acyclic.        
        bool isHCF( unsigned componentIdx ) const { return graph.isHCF(componentIdx); }
        // Returns true iff the program is HCF.
        // A program is HCF if all of its components are HCF.
        bool isHCF() const { return graph.isHCF(); }
        // Returns true iff the component with the index componentidx is stratified.
        bool isStratified( unsigned componentIdx ) { return graph.isStratified(componentIdx); }
        // Returns true iff the program is stratified.
        // A program is stratified if all of its components are stratified.
        bool isStratified() { return graph.isStratified(); }
        // Returns true iff the component with the index componentidx is cyclic.
        // A component is cyclic iff it contains more than one atom or it is recursive.
        bool isCyclic( unsigned componentIdx ) const { return graph.isCyclic(componentIdx); }
        // Returns true iff the program is cyclic.
        // A program is cyclic iff at least one of its components is cyclic.
        bool isCyclic() const { return graph.isCyclic(); }
        // Return true iff the program is tight.
        // A program is tight iff its dependency graph has no cyclic components.
        bool isTight() const { return graph.isTight(); }
        
    private:      
        // Adds an edge from p1 to p2. Notice that, p1 and p2 are labels,
        // so their vertex_descriptors have to be first retrieved 
        // through 'addVertex'. 
        void addEdge( Label p1, Label p2, unsigned edgeLabel = POSITIVE_EDGE );
        bool isEdge( Label p1, Label p2, unsigned edgeLabel = POSITIVE_EDGE ) const;
        
        DependencyGraph< ControlStrategy > graph;
        // Maps each predicate name to its vertex_descriptor in the graph.
        std::unordered_map< Label, unsigned > predsMap;
        // Maps each vertex_descriptor to its record in the previous map.
        std::unordered_map<
            unsigned, 
            typename std::unordered_map< Label, unsigned >::const_iterator > vertexToLabel;
        
        template< typename T, typename L >
        friend inline std::ostream& operator<<( std::ostream&, 
                LabeledDependencyGraph< T, L >& );
    };

    template < typename ControlStrategy,
               typename Label >
    std::ostream&
    operator<<( 
        std::ostream& out,
        LabeledDependencyGraph< ControlStrategy, Label >& labGraph )
    {
        out << labGraph.graph << std::endl << std::endl;
        
        // Print the vertex set.
        out << "Predicate names map:" << std::endl;
        for( typename std::unordered_map< Label, unsigned >::const_iterator it = labGraph.predsMap.begin();
             it != labGraph.predsMap.end(); 
             it++ )
            // For each vertex descriptor, print the corresponding predicate name.
            out << it->second << ": " << it->first << std::endl;

        out << std::endl;
        
        return out;
    }
};

template < typename ControlStrategy,
           typename Label >
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::LabeledDependencyGraph( 
    const LabeledDependencyGraph< ControlStrategy, Label >& ldg ):
        graph(ldg.graph),
        predsMap(ldg.predsMap)
{
    for( typename std::unordered_map< Label, unsigned >::const_iterator it = predsMap.begin();
            it != predsMap.end(); 
            it++ )
    {
        vertexToLabel[it->first] = it;
    }
}

template < typename ControlStrategy,
           typename Label >
unsigned
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::addVertex(
    Label p )
{
    typename std::unordered_map< Label, unsigned >::const_iterator it = predsMap.find(p);
    if( it == predsMap.end() )
    {
        unsigned descriptor = graph.addVertex();
        std::pair< Label, unsigned > element(p,descriptor);
        std::pair< typename std::unordered_map< Label, unsigned >::const_iterator, bool > ins =
            predsMap.insert(element);
        vertexToLabel[descriptor] = ins.first;
        return descriptor;
    }
    else 
        return it->second;
}

template < typename ControlStrategy,
           typename Label >
unsigned
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::getAtomComponent(
    Label p ) const
{
    typename std::unordered_map< Label, unsigned >::const_iterator it = predsMap.find(p);
    assert_msg( it != predsMap.end(), "Unknown predicate name." );
    return graph.getAtomComponent(it->second);
}

template < typename ControlStrategy,
           typename Label >
void 
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::addDisjunctiveHead( 
    std::vector< Label > head )
{
    assert_msg( head.size() > 0, "The head is empty." );    

    std::vector< unsigned > unsignedHead;
    for( unsigned i=0; i<head.size(); i++ )
    {
        typename std::unordered_map< Label, unsigned >::const_iterator it = predsMap.find(head[i]);
        assert_msg( it != predsMap.end(), "Unknown predicate name." );
        unsignedHead.push_back(it->second);
    }
    graph.addDisjunctiveHead(unsignedHead);
}

template < typename ControlStrategy,
           typename Label >
void 
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::addDisjunctiveHead( 
    std::vector< unsigned > head )
{
    assert_msg( head.size() > 0, "The head is empty." );    
    graph.addDisjunctiveHead(head);
}

template < typename ControlStrategy,
           typename Label >
unsigned
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::getVertexDescriptor( 
    Label label )
{
    typename std::unordered_map< Label, unsigned >::const_iterator it = predsMap.find(label);
    assert_msg( it != predsMap.end(), "Label not valid" );
    return it->second;
}
template < typename ControlStrategy,
           typename Label >
const Label&
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::getLabelOfVertex( 
    unsigned descriptor )
{
    typename std::unordered_map< 
        unsigned,
        typename std::unordered_map< Label, unsigned >::const_iterator 
        >::const_iterator it = vertexToLabel.find(descriptor);
    assert_msg( it != vertexToLabel.end(), "Not valid vertex descriptor" );    
    return it->second->first;
}

template < typename ControlStrategy,
           typename Label >
void
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::addEdge(
    Label src,
    Label dest,
    unsigned label )
{
    //assert_msg( strcmp(p1,p2) != 0, "Adding a noose to the depgraph." );
    // Retrieve the vertex descriptors.
    unsigned v1 = addVertex(src);
    unsigned v2 = addVertex(dest);
    if( !graph.isEdge(v1,v2,label) )
        graph.addEdge(v1,v2,label);
}

template < typename ControlStrategy,
           typename Label >
bool 
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::isEdge( 
    Label src, 
    Label dest, 
    unsigned edgeLabel ) const
{
    // Retrieve the vertex descriptors.
    unsigned v1 = addVertex(src);
    unsigned v2 = addVertex(dest);
    return graph.isEdge(v1,v2,edgeLabel);
}

template < typename ControlStrategy,
           typename Label >
bool 
DLV2::LabeledDependencyGraph< ControlStrategy, Label >::isAnyEdge( 
    Label src, 
    Label dest ) const
{
    // Retrieve the vertex descriptors.
    unsigned v1 = addVertex(src);
    unsigned v2 = addVertex(dest);
    return graph.isAnyEdge(v1,v2);
}

#endif	/* LABELEDDEPENDENCYGRAPH_H */



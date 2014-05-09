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

    template<typename ControlStrategy>
    class DependencyGraph;
    
    template< typename ControlStrategy = DepGraphNoStrategy >
    class LabeledDependencyGraph {
    public:
        LabeledDependencyGraph() {}
        ~LabeledDependencyGraph() {}
        
        unsigned addVertex( const char* );
        void addPositiveEdge( const char* p1, const char* p2 ) { addEdge(p1,p2,POSITIVE_EDGE); }
        void addNegativeEdge( const char* p1, const char* p2 ) { addEdge(p1,p2,NEGATIVE_EDGE); }
        bool isPositiveEdge( const char* p1, const char* p2 ) { return isEdge(p1,p2,POSITIVE_EDGE); }
        bool isNegativeEdge( const char* p1, const char* p2 ) { return isEdge(p1,p2,NEGATIVE_EDGE); }
        void computeStronglyConnectedComponents();
        unsigned getAtomComponent( const char* );
        const Component& getComponent( unsigned id ) { return graph.getComponent(id); }
        const Components& getComponentList() { return graph.getComponentList(); }
        unsigned numberOfComponents() { return graph.numberOfComponents(); }
        
        void addDisjunctiveHead( std::vector<const char*> );

        // Returns true iff the component with the index componentidx is 
        // head-cycle free (HCF). A component is HCF if it contains no 
        // disjunctions or if it is acyclic.        
        bool isHCF(unsigned componentIdx) { return graph.isHCF(componentIdx); }
        // Returns true iff the program is HCF.
        // A program is HCF if all of its components are HCF.
        bool isHCF() { return graph.isHCF(); }
        // Returns true iff the component with the index componentidx is stratified.
        bool isStratified(unsigned componentIdx) { return graph.isStratified(componentIdx); }
        // Returns true iff the program is stratified.
        // A program is stratified if all of its components are stratified.
        bool isStratified() { return graph.isStratified(); }
        // Returns true iff the component with the index componentidx is cyclic.
        // A component is cyclic iff it contains more than one atom or it is recursive.
        bool isCyclic(unsigned componentIdx) { return graph.isCyclic(componentIdx); }
        // Returns true iff the program is cyclic.
        // A program is cyclic iff at least one of its components is cyclic.
        bool isCyclic() { return graph.isCyclic(); }
        // Return true iff the program is tight.
        // A program is tight iff its dependency graph has no cyclic components.
        bool isTight() { return graph.isTight(); }
        
    private:      
        // Adds an edge from p1 to p2. Notice that, p1 and p2 are strings,
        // so their vertex_descriptors have to be first retrieved 
        // through 'addVertex'. 
        void addEdge( const char*, const char*, unsigned label = POSITIVE_EDGE );
        bool isEdge( const char*, const char*, unsigned label = POSITIVE_EDGE );
        
        DependencyGraph<ControlStrategy> graph;
        // Maps each predicate name to its vertex_descriptor in the graph.
        std::unordered_map<const char*, unsigned> predsMap;
    };
    
    template<typename ControlStrategy>
    unsigned
    LabeledDependencyGraph<ControlStrategy>::addVertex(
        const char* p )
    {
        std::unordered_map<const char*, unsigned>::const_iterator it = predsMap.find(p);
        if( it == predsMap.end() )
        {
            unsigned descriptor = graph.addVertex();
            predsMap[p] = descriptor;
            return descriptor;
        }
        else 
            return it->second;
    }

    template<typename ControlStrategy>
    void
    LabeledDependencyGraph<ControlStrategy>::addEdge(
        const char* p1,
        const char* p2,
        unsigned label )
    {
        //assert_msg( strcmp(p1,p2) != 0, "Adding a noose to the depgraph." );
        // Retrieve the vertex_descriptors.
        unsigned v1 = addVertex(p1);
        unsigned v2 = addVertex(p2);
        if( !graph.isEdge(v1,v2,label) )
            graph.addEdge(v1,v2,label);
    }

    template<typename ControlStrategy>
    void
    LabeledDependencyGraph<ControlStrategy>::computeStronglyConnectedComponents()
    {
        graph.computeStronglyConnectedComponents();
    }

    template<typename ControlStrategy>
    unsigned
    LabeledDependencyGraph<ControlStrategy>::getAtomComponent(
        const char* p )
    {
        std::unordered_map<const char*, unsigned>::const_iterator it = predsMap.find(p);
        assert_msg( it != predsMap.end(), "Unknown predicate name." );
        return graph.getAtomComponent(it->second);
    }

    template<typename ControlStrategy>
    void 
    LabeledDependencyGraph<ControlStrategy>::addDisjunctiveHead( 
        std::vector<const char*> head )
    {
        assert_msg( head.size() > 0, "The head is empty." );    

        std::vector<unsigned> unsignedHead;
        for( unsigned i=0; i<head.size(); i++ )
        {
            std::unordered_map<const char*, unsigned>::const_iterator it = predsMap.find(head[i]);
            assert_msg( it != predsMap.end(), "Unknown predicate name." );
            unsignedHead.push_back(it->second);
        }
        graph.addDisjunctiveHead(unsignedHead);
    }

};

#endif	/* LABELEDDEPENDENCYGRAPH_H */



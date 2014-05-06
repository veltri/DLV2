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

#ifndef DEPENDENCYGRAPH_H
#define	DEPENDENCYGRAPH_H
        
#include <unordered_map>

namespace DLV2
{

    class Graph;
    
    class DependencyGraph {
    public:
        DependencyGraph();
        ~DependencyGraph();
        
        unsigned addVertex( const char* );
        void addPositiveEdge( const char* p1, const char* p2 ) { addEdge(p1,p2,0); }
        void addNegativeEdge( const char* p1, const char* p2 ) { addEdge(p1,p2,1); }
        void computeStronglyConnectedComponents();

        // Returns true iff the component with the index componentidx is 
        // head-cycle free (HCF). A component is HCF if it contains no 
        // disjunctions or if it is acyclic.        
        bool isHCF(unsigned componentIdx);
        // Returns true iff the program is HCF.
        // A program is HCF if all of its components are HCF.
        bool isHCF();
        // Returns true iff the component with the index componentidx is stratified.
        bool isStratified(unsigned componentIdx);
        // Returns true iff the program is stratified.
        // A program is stratified if all of its components are stratified.
        bool isStratified();
        // Returns true iff the component with the index componentidx is cyclic.
        // A component is cyclic iff it contains more than one atom or it is recursive.
        bool isCyclic(unsigned componentIdx);
        // Returns true iff the program is cyclic.
        // A program is cyclic iff at least one of its components is cyclic.
        bool isCyclic();
        // Return true iff the program is tight.
        // A program is tight iff its dependency graph has no cyclic components.
        bool isTight();
        
    private:      
        // Adds an edge from p1 to p2. Notice that, p1 and p2 are strings,
        // so their vertex_descriptors have to be first retrieved 
        // through 'addVertex'. 
        void addEdge( const char* p1, const char* p2, unsigned label );
        
        Graph* graph;
        // Maps each predicate name to its vertex_descriptor in the graph.
        std::unordered_map<const char*, unsigned> predsMap;
    };

};

#endif	/* DEPENDENCYGRAPH_H */


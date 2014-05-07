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

#ifndef GRAPH_H
#define	GRAPH_H

#include "../util/Constants.h"
#include <vector>

namespace DLV2
{
    class DirectedGraph;
    
    typedef std::vector<unsigned> Component;
    
    class Graph {
    public:
        Graph();
        ~Graph();
        
        unsigned addVertex();
        void addEdge( unsigned v1, unsigned v2, unsigned label = POSITIVE_EDGE );
        bool isEdge( unsigned v1, unsigned v2, unsigned label = POSITIVE_EDGE );
        void computeStronglyConnectedComponents();
        
        bool isHCF( unsigned componentIdx );
        bool isHCF();
        bool isStratified( unsigned componentIdx );
        bool isStratified();
        bool isCyclic( unsigned componentIdx );
        bool isCyclic();
        bool isTight();
        
    private:        
        void computeLabeledEdges();
        
        DirectedGraph& graph;
        // It represents vertices by components
        std::vector<Component> stronglyConnectedComponents;
        // It represents components by vertices
        std::vector<int> vertexComponents;
        bool hasLabeledEdges;
        bool* componentHasNegations;
    };
    
};


#endif	/* GRAPH_H */


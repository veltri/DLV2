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
 * File:   XPropagationGraph.h
 * Author: pierfrancesco
 *
 * Created on 17 febbraio 2015, 17.03
 */

#ifndef XPROPAGATIONGRAPH_H
#define XPROPAGATIONGRAPH_H

#include <string>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

namespace DLV2{ namespace REWRITERS{

    typedef boost::property< boost::edge_name_t, unsigned > EdgeProperty;
    typedef boost::property< boost::vertex_name_t, std::string > VertexProperty;

    class DirectedMultiGraph: public boost::adjacency_list<
            boost::vecS,
            boost::vecS,
            boost::directedS,
            VertexProperty,
            EdgeProperty >
    {
    };

    typedef DirectedMultiGraph::vertex_descriptor Vertex;
    typedef DirectedMultiGraph::edge_descriptor Edge;
    typedef DirectedMultiGraph::vertex_iterator VertexIterator;
    typedef DirectedMultiGraph::edge_iterator EdgeIterator;
    typedef DirectedMultiGraph::out_edge_iterator OutEdgeIterator;

    class XPropagationGraph {
    public:
        XPropagationGraph( const XPropagationGraph& pg );
        ~XPropagationGraph() { }

        // Add a noose with the same label to each vertex.
        void addNooses( unsigned label );
        void addEdge( const std::string& srcPredPos, const std::string& destPredPos, unsigned label );
        bool isEdge( const std::string& srcPredPos, const std::string& destPredPos, unsigned label ) const;
        unsigned numOfVertices() const { return boost::num_vertices(graph); }
        const std::string& toString();

    private:
        friend class XProgram;

        XPropagationGraph();
        unsigned addVertex( const std::string& atomPredPos );

        DirectedMultiGraph graph;
        std::string graphString;
        std::unordered_map< std::string, Vertex > vertexLabels;

    };

};};

#endif /* XPROPAGATIONGRAPH_H */

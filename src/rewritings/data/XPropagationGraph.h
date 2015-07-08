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
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

namespace DLV2{ namespace REWRITERS{

    typedef size_t index_t;

    class XProgram;

    struct VertexProperty {
        index_t predicateIndex;
        unsigned termPosition;
    };
    typedef boost::property< boost::edge_name_t, unsigned > EdgeProperty;

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
        void addEdge( index_t srcPredIdx, unsigned srcPos, index_t destPredIdx, unsigned destPos, unsigned label );
        bool isEdge( index_t srcPredIdx, unsigned srcPos, index_t destPredIdx, unsigned destPos, unsigned label ) const;
        unsigned numOfVertices() const { return boost::num_vertices(graph); }
        std::pair< Vertex, bool > getVertexId( index_t predIdx, unsigned termPos ) const;
        std::pair< index_t, unsigned > getIndexByVertexId( Vertex id ) const;
        const std::string& toString();

    private:
        friend class XProgram;

        XPropagationGraph( const XProgram& p );
        unsigned addVertex( index_t predIdx, unsigned pos );

        const XProgram& program;
        DirectedMultiGraph graph;
        std::string graphString;
        // For each predicate index there is a vector containing the vertex id for each position.
        std::unordered_map< index_t, std::vector< Vertex > > index2vertexId;

    };

};};

#endif /* XPROPAGATIONGRAPH_H */

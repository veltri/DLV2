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
 * File:   XPropagationGraph.cpp
 * Author: pierfrancesco
 *
 * Created on 17 febbraio 2015, 18.30
 */

#include "XPropagationGraph.h"

#include "../../util/Assert.h"

using namespace std;
using namespace DLV2::REWRITERS;

XPropagationGraph::XPropagationGraph():
        graph(),
        graphString(),
        vertexLabels()
{
}

XPropagationGraph::XPropagationGraph(
    const XPropagationGraph& g ):
        graph(g.graph),
        graphString(g.graphString),
        vertexLabels(g.vertexLabels)
{
}

unsigned
XPropagationGraph::addVertex(
    const std::string& atomPredPos )
{
    unordered_map< string, Vertex >::const_iterator it = vertexLabels.find(atomPredPos);
    if( it == vertexLabels.end() )
    {
        Vertex v = boost::add_vertex(atomPredPos,graph);
        vertexLabels.insert(pair< const string&, const Vertex& >(atomPredPos,v));
        return v;
    }
    else
        return it->second;
}

void
XPropagationGraph::addNooses(
    unsigned label )
{
    pair< VertexIterator, VertexIterator > verticesIt = boost::vertices(graph);
    for( VertexIterator currVertexIt = verticesIt.first; currVertexIt != verticesIt.second; currVertexIt++ )
        addEdge(boost::get(boost::vertex_name,graph,*currVertexIt),boost::get(boost::vertex_name,graph,*currVertexIt),label);
}

void
XPropagationGraph::addEdge(
    const string& srcPredPos,
    const string& destPredPos,
    unsigned label )
{
    Vertex src = addVertex(srcPredPos);
    Vertex dest = addVertex(destPredPos);
    boost::add_edge(src,dest,label,graph);
}

bool
XPropagationGraph::isEdge(
    const string& srcPredPos,
    const string& destPredPos,
    unsigned label ) const
{
    unordered_map< string, Vertex >::const_iterator itSrc = vertexLabels.find(srcPredPos);
    if( itSrc == vertexLabels.end() )
        return false;

    unordered_map< string, Vertex >::const_iterator itDest = vertexLabels.find(destPredPos);
    if( itDest == vertexLabels.end() )
        return false;

    std::pair< Edge, bool > alreadyExists = boost::edge(itSrc->second,itDest->second,graph);
    if( !alreadyExists.second )
        return false;

    unsigned l = boost::get(boost::edge_name,graph,alreadyExists.first);
    if( label != l )
        return false;

    return true;
}

const string&
XPropagationGraph::toString()
{
    if( graphString.size() == 0 )
    {
        stringstream graphStream;

        pair< VertexIterator, VertexIterator > verticesIt = boost::vertices(graph);
        for( VertexIterator currVertexIt = verticesIt.first; currVertexIt != verticesIt.second; currVertexIt++ )
            graphStream << "vertex(\"" << boost::get(boost::vertex_name,graph,*currVertexIt) << "\").\n";

        pair< EdgeIterator, EdgeIterator > edgesIt = boost::edges(graph);
        for( EdgeIterator currEdgeIt = edgesIt.first; currEdgeIt != edgesIt.second; currEdgeIt++ )
        {
            unsigned edgeLabel = boost::get(boost::edge_name,graph,*currEdgeIt);
            Vertex src = source(*currEdgeIt,graph);
            Vertex trgt = target(*currEdgeIt,graph);
            graphStream << "edge(\""
                    << boost::get(boost::vertex_name,graph,src) << "\",\""
                    << boost::get(boost::vertex_name,graph,trgt) << "\","
                    << edgeLabel << ").\n";
        }
        graphString.append(graphStream.str());
    }
    return graphString;
}

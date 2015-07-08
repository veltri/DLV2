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
#include "XProgram.h"
#include "../../util/Assert.h"
#include "../../util/Trace.h"
#include "../../util/Options.h"

using namespace std;
using namespace DLV2::REWRITERS;

XPropagationGraph::XPropagationGraph(
    const XProgram& p ):
        program(p),
        graph(),
        graphString(),
        index2vertexId()
{
}

XPropagationGraph::XPropagationGraph(
    const XPropagationGraph& g ):
        program(g.program),
        graph(g.graph),
        graphString(g.graphString),
        index2vertexId(g.index2vertexId)
{
}

unsigned
XPropagationGraph::addVertex(
    index_t predIdx,
    unsigned pos )
{
    assert_msg( pos < program.getPredicateArity(predIdx), "Position out of range" );
    unordered_map< index_t, vector< Vertex > >::const_iterator it = index2vertexId.find(predIdx);
    if( it == index2vertexId.end() )
    {
        vector< Vertex > vertices;
        for( unsigned i=0; i<program.getPredicateArity(predIdx); i++ )
            vertices.push_back(boost::add_vertex(graph));
        index2vertexId.insert(pair< index_t, vector< Vertex > >(predIdx,vertices));
        graph[vertices[pos]].predicateIndex = predIdx;
        graph[vertices[pos]].termPosition = pos;
        return vertices[pos];
    }
    else
    {
        assert_msg( pos < it->second.size(), "Position out of range" );
        return it->second.at(pos);
    }
}

void
XPropagationGraph::addNooses(
    unsigned label )
{
    pair< VertexIterator, VertexIterator > verticesIt = boost::vertices(graph);
    for( VertexIterator currVertexIt = verticesIt.first; currVertexIt != verticesIt.second; currVertexIt++ )
        boost::add_edge(*currVertexIt,*currVertexIt,label,graph);
}

void
XPropagationGraph::addEdge(
    index_t srcPredIdx,
    unsigned srcPos,
    index_t destPredIdx,
    unsigned destPos,
    unsigned label )
{
    Vertex src = addVertex(srcPredIdx,srcPos);
    Vertex dest = addVertex(destPredIdx,destPos);
    boost::add_edge(src,dest,label,graph);
}

bool
XPropagationGraph::isEdge(
    index_t srcPredIdx,
    unsigned srcPos,
    index_t destPredIdx,
    unsigned destPos,
    unsigned label ) const
{
    unordered_map< index_t, vector< Vertex > >::const_iterator itSrc = index2vertexId.find(srcPredIdx);
    if( itSrc == index2vertexId.end() )
        return false;

    unordered_map< index_t, vector < Vertex > >::const_iterator itDest = index2vertexId.find(destPredIdx);
    if( itDest == index2vertexId.end() )
        return false;

    assert_msg( ( srcPos < itSrc->second.size() && destPos < itDest->second.size() ), "Position out of range" );
    std::pair< Edge, bool > alreadyExists = boost::edge(itSrc->second.at(srcPos),itDest->second.at(destPos),graph);
    if( !alreadyExists.second )
        return false;

    unsigned l = boost::get(boost::edge_name,graph,alreadyExists.first);
    if( label != l )
        return false;

    return true;
}

pair< Vertex, bool >
XPropagationGraph::getVertexId(
    index_t predIdx,
    unsigned termPos ) const
{
    unordered_map< index_t, vector< Vertex > >::const_iterator it = index2vertexId.find(predIdx);
    if( it != index2vertexId.end() )
    {
        assert_msg( termPos < it->second.size(), "Index out of range" );
        return pair< Vertex, bool >(it->second.at(termPos),true);
    }
    return pair< Vertex, bool >(0,false);
}

pair< index_t, unsigned >
XPropagationGraph::getIndexByVertexId(
    Vertex id ) const
{
    assert_msg( id < boost::num_vertices(graph), "Index out of range" );
    return pair < index_t, unsigned >(graph[id].predicateIndex,graph[id].termPosition);
}

const string&
XPropagationGraph::toString()
{
    if( graphString.size() == 0 )
    {
        stringstream graphStream;

        pair< VertexIterator, VertexIterator > verticesIt = boost::vertices(graph);
        for( VertexIterator currVertexIt = verticesIt.first; currVertexIt != verticesIt.second; currVertexIt++ )
            graphStream << "vertex(" << *currVertexIt << ").\n";

        pair< EdgeIterator, EdgeIterator > edgesIt = boost::edges(graph);
        for( EdgeIterator currEdgeIt = edgesIt.first; currEdgeIt != edgesIt.second; currEdgeIt++ )
        {
            unsigned edgeLabel = boost::get(boost::edge_name,graph,*currEdgeIt);
            Vertex src = source(*currEdgeIt,graph);
            Vertex trgt = target(*currEdgeIt,graph);
            graphStream << "edge(" << src << "," << trgt << "," << edgeLabel << ").\n";
        }
        graphString.append(graphStream.str());
    }
    trace_action( rewriting, 3,
            trace_tag( cerr, rewriting, 3 );
            cerr << "Propagation graph:";
            if( numOfVertices() > 0 )
            {
                cerr << endl;
                char* tmpGraphString = new char[strlen(graphString.c_str())+1];
                strcpy(tmpGraphString,graphString.c_str());
                tmpGraphString[strlen(graphString.c_str())] = '\0';
                char* t = NULL;
                t = strtok(tmpGraphString,"\n");
                while( t != NULL )
                {
                    trace_tag( cerr, rewriting, 3 );
                    cerr << "\t" << t << endl;
                    t = strtok(NULL,"\n");
                }
                delete[] tmpGraphString;
                trace_tag( cerr, rewriting, 3 );
                cerr << "Vertices map:" << endl;
                for( std::unordered_map< index_t, std::vector <Vertex > >::const_iterator it = index2vertexId.begin(); it != index2vertexId.end(); it++ )
                {
                    for( unsigned i=0; i<it->second.size(); i++ )
                    {
                        trace_tag( cerr, rewriting, 3 );
                        cerr << "\t" << program.getPredicateName(it->first) << "-" << i << ": " << it->second.at(i) << endl;
                    }
                }
            }
            else
                cerr << " EMPTY!" << endl;
    );
    return graphString;
}

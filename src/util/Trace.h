/*
 *
 *  Copyright 2013 Mario Alviano, Carmine Dodaro, and Francesco Ricca.
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

#ifndef TRACE_H
#define TRACE_H

#include <cstdio>
#include <string>
#include <vector>
#include <sstream>

using std::pair;
using std::string;
using std::vector;
using std::stringstream;

/*
 * The tracing macros are expanded only if TRACE_OFF is not defined.
 * The tracing structures are defined only if TRACE_OFF is not defined.
 */
#ifndef TRACE_ON
    #define trace_tag( stream, type, level )
    #define trace( type, level, msg, ... )
    #define traceIf( type, level, condition, msg, ... )
    #define setTraceLevel( type, level )
    #define trace_msg( type, level, msg )
    #define trace_action( type, level, action )
	#define trace_action_tag( type, level, action )
#else
    #define trace_tag( stream, type, level ) \
        stream << "[" << DLV2::Options::traceLevels.types[ DLV2::Options::traceLevels.type() ].first.substr( 0, 10 ) << "]"; \
        for( unsigned __indent_Level__ = 0; __indent_Level__ < 11 - DLV2::Options::traceLevels.types[ Options::traceLevels.type() ].first.substr( 0, 10 ).length(); ++__indent_Level__ ) \
            stream <<  " "; \
        for( unsigned __indent_Level__ = 1; __indent_Level__ < level; ++__indent_Level__ ) \
            stream << "    ";
    #define trace( type, level, msg, ... ) \
        if( DLV2::Options::traceLevels.types[ DLV2::Options::traceLevels.type() ].second >= level ) \
        { \
            trace_tag( cerr, type, level ); \
            fprintf( stderr, msg, ##__VA_ARGS__ ); \
        }
    #define traceIf( type, level, condition, msg, ... ) \
        if( condition ) \
            trace( type, level, msg, ##__VA_ARGS__ )
    #define setTraceLevel( type, level ) \
		DLV2::Options::traceLevels.types[ DLV2::Options::traceLevels.type() ].second = level
    #define trace_msg( type, level, msg ) {\
		if( DLV2::Options::traceLevels.types[ DLV2::Options::traceLevels.type() ].second >= level ) \
        { \
        trace_tag( cerr, type, level ); \
        cerr << msg << std::endl; \
        } \
    }
    #define trace_action( type, level, action ) \
		if( DLV2::Options::traceLevels.types[ Options::traceLevels.type() ].second >= level ) \
        { action }
	#define trace_action_tag( type, level, action ) \
		if( DLV2::Options::traceLevels.types[ Options::traceLevels.type() ].second >= level ) \
		{ trace_tag( cerr, type, level ); action }

namespace DLV2{
/**
* This class contains an unsigned integer for each kind of trace present in
* wasp.
*/
class TraceLevels
{
    friend class Options;

    public:
        vector< pair< string, unsigned > > types;

        unsigned parser() { return 0; }
        unsigned grounding() { return 1; }
        unsigned aggregates() { return 2; }
        unsigned weakconstraints() { return 3; }
        unsigned backjumping() { return 4; }
        unsigned backtracking() { return 5; }


    private:
        inline TraceLevels();
};

TraceLevels::TraceLevels()
{
    types.push_back( pair< string, unsigned >( "parser", 0 ) );
    types.push_back( pair< string, unsigned >( "grounding", 2 ) );
    types.push_back( pair< string, unsigned >( "aggregates", 0 ) );
    types.push_back( pair< string, unsigned >( "weakconstraints", 0 ) );
    types.push_back( pair< string, unsigned >( "backjumping", 2 ) );
    types.push_back( pair< string, unsigned >( "backtracking", 2 ) );

}

}
#endif

#endif

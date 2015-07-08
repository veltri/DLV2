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

#include "Options.h"
#include "ErrorMessage.h"
#include "Help.h"

#include <getopt.h>
#include <cstdlib>

namespace DLV2 
{
// Options with a short alias.
#define OPTIONID_help 'h'

// "Only-long" options with their code.

/* INPUT OPTIONS */
#define OPTIONID_aspcore2strict ( 'z' + 1 )
#define OPTIONID_inmemory ( 'z' + 2 )
#define OPTIONID_dlvdb ( 'z' + 3 )
#define OPTIONID_testparser ( 'z' + 4 )
#define OPTIONID_datalogpm ( 'z' + 5 )

/* OUTPUT OPTIONS */
#define OPTIONID_silent ( 'z' + 10 )
#define OPTIONID_printprogram ( 'z' + 11 )
#define OPTIONID_selector ( 'z' + 12 )
#define OPTIONID_printdepgraph ( 'z' + 13 )
#define OPTIONID_printstatistics ( 'z' + 14 )
#define OPTIONID_printirisoutput ( 'z' + 15 )

/* GENERIC OPTIONS */
#define OPTIONID_stdin ( 'z' + 20 )
#define OPTIONID_parallelrewriting ( 'z' + 21 )

/* DB OPTIONS */
#define OPTIONID_datasource ('z' + 30 )
#define OPTIONID_username ('z' + 31 )
#define OPTIONID_password ('z' + 32 )

/* TRACE OPTIONS */
#define OPTIONID_trace_parser ('z' + 40 )
#define OPTIONID_trace_sticky_join_check ('z' + 41 )
#define OPTIONID_trace_rewriting ('z' + 42 )

};

using namespace std; 
using namespace DLV2;
    
// Initialize singleton
Options* Options::instance = NULL;

#ifdef TRACE_ON
TraceLevels Options::traceLevels;
#endif

Options* 
Options::globalOptions() 
{
    if( instance == NULL )
    {
        instance = new Options();
    }
    return instance;
}

void
Options::finalizeGlobalOptions() 
{
    if( instance != NULL )
    {
        delete instance;
        instance = NULL;
    }
}


Options::Options(): 
        aspCore2Strict(false),
        datalogpm(false),
        parallelRewriting(false),
        printProgram(false),
        printDepGraph(false),
        printStatistics(false),
        inputPolicy(-1),
        outputPolicy(-1)
{

}

Options::Options(
    const Options& o):
        aspCore2Strict(o.aspCore2Strict),
        datalogpm(o.datalogpm),
        parallelRewriting(o.parallelRewriting),
        printProgram(o.printProgram),
        printDepGraph(o.printDepGraph),
        printStatistics(o.printStatistics),
        inputPolicy(o.inputPolicy),
        outputPolicy(o.outputPolicy) 
{

}

void
Options::init(
    int argc,
    char* const* argv )
{
    // It will store the option code.
    int code;
    
    // A string listing valid short options letters. 
    const char* const shortOptions = "h";
    
    // An array describing valid long options. 
    const struct option longOptions[] = 
    {    
        /* INPUT OPTIONS */
        { "aspcore2strict", no_argument, NULL, OPTIONID_aspcore2strict },
        { "inmemory", no_argument, NULL, OPTIONID_inmemory },
        { "dlvdb", no_argument, NULL, OPTIONID_dlvdb },
        { "test-parser", no_argument, NULL, OPTIONID_testparser },
        { "datalogpm", no_argument, NULL, OPTIONID_datalogpm },

        /* OUTPUT OPTIONS */
        { "silent", no_argument, NULL, OPTIONID_silent },
        { "printprogram", no_argument, NULL, OPTIONID_printprogram },
        { "selector", required_argument, NULL, OPTIONID_selector },
        { "printdepgraph", no_argument, NULL, OPTIONID_printdepgraph },
        { "stats", no_argument, NULL, OPTIONID_printstatistics },
        { "printprogram-iris-output", no_argument, NULL, OPTIONID_printirisoutput },

        /* GENERIC OPTIONS */
        { "help", no_argument, NULL, OPTIONID_help },
        { "stdin", no_argument, NULL, OPTIONID_stdin },
        { "parallel-rewriting", no_argument, NULL, OPTIONID_parallelrewriting },
        
        /* DB OPTIONS */
        { "db-source", required_argument, NULL, OPTIONID_datasource },
        { "db-user", required_argument, NULL, OPTIONID_username },
        { "db-pwd", required_argument, NULL, OPTIONID_password },

        /* TRACE OPTIONS */
        { "trace-parser", required_argument, NULL, OPTIONID_trace_parser },
        { "trace-sticky-join-check", required_argument, NULL, OPTIONID_trace_sticky_join_check },
        { "trace-rewriting", required_argument, NULL, OPTIONID_trace_rewriting },

        // Required at end of array. 
        { NULL, 0, NULL, 0 }
    };
  
    do{
        // The function getopt_long() stores the option index here.
        int optionIndex = 0;
        
        code = getopt_long (argc, argv, shortOptions, longOptions, &optionIndex);
        
        switch (code)
        {
            case -1:
                // All the lines were parsed
                break;
            case OPTIONID_aspcore2strict:
                if( datalogpm )
                    ErrorMessage::errorGeneric( "Options --datalogpm and --aspcore2strict collide one another" );
                aspCore2Strict = true;
                break;
            
            case OPTIONID_inmemory:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                inputPolicy = BUILDER_IN_MEMORY;
                break;
                
            case OPTIONID_dlvdb:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                inputPolicy = BUILDER_DLV_DB;
                break;
                
            case OPTIONID_testparser:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                inputPolicy = BUILDER_EMPTY;
                printStatistics = true;
                break;
                
            case OPTIONID_datalogpm:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                if( aspCore2Strict )
                    ErrorMessage::errorGeneric( "Options --datalogpm and --aspcore2strict collide one another" );
                inputPolicy = BUILDER_DATALOGPM;
                datalogpm = true;
                break;

            case OPTIONID_silent:
                outputPolicy = OUTPUT_SILENT;
                break;
                
            case OPTIONID_printprogram:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                inputPolicy = BUILDER_MOCK_OBJECTS;
                printProgram = true;
                break;
                
            case OPTIONID_selector:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                inputPolicy = BUILDER_SELECTOR;
                printProgram = true;
                namedpipe = atoi( optarg );
                break;
                
            case OPTIONID_printdepgraph:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                inputPolicy = BUILDER_DEPGRAPH;
                printDepGraph = true;
                break;

            case OPTIONID_printstatistics:
                printStatistics = true;
                break;
                
            case OPTIONID_printirisoutput:
                if( inputPolicy != -1 )
                    ErrorMessage::errorGeneric( "Options about input policy must be set at most once" );
                inputPolicy = BUILDER_DATALOGPM;
                printProgram = true;
                break;

            case OPTIONID_help:
                Help::printHelp(argv[0]);
                exit(0);
                break;
                
            case OPTIONID_stdin:
                inputFiles.push_back("--");
                break;
            
            case OPTIONID_parallelrewriting:
                setParallelRewriting(true);
                break;

            case OPTIONID_datasource:
                dbDataSource.append(optarg);
                break;
                
            case OPTIONID_username:
                dbUsername.append(optarg);
                break;
                
            case OPTIONID_password:
                dbPassword.append(optarg);
                break;
                
            case OPTIONID_trace_parser:
                setTraceLevel( parser, atoi(optarg) );
                break;

            case OPTIONID_trace_sticky_join_check:
                setTraceLevel( stickyJoinCheck, atoi(optarg) );
                break;

            case OPTIONID_trace_rewriting:
                setTraceLevel( rewriting, atoi(optarg) );
                break;

            default:
                ErrorMessage::errorGeneric( "This option is not supported." );
                break;
        }
    }while( code != -1 );
    
    // Default policy
    if( inputPolicy == -1 )
        inputPolicy = BUILDER_IN_MEMORY;
    if( outputPolicy == -1 )
        outputPolicy = OUTPUT_ASPCORE2;

    // Manage the reminder options (probably, they are all input files).
    for( int i = optind; i < argc; i++ )
    {
        inputFiles.push_back( argv[ i ] );
    }
}

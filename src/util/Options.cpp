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
#include "Assert.h"

#include <getopt.h>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

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

/* OUTPUT OPTIONS */
#define OPTIONID_silent ( 'z' + 10 )
#define OPTIONID_printprogram ( 'z' + 11 )
#define OPTIONID_selector ( 'z' + 12 )
#define OPTIONID_printdepgraph ( 'z' + 13 )
#define OPTIONID_printstatistics ( 'z' + 14 )

/* GENERIC OPTIONS */
#define OPTIONID_stdin ( 'z' + 20 )

/* DB OPTIONS */
#define OPTIONID_datasource ('z' + 30 )
#define OPTIONID_username ('z' + 31 )
#define OPTIONID_password ('z' + 32 )

/* GROUNDER OPTIONS */
#define OPTIONID_hashType ('z' + 33)
#define OPTIONID_indexType ('z' + 34)
#define OPTIONID_predIndexTerm ('z' + 35)
#define OPTIONID_predIndexType ('z' + 36)
#define OPTIONID_nofacts ('z' + 37)


};

using namespace std; 
using namespace DLV2;
    
// Initialize singleton
Options* Options::instance = NULL;

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
        printProgram(false),
        printDepGraph(false),
        printStatistics(false),
        inputPolicy(BUILDER_IN_MEMORY),
        outputPolicy(OUTPUT_ASPCORE2),
		hashType(STL_HASH),
		indexType(DEFAULT),
		predicatesIndexTerm(""),
		predicatesIndexType(""),
		nofacts(false)
{

}

Options::Options(
    const Options& o):
        aspCore2Strict(o.aspCore2Strict),
        printProgram(o.printProgram),
        printDepGraph(o.printDepGraph),
        printStatistics(o.printStatistics),
        inputPolicy(o.inputPolicy),
        outputPolicy(o.outputPolicy),
		hashType(o.hashType),
		indexType(o.indexType),
		predicatesIndexTerm(o.predicatesIndexTerm),
		predicatesIndexType(o.predicatesIndexTerm),
		nofacts(o.nofacts)
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

        /* OUTPUT OPTIONS */
        { "silent", no_argument, NULL, OPTIONID_silent },
        { "printprogram", no_argument, NULL, OPTIONID_printprogram },
        { "selector", required_argument, NULL, OPTIONID_selector },
        { "printdepgraph", no_argument, NULL, OPTIONID_printdepgraph },
        { "stats", no_argument, NULL, OPTIONID_printstatistics },

        /* GENERIC OPTIONS */
        { "help", no_argument, NULL, OPTIONID_help },
        { "stdin", no_argument, NULL, OPTIONID_stdin },
        
        /* DB OPTIONS */
        { "db-source", required_argument, NULL, OPTIONID_datasource },
        { "db-user", required_argument, NULL, OPTIONID_username },
        { "db-pwd", required_argument, NULL, OPTIONID_password },

		{"hashtype",required_argument, NULL, OPTIONID_hashType },
		{"indextype",required_argument,NULL,OPTIONID_indexType},
		{"predindexterm",required_argument, NULL, OPTIONID_predIndexTerm},
		{"predindextype",required_argument, NULL, OPTIONID_predIndexType},
		{"nofacts",no_argument, NULL, OPTIONID_nofacts},

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
                aspCore2Strict = true;
                break;
            
            case OPTIONID_inmemory:
                inputPolicy = BUILDER_IN_MEMORY;
                break;
                
            case OPTIONID_dlvdb:     
                inputPolicy = BUILDER_DLV_DB;
                break;
                
            case OPTIONID_testparser:
                inputPolicy = BUILDER_EMPTY;
                printStatistics = true;
                break;
                
            case OPTIONID_silent:
                outputPolicy = OUTPUT_SILENT;
                break;
                
            case OPTIONID_printprogram:
                inputPolicy = BUILDER_MOCK_OBJECTS;
                printProgram = true;
                break;
                
            case OPTIONID_selector:
                inputPolicy = BUILDER_SELECTOR;
                printProgram = true;
                namedpipe = atoi( optarg );
                break;
                
            case OPTIONID_printdepgraph:
                inputPolicy = BUILDER_DEPGRAPH;
                printDepGraph = true;
                break;

            case OPTIONID_printstatistics:
                printStatistics = true;
                break;
                
            case OPTIONID_help:
                Help::printHelp(argv[0]);
                exit(0);
                break;
                
            case OPTIONID_stdin:
                inputFiles.push_back("--");
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
                
            case OPTIONID_hashType:
            	hashType = atoi(optarg);
                assert_msg((hashType>=STL_HASH && hashType<=PERL_B),"Hash type not supported");
            	break;

            case OPTIONID_indexType:
            	indexType = atoi(optarg);
                assert_msg((indexType>=DEFAULT && indexType<=DOUBLEMAP),"Index type not supported");
                break;

            case OPTIONID_predIndexTerm:
                predicatesIndexTerm.append(optarg);
                this->splitOption(predicatesIndexTerm, predicatesIndexTermMap);
                break;

            case OPTIONID_predIndexType:
				predicatesIndexType.append(optarg);
				this->splitOption(predicatesIndexType, predicatesIndexTypeMap);
				break;

            case OPTIONID_nofacts:
            	nofacts=true;
				break;

            default:
                ErrorMessage::errorGeneric( "This option is not supported." );
                break;
        }
    }while( code != -1 );
    
    // Manage the reminder options (probably, they are all input files).
    for( int i = optind; i < argc; i++ )
    {
        inputFiles.push_back( argv[ i ] );
    }
}

void Options::splitOption(const std::string& string, std::unordered_map<std::string, unsigned int>& map){
	// Split the string indexingPreferences and
	// fill in the map with the indexing strategies for the specified
	if(string.compare("")!=0){
		std::stringstream stream(string);
		std::string segment="";
		while(getline(stream, segment, ','))
		{
			std::vector<std::string> pair_pred_term;
			boost::split(pair_pred_term, segment, boost::is_any_of("="));
			map.insert({pair_pred_term[0],boost::lexical_cast<unsigned int>(pair_pred_term[1])});
		}
	}
}

int Options::getPredicateIndexTerm(const string& predicate){
	if(predicatesIndexTermMap.count(predicate))
		return predicatesIndexTermMap[predicate];
	return -1;
}

int Options::getPredicateIndexType(const string& predicate){
	if(predicatesIndexTypeMap.count(predicate)){
		unsigned type=predicatesIndexTypeMap[predicate];
		assert_msg((type>=DEFAULT && type<=HASHSET),"Index type not supported");
		return type;
	}
	return -1;
}


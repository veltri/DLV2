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

#include "../DLV2Facade.h"

#include <getopt.h>
#include <cstdlib>

namespace dlv2{
  
// Options with a short alias.
#define OPTIONID_help 'h'

// "Only-long" options with their code.
    
/* INPUT OPTIONS */
#define OPTIONID_aspcore2strict ( 'z' + 1 )
#define OPTIONID_inmemory ( 'z' + 2 )
#define OPTIONID_dlvdb ( 'z' + 3 )    

/* OUTPUT OPTIONS */
#define OPTIONID_silent ( 'z' + 10 )
#define OPTIONID_printprogram ( 'z' + 11 )
    
/* GENERIC OPTIONS */
#define OPTIONID_stdin ( 'z' + 20 )

// Initialize static fields.
bool Options::aspCore2Strict = false;    
    
bool Options::printProgram = false;

INPUT_HANDLING_POLICY Options::inputPolicy = INPUT_IN_MEMORY;

OUTPUT_POLICY Options::outputPolicy = OUTPUT_ASPCORE2;

vector< const char* > Options::inputFiles;

void
Options::parse(
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
        { "dlv-db", no_argument, NULL, OPTIONID_dlvdb },

        /* OUTPUT OPTIONS */
        { "silent", no_argument, NULL, OPTIONID_silent },
        { "printprogram", no_argument, NULL, OPTIONID_printprogram },

        /* GENERIC OPTIONS */
        { "help", no_argument, NULL, OPTIONID_help },
        { "stdin", no_argument, NULL, OPTIONID_stdin },

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
                inputPolicy = INPUT_IN_MEMORY;
                break;
                
            case OPTIONID_dlvdb:     
                inputPolicy = INPUT_DLV_DB;
                break;
                
            case OPTIONID_silent:
                outputPolicy = OUTPUT_SILENT;
                break;
                
            case OPTIONID_printprogram:
                inputPolicy = INPUT_MOCK_OBJECTS;
                printProgram = true;
                break;
                
            case OPTIONID_help:
                Help::printHelp(argv[0]);
                exit(0);
                break;
                
            case OPTIONID_stdin:
                inputFiles.push_back("--");
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

void
Options::setOptions(
    DLV2Facade& dlv2Facade )
{
    dlv2Facade.setAspCore2Strict( aspCore2Strict );
    dlv2Facade.setPrintProgram( printProgram );
    dlv2Facade.setInputHandlingPolicy( inputPolicy );
    dlv2Facade.setOutputPolicy( outputPolicy );
    dlv2Facade.setInputFiles( inputFiles );
}

};
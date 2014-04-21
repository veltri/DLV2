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

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include "InputDirector.h"
#include "../util/ErrorMessage.h"
#include "../aspcore2_lexer.hpp"
#include "../aspcore2_parser.hpp"
#include "../data/Program.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Some LEX/FLEX dependencies

extern "C" int yywrap() { return 1; }    // End-of-file handler for LEX
extern FILE* yyin;     // Where LEX reads its input from

int 
yyerror( 
    const char* msg ) 
{ 
    return InputDirector::getInstance().onError(msg); 
}

InputDirector* InputDirector::instance = NULL;

InputDirector&
InputDirector::getInstance() 
{
    if(instance == NULL)
        instance = new InputDirector();
    return *instance;
}

void
InputDirector::free() 
{
    if(instance != NULL) {
        delete instance;
        instance = NULL;
        //yylex_destroy();
    }
}

void 
InputDirector::configureBuilder( 
    InputBuilder* b )
{
    assert_msg( b != NULL, "InputBuilder has been already initialized" );
    builder = b;  	
}

InputDirector::InputDirector():   
    parserLine(0),
    parserFile(NULL),
    parserErrors(0),
    parserStateInternal(true),
    builder(NULL)
{
    
}

InputDirector::~InputDirector()
{
}

int
InputDirector::parse(
    vector<const char*> files ) 
{
    if( files.size() == 0 )
        ErrorMessage::errorGeneric( "No input files." );
    else if( files.size() == 1 && !strcmp(files[0],"--") )
        return InputDirector::parse();
    
    for( unsigned i = 0; i < files.size(); i++) {
        FILE *file = fopen(files[i], "r");
        if(file) {
            int res = parse(files[i], file);
            fclose(file);
            if(res != 0)
                return res;
        }
        else {
            yyerror("Can't open input");
            return -1;
        }
    }
    return 0;
}

int
InputDirector::parse(
    int filesSize,
    const char **files ) 
{
    for(int i = 1; i < filesSize; i++) {
        FILE *file = fopen(files[i], "r");
        if(file) {
            int res = parse(files[i], file);
            fclose(file);
            if(res != 0)
                return res;
        }
        else {
            yyerror("Can't open input");
            return -1;
        }
    }
    return 0;
}

int
InputDirector::parse(
    const char* fileName,
    FILE *file ) 
{
    yyin = file;
    parserFile = fileName;
    parserLine = 1;
    yyparse();

    if( parserErrors > 0 ) {
        cerr << "Aborting due to parser errors." << endl;
        return -1;
    }
    return 0;
}


int
InputDirector::parse( ) 
{
    yyin = stdin;
    parserFile = "STDIN";
    parserLine = 1;
    yyparse();

    if( parserErrors > 0 ) {
        cerr << "Aborting due to parser errors." << endl;
        return -1;
    }
    return 0;
}

int 
InputDirector::onError( 
    const char* msg ) // Error handler for YACC
{
    parserErrors++;

    if( !parserStateInternal )
        {
        if(parserFile && strlen(parserFile) > 0 )
            cerr << parserFile << ": ";
        cerr << "line " << parserLine;

        cerr << ": ";
        }
    else
        cerr << "Internal parser invocation: ";

    cerr << msg << "." << endl;

    return 0;
}

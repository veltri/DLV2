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
 * File:   InputDirector.h
 * Author: cesco
 *
 * Created on 17 marzo 2014, 13.10
 */

#ifndef INPUTDIRECTOR_H
#define INPUTDIRECTOR_H

#include "../util/Assert.h"
#include "InputBuilder.h"

#include <vector>

// TODO: why should this be a singleton?

class InputDirector {
public:

    ~InputDirector();

    static void free();

    static InputDirector& getInstance();


    void configureBuilder( InputBuilder* );
    InputBuilder* getBuilder() { return builder; }
    
    //////////////////////////////////////////////////////////////////////////////
    // Parsing functions
    int parse( std::vector<const char*> files);
    int parse( int filesSize, const char **files );
    int parse( const char* filename, FILE *file );
    int parse( );
    
    int onError(const char* msg);
    void onNewLine() { parserLine++; }
    

private:
    static InputDirector* instance;

    InputDirector();
    InputDirector(const InputDirector&):
    	parserLine(0),  parserFile(0), parserErrors(0),
    	ParserStateInternal(false),builder(0)
    		{ assert(0); }
    
    int parserLine;
    const char* parserFile;
    unsigned parserErrors;
    bool ParserStateInternal;
    InputBuilder* builder;
};

//////////////////////////////////////////////////////////////////////////////
// Bug Fixes for Various Environments

// BUG-FIX: bison[1.24] fails to prototype its interfaces yylex() and yyerror().
extern "C" int yylex();
extern "C" int yyerror(const char*);

#endif	/* INPUTDIRECTOR_H */


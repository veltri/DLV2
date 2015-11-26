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

#ifndef HELP_H
#define HELP_H

#include <iostream>
#include "Constants.h"

namespace DLV2
{
    
    class Help
    {
    public:
        static void printHelp( const char* exec )
        {
            std::string separator = "\n---------------------------\n";

            std::cout << DLV2_STRING << std::endl;
            std::cout << "usage: " << exec << " {OPTIONS} [filename [filename [...]]]" << std::endl;
            std::cout << separator << std::endl;

            std::cout << "Input options                         " << std::endl << std::endl;
            std::cout << "--aspcore2strict                       - Enable \"strict\" AspCore2 format as input." << std::endl;
            std::cout << "--inmemory                             - Enable the input builder for the in-memory version. (default choice)" << std::endl;
            std::cout << "--dlv-db                               - Enable the input builder for the DB-based version." << std::endl;
            std::cout << "--test-parser                          - Enable an empty input builder in order to test just parsing functionalities." << std::endl;
            std::cout << separator << std::endl;

            std::cout << "Output options                         " << std::endl << std::endl;
            std::cout << "--silent                               - Suppress the startup banner and blank lines." << std::endl;
            std::cout << "--printprogram                         - Enable the input builder for mock objects, print the input program and exit." << std::endl;
            std::cout << "--printdepgraph                        - Enable the input builder for the dependency graph, print it and exit." << std::endl;
            std::cout << "--stats                                - Print final statistics." << std::endl;
            std::cout << separator << std::endl;

            std::cout << "Grounder options                         " << std::endl << std::endl;
            std::cout << "--hashtype                               - Set the hash type of objects. Possible values: STL_HASH=0, BOOST_HASH=1, JAVA_HASH=2, MUR_HASH=3, PERL_DJ=4, PERL_B=5." << std::endl;
            std::cout << "--indextype                              - Set the index table of object. Possible values: DEFAULT=0, MAP=1, MULTIMAP=2, HASHSET=3, DOUBLEMAP=4." << std::endl;
            std::cout << "--predindexterm                          - Set on which term predicates have to be indexed. Example: -i p=2,a=3" << std::endl;
            std::cout << "--predindextype                          - Set the index type for the given predicates. Example: --predindextype=p=1,a=2" << std::endl;
            std::cout << "--rewritingtype                          - Set the rewriting type of the choice: 0:Native choice with all atoms in the body of the choice; 2:Rewriting with disjunction.3: Native choice avoiding unnecessary atoms in the body. " << std::endl;
            std::cout << "--printRewrite                           - Print the rewrited program." << std::endl;
            std::cout << "--outputformat                           - Set the output format: 0=NUmeric, 1=Textual." << std::endl;
            std::cout << "--positiveOrdering                       - 0=NO ORDERING, 1=COMBINED." << std::endl;
            std::cout << separator << std::endl;


            std::cout << "DB options                             " << std::endl << std::endl;
            std::cout << "--db-source=[db_name]                  - Set the name of the database where input data are stored." << std::endl;
            std::cout << "--db-user=[db_username]                - Set the username to have access to the database." << std::endl;
            std::cout << "--db-pwd=[db_password]                 - Set the password to have access to the database." << std::endl;
            std::cout << separator << std::endl;
            
            std::cout << "General options                     " << std::endl << std::endl;
            std::cout << "--help                                 - Print this guide and exit." << std::endl;
            std::cout << "--stdin                                - Read input from standard input." << std::endl;
        }
    };

};

#endif /* HELP_H */

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

            std::cout << IDLV_STRING << std::endl;
            std::cout << "usage: " << exec << " {OPTIONS} [filename [filename [...]]]" << std::endl;
            std::cout << separator << std::endl;

//            std::cout << "Input options                         " << std::endl << std::endl;
//            std::cout << "--aspcore2strict                       - Enable \"strict\" AspCore2 format as input." << std::endl;
//            std::cout << "--inmemory                             - Enable the input builder for the in-memory version. (default choice)" << std::endl;
//            std::cout << "--dlv-db                               - Enable the input builder for the DB-based version." << std::endl;
//            std::cout << "--test-parser                          - Enable an empty input builder in order to test just parsing functionalities." << std::endl;
//            std::cout << separator << std::endl;

            std::cout << "Output options                         " << std::endl << std::endl;
            std::cout << "--silent                              - Suppress the startup banner and blank lines." << std::endl;
            std::cout << "--no-facts                            - Suppress the printing of EDB." << std::endl;
            std::cout << "--output-format                       - Set the output format: 0=Numeric, 1=Textual." << std::endl;
            std::cout << "--t                                   - Print in textual mode." << std::endl;
            std::cout << "--filter                              - Filter the specified predicates with the specified arity. Example: --filter=p1/2,p2/3." << std::endl;
            std::cout << "--print-rewriting                     - Print the rewritten program." << std::endl;
            std::cout << "--query                               - Print the results of the input query." << std::endl;

//            std::cout << "--printprogram                         - Enable the input builder for mock objects, print the input program and exit." << std::endl;
//            std::cout << "--printdepgraph                        - Enable the input builder for the dependency graph, print it and exit." << std::endl;
//            std::cout << "--stats                                - Print final statistics." << std::endl;
            std::cout << separator << std::endl;

            std::cout << "Grounding options                         " << std::endl << std::endl;
//            std::cout << "--hash-type                           - Set the hash type of objects. Possible values: STL_HASH=0, BOOST_HASH=1, JAVA_HASH=2, MUR_HASH=3, PERL_DJ=4, PERL_B=5." << std::endl;
//            std::cout << "--index-type                          - Set the index table of object. Possible values: DEFAULT=0, MAP=1, MULTIMAP=2, HASHSET=3, DOUBLEMAP=4." << std::endl;
//            std::cout << "--pred-index-type                     - Set the index type for the given predicates. Example: --pred-index-type=p=1,a=2" << std::endl;
            std::cout << "--check-edb-duplication               - If present, remove duplicate EDB." << std::endl;
            std::cout << "--rewriting                           - Set the rewriting strategy to adopt for choice rules: 0: Native Rewriting (Default); 1: By means of disjunction." << std::endl;
            std::cout << "--rewrite-arith-terms                 - Enable the rewriting of arithmetic terms into assignment built-in atoms." << std::endl;
            std::cout << "--align-dictionaries                  - Enable the dictionaries alignment mechanism." << std::endl;
            std::cout << "--ordering                            - Set the body ordering strategy: " << std::endl;
            std::cout << "                                            0=BASE ORDERING," << std::endl;
            std::cout << "                                            1=DLV COMBINED CRITERION," << std::endl;
            std::cout << "                                            2=COMBINED+ CRITERION (Default)," << std::endl;
            std::cout << "                                            3=FUNCTIONAL TERMS CRITERION," << std::endl;
            std::cout << "                                            4=INDEXING CRITERION," << std::endl;
            std::cout << "                                            5=BACKJUMPING CRITERION," << std::endl;
            std::cout << "                                            6=COMBINATION OF 4 and 5 CRITERIA." << std::endl;
            std::cout << "--no-isolated-filter                  - Disable the filtering mechanism of isolated variables." << std::endl;
            std::cout << "--no-projection                       - Disable the projection rewriting of irrelevant variables." << std::endl;
            std::cout << "--indexing                            - Set the indexing terms for the specified predicates. Example: --indexing=p/1={0,1},p/2={2}." << std::endl;
            std::cout << "--FC                                  - Enable cautious reasoning." << std::endl;
            std::cout << "--FB                                  - Enable brave reasoning." << std::endl;
            std::cout << "--no-MS                               - Disable the Magic Sets rewriting." << std::endl;
//          std::cout << "--compact-facts                       - Assign the fact atom a unique index" << std::endl;
            std::cout << separator << std::endl;

            std::cout << "Statistics options                         " << std::endl << std::endl;
            std::cout << "--time                                - Print the grounding time of each rule." << std::endl;
            std::cout << "--gstats                              - Display grounding statistics." << std::endl;
            std::cout << separator << std::endl;

//            std::cout << "DB options                             " << std::endl << std::endl;
//            std::cout << "--db-source=[db_name]                  - Set the name of the database where input data are stored." << std::endl;
//            std::cout << "--db-user=[db_username]                - Set the username to have access to the database." << std::endl;
//            std::cout << "--db-pwd=[db_password]                 - Set the password to have access to the database." << std::endl;
//            std::cout << separator << std::endl;
            
            std::cout << "General options                     " << std::endl << std::endl;
            std::cout << "--help                                - Print this guide and exit." << std::endl;
            std::cout << "--stdin                               - Read input from standard input." << std::endl;
            std::cout << separator << std::endl;
        }
    };

};

#endif /* HELP_H */

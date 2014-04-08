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
using namespace std;
#include "Constants.h"

class Help
{
public:
    static void printHelp( const char* exec )
    {
        string separator = "\n---------------------------\n";

        cout << DLV2_STRING << endl;
        cout << "usage: " << exec << " {OPTIONS} [filename [filename [...]]]" << endl;
        cout << separator << endl;

        cout << "Input options                         " << endl << endl;
        cout << "--aspcore2strict                       - Enable \"strict\" AspCore2 format as input." << endl;
        cout << "--inmemory                             - Enable the input builder for the in-memory version. (default choice)" << endl;
        cout << "--dlv-db                               - Enable the input builder for the DB-based version." << endl;
        cout << separator << endl;
            
        cout << "Output options                         " << endl << endl;
        cout << "--silent                               - Suppress the startup banner and blank lines." << endl;
        cout << "--printprogram                         - Enable the input builder for mock objects, print the input program and exit." << endl;
        cout << separator << endl;

        cout << "General options                     " << endl << endl;
        cout << "--help                                 - Print this guide and exit." << endl;
        cout << "--stdin                                - Read input from standard input." << endl;
    }
};

#endif /* HELP_H */
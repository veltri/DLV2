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
 * File:   Options.h
 * Author: cesco
 *
 * Created on 4 aprile 2014, 12.52
 */

#ifndef OPTIONS_H
#define	OPTIONS_H

#include <vector>

#include "Constants.h"
using namespace std; 

class DLV2Facade;

namespace dlv2
{

    class Options{
    public:
        static void parse( int argc, char* const* argv );
        static void setOptions( DLV2Facade& dlv2Facade );
        
    private:      
        static bool aspCore2Strict;
        
        static bool printProgram;
        
        static INPUT_HANDLING_POLICY inputPolicy;
        
        static OUTPUT_POLICY outputPolicy;
        
        static vector< const char* > inputFiles;
    };
};

#endif	/* OPTIONS_H */
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
#include <stddef.h>

#include "Constants.h"
using namespace std; 

class DLV2Facade;

namespace dlv2
{

    class Options{
    public:

        void init( int argc, char* const* argv );

        static Options* globalOptions() {
        	if( instance == NULL )
        	{
        		instance = new Options();
        	}
        	return instance;
        }

        bool isAspCore2Strict() const { return aspCore2Strict; }

        const vector<const char*>& getInputFiles() const { return inputFiles; }

        INPUT_BUILDER_POLICY inputBuilderPolicy() const { return inputPolicy; }

        OUTPUT_POLICY getOutputPolicy() const { return outputPolicy; }

        ~Options() { if (instance != NULL) delete instance; }

    private:

        static Options* instance;

        Options() : aspCore2Strict(false), printProgram(false),
                    inputPolicy( BUILDER_IN_MEMORY),
                    outputPolicy( OUTPUT_ASPCORE2) {}

        Options(const Options& o) : aspCore2Strict(o.aspCore2Strict),
        		    printProgram(o.printProgram),
                    inputPolicy( o.inputPolicy),
                    outputPolicy( o.outputPolicy) {}

        void setOutputPolicy(OUTPUT_POLICY outPolicy) { outputPolicy = outPolicy; }

        void setInputBuilderPolicy(INPUT_BUILDER_POLICY inPolicy) { inputPolicy = inPolicy; }

        void setInputFiles(const vector<const char*>& inFiles) { inputFiles = inFiles; }

        void setAspCore2Strict(bool strict) { aspCore2Strict = strict;	}

        vector< const char* > inputFiles;

        bool aspCore2Strict;
        
        bool printProgram;
        
        INPUT_BUILDER_POLICY inputPolicy;
        
        OUTPUT_POLICY outputPolicy;
        
    }; // class
}; // namespace

#endif	/* OPTIONS_H */

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
 * File:   DLV2Facade.h
 * Author: cesco
 *
 * Created on 4 aprile 2014, 18.50
 */

#ifndef DLV2FACADE_H
#define	DLV2FACADE_H

#include "util/Options.h"
#include "input/InputDirector.h"

namespace DLV2
{
    // TODO: discuss the issue of options and facade methods

    class DLV2Facade {
    public:
        DLV2Facade() : options(*Options::globalOptions()), builder(NULL), parserDuration(0) { }
        ~DLV2Facade();

        void parseOptions( int, char* const* );
        void greetings();
        int readInput();
        void solve();

        Options& getOptions() { return options; }

    private:

        Options& options;

        InputDirector director;
        InputBuilder* builder;
        
        double parserDuration;

    }; 
    
}; 

#endif	/* DLV2FACADE_H */


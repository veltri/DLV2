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
 * File:   InputClassCheckingStrategy.h
 * Author: pierfrancesco
 *
 * Created on 04 novembre 2014, 13.44
 */

#ifndef INPUTCLASSCHECKINGSTRATEGY_H
#define INPUTCLASSCHECKINGSTRATEGY_H

#include "../data/XProgram.h"

namespace DLV2{ namespace REWRITERS{

    class InputClassCheckingStrategy {
    public:
        InputClassCheckingStrategy( const XProgram& p ): program(p) { }
        virtual ~InputClassCheckingStrategy() { }

        virtual bool check() = 0;

    protected:
        const XProgram& program;

    };

};};


#endif /* INPUTCLASSCHECKINGSTRATEGY_H */

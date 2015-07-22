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
 * File:   XParallelRuleset.h
 * Author: pierfrancesco
 *
 * Created on 17 luglio 2015, 17.31
 */

#ifndef XPARALLELRULESET_H
#define XPARALLELRULESET_H

#include "XProgram.h"

namespace DLV2{ namespace REWRITERS{

    class XParallelRuleset {
    public:
        XParallelRuleset( const XProgram& inputProgram ): program(inputProgram) { }
        virtual ~XParallelRuleset() { }

        virtual bool hasNext() = 0;
        virtual const XRule& next() = 0;
        virtual const size_t size() const = 0;
        virtual void reset() = 0;

    protected:
        const XProgram& program;

    };

};};

#endif /* XPARALLELRULESET_H */

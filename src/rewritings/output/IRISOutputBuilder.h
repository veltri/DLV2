/*  Copyright 2014 Mario Alviano, Carmine Dodaro, Francesco Ricca and
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
 * File:   IRISOutputBuilder.h
 * Author: cesco
 *
 * Created on 18 maggio 2015, 18.12
 */

#ifndef IRISOUTPUTBUILDER_H
#define IRISOUTPUTBUILDER_H

#include "../data/XRule.h"

#include <string>
#include <vector>

namespace DLV2{ namespace REWRITERS{

    class IRISOutputBuilder {
    public:
        IRISOutputBuilder( const XProgram& inputProgram ): input(inputProgram) { }
        ~IRISOutputBuilder() { }

        std::string toString() const;

    private:
        void bubbleSort( const XRule& rule, std::vector< unsigned >& headPos, std::vector< unsigned >& bodyPos ) const;

        const XProgram& input;

    };

};};

#endif /* IRISOUTPUTBUILDER_H */

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
 * File:   ParserConstraintDatalogPM.h
 * Author: pierfrancesco
 *
 * Created on 24 ottobre 2014, 17.51
 */

#ifndef PARSERCONSTRAINTDATALOGPM_H_
#define PARSERCONSTRAINTDATALOGPM_H_

#include "../../input/ParserConstraint.h"

namespace DLV2{ namespace REWRITERS{

    class ParserConstraintDatalogPM: public ParserConstraint {
    public:
        ParserConstraintDatalogPM() {}
        virtual ~ParserConstraintDatalogPM() {}

        inline virtual void rangeFacts() {}
        inline virtual void directives() {}
        inline virtual void conjunctiveHeads() {}
    };

};};

#endif /* PARSERCONSTRAINTDATALOGPM_H_ */

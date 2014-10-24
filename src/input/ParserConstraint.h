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
 * File:   ParserConstraint.h
 * Author: cesco
 *
 * Created on 12 maggio 2014, 18.32
 */

#ifndef PARSERCONSTRAINT_H
#define	PARSERCONSTRAINT_H

#include "../util/Options.h"
#include "../util/ErrorMessage.h"

namespace DLV2
{

    class ParserConstraint {
    public:
        ParserConstraint() {}
        virtual ~ParserConstraint() {}
        
        inline virtual void rangeFacts() {}
        inline virtual void directives() {}
        inline virtual void conjunctiveHeads();
    };
    
};

void
DLV2::ParserConstraint::conjunctiveHeads()
{
    DLV2::ErrorMessage::errorDuringParsing("conjunctive heads are not in the DLV2.0 standard! Use --datalogpm option");
}

#endif	/* PARSERCONSTRAINT_H */


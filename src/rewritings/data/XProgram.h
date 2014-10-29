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
 * File:   XProgram.h
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 19.23
 */

#ifndef XPROGRAM_H
#define XPROGRAM_H

#include <vector>
#include "XPredicateNames.h"

namespace DLV2{ namespace REWRITERS{

    class XProgram {
    public:
        XProgram() {}
        ~XProgram() {}

        const XPredicateNames& getPredicateNamesTable() const { return predicates; }

    private:
        XPredicateNames predicates;

    };

};};


#endif /* XPROGRAM_H */

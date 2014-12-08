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
 * File:   IsomorphismCheckStrategy.h
 * Author: pierfrancesco
 *
 * Created on 14 novembre 2014, 16.00
 */

#ifndef ISOMORPHISMCHECKSTRATEGY_H
#define ISOMORPHISMCHECKSTRATEGY_H

#include "../data/XIterableMap.h"
#include "../data/XProgram.h"

namespace DLV2{ namespace REWRITERS{

    class IsomorphismCheckStrategy {
    public:
        IsomorphismCheckStrategy( const XProgram& p ): program(p) { }
        virtual ~IsomorphismCheckStrategy() { }

        virtual std::pair< XMapping*, bool > areIsomorphic(
                const XRule& rule1,
                const XRule& rule2 ) = 0;
//        virtual std::pair< XMapping*, bool > isHomomorphicTo(
//                const std::vector< XAtom >& atomsLeftSide,
//                const std::vector< XAtom >& atomsRightSide ) = 0;
        virtual std::pair< const XMapping*, bool > areUnifiable(
                const std::vector< XAtom >& atoms1,
                const XRule& rule1,
                const std::vector< XAtom >& atoms2,
                const XRule& rule2 ) = 0;

    protected:
        const XProgram& program;

    };

};};

#endif /* ISOMORPHISMCHECKSTRATEGY_H */

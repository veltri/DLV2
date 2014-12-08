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
 * File:   DLVXFacade.h
 * Author: pierfrancesco
 *
 * Created on 03 novembre 2014, 18.44
 */

#ifndef DLVXFACADE_H
#define DLVXFACADE_H

#include "data/XProgram.h"
#include "input/StickyJoinCheckingStrategy.h"

namespace DLV2{ namespace REWRITERS{

    class DLVXFacade {
    public:
        DLVXFacade( XProgram& p, XAtom* q ): program(p), query(q), inputClassChecker(new StickyJoinCheckingStrategy(p)) { }
        ~DLVXFacade() { assert( inputClassChecker != NULL ); delete inputClassChecker; }

        void solve();

    private:
        XProgram& program;
        XAtom* query;

        InputClassCheckingStrategy* inputClassChecker;

    };

};};


#endif /* DLVXFACADE_H */

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
 * File:   DLVDBFacade.h
 * Author: pierfrancesco
 *
 * Created on 23 agosto 2014, 17.41
 */

#ifndef DLVDBFACADE_H
#define	DLVDBFACADE_H

#include "data/DBProgram.h"
#include "../depgraph/LabeledDependencyGraph.h"
#include "../util/DBConnection.h"

namespace DLV2{ namespace DB{

    class DLVDBFacade {
    public:
        DLVDBFacade( DBProgram& p, DBConnection& con );
        ~DLVDBFacade() { }
        
        void solve();
        
    private:
        DBProgram& program;
        DBConnection& connection;
    };

};};

#endif	/* DLVDBFACADE_H */


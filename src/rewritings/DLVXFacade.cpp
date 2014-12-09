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
 * File:   DLVXFacade.cpp
 * Author: pierfrancesco
 *
 * Created on 03 novembre 2014, 18.44
 */

#include "DLVXFacade.h"

using namespace std;
using namespace DLV2::REWRITERS;

void
DLVXFacade::solve()
{
    // TODO
    cout << program << endl;
    if( program.getQuery() != NULL )
        cout << *program.getQuery() << endl;
    if( inputClassChecker->check() )
        cout << "Sticky join" << endl;
    else
        cout << "Not Sticky join" << endl;
}

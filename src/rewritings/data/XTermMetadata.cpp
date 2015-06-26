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
 * File:   XTermMetadata.cpp
 * Author: pierfrancesco
 *
 * Created on 05 novembre 2014, 15.40
 */

#include "XTermMetadata.h"

using namespace std;
using namespace DLV2::REWRITERS;

XTermMetadata::XTermMetadata(
    const XTermMetadata& meta ):
        term(meta.term),
        nHeadOccurrences(meta.nHeadOccurrences),
        nBodyOccurrences(meta.nBodyOccurrences),
        stickyMarked(meta.stickyMarked),
        headPositions(meta.headPositions),
        bodyPositions(meta.bodyPositions)
{
}

XTermMetadata::XTermMetadata(
    const XTerm& t ):
        term(t),
        nHeadOccurrences(0),
        nBodyOccurrences(0),
        stickyMarked(false),
        headPositions(),
        bodyPositions()
{

}

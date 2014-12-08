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
 * File:   XStickyTermMetadata.h
 * Author: pierfrancesco
 *
 * Created on 05 novembre 2014, 15.25
 */

#ifndef XSTICKYTERMMETADATA_H
#define XSTICKYTERMMETADATA_H

#include <vector>
#include "XTerm.h"
#include "../../util/Constants.h"

namespace DLV2{ namespace REWRITERS{

    class XStickyTermMetadata {
    public:
        XStickyTermMetadata( const XStickyTermMetadata& meta );

        const std::vector< XStickyCoordinates >& getHeadPositions() const { return headPositions; }
        const std::vector< XStickyCoordinates >& getBodyPositions() const { return bodyPositions; }
        unsigned getHeadOccurrences() const { return nHeadOccurrences; }
        unsigned getBodyOccurrences() const { return nBodyOccurrences; }
        bool isMarked() const { return marked; }
        void setMarked( bool isMarked ) { this->marked = isMarked; }

        const XTerm& getTerm() const { return term; }

    private:
        friend class XStickyExpandedRule;

        XStickyTermMetadata( const XTerm& t );
        void incrementHeadOccurrences() { nHeadOccurrences++; }
        void incrementBodyOccurrences() { nBodyOccurrences++; }
        void addHeadPosition( const XStickyCoordinates& headPosition ) { this->headPositions.push_back(headPosition); }
        void addBodyPosition( const XStickyCoordinates& bodyPosition ) { this->bodyPositions.push_back(bodyPosition); }

        XTerm term;
        unsigned nHeadOccurrences;
        unsigned nBodyOccurrences;
        bool marked;
        std::vector< XStickyCoordinates > headPositions;
        std::vector< XStickyCoordinates > bodyPositions;

    };

};};


#endif /* XSTICKYTERMMETADATA_H */

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
 * File:   XTermMetadata.h
 * Author: pierfrancesco
 *
 * Created on 05 novembre 2014, 15.25
 */

#ifndef XTERMMETADATA_H
#define XTERMMETADATA_H

#include <vector>
#include "XTerm.h"
#include "../../util/Constants.h"

namespace DLV2{ namespace REWRITERS{

    class XTermMetadata {
    public:
        XTermMetadata( const XTermMetadata& meta );

        const std::vector< XCoordinates >& getHeadPositions() const { return headPositions; }
        const std::vector< XCoordinates >& getBodyPositions() const { return bodyPositions; }
        unsigned getHeadOccurrences() const { return nHeadOccurrences; }
        unsigned getBodyOccurrences() const { return nBodyOccurrences; }
        bool isStickyMarked() const { return stickyMarked; }
        void setStickyMarked( bool isMarked ) { this->stickyMarked = isMarked; }

        const XTerm& getTerm() const { return term; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XTermMetadata& );

        friend class XRule;
        friend class XProgram;

        XTermMetadata( const XTerm& t );
        void incrementHeadOccurrences() { nHeadOccurrences++; }
        void incrementBodyOccurrences() { nBodyOccurrences++; }
        void addHeadPosition( const XCoordinates& headPosition ) { this->headPositions.push_back(headPosition); }
        void addBodyPosition( const XCoordinates& bodyPosition ) { this->bodyPositions.push_back(bodyPosition); }

        XTerm term;
        unsigned nHeadOccurrences;
        unsigned nBodyOccurrences;
        bool stickyMarked;
        std::vector< XCoordinates > headPositions;
        std::vector< XCoordinates > bodyPositions;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XTermMetadata& tm )
    {
        out << "Term: " << tm.term << std::endl;
        out << "Head positions: ";
        for( unsigned i=0; i<tm.headPositions.size(); i++ )
            out << "[" << tm.headPositions[i].atomPos << "," << tm.headPositions[i].termPos << "]" << std::endl;
        out << std::endl << "Body positions: ";
        for( unsigned i=0; i<tm.bodyPositions.size(); i++ )
            out << "[" << tm.bodyPositions[i].atomPos << "," << tm.bodyPositions[i].termPos << "]" << std::endl;
        out << std::endl;
        return out;
    }
};};


#endif /* XTERMMETADATA_H */

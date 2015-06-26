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
 * File:   XPieceUnifier.h
 * Author: pierfrancesco
 *
 * Created on 31 gennaio 2015, 13.40
 */

#ifndef XPIECEUNIFIER_H
#define XPIECEUNIFIER_H

#include <vector>
#include <unordered_set>
#include "XRule.h"
#include "XPartition.h"

namespace DLV2{ namespace REWRITERS{

    class XPieceUnifier {
    public:
        XPieceUnifier( const XPieceUnifier& unifier );
        ~XPieceUnifier();

        const std::vector< XAtom >& getSubQuery() const { return subQuery; }
        const std::vector< XAtom >& getSubHead() const { return subHead; }
        XPartition& getPartition() const { assert_msg( partition != NULL, "Null partition" ); return *partition; }
        const XRule& getQuery() const { return originalQuery; }
        const XRule& getRule() const { return originalRule; }
        const std::unordered_set< XTerm >& getStickyVariables();
        const std::unordered_set< unsigned >& getSubQueryAtomPositions() const { return subQueryAtomPositions; }
        bool isThisSubQueryDisjointWith( const XPieceUnifier& p ) const;
        void extendThisIsNotSinglePiece(
            const std::vector< XAtom >& subQ,
            const std::vector< XAtom >& subH,
            const std::unordered_set< unsigned >& subQueryPos );

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XPieceUnifier& );
        friend class XProgram;

        XPieceUnifier(
            const std::vector< XAtom >& q,
            const std::vector< XAtom >& h,
            XPartition* p,
            const XRule& query,
            const XRule& rule,
            const std::unordered_set< unsigned >& subQueryPos );

        std::vector< XAtom > subQuery;
        std::vector< XAtom > subHead;
        XPartition* partition;

        const XRule& originalQuery;
        const XRule& originalRule;
        // These informations are necessary to compute the set of sticky variables.
        std::unordered_set< unsigned > subQueryAtomPositions;
        std::unordered_set< XTerm > stickyVariables;
        bool stickyVariablesComputed;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XPieceUnifier& p )
    {
        out << "<Q':{";
        for( unsigned i=0; i<p.subQuery.size(); i++ )
        {
            out << p.subQuery[i];
            if( i < p.subQuery.size()-1 )
                out << ",";
        }
        out << "},H':{";
        for( unsigned i=0; i<p.subHead.size(); i++ )
        {
            out << p.subHead[i];
            if( i < p.subHead.size()-1 )
                out << ",";
        }
        out << "},P:" << *(p.partition) << ">";
        return out;
    }

};};

#endif /* XPIECEUNIFIER_H */

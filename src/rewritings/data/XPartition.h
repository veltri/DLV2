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
 * File:   XPartition.h
 * Author: pierfrancesco
 *
 * Created on 09 gennaio 2015, 17.38
 */

#ifndef XPARTITION_H
#define XPARTITION_H

#include <list>
#include <unordered_set>
#include "XEquivalenceClass.h"

namespace DLV2{ namespace REWRITERS{

    class XPartition {
    public:
        XPartition( const XPartition& );
        ~XPartition() { }

        bool isValid() const;
        void addEquivalence( const XTerm& term1, const XTermType& typeTerm1, const XTerm& term2, const XTermType& typeTerm2 );
        void merge( const XPartition& partition );
        void mergePartitionToBeRenamed( const XPartition& partitionToBeRenamed, const XMapping& renaming );
        const XTerm& getMapping( const XTerm& termToBeMapped );
        bool isPartitionedWithAnExistentialVariable( const XTerm& term ) const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XPartition& );
        friend class XProgram;

        XPartition( XProgram& p );

        XProgram& program;
        std::list< XEquivalenceClass > classes;
        typedef std::unordered_map< XTerm, typename std::list< XEquivalenceClass >::iterator > XPartitionMap;
        XPartitionMap substitution;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XPartition& p )
    {
        out << "{";
        unsigned counter = 0;
        for( std::list< DLV2::REWRITERS::XEquivalenceClass >::const_iterator it = p.classes.begin();
                it != p.classes.end();
                it++, counter++ )
        {
            out << *it;
            if( counter < p.classes.size()-1 )
                out << ",";
        }
        out << "}";
        return out;
    }

};};

#endif /* XPARTITION_H */

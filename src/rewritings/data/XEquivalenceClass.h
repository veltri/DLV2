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
 * File:   XEquivalenceClass.h
 * Author: pierfrancesco
 *
 * Created on 08 gennaio 2015, 17.26
 */

#ifndef XEQUIVALENCECLASS_H
#define XEQUIVALENCECLASS_H

#include <unordered_set>
#include <vector>
#include "XTerm.h"
#include "XProgram.h"

namespace DLV2{ namespace REWRITERS{

    class XEquivalenceClass {
    public:
        typedef typename std::unordered_map< XTerm, typename std::list< XEquivalenceClass >::iterator >::iterator XPartitionMapIterator;

        XEquivalenceClass( const XEquivalenceClass& );
        ~XEquivalenceClass();

        void pushTerm( const XPartitionMapIterator& termIt, const XTermType& termType );
        void merge( const XEquivalenceClass& eq );
        bool isValid() const;
        const XTerm& getRepresentativeTerm();

        const std::vector< XPartitionMapIterator >& getStandardVars() const { return standardVars; }
        const std::vector< XPartitionMapIterator >& getFrontierVars() const { return frontierVars; }
        const std::vector< XPartitionMapIterator >& getExistentialVars() const { return existentialVars; }
        const std::vector< XPartitionMapIterator >& getConstants() const { return constants; }
        const XPartitionMapIterator& at( index_t index ) const;
        XTermType typeOfElementAt( index_t index ) const;
        size_t size() const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XEquivalenceClass& );
        friend class XProgram;

        XEquivalenceClass( XProgram& p );

        XProgram& program;
        XTerm* representativeTerm;
        std::vector< XPartitionMapIterator > standardVars;
        std::vector< XPartitionMapIterator > frontierVars;
        std::vector< XPartitionMapIterator > existentialVars;
        std::vector< XPartitionMapIterator > constants;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XEquivalenceClass& c )
    {
        out << "{";
        for( unsigned i=0; i<c.size(); i++ )
        {
            out << c.at(i)->first;
            if( i < c.size()-1 )
                out << ",";
        }
        out << "}";
        return out;
    }

};};

#endif /* XEQUIVALENCECLASS_H */

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
 * File:   DBLiteral.h
 * Author: pierfrancesco
 *
 * Created on 29 luglio 2014, 16.15
 */

#ifndef DBLITERAL_H
#define	DBLITERAL_H

#include "DBAtom.h"
#include "DBAggregateElement.h"

namespace DLV2{ namespace DB{
    
    class DBLiteral {
    public:
        DBLiteral( const DBLiteral& l );
        ~DBLiteral();

        DBAtom* getAtom() const { return atom; }
        bool isNaf() const { return isNegative; }
        bool isBuiltin() const;
        bool isAggregate() const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBLiteral& );
        friend class DBProgram;
        
        // Only class Program can create Literal objects.
        // Classic literal constructor
        DBLiteral( DBAtom* a, bool neg = false );
        void setIsNaf( bool isNaf ) { isNegative = isNaf; }
        
        DBAtom* atom;
        bool isNegative;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const DBLiteral& l )
    {
        if( l.isNegative )
                out << "not ";
        assert_msg( l.atom != NULL, "Invalid literal: null atom!");
        out << *(l.atom);
        return out;
    }

};};

#endif	/* DBLITERAL_H */


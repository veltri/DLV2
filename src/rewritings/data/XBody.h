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
 * File:   XBody.h
 * Author: pierfrancesco
 *
 * Created on 28 ottobre 2014, 17.13
 */

#ifndef XBODY_H
#define XBODY_H

#include "XRandomAccessSet.h"
#include "XLiteral.h"

namespace DLV2{ namespace REWRITERS{

    class XBody {
    public:
        XBody( const XBody& body ): literals(body.literals) { }
        virtual ~XBody() { }

        size_t size() const { return literals.size(); }
        const XLiteral& operator[]( index_t index ) const { return literals[index]; }
        const XLiteral& at( index_t index ) const { return literals.at(index); }
        bool isGround() const;
        bool pushLiteral( const XLiteral& literal ) { return literals.pushItem(literal); }
        bool popLiteral() { return literals.popItem(); }
        bool insertLiteral( index_t pos, const XLiteral& literal ) { return literals.insertItem(pos,literal); }
        bool removeLiteral( unsigned position ) { return literals.removeItem(position); }
        bool findLiteral( const XLiteral& literal ) { return literals.find(literal); }
        void clear() { literals.clear(); }

    protected:
        XRandomAccessSet< XLiteral > literals;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XBody& );
        friend class XProgram;

        XBody(): literals() { }
        XBody( const XRandomAccessSet< XLiteral >& literals2 ): literals(literals2) { }
        XBody( const std::vector< XLiteral >& literals2 ): literals(literals2) { }

    };

    inline
    std::ostream& operator<< (
        std::ostream& out,
        const XBody& body )
    {
        for( unsigned i=0; i<body.size(); i++ )
        {
            out << body[i];
            if( i < body.size()-1 )
                out << " , ";
        }
        out << ".";
        return out;
    }

};};


#endif /* XBODY_H */

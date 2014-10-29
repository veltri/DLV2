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
 * File:   XRule.h
 * Author: pierfrancesco
 *
 * Created on 29 ottobre 2014, 15.48
 */

#ifndef XRULE_H
#define XRULE_H

#include "XBody.h"

namespace DLV2{ namespace REWRITERS{

    class XHead;

    class XRule {
    public:
        XRule( const XRule& rule );
        ~XRule();

        XHead* const getHead() const { return head; }
        XBody* const getBody() const { return body; }
        bool hasNegation();
        bool hasAtomicHead() const;
        bool hasDisjunctiveHead() const;
        bool hasConjunctiveHead() const;
        bool isRecursive() const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XRule& );
        friend class XProgram;

        XRule(): head(NULL), body(NULL), naf(false), recursion(false) { assert(0); }
        XRule( XHead* head, XBody* body );
        // The recursive flag could be set after that the dependency graph
        // has been computed, hence after the creation of the rule itself.
        void setRecursive( bool rec ) { recursion = rec; }

        XHead* head;
        XBody* body;
        int naf;
        int recursion;

    };

};};

#endif /* XRULE_H */

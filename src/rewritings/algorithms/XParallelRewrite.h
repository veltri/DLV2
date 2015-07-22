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
 * File:   XParallelRewrite.h
 * Author: pierfrancesco
 *
 * Created on 26 giugno 2015, 18.27
 */

#ifndef XPARALLELREWRITE_H
#define XPARALLELREWRITE_H

#include "XRewrite.h"

namespace DLV2{ namespace REWRITERS{

    class XParallelRuleset;

    class XParallelRewrite: public XRewrite {
    public:
        XParallelRewrite( XProgram& input ): XRewrite(input), queryPredIdx(0) { }
        virtual ~XParallelRewrite() { }

        virtual std::vector< XRule* > rewrite();

    private:
        void rewriteQueries( const std::vector< XRule* >& queries, XParallelRuleset* rulesetIterator, std::vector< XRule* >& output );
        void rewriteAtomicQuery( const XRule& query, XParallelRuleset* rulesetIterator, std::vector< XRule* >& output );
        void rewriteConjunctiveQuery( const XRule& query, XParallelRuleset* rulesetIterator, std::vector< XRule* >& output );
        bool isBreakable( const XRule& query ) const;

        unsigned queryPredIdx;
    };

};};

#endif /* XPARALLELREWRITE_H */

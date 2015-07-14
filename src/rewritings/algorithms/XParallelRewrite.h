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

    class XParallelRewrite: public XRewrite {
    public:
        XParallelRewrite( XProgram& input ): XRewrite(input) { }
        virtual ~XParallelRewrite() { }

        virtual std::vector< XRule* > rewrite();

    private:
        std::vector< XRule* > rewriteAtomicQuery( std::vector< XProgram::const_iterator > rules, const XRule& query );
        std::vector< XRule* > rewriteConjunctiveQuery( std::vector< XProgram::const_iterator > rules, const XRule& query );
    };

};};

#endif /* XPARALLELREWRITE_H */

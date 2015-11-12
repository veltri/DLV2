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
 * File:   XQuery.h
 * Author: pierfrancesco
 *
 * Created on 01 ottobre 2015, 20.39
 */

#ifndef XQUERY_H
#define XQUERY_H

#include "XRule.h"
#include "XRandomAccessSet.h"

#include "../../util/Assert.h"

namespace DLV2{ namespace REWRITERS{

    class XQuery {
    public:
        XQuery( const XQuery& q ): query(q.query), sharedNulls(q.sharedNulls) { }
        ~XQuery() { }

        bool isAtomic() const { assert_msg( (query != NULL && query->getBody() != NULL) , "Not valid query" ); return query->getBody()->size() == 1; }
        bool isConjunctive() const { return !isAtomic(); }
        XRule* getQueryRule() const { return query; }
        const XRandomAccessSet< index_t >& getSharedNulls() const { return sharedNulls; }

    private:
        friend class XProgram;

        XQuery( XRule* qRule, const XRandomAccessSet< index_t >& sNulls ): query(qRule), sharedNulls(sNulls) { }

        XRule* query;
        XRandomAccessSet< index_t > sharedNulls;

    };

};};


#endif /* XQUERY_H */

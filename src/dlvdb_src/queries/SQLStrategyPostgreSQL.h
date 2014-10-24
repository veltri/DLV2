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
 * File:   SQLStrategyPostgreSQL.h
 * Author: pierfrancesco
 *
 * Created on 22 ottobre 2014, 16.19
 */

#ifndef SQLSTRATEGYPOSTGRESQL_H_
#define SQLSTRATEGYPOSTGRESQL_H_

#include "SQLStrategy.h"

namespace DLV2{ namespace DB{

    class SQLStrategyPostgreSQL: public SQLStrategy {
    public:
        SQLStrategyPostgreSQL( DBProgram* program ): SQLStrategy(program) { }
        SQLStrategyPostgreSQL( const SQLStrategyPostgreSQL& ss ): SQLStrategy(ss.program) { }
        virtual ~SQLStrategyPostgreSQL() { }

    private:
        virtual void getRuleInSQL( std::string& sqlOutput ) const;
        virtual void getFactInSQL( std::string& sqlOutput ) const;

    };

};};

#endif /* SQLSTRATEGYPOSTGRESQL_H_ */

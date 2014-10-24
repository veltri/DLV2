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
 * File:   SQLStrategy.h
 * Author: pierfrancesco
 *
 * Created on 22 ottobre 2014, 15.57
 */

#ifndef SQLSTRATEGY_H_
#define SQLSTRATEGY_H_

#include <unordered_map>
#include <vector>
#include <string>
#include "../data/DBProgram.h"
#include "../../util/Constants.h"

namespace DLV2{ namespace DB{

    class SQLStrategy {
    public:
        SQLStrategy( DBProgram* program );
        SQLStrategy( const SQLStrategy& );
        virtual ~SQLStrategy() { }

        void rewriteRule( const DBRule& rule, std::string& sqlOutput );
        void rewriteFact( const DBRule& fact, std::string& sqlOutput );

    protected:
        virtual void getRuleInSQL( std::string& sqlOutput ) const = 0;
        virtual void getFactInSQL( std::string& sqlOutput ) const = 0;

        virtual void rewriteNonRecursiveRule( const DBRule& rule );
        virtual void rewriteRecursiveRule( const DBRule& rule );
        virtual void rewritePositiveRule( const DBRule& rule );
        virtual void rewriteNegativeRule( const DBRule& rule );
        virtual void rewriteRuleWithBuiltins( const DBRule& rule );
        virtual void rewriteRuleWithAggregates( const DBRule& rule );

        virtual void addInHead( const DBAtom& headAtom );
        virtual void addInPositiveBody( const DBLiteral& literal );
        virtual void addInNegativeBody( const DBLiteral& literal );
        virtual void addAggregateInPositiveBody( const DBLiteral& aggregate );
        virtual void addAggregateInNegativeBody( const DBLiteral& aggregate );
        virtual void addBuiltin( const DBLiteral& builtin );
        virtual void reset();

        // Return the position where the predicate is going to be located.
        unsigned addSource( const DBAtom& sourceAtom );
        const std::string& getTableName( index_t predIndex ) const;
        std::string getTableAlias( unsigned pos ) const;
        const std::string& getAttributeName( unsigned predPos, unsigned termPos ) const;

        struct Coordinates {
            unsigned predPos;
            unsigned termPos;
        };
        typedef std::unordered_map< std::string, std::vector< Coordinates > > VariableMap;
        typedef std::pair< std::string, std::string > QCondition;

        // Each variable in a rule might appear in more than one location.
        VariableMap headVariablesMap;
        VariableMap bodyVariablesMap;
        // We can retrieve name and arity of a predicate only by its index.
        // There is a one-to-one correspondence between this vector and the vector
        // of source predicates in the current query object.
        std::vector< index_t > bodyPredicates;

        std::string targetTable;
        std::vector< std::string > attributesToSelect;
        std::vector< std::string > sourceTables;
        std::vector< QCondition > conditions;

        DBProgram* program;
    };

};};

#endif /* SQLSTRATEGY_H_ */

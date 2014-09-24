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
 * File:   QueryBuilder.h
 * Author: pierfrancesco
 *
 * Created on 19 agosto 2014, 16.35
 */

#ifndef QUERYBUILDER_H
#define	QUERYBUILDER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../../util/Constants.h"

namespace DLV2{ namespace DB{
    
    class QueryObject;
    class DBProgram;
    class DBRule;
    class DBLiteral;
    class DBAtom;
    class DBTerm;
    
    struct Coordinates {
        unsigned predPos;
        unsigned termPos;
    };
    typedef std::unordered_map< std::string, std::vector< Coordinates > > VariableMap;
    typedef std::pair< std::string, std::string > QCondition;
    
    class QueryBuilder {
    public:
        QueryBuilder( DBProgram* p );
        QueryBuilder( const QueryBuilder& qb );
        virtual ~QueryBuilder() { }
        
        /** This function dinamically instantiates a new query object
         * which should be retrieved by calling function getQueryObject;
         * the caller will be responsible of such an object's destruction.
         * @param rule The rule which is to be translated.
         */
        virtual void rewriteNonRecursiveRule( DBRule* rule );
        /** This function dinamically instantiates new query object
         * which should be retrieved by calling function getQueryObject;
         * the caller will be responsible of such an object's destruction.
         * @param rule The rule which is to be translated.
         */
        virtual void rewriteRecursiveRule( DBRule* rule );
        virtual void reset();
        
        virtual QueryObject* getQueryObject() { return query; }        
        virtual DBProgram* getProgram() const { return program; }
    
    protected:
        virtual void rewritePositiveRule( DBRule* rule );
        virtual void rewriteRuleWithNegation( DBRule* rule );
        virtual void rewriteRuleWithBuiltins( DBRule* rule );
        virtual void rewriteRuleWithAggregates( DBRule* rule );
        
        virtual void addInHead( DBAtom* headAtom );
        virtual void addInPositiveBody( DBLiteral* literal );
        virtual void addInNegativeBody( DBLiteral* literal );
        virtual void addAggregateInPositiveBody( DBLiteral* aggregate );
        virtual void addAggregateInNegativeBody( DBLiteral* aggregate );
        virtual void addBuiltin( DBLiteral* builtin );
        
        QueryObject* query;
        DBProgram* program;
        
    private:
        // Return the position where the predicate is going to be located.
        unsigned addSource( DBAtom* sourceAtom );
        const std::string& getTableName( index_t predIndex ) const;
        std::string getTableAlias( unsigned pos ) const;
        const std::string& getAttributeName( unsigned predPos, unsigned termPos ) const;
        
        // Each variable in a rule might appear 
        // in more than one location.
        VariableMap headVariablesMap;
        VariableMap bodyVariablesMap;
        // We can retrieve name and arity 
        // of a predicate only by its index.
        // There is a one-to-one correspondance between 
        // this vector and the vector of source predicates 
        // in the current query object.
        std::vector< index_t > bodyPredicates; 
    };

};};

#endif	/* QUERYBUILDER_H */


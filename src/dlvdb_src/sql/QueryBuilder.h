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

namespace DLV2{ namespace DB{
    
    class QueryObject;
    class DBProgram;
    class DBRule;
    class DBLiteral;
    class DBAtom;
    class DBTerm;
    
    struct COORDINATES {
        unsigned predIndex;
        unsigned termIndex;
    };
    typedef std::unordered_map<std::string,std::vector<COORDINATES>> VARIABLEMAP;
    typedef std::pair<std::string,std::string> QCondition;
    
    class QueryBuilder {
    public:
        QueryBuilder( DBProgram* p );
        virtual ~QueryBuilder() { }
        
        virtual void rewriteNonRecursiveRule( DBRule* rule );
        virtual void rewriteRecursiveRule( DBRule* rule );
        virtual void reset();
        
        virtual QueryObject* getQueryObject() { return query; }        
        virtual DBProgram* getProgram() const { return program; }
    
    protected:
        virtual void rewritePositiveRule( DBRule* rule );
        virtual void rewriteRuleWithNegation( DBRule* rule );
        virtual void rewriteRuleWithBuiltins( DBRule* );
        virtual void rewriteRuleWithAggregates( DBRule* );
        
        virtual void addInHead( DBAtom* headAtom );
        virtual void addInPositiveBody( DBLiteral* literal );
        virtual void addInNegativeBody( DBLiteral* literal );
        virtual void addAggregateInPositiveBody( DBLiteral* literal );
        virtual void addAggregateInNegativeBody( DBLiteral* literal );
        virtual void addBuiltin( DBLiteral* );
        
        QueryObject* query;
        DBProgram* program;
        
    private:
        unsigned addSourcePredicate( const std::string& predName );
        const std::string& getAttributeName( 
            const std::string& predName,
            unsigned termIndex );
        
        // Each variable in a rule could appear in more than one location.
        VARIABLEMAP headVariablesMap;
        VARIABLEMAP bodyVariablesMap;
    };

};};

#endif	/* QUERYBUILDER_H */


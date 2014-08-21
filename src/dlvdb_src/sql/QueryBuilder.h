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

namespace DLV2{ namespace DB{
    
    class QueryObject;
    class DBProgram;
    class DBRule;
    class DBAtom;
    class DBTerm;
    
    typedef std::pair<std::string,std::string> QCondition;
    
    class QueryBuilder {
    public:
        QueryBuilder( DBProgram* p );
        virtual ~QueryBuilder() { }
        
        virtual void rewriteNonRecursiveRule( DBRule* );
        virtual void rewriteRecursiveRule( DBRule* );
        
        virtual QueryObject* getQueryObject() { return query; }        
        virtual DBProgram* getProgram() const { return program; }
    
    protected:
        virtual void rewritePositiveRule( DBRule* );
        virtual void rewriteRuleWithNegation( DBRule* );
        //virtual void rewriteRuleWithBuiltins( DBRule* );
        //virtual void rewriteRuleWithAggregates( DBRule* );
        virtual void reset();
        
        QueryObject* query;
        DBProgram* program;
        
    private:
        bool occursVariable( DBAtom*, DBTerm* );
        void fillAttributesToSelect( DBRule* );
        void addSourcePredicate( const std::string& );
        
    };

};};

#endif	/* QUERYBUILDER_H */


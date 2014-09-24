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
 * File:   QueryObject.h
 * Author: pierfrancesco
 *
 * Created on 19 agosto 2014, 17.26
 */

#ifndef QUERYOBJECT_H
#define	QUERYOBJECT_H

#include "QueryBuilder.h"
#include "SQLBuilder.h"

namespace DLV2{ namespace DB{
    
    class QueryObject: public SQLBuilder{
    public:
        QueryObject( const QueryObject& );
        virtual ~QueryObject() { }
        
        SQLBuilder* getSQLBuilder() { return sqlBuilder; }
        void setSQLBuilder( SQLBuilder* );
        std::string* getSQL();
        
        const std::string& getTargetPredicate() const { return targetPredicate; }
        const std::vector< std::string >& getAttributesToSelect() const { return attributesToSelect; }
        const std::vector< std::string >& getSourcePredicates() const { return sourcePredicates; }
        const std::vector< QCondition >& getConditions() const { return conditions; }
        
    private:
        friend class QueryBuilder;

        QueryObject();
        
        virtual std::string* generateSQL( QueryObject* );
        
        SQLBuilder* sqlBuilder;
        std::string targetPredicate;
        std::vector< std::string > attributesToSelect;
        std::vector< std::string > sourcePredicates;
        std::vector< QCondition > conditions;
    };

};};

#endif	/* QUERYOBJECT_H */


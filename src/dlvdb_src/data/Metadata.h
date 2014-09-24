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
 * File:   Metadata.h
 * Author: pierfrancesco
 *
 * Created on 28 luglio 2014, 15.40
 */

#ifndef METADATA_H
#define	METADATA_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include "../../util/Constants.h"

namespace DLV2{ namespace DB{

    class Metadata {
    public:
        Metadata( const Metadata& );
        ~Metadata();
        
        index_t getPredicateIndex() const { return predIndex; }
        const std::string& getTableName() const;
        const std::string& getAttributeName( unsigned position ) const;
        unsigned getAttributePosition( const std::string& name ) const;
        //const std::string& getAttributeType( unsigned index ) const;
        
    private:
        friend class DBProgram;
        // Only class Program can create Metadata objects.
        Metadata() { }
        Metadata( index_t predIndex, std::string* tableName , std::vector< std::string >* attrs );
        friend inline std::ostream& operator<< ( std::ostream&, const Metadata& );
            
        index_t predIndex;
        std::string* tableName;
        std::vector< std::string >* attributeNames;
        std::unordered_map< std::string, unsigned > attributePositions;
        //std::vector<std::string> attributeTypes;
    };
    
    inline
    std::ostream&
    operator<<(
        std::ostream& out,
        const Metadata& m )
    {
        out << "Predicate index: " << m.predIndex << std::endl;
        out << "Actual table name: " << m.tableName << std::endl;
        for( unsigned i=0; i<m.attributeNames->size(); i++ )
            out << i << " --> " << m.attributeNames->at(i) << std::endl;
        return out;
    }
    
};};

#endif	/* METADATA_H */


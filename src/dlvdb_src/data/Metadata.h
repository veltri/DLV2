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

namespace DLV2{ namespace DB{

    class Metadata {
    public:
        Metadata( const Metadata& );
        ~Metadata() { delete attributeNames; }
        
        const std::string& getPredicateName() const { return predicateName; }
        unsigned getArity() const { return arity; }
        const std::string& getAttributeName( unsigned index ) const;
        unsigned getAttributeIndex( const std::string& name ) const;
        //const std::string& getAttributeType( unsigned index ) const;
        
    private:
        friend class DBProgram;
        // Only class Program can create Metadata objects.
        Metadata() { }
        Metadata( const std::string& pred, unsigned a, std::vector<std::string>* attrs );
        Metadata( char* pred, unsigned a, std::vector<std::string>* attrs );
        friend inline std::ostream& operator<< ( std::ostream&, const Metadata& );
            
        std::string predicateName;
        unsigned arity;
        std::vector<std::string>* attributeNames;
        std::unordered_map<std::string,unsigned> attributeIndexes;
        //std::vector<std::string> attributeTypes;
    };
    
    inline
    std::ostream&
    operator<<(
        std::ostream& out,
        const Metadata& m )
    {
        out << "Predicate: " << m.predicateName << std::endl;
        out << "Arity: " << m.arity << std::endl;
        for( unsigned i=0; i<m.attributeNames->size(); i++ )
            out << i << " --> " << m.attributeNames->at(i) << std::endl;
        return out;
    }
    
};};

#endif	/* METADATA_H */


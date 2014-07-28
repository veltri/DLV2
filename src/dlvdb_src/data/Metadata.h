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

namespace DLV2{ namespace DB{

    class Metadata {
    public:
        
        ~Metadata() { }
        
        bool pushAttribute( const std::string& name, const std::string& type );
        const std::string& getPredicateName() { return predicateName; }
        unsigned getArity() { return arity; }
        const std::string& getAttributeName( unsigned index );
        unsigned getAttributeIndex( const std::string& name );
        const std::string& getAttributeType( unsigned index );
        
    private:
        // Only class Program can create Metadata objects.
        Metadata() { }
        Metadata( const std::string& pred, unsigned a ): predicateName(pred), arity(a) { }
        //friend class Program;
        
        std::string predicateName;
        unsigned arity;
        std::vector<std::string> attributeNames;
        std::unordered_map<std::string,unsigned> attributeIndexes;
        std::vector<std::string> attributeTypes;
    };
    
};};

#endif	/* METADATA_H */


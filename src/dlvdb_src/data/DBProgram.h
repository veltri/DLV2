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
 * File:   Program.h
 * Author: pierfrancesco
 *
 * Created on 29 luglio 2014, 17.51
 */

#ifndef DBPROGRAM_H
#define	DBPROGRAM_H

#include "DBRule.h"
#include "Metadata.h"
#include "../../util/DBConnection.h"
#include <unordered_map>
#include <set>

namespace DLV2{ namespace DB{
    
    class DBProgram {
    public:
        typedef std::unordered_map<std::string,Metadata*> SCHEMAMAP;
        typedef std::unordered_map<std::string,std::set<unsigned>*> SUBPROGRAMSMAP;
        
        DBProgram( DBConnection& con ): connection(con) { }
        DBProgram( const DBProgram& p );
        ~DBProgram();

        DBTerm* createIntegerConstant( int val );
        DBTerm* createStringConstant( const std::string& val );
        DBTerm* createStringConstant( char* val );
        DBTerm* createVariable( const std::string& name );
        DBTerm* createVariable( char* name );
        DBAtom* createAtom( const std::string& predName, const std::vector<DBTerm*>& terms, bool tNeg=false );
        DBAtom* createAtom( char* predName, const std::vector<DBTerm*>& terms, bool tNeg=false );
        DBAtom* createBuiltinAtom( DBTerm* leftOp, const std::string& binop, DBTerm* rightOp );
        DBLiteral* createLiteral( DBAtom* a, bool naf=false );
        DBLiteral* createAggregateLiteral( DBTerm* lowerGuard, 
                                         const std::string& lowerBinop, 
                                         DBTerm* upperGuard, 
                                         const std::string& upperBinop, 
                                         const std::string& aggregateFunction, 
                                         const std::vector<DBAggregateElement*>& aggregateSet, 
                                         bool isNegative = false );
        DBAggregateElement* createAggregateElement( const std::vector<DBTerm*>& terms, const std::vector<DBLiteral*>& lits );
        DBRule* createRule( const std::vector<DBAtom*>& head, const std::vector<DBLiteral*>& body );
        void createAndAddRule( const std::vector<DBAtom*>& head, const std::vector<DBLiteral*>& body );
        void addRule( DBRule* r );
        bool addPredicateName( const std::string& name, unsigned arity );
        bool addToPredicateSubProgram( const std::string& name, unsigned arity, unsigned ruleIndex );
        
        const std::vector<DBRule*>& getRules() const { return rules; }
        const SCHEMAMAP& getMapSchema() const { return schemaMapping; }
        Metadata* getMetadata( const std::string& predName );
        const SUBPROGRAMSMAP& getMapSubPrograms() const { return subProgramsMapping; }
        std::set<unsigned>* getSubProgram( const std::string& predName );

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const DBProgram& );
        DBConnection& getDBConnection() { return connection; }

        std::vector<DBRule*> rules;
        SCHEMAMAP schemaMapping;
        SUBPROGRAMSMAP subProgramsMapping;
        
        DBConnection& connection;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const DBProgram& p )
    {
        for( unsigned i=0; i<p.rules.size(); i++ )
        {
            if( p.rules[i] != NULL )
                out << *(p.rules[i]) << std::endl;
        }
        out << std::endl;
        for( DBProgram::SCHEMAMAP::const_iterator it = p.schemaMapping.begin();
                it != p.schemaMapping.end();
                it++ )
        {
            if( it->second != NULL )
                out << *(it->second) << std::endl;
        }
        return out;
    }

};};

#endif	/* DBPROGRAM_H */


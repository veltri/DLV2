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

#ifndef PROGRAM_H
#define	PROGRAM_H

#include "Rule.h"
#include "../../util/DBConnection.h"
#include <unordered_map>
#include <set>

namespace DLV2{ namespace DB{
    
    class Metadata;
    
    class Program {
    public:
        typedef std::unordered_map<std::string,Metadata*> SCHEMAMAP;
        typedef std::unordered_map<std::string,std::set<unsigned>*> SUBPROGRAMSMAP;
        
        Program( DBConnection& con ): connection(con) { }
        Program( const Program& p );
        ~Program();

        Term* createIntegerConstant( int val );
        Term* createStringConstant( const std::string& val );
        Term* createStringConstant( char* val );
        Term* createVariable( const std::string& name );
        Term* createVariable( char* name );
        Atom* createAtom( const std::string& predName, const std::vector<Term*>& terms, bool tNeg=false );
        Atom* createAtom( char* predName, const std::vector<Term*>& terms, bool tNeg=false );
        Atom* createBuiltinAtom( Term* leftOp, const std::string& binop, Term* rightOp );
        Literal* createLiteral( Atom* a, bool naf=false );
        Literal* createAggregateLiteral( Term* lowerGuard, 
                                         const std::string& lowerBinop, 
                                         Term* upperGuard, 
                                         const std::string& upperBinop, 
                                         const std::string& aggregateFunction, 
                                         const std::vector<AggregateElement*>& aggregateSet, 
                                         bool isNegative = false );
        AggregateElement* createAggregateElement( const std::vector<Term*>& terms, const std::vector<Literal*>& lits );
        Rule* createRule( const std::vector<Atom*>& head, const std::vector<Literal*>& body );
        void createAndAddRule( const std::vector<Atom*>& head, const std::vector<Literal*>& body );
        void addRule( Rule* r );
        
        const std::vector<Rule*>& getRules() const { return rules; }
        const SCHEMAMAP& getMapSchema() const { return schemaMapping; }
        Metadata* getMetadata( const std::string& predName );
        const SUBPROGRAMSMAP& getMapSubPrograms() const { return subProgramsMapping; }
        std::set<unsigned>* getSubProgram( const std::string& predName );
        DBConnection& getDBConnection() { return connection; }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Program& );
        
        bool addPredicate( const std::string& name, unsigned arity );
        bool addHeadPredicate( const std::string& name, unsigned arity, unsigned ruleIndex );

        std::vector<Rule*> rules;
        SCHEMAMAP schemaMapping;
        SUBPROGRAMSMAP subProgramsMapping;
        
        DBConnection& connection;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const Program& p )
    {
        for( unsigned i=0; i<p.rules.size(); i++ )
        {
            out << *(p.rules[i]) << std::endl;
        }
        return out;
    }

};};

#endif	/* PROGRAM_H */


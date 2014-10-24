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
#include "../../depgraph/LabeledDependencyGraph.h"
#include "../../util/DBConnection.h"
#include "DBPredicateNames.h"
#include "DBSubProgram.h"
#include "SafetyException.h"
#include <unordered_map>
#include <set>

namespace DLV2{ namespace DB{

    class SQLStrategy;

    class DBProgram {
    public:
                
        DBProgram( DBConnection& con );
        DBProgram( const DBProgram& p );
        ~DBProgram();

        DBTerm* createIntegerConstant( int val );
        DBTerm* createStringConstant( const std::string& val );
        DBTerm* createStringConstant( char* val );
        DBTerm* createVariable( const std::string& name );
        DBTerm* createVariable( char* name );
        DBAtom* createAtom( const std::string& predName, const std::vector< DBTerm* >& terms );
        DBAtom* createAtom( char* predName, const std::vector< DBTerm* >& terms );
        DBAtom* createNegatedAtom( const std::string& predName, const std::vector< DBTerm* >& terms );
        DBAtom* createNegatedAtom( char* predName, const std::vector< DBTerm* >& terms );
        DBAtom* createBuiltinAtom( DBTerm* leftOp, const std::string& binop, DBTerm* rightOp );
        DBLiteral* createLiteral( DBAtom* a, bool naf=false );
        DBAtom* createAggregateAtom( DBTerm* lowerGuard, 
                                        const std::string& lowerBinop, 
                                        DBTerm* upperGuard, 
                                        const std::string& upperBinop, 
                                        const std::string& aggregateFunction, 
                                        const std::vector< DBAggregateElement* >& aggregateSet, 
                                        const std::string& name = "" );
        DBAggregateElement* createAggregateElement(
                const std::vector< DBTerm* >& terms,
                const std::vector< DBLiteral* >& lits );
        DBRule* createRule( 
            const std::vector< DBAtom* >& head, 
            const std::vector< DBLiteral* >& body, 
            bool hasNegation, 
            bool hasAggregates, 
            bool hasBuiltins,
            bool hasDisjunction );
        void createAndAddRule( 
            const std::vector< DBAtom* >& head, 
            const std::vector< DBLiteral* >& body,
            bool hasNegation, 
            bool hasAggregates, 
            bool hasBuiltins,
            bool hasDisjunction );
        void addRule( DBRule* r );
        std::pair< index_t, bool > addPredicate( const std::string&, unsigned arity );
        bool addToPredicateRuleSet( index_t predIndex, unsigned ruleIndex );
        // Check whether rule is safe, throw an exception if it's not.
        void assertIsRuleSafe( DBRule* rule ) const throw (SafetyException);
        
        const DBPredicateNames& getPredicateNamesTable() const { return predicates; }
        const std::vector< DBRule* >& getRules() const { return rules; }
        const std::vector< DBRule* >& getFacts() const { return facts; }
        void setSQLStrategy( SQLStrategy* sqlStrategy );
        const std::string& getRuleQuery( DBRule* rule );
        const std::string& getFactQuery( DBRule* fact );
        const Metadata* getMetadata( index_t predIndex ) const;
        const DBRuleSet* getPredicateRuleSet( index_t predIndex ) const;
        
        void computeStrictlyConnectedComponents();
        void computeComponentSubPrograms();
        const std::vector< DBSubProgram >& getComponentSubPrograms() const;
        bool isHCF() const { assert_msg( graph != NULL, "Null graph" ); return graph->isHCF(); }
        bool isStratified() { assert_msg( graph != NULL, "Null graph" ); return graph->isStratified(); }
        bool isCyclic() const { assert_msg( graph != NULL, "Null graph" ); return graph->isCyclic(); }
        bool isTight() const { assert_msg( graph != NULL, "Null graph" ); return graph->isTight(); }
        bool isDisjunctive() const { return hasDisjunction; }
        
    private:
        typedef std::unordered_map< index_t, Metadata* > SchemaMap;
        typedef std::unordered_map< index_t, DBRuleSet* > RuleSetsMap;
        typedef std::unordered_map< DBRule*, std::string > QueryCacheMap;
        
        friend inline std::ostream& operator<< ( std::ostream&, const DBProgram& );
        DBConnection& getDBConnection() { return connection; }
        void addEdgeToDepGraph( DBLiteral* src, index_t targetIdx );

        /** Checks whether conjunction is safe
         * @return true if such a condition holds, false otherwise
         */
        bool checkConjunctionSafety(
            const std::vector< DBLiteral* >& conjunction ) const;
        /** Checks whether literals in toBeChecked are safe w.r.t. safeBody
         * @return true if such a condition holds, false otherwise
         */
        bool checkLiteralsSafety(
            std::vector< DBLiteral* >& safeBody, 
            std::vector< DBLiteral* >& toBeChecked ) const;
        bool safeRegularAtom(
            const std::vector< DBLiteral* >& conjunction,
            const std::vector< DBTerm* >& params,
            const unsigned numTermsToCheck ) const;
        bool safeAggregate(
            const std::vector< DBLiteral* >& conjunction,
            const DBLiteral& aggrLit ) const;
        bool safeBuiltin(
            const std::vector< DBLiteral* >& conjunction,
            const DBLiteral& builtinLit ) const;
        /** Checks whether term is safe in conjunction
         * @return true if term appears as:
         * - a variable in a positive literal;
         * - a variable of an assignment builtin which is bound
         *   by a constant or integer, for instance X=5 or X=goofie;
         * - a guard of an assigning aggregate in the 
         *   range [ conj.begin(), conj.end() ).
         */
        bool saves( const std::vector< DBLiteral* >& conjunction, const DBTerm& term ) const;
 
        DBPredicateNames predicates;
        std::vector< DBRule* > rules;
        std::vector< DBRule* > facts;
        SQLStrategy* queryGeneratorStrategy;
        bool hasDisjunction;
        SchemaMap schemaMapping;
        RuleSetsMap ruleSetsMapping;
        QueryCacheMap queryMapping;
        LabeledDependencyGraph< DepGraphNoStrategy, index_t >* graph;
        // An element here is the subProgram of the component with the corresponding index.
        std::vector< DBSubProgram > componentSubPrograms;
        
        DBConnection& connection;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const DBProgram& p )
    {
        out << "RULES (index --> rule):" << std::endl;
        for( unsigned i=0; i<p.rules.size(); i++ )
        {
            if( p.rules[i] != NULL )
                out << i << "  -->  " << *(p.rules[i]) << std::endl;
        }
        out << std::endl << "PREDICATE-RULE-SET (predicate --> rule indices list):" << std::endl;
        for( DBProgram::RuleSetsMap::const_iterator it = p.ruleSetsMapping.begin();
                it != p.ruleSetsMapping.end();
                it++ )
        {
            if( it->second != NULL )
            {
                out << "(" << p.getPredicateNamesTable().getName(it->first) 
                    << "," << p.getPredicateNamesTable().getArity(it->first)
                    << ") -->";
                for( DBRuleSet::const_iterator it1 = it->second->begin();
                        it1 != it->second->end();
                        it1++ )
                    out << " " << *it1;
                out << std::endl;
            }
        }
        out << std::endl << p.predicates << std::endl;
        out << std::endl << "METADATA:" << std::endl;
        for( DBProgram::SchemaMap::const_iterator it = p.schemaMapping.begin();
                it != p.schemaMapping.end();
                it++ )
        {
            if( it->second != NULL )
                out << *(it->second) << std::endl;
        }
        // Boost function "strong_components" computes the 
        // SCCs of a graph and returns them in a reverse 
        // topological order.
        out << std::endl << *p.graph;
        out << std::endl << "COMPONENT-SUB-PROGRAMS (component index --> exit rule list, recursive rule list):" << std::endl;
        for( int i=p.componentSubPrograms.size()-1; i>=0; i-- )
        {
            out << "Component " 
                << p.componentSubPrograms.size()-1-i << ":" << std::endl
                << p.componentSubPrograms[i] << std::endl;
        }
        return out;
    }

};};

#endif	/* DBPROGRAM_H */


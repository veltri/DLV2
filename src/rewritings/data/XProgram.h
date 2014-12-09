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
 * File:   XProgram.h
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 19.23
 */

#ifndef XPROGRAM_H
#define XPROGRAM_H

#include <list>
#include "XPredicateNames.h"
#include "XRule.h"
#include "XSafetyException.h"
#include "../../util/Constants.h"
#include "XRulePointersCollection.h"
#include "XStickyUnifier.h"

namespace DLV2{ namespace REWRITERS{

    class XStickyLabel;
    class XStickyExpandedRule;

    class XProgram {
    public:
        typedef typename std::unordered_map< index_t, XRulePointersCollection > XPredicateToXRulesetMap;

        XProgram();
        XProgram( const XProgram& program );
        ~XProgram();

        XTerm* createIntegerConstant( int val ) const;
        XTerm* createStringConstant( const std::string& val ) const;
        XTerm* createStringConstant( char* val ) const;
        XTerm* createStandardVariable( const std::string& name ) const;
        XTerm* createStandardVariable( char* name ) const;
        XTerm* createUnknownVariable() const;
        XTerm* createNull( const std::string& name ) const;
        XTerm* createNull( char* name ) const;
        XAtom* createAtom( index_t predIndex, const std::vector< XTerm >& terms, bool trueNegated = false ) const;
        XLiteral* createLiteral( const XAtom& a, bool naf = false ) const;
        XHead* createAtomicHead( const XAtom& a ) const;
        XHead* createDisjunctiveHead( const std::vector< XAtom >& atoms ) const;
        XHead* createConjunctiveHead( const std::vector< XAtom >& atoms ) const;
        XBody* createBody( const XRandomAccessSet< XLiteral >& lits ) const;
        XBody* createBody( const std::vector< XLiteral >& lits ) const;
        XRule* createRule( XHead* head, XBody* body ) const;
        // The following methods create objects for the algorithm which checks the {sticky-join}-ness.
        XStickyLabel* createStickyLabel( index_t expRuleIndex, const XAtom& atom ) const;
        XStickyExpandedRule* createStickyExpandedRule( const XRule& rule ) const;
        XStickyUnifier* createStickyUnifier( const XAtom& headAt, const XAtom& bodyAt, const XMapping& subst ) const;

        void addRule( const XRule& r );
        void addQuery( const XAtom& q );
        std::pair< index_t, bool > addPredicate( const std::string& name, unsigned arity, bool internal = false );
        unsigned incrementVariablesCounter() { return varsCounter++; }
        void computeQueryRules();

        unsigned getVariablesCounter() const { return varsCounter; }
        const XPredicateNames& getPredicateNamesTable() const { return predicates; }
        const std::string& getPredicateName( index_t predIndex ) const;
        unsigned getPredicateArity( index_t predIndex ) const;
        XRule::const_iterator beginRules() const { return rules.begin(); }
        XRule::const_iterator endRules() const { return rules.end(); }
        size_t rulesSize() const { return rules.size(); }
        XRule::const_iterator beginFacts() const { return facts.begin(); }
        XRule::const_iterator endFacts() const { return facts.end(); }
        size_t factsSize() const { return facts.size(); }
        bool isDisjunctive() const { return hasDisjunction; }
        bool isConjunctive() const { return hasConjunction; }
        const XRulePointersCollection& getPredicateRulePointers( index_t predIndex ) const;
        const XAtom* getQuery() const { return query; }
        XRule::const_iterator beginQueryRules() const { return queryRules.begin(); }
        XRule::const_iterator endQueryRules() const { return queryRules.end(); }
        size_t queryRulesSize() const { return queryRules.size(); }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XProgram& );

        bool addToPredicateRuleSet( index_t predIndex, XRule::const_iterator ruleIt );
        // Check whether rule is safe, throw an exception if it's not.
        void checkSafety( const XRule& rule ) const throw (XSafetyException);

        XPredicateNames predicates;
        std::list< XRule > rules;
        std::list< XRule > facts;
        bool hasDisjunction;
        bool hasConjunction;
        XPredicateToXRulesetMap predicateToRulesMapping;
        unsigned varsCounter;
        XAtom* query;
        std::list< XRule > queryRules;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XProgram& p )
    {
        if( p.rules.size() > 0 )
            out << "RULES (ruleIndex --> rule):" << std::endl;
        unsigned counter = 0;
        for( XRule::const_iterator it=p.rules.begin(); it!=p.rules.end(); it++ )
        {
            out << counter++ << "  -->  " << *it << std::endl;
        }
        if( p.facts.size() > 0 )
            out << "FACTS (factIndex --> fact):" << std::endl;
        counter = 0;
        for( XRule::const_iterator it=p.facts.begin(); it!=p.facts.end(); it++ )
        {
            out << counter << "  -->  " << *it << std::endl;
        }
        if( p.predicateToRulesMapping.size() > 0 )
            out << std::endl << "PREDICATE-RULE-SET (<predicate> : {rule set}):" << std::endl;
        for( XProgram::XPredicateToXRulesetMap::const_iterator it = p.predicateToRulesMapping.begin();
                it != p.predicateToRulesMapping.end();
                it++ )
        {
            out << "(" << p.getPredicateName(it->first)
                << "," << p.getPredicateArity(it->first)
                << "): {" << std::endl;
            for( index_t i=0; i<it->second.size(); i++ )
                out << *(it->second[i]) << std::endl;
            out << "}" << std::endl << std::endl;
        }
        return out;
    }

};};


#endif /* XPROGRAM_H */

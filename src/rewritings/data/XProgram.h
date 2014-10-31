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

#include <vector>
#include "XRuleIndicesCollection.h"
#include "XPredicateNames.h"
#include "XRule.h"
#include "XSafetyException.h"
#include "../../util/Constants.h"

namespace DLV2{ namespace REWRITERS{

    class XProgram {
    public:
        typedef typename std::unordered_map< index_t, XRuleIndicesCollection > XPredicateToXRulesetMap;

        XProgram();
        XProgram( const XProgram& program );
        ~XProgram();

        XTerm* createIntegerConstant( int val );
        XTerm* createStringConstant( const std::string& val );
        XTerm* createStringConstant( char* val );
        XTerm* createVariable( const std::string& name );
        XTerm* createVariable( char* name );
        XTerm* createNull( const std::string& name );
        XTerm* createNull( char* name );
        XAtom* createAtom( index_t predIndex, const std::vector< XTerm >& terms, bool trueNegated = false );
        XLiteral* createLiteral( const XAtom& a, bool naf = false );
        XHead* createAtomicHead( const XAtom& a );
        XHead* createDisjunctiveHead( const std::vector< XAtom >& atoms );
        XHead* createConjunctiveHead( const std::vector< XAtom >& atoms );
        XBody* createBody( const XRandomAccessSet< XLiteral >& lits );
        XRule* createRule( XHead* head, XBody* body );

        void addRule( const XRule& r );
        std::pair< index_t, bool > addPredicate( const std::string& name, unsigned arity );
        bool addToPredicateRuleSet( index_t predIndex, XRuleIndex ruleIndex );
        // Check whether rule is safe, throw an exception if it's not.
        void assertIsRuleSafe( const XRule& rule ) const throw (XSafetyException);

        const XPredicateNames& getPredicateNamesTable() const { return predicates; }
        const std::string& getPredicateName( index_t predIndex ) const;
        unsigned getPredicateArity( index_t predIndex ) const;
        const XRule& getRule( XRuleIndex ruleIndex ) const;
        size_t rulesSize() const { return rules.size(); }
        const XRule& getFact( index_t factIndex ) const;
        size_t factsSize() const { return facts.size(); }
        bool isDisjunctive() const { return hasDisjunction; }
        bool isConjunctive() const { return hasConjunction; }
        const XRuleIndicesCollection& getPredicateRuleIndices( index_t predIndex ) const;

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XProgram& );

        XPredicateNames predicates;
        std::vector< XRule > rules;
        std::vector< XRule > facts;
        bool hasDisjunction;
        bool hasConjunction;
        XPredicateToXRulesetMap predicateToRulesMapping;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XProgram& p )
    {
        if( p.rules.size() > 0 )
            out << "RULES (ruleIndex --> rule):" << std::endl;
        for( unsigned i=0; i<p.rules.size(); i++ )
        {
            out << i << "  -->  " << p.rules[i] << std::endl;
        }
        if( p.facts.size() > 0 )
            out << "FACTS (factIndex --> fact):" << std::endl;
        for( unsigned i=0; i<p.facts.size(); i++ )
        {
            out << i << "  -->  " << p.facts[i] << std::endl;
        }
        if( p.predicateToRulesMapping.size() > 0 )
            out << std::endl << "PREDICATE-RULE-SET (predicate --> rule set):" << std::endl;
        for( XProgram::XPredicateToXRulesetMap::const_iterator it = p.predicateToRulesMapping.begin();
                it != p.predicateToRulesMapping.end();
                it++ )
        {
            out << "(" << p.getPredicateName(it->first)
                << "," << p.getPredicateArity(it->first)
                << ") --> " << std::endl;
            for( XRuleIndex i=0; i<it->second.size(); i++ )
                out << p.getRule(it->second[i]) << std::endl;
            out << std::endl;
        }
        return out;
    }

};};


#endif /* XPROGRAM_H */

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
 * File:   XStickyExpandedRule.h
 * Author: pierfrancesco
 *
 * Created on 04 novembre 2014, 16.30
 */

#ifndef XSTICKYEXPANDEDRULE_H
#define XSTICKYEXPANDEDRULE_H

#include "../../util/Assert.h"
#include "XRandomAccessSet.h"
#include "XRule.h"
#include "XStickyLabel.h"

namespace DLV2{ namespace REWRITERS{

    class XStickyExpandedRule {
    public:
        XStickyExpandedRule( const XStickyExpandedRule& expRule ): rule(expRule.rule), labels(expRule.labels) { }
        ~XStickyExpandedRule() { }

        const XRule& getRule() const { return rule; }
        const XRandomAccessSet< XStickyLabel >& getLabels() const { return labels; }
        void addLabel( const XStickyLabel& label ) { labels.pushItem(label); }

        const std::vector< XCoordinates >& getHeadPositions( const XTerm& term ) const { return rule.getHeadPositions(term); }
        const std::vector< XCoordinates >& getBodyPositions( const XTerm& term ) const { return rule.getBodyPositions(term); }
        unsigned getHeadOccurrences( const XTerm& term ) const { return rule.getHeadOccurrences(term); }
        unsigned getBodyOccurrences( const XTerm& term ) const { return rule.getBodyOccurrences(term); }
        bool isMarked( const XTerm& term ) const { return rule.isMarked(term); }
        void markVariable( const XTerm& term ) { rule.markVariable(term); }

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const XStickyExpandedRule& );
        friend class XProgram;

        XStickyExpandedRule( const XRule& rul ): rule(rul), labels() { }

        XRule rule;
        XRandomAccessSet< XStickyLabel > labels;

    };

    inline
    std::ostream&
    operator<< (
        std::ostream& out,
        const XStickyExpandedRule& expandedRule )
    {
        out << "Rule: " << expandedRule.getRule() << "          ";
        for( unsigned i=0; i<expandedRule.getLabels().size(); i++ )
        {
            out << expandedRule.getLabels().at(i);
            if( i < expandedRule.getLabels().size()-1 )
                out << ", ";
        }
        return out;
    }

};};


#endif /* XSTICKYEXPANDEDRULE_H */

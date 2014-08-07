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
 * Author: cesco
 *
 * Created on 28 febbraio 2014, 11.22
 */

#ifndef PROGRAM_H
#define	PROGRAM_H

#include "Rule.h"
#include "ChoiceRule.h"
#include "Constraint.h"
#include "WeakConstraint.h"

namespace DLV2
{
    
    class Program {
    public:
        Program() { }
        Program( const Program& p );
        ~Program() { }

        void addRule( const Rule& r );
        void addConstraint( const Constraint& c );
        void addWeakConstraint( const WeakConstraint& wc );
        void addChoiceRule( const ChoiceRule& cr );

    private:
        friend inline std::ostream& operator<< ( std::ostream&, const Program& );

        std::vector<Rule> rules;
        std::vector<Constraint> constraints;
        std::vector<WeakConstraint> weakConstraints;
        std::vector<ChoiceRule> choiceRules;
    };

    inline
    std::ostream& 
    operator<< ( 
        std::ostream& out, 
        const Program& p )
    {
        for( unsigned i=0; i<p.rules.size(); i++ )
        {
            out << p.rules[i] << std::endl;
        }
        for( unsigned i=0; i<p.choiceRules.size(); i++ )
        {
            out << p.choiceRules[i] << std::endl;
        }
        for( unsigned i=0; i<p.constraints.size(); i++ )
        {
            out << p.constraints[i] << std::endl;
        }
        for( unsigned i=0; i<p.weakConstraints.size(); i++ )
        {
            out << p.weakConstraints[i] << std::endl;
        }
        return out;
    }

};

#endif	/* PROGRAM_H */


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
 * File:   ChoiceAtom.h
 * Author: cesco
 *
 * Created on 28 marzo 2014, 20.00
 */

#ifndef CHOICEATOM_H
#define	CHOICEATOM_H

#include "Term.h"
#include "ChoiceElement.h"

namespace DLV2
{
    
    class ChoiceAtom {
    public:
        ChoiceAtom( Term*, string, vector<ChoiceElement>, string, Term* );
        ChoiceAtom( const ChoiceAtom& );
        ~ChoiceAtom();
    private:
        friend inline ostream& operator<< ( ostream&, const ChoiceAtom& );

        Term* lowerGuard;
        string lowerBinop;
        vector<ChoiceElement> choices;
        string upperBinop;
        Term* upperGuard;
    };

    inline ostream& operator<< ( ostream& out, const ChoiceAtom& ca )
    {
        if( ca.lowerGuard )
            out << *(ca.lowerGuard) << ca.lowerBinop;
        out << "{";
        for( unsigned i=0; i<ca.choices.size(); i++ )
        {
            out << ca.choices[i];
            if( i<ca.choices.size()-1 )
                out << ";";
        }
        out << "}";
        if( ca.upperGuard )
            out << ca.upperBinop << *(ca.upperGuard);
        return out;
    }

};

#endif	/* CHOICEATOM_H */


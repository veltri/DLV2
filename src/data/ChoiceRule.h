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
 * File:   ChoiceRule.h
 * Author: cesco
 *
 * Created on 27 marzo 2014, 19.03
 */

#ifndef CHOICERULE_H
#define	CHOICERULE_H

#include <vector>
#include "Literal.h"
#include "ChoiceAtom.h"

class ChoiceRule {
public:
    ChoiceRule( const ChoiceAtom& ca, vector<Literal> b ): head(ca), body(b) { }
    ChoiceRule( const ChoiceRule& cr ): head(cr.head), body(cr.body) { }
    ~ChoiceRule() { }
    
    void addToBody( const Literal& l ) { body.push_back(l); }
        
private:
    friend inline ostream& operator<< ( ostream&, const ChoiceRule& );
    
    ChoiceAtom head;
    vector<Literal> body;
};

ostream& 
operator<< ( 
    ostream& out,
    const ChoiceRule& r )
{
    out << r.head;
    if( r.body.size() > 0 )
        out << " :- ";
    for( unsigned i=0; i<r.body.size(); i++ )
    {
        out << r.body[i];
        if( i<r.body.size()-1 )
            out << ", ";
    }
    out << ".";
    return out;
}

#endif	/* CHOICERULE_H */


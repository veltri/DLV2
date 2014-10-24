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
 * File:   DBSubProgram.h
 * Author: pierfrancesco
 *
 * Created on 22 settembre 2014, 19.44
 */

#ifndef DBSUBPROGRAM_H
#define	DBSUBPROGRAM_H

#include <vector>
#include "../../util/Assert.h"

namespace DLV2{ namespace DB{
    
    class DBSubProgram {
    public:
        typedef typename std::vector< DBRule* >::const_iterator const_iterator;

        DBSubProgram( const DBSubProgram& prog ):
            exitRulesIndices(prog.exitRulesIndices),
            recursiveRulesIndices(prog.recursiveRulesIndices) { }
        ~DBSubProgram() { }

        const_iterator exitBegin() const { return exitRulesIndices.begin(); }
        const_iterator exitEnd() const { return exitRulesIndices.end(); }
        const_iterator recBegin() const { return recursiveRulesIndices.begin(); }
        const_iterator recEnd() const { return recursiveRulesIndices.end(); }
        size_t size() const { return recursiveRulesIndices.size() + exitRulesIndices.size(); }
        size_t recSize() const { return recursiveRulesIndices.size(); }
        size_t exitSize() const { return exitRulesIndices.size(); }
        void operator=( const DBSubProgram& prog ) { assert( 0 ); }

        void addExit( DBRule* rule ) { assert_msg( rule != NULL, "Null rule"); exitRulesIndices.push_back(rule); }
        void addRecursive( DBRule* rule ) { assert_msg( rule != NULL, "Null rule"); recursiveRulesIndices.push_back(rule); }
        
    private:
        friend inline std::ostream& operator<<( std::ostream&, const DBSubProgram& );
        friend class DBProgram;
        
        // Only class Program can create Atom objects.
        DBSubProgram(): exitRulesIndices(), recursiveRulesIndices() { }

        std::vector< DBRule* > exitRulesIndices;
        std::vector< DBRule* > recursiveRulesIndices;
    };

    std::ostream&
    operator<<(
        std::ostream& out,
        const DBSubProgram& p )
    {
        out << "Exit rules: {";
        for( DBSubProgram::const_iterator it = p.exitBegin();
                it != p.exitEnd();
                it++ )
        {
            assert_msg( (*it) != NULL, "Null rule" );
            out << **it << std::endl;
        }
        out << "}" << std::endl;
        out << "Recursive rules: {";
        for( DBSubProgram::const_iterator it = p.recBegin();
                it != p.recEnd();
                it++ )
        {
            assert_msg( (*it) != NULL, "Null rule" );
            out << **it << std::endl;
        }
        out << "}" << std::endl;
        
        return out;
    }
    
};};

#endif	/* DBSUBPROGRAM_H */


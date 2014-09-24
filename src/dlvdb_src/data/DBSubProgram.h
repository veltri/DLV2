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
    
    template < typename T >
    class DBSubProgram : std::vector< T > {   
    public:
        
        DBSubProgram(): std::vector< T >() { sep=inherited_end(); }
        DBSubProgram( const DBSubProgram< T >& prog2 );
        void operator=( const DBSubProgram< T >& ) { assert( 0 ); }
        size_t size() const { return std::vector< T >::size(); }

        class const_iterator
        {
        public:
            const_iterator(): i(0) { }
            const_iterator( const const_iterator& i2 ): i(i2.i) { }
            const_iterator( const typename std::vector< T >::const_iterator i2 ) : i(i2) { }

            void operator= ( const const_iterator& i2 ) { i=i2.i; }
            const T& operator* () const { return *i; }
            const T* operator->() const { return &(operator*()); }
            void operator++ () { i++; }
            void operator++ ( int ) { i++; }
            bool operator== ( const const_iterator& i2 ) const { return i == i2.i; }
            bool operator!= ( const const_iterator& i2 ) const { return i != i2.i; }
            
        private:
            typename std::vector< T >::const_iterator i;
            
        };
        
        const_iterator begin() const { return inherited_begin(); }
        const_iterator end() const { return inherited_end(); }

        const_iterator exitBegin() const { return begin(); }
        const_iterator exitEnd() const { return sep; }
        const_iterator recBegin() const { return sep; }
        const_iterator recEnd() const { return end(); }

        size_t recSize() const;
        size_t exitSize() const;
        void addExit( const T& rule );
        void addRecursive( const T& rule );
        
    private:
        template < typename TP >
        friend inline std::ostream& operator<<( std::ostream&, const DBSubProgram< TP >& );
        
        typename std::vector< T >::const_iterator inherited_begin() const;
        typename std::vector< T >::iterator inherited_begin();
        typename std::vector< T >::const_iterator inherited_end() const;

        typename std::vector< T >::const_iterator sep;

    };

    template < typename T >
    std::ostream&
    operator<<(
        std::ostream& out,
        const DBSubProgram< T >& p )
    {
        out << "{ ";
        for( unsigned i=0; i<p.size(); i++ )
        {
            out << p[i] << " ";
        }
        out << "}";
        
        return out;
    }
    
};};

template < typename T >
DLV2::DB::DBSubProgram< T >::DBSubProgram(
    const DBSubProgram< T >& prog2 ): 
        std::vector< T >()
{
    // Preallocate enough space to avoid the separator will be invalidated.
    std::vector< T >::reserve(prog2.size());
    this->insert(std::vector< T >::end(),prog2.inherited_begin(),prog2.sep);
    sep = inherited_end();
    this->insert(std::vector< T >::end(),prog2.sep, prog2.inherited_end());
}

template < typename T >
size_t
DLV2::DB::DBSubProgram< T >::recSize() const
{
    assert_msg( sep <= inherited_end(), "Not valid separator" );
    return inherited_end()-sep;
}

template < typename T >
size_t
DLV2::DB::DBSubProgram< T >::exitSize() const
{
    assert_msg( sep >= inherited_begin(), "Not valid separator" );
    return sep-inherited_begin();
}

template < typename T >
void
DLV2::DB::DBSubProgram< T >::addExit(
    const T& rule )
{
    assert_msg( (inherited_begin() <= sep && sep <= inherited_end()), "Not valid separator" );
    // Insertions might resize the vector, so the old separator might be invalidated.
    sep = this->insert(inherited_begin()+(sep-inherited_begin()),rule)+1;
    assert_msg( (inherited_begin() <= sep && sep <= inherited_end()), "Not valid separator" );
}

template < typename T >
void
DLV2::DB::DBSubProgram< T >::addRecursive(
    const T& rule )
{
    assert_msg( (inherited_begin() <= sep && sep <= inherited_end()), "Not valid separator" );
    size_t offset = sep-inherited_begin();
    this->push_back(rule);
    // Insertions might resize the vector, so the old separator might be invalidated.
    sep = inherited_begin()+offset;
    assert_msg( (inherited_begin() <= sep && sep <= inherited_end()), "Not valid separator" );
}

template < typename T >
typename std::vector< T >::const_iterator
DLV2::DB::DBSubProgram< T >::inherited_begin() const
{
    return std::vector< T >::begin();
}

template < typename T >
typename std::vector< T >::iterator
DLV2::DB::DBSubProgram< T >::inherited_begin()
{
    return std::vector< T >::begin();
}

template < typename T >
typename std::vector< T >::const_iterator
DLV2::DB::DBSubProgram< T >::inherited_end() const
{
    return std::vector< T >::end();
}

#endif	/* DBSUBPROGRAM_H */


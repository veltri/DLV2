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
 * File:   XIterableMap.h
 * Author: pierfrancesco
 *
 * Created on 15 novembre 2014, 17.01
 */

#ifndef XITERABLEMAP_H
#define XITERABLEMAP_H

#include <unordered_map>
#include <vector>
#include "../../util/Constants.h"
#include "../../util/Assert.h"
#include "XTerm.h"

namespace DLV2{ namespace REWRITERS{

    template < typename X, typename Y >
    class XIterableMap {
    public:
        typedef typename std::unordered_map< X, Y >::iterator iterator;
        typedef typename std::unordered_map< X, Y >::const_iterator const_iterator;

        XIterableMap() { }
        XIterableMap( const XIterableMap< X, Y >& map );
        ~XIterableMap() { }

        size_t size() const { return iterators.size(); }
        const_iterator operator[]( index_t pos ) const;
        iterator operator[]( index_t pos );
        const_iterator at( index_t pos ) const;
        iterator at( index_t pos );
        iterator find( const X& key ) { return substitution.find(key); }
        const_iterator find( const X& key ) const { return substitution.find(key); }
        std::pair< iterator, bool > insert( const std::pair< X, Y >& value );
        bool erase( const X& key );
        bool erase( index_t pos );
        bool erase( index_t from, index_t to );
        std::pair< iterator, bool > substitute( const std::pair< X, Y >& value );
        void clear() { substitution.clear(); iterators.clear(); }
        const_iterator begin() const { return substitution.begin(); }
        const_iterator end() const { return substitution.end(); }

    private:
        std::unordered_map< X, Y > substitution;
        std::vector< iterator > iterators;
    };

    typedef XIterableMap< XTerm, XTerm > XMapping;
};};

template < typename X, typename Y >
DLV2::REWRITERS::XIterableMap< X, Y >::XIterableMap(
    const DLV2::REWRITERS::XIterableMap< X, Y >& map )
{
    for( index_t i=0; i<map.size(); i++ )
    {
        insert(*map.at(i));
    }
}

template < typename X, typename Y >
typename DLV2::REWRITERS::XIterableMap< X, Y >::const_iterator
DLV2::REWRITERS::XIterableMap< X, Y >::operator[](
    DLV2::REWRITERS::index_t pos ) const
{
    assert_msg( pos < iterators.size(), "Index out of range" );
    return iterators[pos];
}

template < typename X, typename Y >
typename DLV2::REWRITERS::XIterableMap< X, Y >::iterator
DLV2::REWRITERS::XIterableMap< X, Y >::operator[](
    DLV2::REWRITERS::index_t pos )
{
    assert_msg( pos < iterators.size(), "Index out of range" );
    return iterators[pos];
}

template < typename X, typename Y >
typename DLV2::REWRITERS::XIterableMap< X, Y >::const_iterator
DLV2::REWRITERS::XIterableMap< X, Y >::at(
    DLV2::REWRITERS::index_t pos ) const
{
    assert_msg( pos < iterators.size(), "Index out of range" );
    return iterators.at(pos);
}

template < typename X, typename Y >
typename DLV2::REWRITERS::XIterableMap< X, Y >::iterator
DLV2::REWRITERS::XIterableMap< X, Y >::at(
    DLV2::REWRITERS::index_t pos )
{
    assert_msg( pos < iterators.size(), "Index out of range" );
    return iterators.at(pos);
}

template < typename X, typename Y >
std::pair< typename DLV2::REWRITERS::XIterableMap< X, Y >::iterator, bool >
DLV2::REWRITERS::XIterableMap< X, Y >::insert(
    const std::pair< X, Y >& value )
{
    std::pair< iterator, bool > ins = substitution.insert(value);
    if( ins.second )
    {
        iterators.push_back(ins.first);
    }
    return ins;
}

template < typename X, typename Y >
bool
DLV2::REWRITERS::XIterableMap< X, Y >::erase(
    const X& key )
{
    bool erased = false;
    for( index_t i=0; i<size() && !erased; i++ )
    {
        if( iterators[i]->first == key )
        {
            substitution.erase(iterators[i]);
            iterators.erase(iterators.begin()+i);
            erased = true;
        }
    }
    return erased;
}

template < typename X, typename Y >
bool
DLV2::REWRITERS::XIterableMap< X, Y >::erase(
    index_t pos )
{
    if( 0 <= pos && pos < iterators.size() )
    {
        substitution.erase(iterators[pos]);
        iterators.erase(iterators.begin()+pos);
        return true;
    }
    else
        return false;
}

template < typename X, typename Y >
bool
DLV2::REWRITERS::XIterableMap< X, Y >::erase(
    index_t from,
    index_t to )
{
    assert_msg( from < to, "Invalid range" );
    if( 0 <= from && from < iterators.size()
            && 0 < to && to <= iterators.size() )
    {
        for( unsigned i=to-1; i>=from; i-- )
        {
            substitution.erase(iterators[i]);
            iterators.pop_back();
        }
        return true;
    }
    else
        return false;
}

template < typename X, typename Y >
std::pair< typename DLV2::REWRITERS::XIterableMap< X, Y >::iterator, bool >
DLV2::REWRITERS::XIterableMap< X, Y >::substitute(
    const std::pair< X, Y >& value )
{
    iterator valueIt = substitution.find(value.first);
    assert_msg( valueIt != substitution.end(), "The key doesn't exist" );
    valueIt->second = value.second;
    return std::pair< iterator, bool >(valueIt,true);
}

#endif /* XITERABLEMAP_H */

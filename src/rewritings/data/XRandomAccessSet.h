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
 * File:   XRandomAccessSet.h
 * Author: pierfrancesco
 *
 * Created on 31 ottobre 2014, 17.02
 */

#ifndef XRANDOMACCESSSET_H
#define XRANDOMACCESSSET_H

#include <unordered_set>
#include <vector>
#include "../../util/Assert.h"
#include "../../util/Constants.h"

namespace DLV2{ namespace REWRITERS{

    template < typename T >
    class XRandomAccessSet {
    public:
        typedef typename std::unordered_set< T >::iterator iterator;
        typedef typename std::unordered_set< T >::const_iterator const_iterator;

        XRandomAccessSet(): items(), itemIterators() { }
        XRandomAccessSet( const XRandomAccessSet& set );
        ~XRandomAccessSet() { }

        size_t size() const { return itemIterators.size(); }
        const T& operator[]( index_t pos ) const;
        bool pushItem( const T& item );
        bool popItem();
        bool insertItem( index_t pos, const T& item );
        bool removeItem( index_t pos );

    private:
        const_iterator cbegin() const { return items.cbegin(); }
        const_iterator cend() const { return items.cend(); }

        std::unordered_set< T > items;
        std::vector< iterator > itemIterators;
    };

};};

template < typename T >
DLV2::REWRITERS::XRandomAccessSet< T >::XRandomAccessSet(
    const DLV2::REWRITERS::XRandomAccessSet< T >& set )
{
    for( const_iterator it=set.cbegin(); it!=set.cend(); it++ )
    {
        pushItem(*it);
    }
}

template < typename T >
const T&
DLV2::REWRITERS::XRandomAccessSet< T >::operator[](
    index_t pos ) const
{
    assert_msg( (0 <= pos && pos < itemIterators.size()), "Index out of range" );
    return *itemIterators[pos];
}

template < typename T >
bool
DLV2::REWRITERS::XRandomAccessSet< T >::pushItem(
    const T& item )
{
    std::pair< iterator, bool > ret = items.insert(item);
    if( ret.second )
    {
        itemIterators.push_back(ret.first);
    }
    return ret.second;
}

template < typename T >
bool
DLV2::REWRITERS::XRandomAccessSet< T >::popItem()
{
    if( itemIterators.size() > 0 )
    {
        items.erase(*itemIterators.rbegin());
        itemIterators.pop_back();
        return true;
    }
    else
        return false;
}

template < typename T >
bool
DLV2::REWRITERS::XRandomAccessSet< T >::insertItem(
    index_t pos,
    const T& item )
{
    if( 0 <= pos && pos < itemIterators.size() )
    {
        std::pair< iterator, bool > ret = items.insert(item);
        if( ret.second )
        {
            itemIterators.insert(itemIterators.begin()+pos,ret.first);
        }
        return ret.second;
    }
    else
        return false;
}

template < typename T >
bool
DLV2::REWRITERS::XRandomAccessSet< T >::removeItem(
    index_t pos )
{
    if( 0 <= pos && pos < itemIterators.size() )
    {
        items.erase(itemIterators[pos]);
        itemIterators.erase(itemIterators.begin()+pos);
        return true;
    }
    else
        return false;
}

#endif /* XRANDOMACCESSSET_H */

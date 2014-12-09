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
 * File:   XNamesTable.h
 * Author: pierfrancesco
 *
 * Created on 27 ottobre 2014, 17.39
 */

#ifndef XNAMESTABLE_H
#define XNAMESTABLE_H

#include <unordered_map>
#include <vector>
#include "../../util/Assert.h"
#include "../../util/Constants.h"

namespace DLV2{ namespace REWRITERS{

    template < typename T >
    class XNamesTable
    {
    private:
        friend class XProgram;
        friend class XPredicateNames;

        XNamesTable( index_t startIndex = 0 );

        typedef std::unordered_map< T, index_t > LookupT;
        typedef std::vector< typename LookupT::const_iterator > IndexedT;

        LookupT lookup;
        IndexedT indexed;
        size_t indexCount;

    public:

        class const_iterator
        {
        public:
            const_iterator() { assert( 0 ); }
            const_iterator(const typename LookupT::const_iterator &it1): it (it1) { }
            const_iterator(const const_iterator& ni1): it(ni1.it) { }
            ~const_iterator() { }

            const T& getItem() { return (*it).first; }
            index_t getIndex() { return (*it).second; }

            const_iterator& operator=(const const_iterator& ni1);
            const T& operator*() const { return (*it).first; }
            void operator++() { it++; }
            void operator++(int) { ++it; }
            bool operator== (const const_iterator& i2) const { return it == i2.it; }
            bool operator!= (const const_iterator& i2) const { return it != i2.it; }

        private:
            typename LookupT::const_iterator it;
        };

        XNamesTable( const XNamesTable< T >& n2 );

        XNamesTable& operator=( const XNamesTable< T >& n2 );
        const_iterator begin() const { return const_iterator(lookup.begin()); }
        const_iterator end() const { return const_iterator(lookup.end()); }
        size_t size() const { return indexed.size(); }

        // @return a pair: The second item indicates whether an entry has been
        // found; the first item contains the index of the entry if one has been
        // found, 0 otherwise.
        std::pair< index_t, bool > find(const T &item) const;
        std::pair< index_t, bool > add(const T &item);
        const T& getItem(index_t index) const;
        std::pair< index_t, bool > getIndex(const T &item) const;

    };

};};

template < typename T >
typename DLV2::REWRITERS::XNamesTable< T >::const_iterator&
DLV2::REWRITERS::XNamesTable< T >::const_iterator::operator=(
    const const_iterator& ni1 )
{
    if( this != &ni1 )
    {
        it = ni1.it;
    }
    return *this;
}

template < typename T >
DLV2::REWRITERS::XNamesTable< T >::XNamesTable(
    index_t startIndex ):
        lookup(),
        indexed(),
        indexCount(startIndex)
{
}

template < typename T >
DLV2::REWRITERS::XNamesTable< T >::XNamesTable(
    const DLV2::REWRITERS::XNamesTable< T >& n2 ):
        lookup(n2.lookup),
        indexed(n2.indexed),
        indexCount(n2.indexCount)
{
    // These tables should not be copied.
    assert(0);
}

template < typename T >
DLV2::REWRITERS::XNamesTable< T >&
DLV2::REWRITERS::XNamesTable< T >::operator=(
    const DLV2::REWRITERS::XNamesTable< T >& n2 )
{
    // These tables should not be copied.
    assert_msg(0, "You should not copy these tables");

    if( this != &n2 )
        {
        lookup = n2.lookup;
        indexed = n2.indexed;
        indexCount = n2.indexCount;
        }

    return *this;
}

template < typename T >
std::pair< DLV2::REWRITERS::index_t, bool >
DLV2::REWRITERS::XNamesTable< T >::find(
    const T &item ) const
{
    typename LookupT::const_iterator i = lookup.find(item);

    if( i == lookup.end() )
        return std::pair< index_t, bool >(0,false);
    else
        return std::pair< index_t, bool >((*i).second,true);
}

template < typename T >
std::pair< DLV2::REWRITERS::index_t, bool >
DLV2::REWRITERS::XNamesTable< T >::add(
    const T& item )
{
    index_t itemindex;

    // Try to insert the item with the next available index (if a
    // copy of item already exists, the index is not overwritten!)
    std::pair< typename LookupT::const_iterator, bool > result =
        lookup.insert(std::pair< const T&, index_t >(item,indexCount));

    // See whether this item already existed in the datastructures.
    if(result.second)
        {
        // This is a new item.
        itemindex = indexCount++;
        indexed.push_back(result.first);
        }
    else
        {
        // The item already existed.
        itemindex = (*(result.first)).second;
        }

    return std::pair< index_t, bool >(itemindex,result.second);
}

template < typename T >
const T&
DLV2::REWRITERS::XNamesTable< T >::getItem(
    DLV2::REWRITERS::index_t index ) const
{
    assert_msg( index < indexed.size(), "Index out of range" );
    return (*(indexed[index])).first;
}

template < typename T >
std::pair< DLV2::REWRITERS::index_t, bool >
DLV2::REWRITERS::XNamesTable< T >::getIndex(
    const T& item ) const
{
    typename LookupT::iterator i = lookup.find(item);
    if( i == lookup.end() )
        return std::pair< index_t, bool >(0,false);
    else
        return std::pair< index_t, bool >((*i).second,true);
}




#endif /* XNAMESTABLE_H */

/* 
 * File:   XAtomicHead.h
 * Author: pierfrancesco
 *
 * Created on 29/ott/2014, 17:07:01
 */

#ifndef XATOMICHEAD_H_
#define XATOMICHEAD_H_

#include "XHead.h"

namespace DLV2{ namespace REWRITERS{

    class XAtomicHead: public XHead {
    public:
        XAtomicHead( const XAtomicHead& head ): XHead(head) { }
        virtual ~XAtomicHead() { }

        virtual void addAtom( const XAtom& atom ) { assert( atoms.size() == 0 ); atoms.push_back(atom); }
        virtual bool isAtomic() const { return true; }
        virtual bool isDisjunctive() const { return false; }
        virtual bool isConjunctive() const { return false; }

    private:
        friend std::ostream& operator<< ( std::ostream&, const XAtomicHead& );
        friend class XProgram;

        XAtomicHead(): XHead() { }
        XAtomicHead( const XAtom& atom ): XHead() { addAtom(atom); }

    };

    inline
    std::ostream&
    operator<< (
        std::ostream & out,
        const XAtomicHead& h )
    {
        assert_msg( h.atoms.size() == 1, "Not valid atomic head" );
        out << h.atoms[0] << " ";
        return out;
    }

};};

#endif /* XATOMICHEAD_H_ */

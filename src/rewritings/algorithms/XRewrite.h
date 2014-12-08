/* 
 * File:   XRewrite.h
 * Author: pierfrancesco
 *
 * Created on 03 dicembre 2014, 13.44
 */

#ifndef XREWRITE_H
#define XREWRITE_H

namespace DLV2{ namespace REWRITERS{

    class XRewrite: public RewritingAlgorithm {
    public:
        XRewrite( IsomorphismCheckStrategy* isoCheck ): RewritingAlgorithm(isoCheck) { }
        virtual ~XRewrite() { }

        XProgram* rewrite( const XProgram& input );

    };

};};

#endif /* XREWRITE_H */

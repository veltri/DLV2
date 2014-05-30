/* 
 * File:   ParserConstraint.h
 * Author: cesco
 *
 * Created on 12 maggio 2014, 18.32
 */

#ifndef PARSERCONSTRAINT_H
#define	PARSERCONSTRAINT_H

#include "../util/Options.h"
#include "../util/ErrorMessage.h"

namespace DLV2
{

    class ParserConstraint {
    public:
        ParserConstraint() {}
        virtual ~ParserConstraint() {}
        
        inline virtual void rangeFacts();
        inline virtual void directives();
    };

    void
    ParserConstraint::rangeFacts()
    {
        if( Options::globalOptions()->isAspCore2Strict() )
            ErrorMessage::errorDuringParsing("range facts are not in the ASPCore2 standard!");
    }
    
    void
    ParserConstraint::directives()
    {
        if( Options::globalOptions()->isAspCore2Strict() )
            ErrorMessage::errorDuringParsing("directives are not in the ASPCore2 standard!");
    }
    
};

#endif	/* PARSERCONSTRAINT_H */


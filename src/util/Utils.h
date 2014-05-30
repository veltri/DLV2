/* 
 * File:   Utils.h
 * Author: cesco
 *
 * Created on 16 maggio 2014, 16.32
 */

#ifndef UTILS_H
#define	UTILS_H

namespace DLV2
{

    class Utils {
    public:
        Utils() {}
        ~Utils() {}
        
        static bool parseLongInteger( const char*, long int& );
        static bool parseInteger( const char*, int& );
    };
    
};

#endif	/* UTILS_H */


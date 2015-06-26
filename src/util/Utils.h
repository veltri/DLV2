/* 
 * File:   Utils.h
 * Author: cesco
 *
 * Created on 16 maggio 2014, 16.32
 */

#ifndef UTILS_H
#define	UTILS_H

#include <string>

namespace DLV2
{

    class Utils {
    public:
        Utils() {}
        ~Utils() {}
        
        /** Convert a string, representing a numeric value, 
         * to a long int variable. 
         * @param value The long int variable to be converted
         * @param result The result of the conversion
         * @return true if the conversion was successfull
         */
        static bool parseLongInteger( const char* value, long int& result );
        /** Convert a string, representing a numeric value, 
         * to an int variable. 
         * @param value The long int variable to be converted
         * @param result The result of the conversion
         * @return true if the conversion was successfull
         */
        static bool parseInteger( const char* value, int& result );
        /** Check whether a string, representing a numeric value, is
         * valid number under base <baseN>
         * @param value The long int variable to be converted
         * @param result The result of the conversion
         * @return true if the check was ok
         */
        static bool isNumeric( const char* value, int baseN );
        /** Return the negative version of a predicate name
         * @param name The predicate name to be converted
         * @return the name with a leading negation symbol.
         * The name is allocated dynamically and should
         * be deallocated by the caller.
         */
        static const char* getNegativeName( const std::string& name );
        /** Return the result of a system call to the program
         * whose executable name is given as input.
         * @param exeuctable The name of the program to be executed
         * @param input The input to be piped
         * @param outputBuffer This is the output parameter which stores the result of the system call
         * @param outputBufferSize The length of the returned output
         */
        static void systemCallTo(
                const char* executable,
                const std::string& input,
                char outputBuffer[],
                size_t outputBufferSize );
    };
    
};

#endif	/* UTILS_H */


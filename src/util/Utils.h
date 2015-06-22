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

        /*
         * Check if set1 is conteined in set2
         * @param set1 unordered_set
         * @param set2 unordered_set
         */
        template<class T>
        static bool isContained(T& set1,T& set2){
        	for(auto element:set1)
        		if(!set2.count(element))
        			return false;
        	return true;
        }

        /*
         * Check if set1 is disjoint with set2
         * @param set1 unordered_set
         * @param set2 unordered_set
         */
        template<class T>
        static bool isDisjoint(T& set1,T& set2){
        	for(auto element:set1)
        		if(set2.count(element))
        			return false;
        	return true;
        }

        /*
         * Do the union of set1 and set2 and put the result set in union
         * @param set1 unordered_set
         * @param set2 unordered_set
         * @param union_set unordered_set
         */
        template<class T>
        static void unionSet(T& set1,T& set2,T& union_set){
        	union_set.insert(set1.begin(),set2.begin());
        }

        /*
         * Do the intersection of set1 and set2 and put the result set in intersection_set
         * @param set1 unordered_set
         * @param set2 unordered_set
         * @param intersection_set unordered_set
         */
        template<class T>
        static void intersectionSet(T& set1,T& set2,T& intersection_set){
        	if(set1.size()<set2.size()){
            	for(auto element:set1)
            		if(set2.count(element))
            			intersection_set.insert(element);
        	}else {
            	for(auto element:set2)
            		if(set1.count(element))
            			intersection_set.insert(element);
        	}
        }

        /*
         * Do the difference of set1 and set2 and put the result set in difference
         * @param set1 unordered_set
         * @param set2 unordered_set
         * @param difference_set unordered_set
         */
        template<class T>
        static void differenceSet(T& set1,T& set2,T& difference_set){
        	if(set1.size()<set2.size()){
            	for(auto element:set1)
            		if(!set2.count(element))
            			difference_set.insert(element);
        	}else {
            	for(auto element:set2)
            		if(!set1.count(element))
            			difference_set.insert(element);
        	}
        }
    };
    
};

#endif	/* UTILS_H */


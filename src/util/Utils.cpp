#include "Utils.h"
#include <cstdlib>
#include <climits>

namespace DLV2
{
    
bool
Utils::parseLongInteger(
    const char* value,
    long int& result ) 
{
    char* err;
 
    int n=strtol(value, &err, 10);
    if ( *err )
        return false;
    
    result = n;
    return true;
}

bool
Utils::parseInteger(
    const char* value,
    int& result ) 
{
    char* err;
 
    int n=strtol(value, &err, 10);
    if ( *err || n < INT_MIN || n > INT_MAX )
        return false;
    
    result = n;
    return true;
}

};

/* 
 * File:   DLV2Facade.h
 * Author: cesco
 *
 * Created on 4 aprile 2014, 18.50
 */

#ifndef DLV2FACADE_H
#define	DLV2FACADE_H

#include "util/Constants.h"
#include <vector>
using namespace std;

class InputBuilder;

class DLV2Facade {
public:
    DLV2Facade() : outputSilent(false), aspCore2Strict(false), printProgram(false) { }
    ~DLV2Facade() { }
    
    void greetings();
    void readInput();
    void solve();
    void free();
    
    void setAspCore2Strict( bool asp2 ) { aspCore2Strict = asp2; }
    void setPrintProgram( bool pp ) { printProgram = pp; }
    void setInputHandlingPolicy( INPUT_HANDLING_POLICY );
    void setOutputPolicy( OUTPUT_POLICY );
    void setInputFiles( vector<const char*> files ) { inputFiles = files; }
    
private:

    bool outputSilent;
    bool aspCore2Strict;
    bool printProgram;
    vector<const char*> inputFiles;
};

#endif	/* DLV2FACADE_H */


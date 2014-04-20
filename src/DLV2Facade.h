/* 
 * File:   DLV2Facade.h
 * Author: cesco
 *
 * Created on 4 aprile 2014, 18.50
 */

#ifndef DLV2FACADE_H
#define	DLV2FACADE_H

#include "util/Constants.h"
#include "util/Options.h"

#include <vector>
using namespace std;

class InputBuilder;

// TODO: discuss the issue of options and facade methods

class DLV2Facade {
public:
    DLV2Facade() : options(*dlv2::Options::globalOptions()), builder(NULL) { }
    ~DLV2Facade();
    
    void greetings();
    int readInput();
    void solve();
    void free();
    
    dlv2::Options& getOptions() { return options; }

//    void setAspCore2Strict( bool asp2 ) { aspCore2Strict = asp2; }
//    void setPrintProgram( bool pp ) { printProgram = pp; }
//    void setInputHandlingPolicy( INPUT_HANDLING_POLICY );
//    void setOutputPolicy( OUTPUT_POLICY );
//    void setInputFiles( vector<const char*> files ) { inputFiles = files; }
    
private:

    dlv2::Options& options;

    InputBuilder* builder;

/*    bool outputSilent;
    bool aspCore2Strict;
    bool printProgram;
    vector<const char*> inputFiles;
    */
};

#endif	/* DLV2FACADE_H */


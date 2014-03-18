/* 
 * File:   SimpleInputBuilder.h
 * Author: cesco
 *
 * Created on 7 marzo 2014, 10.53
 */

#ifndef SIMPLEINPUTBUILDER_H
#define	SIMPLEINPUTBUILDER_H

#include "InputBuilder.h"
#include <vector>

class SimpleInputBuilder : public InputBuilder {
public:
    SimpleInputBuilder();
    ~SimpleInputBuilder();
    
    virtual void onRule();
    virtual void onConstraint();
    virtual void onQuery();
    virtual void addToHead();
    virtual void addToBody();
    virtual void onNafLiteral( bool naf = false );
    virtual void onAtom( bool isStrongNeg = false );
    virtual void predicateName( char* );
    virtual void onTerm( char* );
    virtual void onTerm( int );
    virtual void onFunction( char*, int );
    virtual void onTermDash();
    
    virtual Program& getProgram() { return *program; }
    
    bool isNumeric( const char*, int );
    
private:
    Program* program;
    vector<Atom> head;
    vector<Literal> body;
    Rule* currentRule;
    Literal* currentLiteral;
    Atom* currentAtom;
    string predName;
    Term* currentTerm;
    vector<string> localVariables;    
    vector<Term*> termStack;    
};

#endif	/* SIMPLEINPUTBUILDER_H */


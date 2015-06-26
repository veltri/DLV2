/* 
 * File:   IRISOutputBuilder.cpp
 * Author: cesco
 *
 * Created on 18 maggio 2015, 18.17
 */

#include "IRISOutputBuilder.h"

#include "../data/XProgram.h"
#include "../../util/Assert.h"

using namespace std;
using namespace DLV2::REWRITERS;

string
IRISOutputBuilder::toString() const
{
    stringstream output;
    for( XProgram::const_iterator itRule = input.beginRules(); itRule != input.endRules(); itRule++ )
    {
        unsigned varCounter = 0;
        XMapping renaming;
        // Head
        const XHead* head = itRule->getHead();
        vector< XAtom > renamedHeadAtoms;
        for( unsigned i=0; i<head->size(); i++ )
        {
            const XAtom& atom = head->at(i);
            vector< XTerm > renamedHeadTerms;
            for( unsigned j=0; j<atom.getTerms().size(); j++ )
            {
                const XTerm& term = atom.getTerms().at(j);
                XMapping::iterator itTerm = renaming.find(term);
                if( term.isVar() && itTerm == renaming.end() )
                {
                    stringstream sTerm;
                    sTerm << "?U" << varCounter++;
                    XTerm* renamedTerm = input.createStandardVariable(sTerm.str());
                    renaming.insert(pair< const XTerm&, const XTerm& >(term,*renamedTerm));
                    renamedHeadTerms.push_back(*renamedTerm);
                    delete renamedTerm;
                }
                else if( itTerm != renaming.end() )
                    renamedHeadTerms.push_back(itTerm->second);
                else
                    renamedHeadTerms.push_back(term);
            }
            XAtom* renamedAtom = input.createAtom(atom.getPredIndex(),renamedHeadTerms,atom.isTrueNegated());
            renamedHeadAtoms.push_back(*renamedAtom);
            delete renamedAtom;
        }
        XHead* renamedHead;
        if( head->isAtomic() )
            renamedHead = input.createAtomicHead(renamedHeadAtoms[0]);
        else if( head->isConjunctive() )
            renamedHead = input.createConjunctiveHead(renamedHeadAtoms);
        else
            renamedHead = input.createDisjunctiveHead(renamedHeadAtoms);
        // Body
        vector< XLiteral > renamedBodyLiterals;
        const XBody* body = itRule->getBody();
        assert_msg( body != NULL, "Null body" );
        for( unsigned i=0; i<body->size(); i++ )
        {
            const XAtom& atom = body->at(i).getAtom();
            vector< XTerm > renamedBodyTerms;
            for( unsigned j=0; j<atom.getTerms().size(); j++ )
            {
                const XTerm& term = atom.getTerms().at(j);
                XMapping::iterator itTerm = renaming.find(term);
                if( term.isVar() && itTerm == renaming.end() )
                {
                    stringstream sTerm;
                    sTerm << "?U" << varCounter++;
                    XTerm* renamedTerm = input.createStandardVariable(sTerm.str());
                    renaming.insert(pair< const XTerm&, const XTerm& >(term,*renamedTerm));
                    renamedBodyTerms.push_back(*renamedTerm);
                    delete renamedTerm;
                }
                else if( itTerm != renaming.end() )
                    renamedBodyTerms.push_back(itTerm->second);
                else
                    renamedBodyTerms.push_back(term);
            }
            XAtom* renamedAtom = input.createAtom(atom.getPredIndex(),renamedBodyTerms,atom.isTrueNegated());
            XLiteral* renamedLiteral = input.createLiteral(*renamedAtom,body->at(i).isNaf());
            renamedBodyLiterals.push_back(*renamedLiteral);
            delete renamedLiteral;
            delete renamedAtom;
        }
        XBody* renamedBody = input.createBody(renamedBodyLiterals);
        XRule* renamedRule = input.createRule(renamedHead,renamedBody);

        vector< unsigned > orderedHeadAtomPos;
        for( unsigned i=0; i<renamedHead->size(); i++ )
            orderedHeadAtomPos.push_back(i);
        vector< unsigned > orderedBodyAtomPos;
        for( unsigned i=0; i<renamedBody->size(); i++ )
            orderedBodyAtomPos.push_back(i);
        bubbleSort(*renamedRule,orderedHeadAtomPos,orderedBodyAtomPos);
        for( unsigned i=0; i<orderedHeadAtomPos.size(); i++ )
        {
            assert_msg( orderedHeadAtomPos[i] < renamedHead->size(), "Index out of range" );
            const XAtom& atom = renamedHead->at(orderedHeadAtomPos[i]);
            if( i > 0 )
                output << ", ";
            output << atom;
        }
        if( orderedBodyAtomPos.size() > 0 )
            output << " :- ";
        for( unsigned i=0; i<orderedBodyAtomPos.size(); i++ )
        {
            assert_msg( orderedBodyAtomPos[i] < body->size(), "Index out of range" );
            const XLiteral& literal = renamedBody->at(orderedBodyAtomPos[i]);
            if( i > 0 )
                output << ", ";
            output << literal;
        }
        output << "." << endl;
        delete renamedRule;
    }
    return output.str();
}

void
IRISOutputBuilder::bubbleSort(
    const XRule& rule,
    vector< unsigned >& headPos,
    vector< unsigned >& bodyPos ) const
{
    const XHead* head = rule.getHead();
    const XBody* body = rule.getBody();
    assert_msg( body != NULL, "Null body" );
    bool scambio = true;
    while( scambio )
    {
        scambio = false;
        for( unsigned i=0; i<headPos.size()-1; i++ )
            if( head->at(headPos[i]) > head->at(headPos[i+1]) )
            {
                unsigned tmp = headPos[i];
                headPos[i] = headPos[i+1];
                headPos[i+1] = tmp;
                scambio = true;
            }
    }
    scambio = true;
    while( scambio )
    {
        scambio = false;
        for( unsigned i=0; i<bodyPos.size()-1; i++ )
            if( body->at(bodyPos[i]) > body->at(bodyPos[i+1]) )
            {
                unsigned tmp = bodyPos[i];
                bodyPos[i] = bodyPos[i+1];
                bodyPos[i+1] = tmp;
                scambio = true;
            }
    }
}

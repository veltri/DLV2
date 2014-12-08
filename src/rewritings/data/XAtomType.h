/* 
 * File:   XAtomType.h
 * Author: pierfrancesco
 *
 * Created on 05 dicembre 2014, 15.51
 */

#ifndef XATOMTYPE_H
#define XATOMTYPE_H

namespace DLV2{ namespace REWRITERS{

    class XAtomType {
    public:
        XAtomType( const XAtomType& at ):
            schema(at.schema),
            constantPositions(at.constantPositions),
            variablePositions(at.variablePositions),
            nullPositions(at.nullPositions) { }
        ~XAtomType() { }

        const std::vector< XTerm::Type >& getSchema() const { return schema; }
        const std::vector< unsigned >& getConstantPositions() const { return constantPositions; }
        const std::vector< unsigned >& getVariablePositions() const { return variablePositions; }
        const std::vector< unsigned >& getNullPositions() const { return nullPositions; }
        bool operator==( const XAtomType& at ) const { return schema == at.schema; }
        bool operator!=( const XAtomType& at ) const { return !(*this == at); }

    private:
        friend class XAtom;

        XAtomType() { }

        void addToSchema( const XTerm::Type& type ){ schema.push_back(type); }
        void addToConstantPositions( unsigned pos ) { constantPositions.push_back(pos); }
        void addToVariablePositions( unsigned pos ) { variablePositions.push_back(pos); }
        void addToNullPositions( unsigned pos ) { nullPositions.push_back(pos); }

        std::vector< XTerm::Type > schema;
        std::vector< unsigned > constantPositions;
        std::vector< unsigned > variablePositions;
        std::vector< unsigned > nullPositions;
    };

};};

#endif /* XATOMTYPE_H */

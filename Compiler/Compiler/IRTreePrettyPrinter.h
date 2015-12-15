#pragma once

#include "Digrapg.h"
#include "IRTranslator.h"

class CIRMove;
class CIRExp;
class CIRJump;
class CIRCjump;
class CIRSeq;
class CIRConst;
class CIRName;
class CIRTemp;
class CIRBinop;
class CIRMem;
class CIRCall;
class CIREseq;
class CIRExpList;
class CIRLabel;
class IIRStm;
class IIRExp;

class CIRTreePrettyVisitor {
public:
    CIRTreePrettyVisitor( std::string treeFileName ) : treeRepresentation( treeFileName ), minId( 0 ) {}

    // ћетоды позвол€ют строить линейно св€занные деревь€
    void LinkedVisit( const IIRStm* node );
    void LinkedVisit( const IIRExp* node );

    void Visit( const CIRMove* node );

    void Visit( const CIRExp* node );

    void Visit( const CIRJump* node );

    void Visit( const CIRCjump* node );

    void Visit( const CIRSeq* node );

    void Visit( const CIRConst* node );

    void Visit( const CIRName* node );

    void Visit( const CIRTemp* node );

    void Visit( const CIRBinop* node );

    void Visit( const CIRMem* node );

    void Visit( const CIRCall* node );

    void Visit( const CIREseq* node );

    void Visit( const CIRExpList* node );

    void Visit( const CIRLabel* node );

    void Flush() { treeRepresentation.Flush(); }

private:

    int minId;

    std::string lastNodeName;

    CDigraph treeRepresentation;

    void nextNameWithId( std::string label );
};



#pragma once
#include "classes.h"
#include <stack>
#include "IRClasses.h"
#include "SymbolsTable.h"
#include "Frame.h"
#include "IRConditionalWrapper.h"
#include "IRTreePrettyPrinter.h"

class CIRMoveCall : public IIRStm {
public:
    CIRMoveCall( const CIRTemp* _dst, const CIRCall* _src ) : dst( _dst ), src( _src ) {}
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* kids ) const;
    virtual void Accept( CIRTreePrettyVisitor* p ) const { p->Visit( this ); }
private:
    const CIRTemp* dst;
    const CIRCall* src;
};

class CIRExpCall : public IIRStm {
public:
    CIRExpCall( const CIRCall* _call ) : call( _call ) {}
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* kids ) const;
    virtual void Accept( CIRTreePrettyVisitor* p ) const { p->Visit( this ); }
private:
    const CIRCall* call;
};

struct CIRStmExpList {
    CIRStmExpList( const IIRStm* _stm, const CIRExpList* _exprs ) : stm( _stm ), exprs( _exprs ) {}
    const IIRStm* stm;
    const CIRExpList* exprs;
};

class CCanon {
public:
    bool IsNop( const IIRStm* a );

    const IIRStm* SimplifySeq( const IIRStm* a, const IIRStm* b );

    bool IsCommutable( const IIRStm* a, const IIRExp* b );

    const IIRStm* DoStm( const CIRSeq* s );

    const IIRStm* DoStm( const CIRMove* s );

    const IIRStm* DoStm( const CIRExp* s );

    const IIRStm* DoStm( const IIRStm* s );

    const IIRStm* ReorderStm( const IIRStm* s );

    const CIRESeq* DoExp( const CIRESeq* e );

    const CIRESeq* DoExp( const IIRExp* e );

    const CIRESeq* ReorderExp( const IIRExp* e );

    const CIRStmExpList* Reorder( const CIRExpList* exps );

    const CIRSeq* Linear( const CIRSeq* s, const CIRSeq* l );

    const CIRSeq* Linear( const IIRStm* s, const CIRSeq* l );

    const CIRSeq* Linearize( const IIRStm* s );

private:
    static CIRStmExpList* nopNull;
};

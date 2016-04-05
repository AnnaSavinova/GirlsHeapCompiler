#include "IRCanonizator.h"

const CIRExpList* CIRMoveCall::Kids() const
{
    return src->Kids();
}

const IIRStm* CIRMoveCall::Build( const CIRExpList* kids ) const
{
    return new CIRMove( dst, src->Build( kids ) );
}

const CIRExpList* CIRExpCall::Kids() const
{
    return call->Kids();
}

const IIRStm* CIRExpCall::Build( const CIRExpList* kids ) const
{
    return new CIRExp( call->Build( kids ) );
}

CIRStmExpList* CCanon::nopNull = new CIRStmExpList( new CIRExp( new CIRConst( 0 ) ), 0 );

bool CCanon::IsNop( const IIRStm* a )
{
    return dynamic_cast<const CIRExp*>( a ) != 0
        && dynamic_cast<const CIRConst*>( ( dynamic_cast<const CIRExp*>( a ) )->exp ) != 0;
}

const IIRStm* CCanon::SimplifySeq( const IIRStm* a, const IIRStm* b )
{
    if ( IsNop( a ) ) {
        return b;
    } else if ( IsNop( b ) ) {
        return a;
    } else {
        return new CIRSeq( a, b );
    }
}

bool CCanon::IsCommutable( const IIRStm* a, const IIRExp* b )
{
    return IsNop( a ) || dynamic_cast<const CIRName*>( b ) != 0 || dynamic_cast<const CIRConst*>( b ) != 0;
}

const IIRStm* CCanon::DoStm( const CIRSeq* s )
{
    return SimplifySeq( DoStm( s->left ), DoStm( s->right ) );
}

const IIRStm* CCanon::DoStm( const CIRMove* s )
{
    if ( dynamic_cast<const CIRTemp*>( s->Dst() ) != 0 &&
        dynamic_cast<const CIRCall*>( s->Src() ) != 0 ) {
        return ReorderStm( new CIRMoveCall( dynamic_cast<const CIRTemp*>( s->Dst() ),
            dynamic_cast<const CIRCall*>( s->Src() ) ) );
    } else if ( dynamic_cast<const CIRESeq*>( s->Dst() ) != 0 ) {
        return DoStm( new CIRSeq( ( dynamic_cast<const CIRESeq*>( s->Dst() ) )->stm,
            new CIRMove( ( dynamic_cast<const CIRESeq*>( s->Dst() ) )->exp, s->Src() ) ) );
    } else {
        return ReorderStm( s );
    }
}

const IIRStm* CCanon::DoStm( const CIRExp* s )
{
    if ( dynamic_cast<const CIRCall*>( s->exp ) != 0 ) {
        //оборачиваем вызов функции, результат будет же отброшен, т.к. CExp
        return ReorderStm( new CIRExpCall( dynamic_cast<const CIRCall*>( s->exp ) ) );
    } else {
        return ReorderStm( s );
    }
}

const IIRStm* CCanon::DoStm( const IIRStm* s )
{
    if ( dynamic_cast<const CIRSeq*>( s ) != 0 ) {
        return DoStm( dynamic_cast<const CIRSeq*>( s ) );
    } else if ( dynamic_cast<const CIRMove*>( s ) != 0 ) {
        return DoStm( dynamic_cast<const CIRMove*>( s ) );
    } else if ( dynamic_cast<const CIRExp*>( s ) != 0 ) {
        if ( IsNop( s ) ) {
            return 0;
        } else {
            return DoStm( dynamic_cast<const CIRExp*>( s ) );
        }
    } else {
        return ReorderStm( s );
    }
}

const IIRStm* CCanon::ReorderStm( const IIRStm* s )
{
    if ( s == nullptr ) {
        return 0;
    }
    const CIRStmExpList* x = Reorder( s->Kids() );
    return SimplifySeq( x->stm, s->Build( x->exprs ) );
}

const CIRESeq* CCanon::DoExp( const CIRESeq* e )
{
    if (e == nullptr) {
        return nullptr;
    }
    const IIRStm* stmt = DoStm( e->stm );
    const CIRESeq* b = DoExp( e->exp );
    if (b == nullptr) {
        return new CIRESeq(SimplifySeq(stmt, nullptr), nullptr);
    }
    return new CIRESeq( SimplifySeq( stmt, b->stm ), b->exp );
}

const CIRESeq* CCanon::DoExp( const IIRExp* e )
{
    if ( dynamic_cast<const CIRESeq*>( e ) != 0 ) {
        return DoExp( dynamic_cast<const CIRESeq*>( e ) );
    } else {
        return ReorderExp( e );
    }
}

const CIRESeq* CCanon::ReorderExp( const IIRExp* e )
{
    const CIRStmExpList* x = Reorder( e->Kids() );
    return new CIRESeq( x->stm, e->Build( x->exprs ) );
}

const CIRStmExpList* CCanon::Reorder( const CIRExpList* exprs )
{
    if ( exprs == nullptr || exprs->head == nullptr ) {
        return nopNull;
    } else {
        const IIRExp* a = exprs->head;
        if ( dynamic_cast<const CIRCall*>( a ) != 0 ) {
            //встретили функцию, запишем результат в Temp и вернем его, обернув в Eseq
            CTemp* t = new CTemp();
            IIRExp* e = new CIRESeq( new CIRMove( new CIRTemp( t ), a ), new CIRTemp( t ) );
            return Reorder( new CIRExpList( e, exprs->tail ) );
        } else {
            const CIRESeq* aa = DoExp( a );
            const CIRStmExpList* bb = Reorder( static_cast< const CIRExpList* >( exprs->tail ) );
            if ( IsCommutable( bb->stm, aa->exp ) ) {
                return new CIRStmExpList( SimplifySeq( aa->stm, bb->stm ),
                    new CIRExpList( aa->exp, bb->exprs ) );
            } else {
                CTemp* t = new CTemp();
                return new CIRStmExpList( SimplifySeq( aa->stm,
                    SimplifySeq( new CIRMove( new CIRTemp( t ),
                        aa->exp ),
                        bb->stm ) ),
                    new CIRExpList( new CIRTemp( t ), bb->exprs ) );
            }
        }
    }
}

const CIRSeq* CCanon::Linear( const CIRSeq* s, const CIRSeq* l )
{
    return Linear( s->left, Linear( s->right, l ) );
}

const CIRSeq* CCanon::Linear( const IIRStm* s, const CIRSeq* l )
{
    if ( dynamic_cast<const CIRSeq*>( s ) != 0 ) {
        return Linear( dynamic_cast<const CIRSeq*>( s ), l );
    } else {
        if ( s != 0 ) {
            return new CIRSeq( s, l );
        } else {
            return l;
        }
    }
}

const CIRSeq* CCanon::Linearize( const IIRStm* s )
{
    return Linear( DoStm( s ), nullptr );
}

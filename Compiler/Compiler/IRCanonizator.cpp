#include "IRCanonizator.h"

const CIRExpList* CIRMoveCall::Kids() const
{
    return src->Kids();
}

//нужно часть вершин мы не хотели менять, чтобы call работал корректно, теперь нужно все перестроить
//и вернуть на свои места. Просто записываем результат во временную переменную
const IIRStm* CIRMoveCall::Build( const CIRExpList* kids ) const
{
    return new CIRMove( dst, src->Build( kids ) );
}

const CIRExpList* CIRExpCall::Kids() const
{
    return call->Kids();
}

//все то же самое, как в CIRMoveCall, только для expr. 
const IIRStm* CIRExpCall::Build( const CIRExpList* kids ) const
{
    return new CIRExp( call->Build( kids ) );
}

//nop он и в африке nop.
CIRStmExpList* CCanon::nopNull = new CIRStmExpList( new CIRExp( new CIRConst( 0 ) ), 0 );

//проверка stmt, является ли оно константой.
bool CCanon::IsNop( const IIRStm* a )
{
    return dynamic_cast<const CIRExp*>( a ) != 0
        && dynamic_cast<const CIRConst*>( ( dynamic_cast<const CIRExp*>( a ) )->exp ) != 0;
}

//если nop, то можно упростить дерево
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

//проверка на коммутативность, чтобы можно было упрощать дерево
bool CCanon::IsCommutable( const IIRStm* a, const IIRExp* b )
{
    return IsNop( a ) || dynamic_cast<const CIRName*>( b ) != 0 || dynamic_cast<const CIRConst*>( b ) != 0;
}

//просто рекурсивный обход cseq
const IIRStm* CCanon::DoStm( const CIRSeq* s )
{
    return SimplifySeq( DoStm( s->left ), DoStm( s->right ) );
}

//рекурсивная обработка Move
const IIRStm* CCanon::DoStm( const CIRMove* s )
{
    if ( dynamic_cast<const CIRTemp*>( s->Dst() ) != 0 &&
        dynamic_cast<const CIRCall*>( s->Src() ) != 0 ) {
        //встретили конструкцию, которую нужно сохранить, оборачиваем ее в CIRMoveCall.
        return ReorderStm( new CIRMoveCall( dynamic_cast<const CIRTemp*>( s->Dst() ),
            dynamic_cast<const CIRCall*>( s->Src() ) ) );
    } else if ( dynamic_cast<const CIRESeq*>( s->Dst() ) != 0 ) {
        //Move делается в eseq, тогда делаем сначала stm из eseq, потом записываем
        //exp из eseq в move, короче просто переподвесили вершины. 
        return DoStm( new CIRSeq( ( dynamic_cast<const CIRESeq*>( s->Dst() ) )->stm,
            new CIRMove( ( dynamic_cast<const CIRESeq*>( s->Dst() ) )->exp, s->Src() ) ) );
    } else {
        return ReorderStm( s );
    }
}

//часть рекурсии для обработки CExp
const IIRStm* CCanon::DoStm( const CIRExp* s )
{
    if ( dynamic_cast<const CIRCall*>( s->exp ) != 0 ) {
        //оборачиваем вызов функции, результат будет же отброшен, т.к. CExp
        return ReorderStm( new CIRExpCall( dynamic_cast<const CIRCall*>( s->exp ) ) );
    } else {
        return ReorderStm( s );
    }
}

//часть рекурсии stmt, в первых случаях все корректно и просто рекурсивный вызов для детей
//иначе проверяем stmt на осмысленность(CExp) или reorder
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

//восстанавливаем и упрощаем дерево со stmt в вершине
const IIRStm* CCanon::ReorderStm( const IIRStm* s )
{
    if ( s == nullptr ) {
        return 0;
    }
    const CIRStmExpList* x = Reorder( s->Kids() );
    return SimplifySeq( x->stm, s->Build( x->exprs ) );
}

//получает некоторый eseq и упрощает его, через проверку на некоммутативность
//вроде как в простейшем примере из презентации
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

//чтобы пользоваться простейшим упрощением, нужно уметь приводить exp к eseq
const CIRESeq* CCanon::DoExp( const IIRExp* e )
{
    //если это eseq, то просто пытаемся что-то поменять рекурсивно.
    //иначе это умеет делать специальный reorder
    if ( dynamic_cast<const CIRESeq*>( e ) != 0 ) {
        return DoExp( dynamic_cast<const CIRESeq*>( e ) );
    } else {
        return ReorderExp( e );
    }
}

//вернет корректный eseq, при этом вынеся вроде бы все stmt, которые надо сначала
//посчитать, чтобы вычислять exp.
const CIRESeq* CCanon::ReorderExp( const IIRExp* e )
{
    const CIRStmExpList* x = Reorder( e->Kids() );
    return new CIRESeq( x->stm, e->Build( x->exprs ) );
}

//принимает на вход список Tree::IExp’ов
//возвращать два списка
//Tree.Stm – все действия, которые должны быть проделаны до начала вычислений 
//(или 𝐸𝑋𝑃(𝐶𝑂𝑁𝑆𝑇(0)), а так же некоммутирующие подвыражения.
//Tree.ExpList – выражения без Tree.Stm’ов
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
            //иначе обрабатываем сам expr
            const CIRESeq* aa = DoExp( a );
            //и рекурсивно обрабатываем сам список
            const CIRStmExpList* bb = Reorder( static_cast< const CIRExpList* >( exprs->tail ) );
            //если коммутируют stmt и expr в вершинах, то упрощаем (simplify) и подвешиваем вершины
            if ( IsCommutable( bb->stm, aa->exp ) ) {
                return new CIRStmExpList( SimplifySeq( aa->stm, bb->stm ),
                    new CIRExpList( aa->exp, bb->exprs ) );
            } else {
                //иначе делаем как в случае 3 презентации. коротко:
                //нужно сохранить результат некоммутирущий и подставить в соответствующие места
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

//работа со списками
const CIRSeq* CCanon::Linear( const CIRSeq* s, const CIRSeq* l )
{
    return Linear( s->left, Linear( s->right, l ) );
}

//два seq переподвешиваем, чтобы получить все seq на одной ветке
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

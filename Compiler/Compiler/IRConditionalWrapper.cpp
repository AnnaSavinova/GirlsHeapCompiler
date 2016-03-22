//#include "IRConditionalWrapper.h"
//
//const IIRStm* CConditionalWrapper::ToStm() const
//{
//    CLabel* tempLabel = new CLabel();
//    CIRLabel* irLabel = new CIRLabel( tempLabel );
//    const IIRStm* cond = ToConditional( tempLabel, tempLabel );
//    CIRSeq* seq = new CIRSeq( cond, irLabel );
//    return seq;
//}
//
//const IIRExp* CConditionalWrapper::ToExp() const
//{
//    CTemp* temp = new CTemp();
//    CIRTemp* irTemp = new CIRTemp( *temp );
//    CIRMove* moveTrue = new CIRMove( irTemp, new CIRConst( 1 ) );
//    CIRMove* moveFalse = new CIRMove( irTemp, new CIRConst( 0 ) );
//    CLabel* trueLabel = new CLabel();
//    CLabel* falseLabel = new CLabel();
//    CIRLabel* trueIRLabel = new CIRLabel( trueLabel );
//    IRTree::CLabel* falseIRLabel = new IRTree::CLabel( falseLabel );
//    IRTree::CSeq* seqTrue = new IRTree::CSeq( trueIRLabel, moveTrue );
//    IRTree::CSeq* seqFalse = new IRTree::CSeq( falseIRLabel, moveFalse );
//    const IRTree::IStm* cond = ToConditional( trueLabel, falseLabel );
//    IRTree::CEseq* eseq = new IRTree::CEseq( cond, irTemp );
//    return eseq;
//}
//
//const IRTree::IStm* CConditionalWrapper::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const
//{
//    auto asBinop = dynamic_cast< const IRTree::CBinop* >( exp );
//    if( asBinop != nullptr ) {
//        return binopToConditional( asBinop, t, f );
//    } else {
//        return new IRTree::CCjump( IRTree::CJ_NotEqual, exp, new IRTree::CConst( 0 ), t, f );
//    }
//}
//
//const IRTree::IStm* CConditionalWrapper::binopToConditional( const IRTree::CBinop* binop, const Temp::CLabel* t, const Temp::CLabel* f ) const
//{
//    switch( binop->binop ) {
//        case IRTree::B_And:
//            return andBinopToConditional( binop, t, f );
//        case IRTree::B_Less:
//            return new IRTree::CCjump( IRTree::CJ_Less, binop->left.get(), binop->right.get(), t, f );
//        case IRTree::B_Greater:
//            return new IRTree::CCjump( IRTree::CJ_Greater, binop->left.get(), binop->right.get(), t, f );
//        case IRTree::B_Plus:
//        case IRTree::B_Minus:
//        case IRTree::B_Mul:
//        case IRTree::B_Division:
//        case IRTree::B_Xor:
//            return new IRTree::CCjump( IRTree::CJ_NotEqual, binop, new IRTree::CConst( 0 ), t, f );
//        default:
//            assert( false );
//            return nullptr;
//    }
//}
//
//const IRTree::IStm* CConditionalWrapper::andBinopToConditional( const IRTree::CBinop* binop, const Temp::CLabel* t, const Temp::CLabel* f ) const
//{
//    Temp::CLabel* firstTrueLabel = new Temp::CLabel();
//    IRTree::CLabel* firstTrueIRLabel = new IRTree::CLabel( firstTrueLabel );
//
//    // Рекурсивно смотрим аргументы
//    CConditionalWrapper leftWrapper( binop->left.get() );
//    CConditionalWrapper rightWrapper( binop->right.get() );
//
//    return new IRTree::CSeq( leftWrapper.ToConditional( firstTrueLabel, f ), firstTrueIRLabel, rightWrapper.ToConditional( t, f ) );
//}
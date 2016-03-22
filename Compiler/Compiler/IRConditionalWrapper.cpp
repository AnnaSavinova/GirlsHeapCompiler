#include "IRConditionalWrapper.h"

IIRStm* CConditionalWrapper::ToStm() const
{
    CLabel* tempLabel = new CLabel();
    CIRLabel* irLabel = new CIRLabel( tempLabel );
    IIRStm* cond = ToConditional( tempLabel, tempLabel );
    CIRSeq* seq = new CIRSeq( cond, irLabel );
    return seq;
}

IIRExp* CConditionalWrapper::ToExp() const
{
    CTemp* temp = new CTemp();
    CIRTemp* irTemp = new CIRTemp( temp );
    CIRMove* moveTrue = new CIRMove( irTemp, new CIRConst( 1 ) );
    CIRMove* moveFalse = new CIRMove( irTemp, new CIRConst( 0 ) );
    CLabel* trueLabel = new CLabel();
    CLabel* falseLabel = new CLabel();
    CIRLabel* trueIRLabel = new CIRLabel( trueLabel );
    CIRLabel* falseIRLabel = new CIRLabel( falseLabel );
    CIRSeq* seqTrue = new CIRSeq( trueIRLabel, moveTrue );
    CIRSeq* seqFalse = new CIRSeq( falseIRLabel, moveFalse );
    IIRStm* cond = ToConditional( trueLabel, falseLabel );
    CIRESeq* eseq = new CIRESeq( cond, irTemp );
    return eseq;
}

IIRStm* CConditionalWrapper::ToConditional( CLabel* t, CLabel* f ) const
{
    auto asBinop = dynamic_cast< CIRBinOp* >( exp );
    if( asBinop != nullptr ) {
        return binopToConditional( asBinop, t, f );
    } else {
        return new CIRCjump( NE, exp, new CIRConst( 0 ), t, f );
    }
}

IIRStm* CConditionalWrapper::binopToConditional( CIRBinOp* binop, CLabel* t, CLabel* f ) const
{
    switch( binop->operation ) {
        case AND:
            return andBinopToConditional( binop, t, f );
        case LT:
            return new CIRCjump( LT, binop->left, binop->right, t, f );
        case GT:
            return new CIRCjump( GT, binop->left, binop->right, t, f );
		case LE:
			return new CIRCjump(LE, binop->left, binop->right, t, f);
		case GE:
			return new CIRCjump(GE, binop->left, binop->right, t, f);
        case PLUS:
        case MINUS:
        case MUL:
        case DIV:
        case XOR:
            return new CIRCjump( NE, binop, new CIRConst( 0 ), t, f );
        default:
            assert( false );
            return nullptr;
    }
}

IIRStm* CConditionalWrapper::andBinopToConditional( CIRBinOp* binop, CLabel* t, CLabel* f ) const
{
    CLabel* firstTrueLabel = new CLabel();
    CIRLabel* firstTrueIRLabel = new CIRLabel( firstTrueLabel );

    // Рекурсивно смотрим аргументы
    CConditionalWrapper leftWrapper( binop->left );
    CConditionalWrapper rightWrapper( binop->right );

    return new CIRSeq( new CIRSeq( leftWrapper.ToConditional( firstTrueLabel, f ), firstTrueIRLabel), rightWrapper.ToConditional( t, f ) );
}
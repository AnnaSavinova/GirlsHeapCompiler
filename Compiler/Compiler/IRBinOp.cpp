#include "IRBinOp.h"

CIRBinOp::CIRBinOp(EBinOp _operation, IIRExp * _left, IIRExp * _right) : operation(_operation), left(_left), right(_right)
{
}

const CIRExpList * CIRBinOp::Kids() const
{
    return nullptr;
}

const IIRExp * CIRBinOp::Build( const CIRExpList* ) const
{
    return nullptr;
}

CIRBinOp::~CIRBinOp()
{
}

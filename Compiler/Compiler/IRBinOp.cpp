#include "IRBinOp.h"

CIRBinOp::CIRBinOp(EBinOp _operation, const IIRExp * _left, const IIRExp * _right) : operation(_operation), left(_left), right(_right)
{
}

const CIRExpList * CIRBinOp::Kids() const
{
    std::cout << "BIONP KIDS " << std::endl;
    return new CIRExpList(left, new CIRExpList(right, nullptr));
}

const IIRExp * CIRBinOp::Build( const CIRExpList* kids ) const
{
    return new CIRBinOp(operation, kids->head, kids->tail->head);
}

CIRBinOp::~CIRBinOp()
{
}

#include "IRBinOp.h"

CIRBinOp::CIRBinOp(EBinOp _operation, IIRExp * _left, IIRExp * _right) : operation(_operation), left(_left), right(_right)
{
}

CIRBinOp::~CIRBinOp()
{
}

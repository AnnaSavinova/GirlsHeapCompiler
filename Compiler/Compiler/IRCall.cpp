#include "IRCall.h"

CIRCall::CIRCall( CSymbol * _func , CIRExpList* _args ) : func(_func) , args(_args)
{
}

CIRCall::~CIRCall()
{
}

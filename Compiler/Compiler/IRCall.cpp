#include "IRCall.h"

CIRCall::CIRCall( IIRExp* _func , CIRExpList* _args ) : func(_func) , args(_args)
{
}

const CIRExpList * CIRCall::Kids() const
{
    return nullptr;
}

const IIRExp * CIRCall::Build( const CIRExpList* ) const
{
    return nullptr;
}


CIRCall::~CIRCall()
{
}

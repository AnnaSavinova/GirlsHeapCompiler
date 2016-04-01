#include "IRCall.h"

CIRCall::CIRCall( const IIRExp* _func , const CIRExpList* _args ) : func(_func) , args(_args)
{
}

const CIRExpList * CIRCall::Kids() const
{
    return new CIRExpList(func, args);
}

const IIRExp * CIRCall::Build( const CIRExpList* kids ) const
{
    return new CIRCall(kids->head, kids->tail);
}


CIRCall::~CIRCall()
{
}

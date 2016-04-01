#include "IRMem.h"

CIRMem::CIRMem(const IIRExp * _expression) : exp(_expression)
{
}

const CIRExpList * CIRMem::Kids() const
{
    return new CIRExpList(exp, nullptr);
}

const IIRExp * CIRMem::Build( const CIRExpList * kids ) const
{
    return new CIRMem(kids->head);
}

CIRMem::~CIRMem()
{
}

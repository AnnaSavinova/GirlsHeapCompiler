#include "IRMem.h"

CIRMem::CIRMem(const IIRExp * _expression) : exp(_expression)
{
}

const CIRExpList * CIRMem::Kids() const
{
    return nullptr;
}

const IIRExp * CIRMem::Build( const CIRExpList * ) const
{
    return nullptr;
}

CIRMem::~CIRMem()
{
}

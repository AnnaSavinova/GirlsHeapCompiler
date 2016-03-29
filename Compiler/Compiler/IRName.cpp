#include "IRName.h"

CIRName::CIRName(CLabel * _label) : label(_label)
{
}

const CIRExpList * CIRName::Kids() const
{
    return nullptr;
}

const IIRExp * CIRName::Build( const CIRExpList * ) const
{
    return nullptr;
}

CIRName::~CIRName()
{
}

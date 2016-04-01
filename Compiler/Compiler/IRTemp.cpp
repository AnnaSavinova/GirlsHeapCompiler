#include "IRTemp.h"

CIRTemp::CIRTemp(const CTemp * _temp) : temp(_temp)
{
}

const CIRExpList * CIRTemp::Kids() const
{
    return nullptr;
}

const IIRExp * CIRTemp::Build( const CIRExpList * ) const
{
    return new CIRTemp(temp);
}

CIRTemp::~CIRTemp()
{
}

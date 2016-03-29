#include "IRExp.h"

const IIRStm * CIRExp::Build( const CIRExpList* ) const
{
    return nullptr;
}

CIRExp::~CIRExp()
{}

CIRExp::CIRExp( const IIRExp* _exp ) : exp(_exp)
{}

const CIRExpList * CIRExp::Kids() const
{
    return nullptr;
}

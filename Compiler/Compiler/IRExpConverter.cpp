#include "IRExpConverter.h"
#include "IRExp.h"

CIRExpConverter::~CIRExpConverter()
{}

CIRExpConverter::CIRExpConverter( IIRExp * _exp ) : exp( _exp )
{}

IIRExp * CIRExpConverter::ToExp() const
{
    return exp;
}

IIRStm * CIRExpConverter::ToStm() const
{
    return new CIRExp( exp );
}

IIRStm * CIRExpConverter::ToConditional( CLabel * t, CLabel * f ) const
{
    return nullptr;
}

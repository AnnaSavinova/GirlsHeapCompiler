#include "IRExpConverter.h"
#include "IRExp.h"

CIRExpConverter::~CIRExpConverter()
{}

CIRExpConverter::CIRExpConverter( const IIRExp * _exp ) : exp( _exp )
{}

const IIRExp * CIRExpConverter::ToExp() const
{
    return exp;
}

const IIRStm * CIRExpConverter::ToStm() const
{
    return new CIRExp( exp );
}

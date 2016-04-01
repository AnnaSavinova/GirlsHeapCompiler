#include "IRConst.h"


CIRConst::CIRConst( int _value ) : value( _value )
{}

const CIRExpList * CIRConst::Kids() const
{
    return nullptr;
}

const IIRExp * CIRConst::Build( const CIRExpList* ) const
{
    return this;
}

CIRConst::~CIRConst()
{}

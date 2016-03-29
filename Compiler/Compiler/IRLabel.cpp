#include "IRLabel.h"


CIRLabel::CIRLabel( CLabel * _label ) : label( _label )
{}

const CIRExpList * CIRLabel::Kids() const
{
    return nullptr;
}

const IIRStm * CIRLabel::Build( const CIRExpList* ) const
{
    return nullptr;
}

CIRLabel::~CIRLabel()
{}

#include "IRLabel.h"


CIRLabel::CIRLabel( const CLabel * _label ) : label( _label )
{}

const CIRExpList * CIRLabel::Kids() const
{
    return nullptr;
}

const IIRStm * CIRLabel::Build( const CIRExpList* ) const
{
    return new CIRLabel(label);
}

CIRLabel::~CIRLabel()
{}

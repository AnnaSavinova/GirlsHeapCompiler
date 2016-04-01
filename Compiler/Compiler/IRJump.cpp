#include "IRJump.h"


CIRJump::CIRJump( const CLabel* _label ) : label( _label )
{}

const CIRExpList * CIRJump::Kids() const
{
    return nullptr;
}

const IIRStm * CIRJump::Build( const CIRExpList* ) const
{
    return new CIRJump(label);
}


CIRJump::~CIRJump()
{}

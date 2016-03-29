#include "IRJump.h"


CIRJump::CIRJump( CLabel* _label ) : label( _label )
{}

const CIRExpList * CIRJump::Kids() const
{
    return nullptr;
}

const IIRStm * CIRJump::Build( const CIRExpList* ) const
{
    return nullptr;
}


CIRJump::~CIRJump()
{}

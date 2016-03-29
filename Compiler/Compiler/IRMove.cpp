#include "IRMove.h"


CIRMove::CIRMove( const IIRExp* _dst, const IIRExp* _src ) : dst( _dst ), src( _src )
{}

const CIRExpList * CIRMove::Kids() const
{
    return nullptr;
}

const IIRStm * CIRMove::Build( const CIRExpList * ) const
{
    return nullptr;
}

CIRMove::~CIRMove()
{}

const IIRExp * CIRMove::Dst() const
{
    return dst;
}

const IIRExp * CIRMove::Src() const 
{
    return src;
}

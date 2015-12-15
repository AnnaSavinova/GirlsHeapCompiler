#include "IRMove.h"


CIRMove::CIRMove( const IIRExp* _dst, const IIRExp* _src ) : dst( _dst ), src( _src )
{}

CIRMove::~CIRMove()
{}

const IIRExp * CIRMove::Dst()
{
    return dst;
}

const IIRExp * CIRMove::Src()
{
    return src;
}

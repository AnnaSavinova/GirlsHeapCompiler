#include "IRMove.h"


CIRMove::CIRMove( const IIRExp* _dst, const IIRExp* _src ) : dst( _dst ), src( _src )
{}

const CIRExpList * CIRMove::Kids() const
{
  return new CIRExpList(dst, new CIRExpList(src, nullptr));
}

const IIRStm * CIRMove::Build( const CIRExpList * kids ) const
{
  return new CIRMove(kids->head, kids->tail->head);
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

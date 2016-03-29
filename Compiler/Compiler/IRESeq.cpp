#include "IRESeq.h"

const CIRExpList * CIRESeq::Kids() const
{
    return nullptr;
}

const IIRExp * CIRESeq::Build( const CIRExpList* ) const
{
    return nullptr;
}

CIRESeq::~CIRESeq()
{
}

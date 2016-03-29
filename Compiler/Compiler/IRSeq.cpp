#include "IRSeq.h"

const CIRExpList * CIRSeq::Kids() const
{
    return nullptr;
}

const IIRStm * CIRSeq::Build( const CIRExpList * ) const
{
    return nullptr;
}

CIRSeq::CIRSeq( std::list<IIRStm*> list ) : left(list.front())
{
    list.pop_front();
    right = new CIRSeq( list );
}

CIRSeq::~CIRSeq()
{}

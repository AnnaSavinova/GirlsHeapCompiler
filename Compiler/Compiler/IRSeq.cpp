#include "IRSeq.h"

CIRSeq::CIRSeq( IIRStm * _left, IIRStm * _right ) : left( _left ), right( _right )
{}

CIRSeq::CIRSeq( std::list<IIRStm*> list ) : left(list.front())
{
    list.pop_front();
    right = new CIRSeq( list );
}

CIRSeq::~CIRSeq()
{}

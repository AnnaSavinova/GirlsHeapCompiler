#include "IRCjump.h"

CIRCjump::CIRCjump( const EBinOp _relop, const IIRExp * _left, const IIRExp * _right, const CLabel * _ifTrue, const CLabel * _ifFalse ) :
    relop( _relop ), left( _left ), right( _right), ifTrue( _ifTrue ), ifFalse( _ifFalse )
{}


CIRCjump::~CIRCjump()
{}

const CIRExpList * CIRCjump::Kids() const
{
    return new CIRExpList( left, new CIRExpList( right, nullptr ) );
}

const IIRStm * CIRCjump::Build( const CIRExpList* kids) const
{
    return new CIRCjump( relop, kids->head, kids->tail->head, ifTrue, ifFalse );
}

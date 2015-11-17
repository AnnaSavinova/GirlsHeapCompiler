#include "IRCjump.h"

CIRCjump::CIRCjump( int _relop, IIRExp * _left, IIRExp * _right, CLabel * _ifTrue, CLabel * _ifFalse ) : relop( _relop ), left( _left ), right( _right), ifTrue( _ifTrue ), ifFalse( _ifFalse )
{}

CIRCjump::~CIRCjump()
{}

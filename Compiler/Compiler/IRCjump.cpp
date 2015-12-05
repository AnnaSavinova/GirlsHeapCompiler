#include "IRCjump.h"

CIRCjump::CIRCjump( EBinOp _relop, IIRExp * _left, IIRExp * _right, CIRLabel * _ifTrue, CIRLabel * _ifFalse ) : relop( _relop ), left( _left ), right( _right), ifTrue( _ifTrue ), ifFalse( _ifFalse )
{}

CIRCjump::~CIRCjump()
{}

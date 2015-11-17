#include "IRSeq.h"

CIRSeq::CIRSeq( IIRStm * _left, IIRStm * _right ) : left( _left ), right( _right )
{}

CIRSeq::~CIRSeq()
{}

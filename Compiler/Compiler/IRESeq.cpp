#include "IRESeq.h"

CIRESeq::CIRESeq(IIRStm * _stm, IIRExp * _exp) : statement(_stm), expression(_exp)
{
}

CIRESeq::~CIRESeq()
{
}

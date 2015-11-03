#include "Number.h"



CNumber::CNumber( int _number, int _line ) : number(_number)
{
	line = _line;
}


CNumber::~CNumber()
{}

int CNumber::Number() const
{
    return number;
}

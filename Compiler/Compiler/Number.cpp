#include "Number.h"



CNumber::CNumber( int _number) : number(_number)
{}


CNumber::~CNumber()
{}

int CNumber::Number() const
{
    return number;
}

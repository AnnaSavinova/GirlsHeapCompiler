#include "NewInt.h"



CNewInt::CNewInt( IExp* exp ) : expression(exp)
{
    assert( expression != nullptr );
}


CNewInt::~CNewInt()
{
    delete expression;
}

#include "BinExp.h"



CBinExp::CBinExp( IExp* exp1, IExp* exp2, std::string op ) : expression1(exp1), expression2(exp2), operation(op)
{
    assert( exp1 != nullptr );
    assert( exp2 != nullptr );
}


CBinExp::~CBinExp()
{
    delete expression1;
    delete expression2;
}

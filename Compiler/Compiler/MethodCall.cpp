#include "MethodCall.h"

CMethodCall::CMethodCall( IExp* _exp, std::string _id, IExpList* _args, int _line ) :  exp(_exp), id( symbolStorage.Get(_id) ), args(_args)
{
	line = _line;
}


CMethodCall::~CMethodCall()
{}

IExp * CMethodCall::Exp() const
{
    return exp;
}

CSymbol* CMethodCall::Id() const
{
    return id;
}

IExpList * CMethodCall::Args() const
{
    return args;
}

#include "MethodCall.h"

CMethodCall::CMethodCall( IExp* _exp, std::string _id, IExpList* _args ) : exp(_exp), id(_id), args(_args)
{}


CMethodCall::~CMethodCall()
{}

IExp * CMethodCall::Exp() const
{
    return exp;
}

std::string CMethodCall::Id() const
{
    return id;
}

IExpList * CMethodCall::Args() const
{
    return args;
}

#pragma once
#include "common.h"

class CMethodCall : public IExp, public CCoord
{
public:
    CMethodCall( IExp*, std::string, IExpList*, int _line );
    ~CMethodCall();

    IExp* Exp() const;
    CSymbol* Id() const;
    IExpList* Args() const;

    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    IExp* exp;
    CSymbol* id;
    IExpList* args;
};


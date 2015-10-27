#pragma once
#include "common.h"

class CMethodCall : public IExp {
public:
    CMethodCall( IExp*, std::string, IExpList* );
    ~CMethodCall();

    IExp* Exp() const;
    std::string Id() const;
    IExpList* Args() const;

    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    IExp* exp;
    std::string id;
    IExpList* args;
};


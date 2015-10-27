#pragma once
#include "common.h"

class CElementAssignment : public IStatement {
public:
    CElementAssignment( std::string, IExp*, IExp* );
    ~CElementAssignment();

    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    std::string id;
    IExp* exp1;
    IExp* exp2;
};


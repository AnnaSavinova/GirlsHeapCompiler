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

    std::string Id() const;
    const IExp* Exp1() const;
    const IExp* Exp2() const;
private:
    std::string id;
    IExp* exp1;
    IExp* exp2;
};


#pragma once
#include "common.h"

class CElementAssignment : public IStatement, public CCoord
{
public:
    CElementAssignment( std::string, IExp*, IExp*, int _line );
    ~CElementAssignment();

    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CSymbol* Id() const;
    const IExp* Exp1() const;
    const IExp* Exp2() const;
private:
    CSymbol* id;
    IExp* exp1;
    IExp* exp2;
};


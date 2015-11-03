#pragma once
#include "common.h"
class CStatementBlock : public IStatement, public CCoord
{
public:
    CStatementBlock( IStatementList* statements, int _line );
    ~CStatementBlock();

    IStatementList* Statements() const;
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    IStatementList* statements;
};


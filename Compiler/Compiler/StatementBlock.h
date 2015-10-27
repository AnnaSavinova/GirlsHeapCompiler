#pragma once
#include "common.h"
class CStatementBlock : public IStatement {
public:
    CStatementBlock( IStatementList* statements );
    ~CStatementBlock();

    IStatementList* Statements() const;
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    IStatementList* statements;
};


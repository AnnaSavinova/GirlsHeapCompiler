#pragma once
#include "common.h"
class CStatementBlock : public IStatement {
public:
    CStatementBlock( IStatementList* statements );
    ~CStatementBlock();

    IStatementList* Statements() const;
private:
    IStatementList* statements;
};


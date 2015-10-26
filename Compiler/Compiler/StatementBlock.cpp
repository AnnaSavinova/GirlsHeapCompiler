#include "StatementBlock.h"



CStatementBlock::CStatementBlock( IStatementList* _statements ) : statements(_statements)
{}


CStatementBlock::~CStatementBlock()
{}

IStatementList * CStatementBlock::Statements() const
{
    return statements;
}

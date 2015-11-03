#include "StatementBlock.h"



CStatementBlock::CStatementBlock( IStatementList* _statements, int _line ) : statements(_statements)
{
	line = _line;
}


CStatementBlock::~CStatementBlock()
{}

IStatementList * CStatementBlock::Statements() const
{
    return statements;
}

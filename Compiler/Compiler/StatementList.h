#pragma once
#include "common.h"

class CStatementList : public IStatementList
{
public:
	CStatementList( std::vector<IStatement*> &_statementList );
	~CStatementList();
	void Accept( IVisitor* ) const;

	const std::vector<IStatement*>* StatementList() const;

private:
	std::vector<IStatement*> statementList;
};
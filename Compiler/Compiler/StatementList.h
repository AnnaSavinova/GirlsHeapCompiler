#pragma once
#include "common.h"
class CStatementList : public IStatementList
{
public:
    CStatementList( IStatement* _statement );
	CStatementList( std::vector<IStatement*>& _statementList );

	~CStatementList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<IStatement*>& StatementList() const;

private:
	std::vector<IStatement*> statementList;
};
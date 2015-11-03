#pragma once
#include "common.h"
class CStatementList : public IStatementList, public CCoord
{
public:
    CStatementList( IStatement* _statement, int _line );
	CStatementList( std::vector<IStatement*>& _statementList, int _line );

	~CStatementList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<IStatement*>& StatementList() const;

private:
	std::vector<IStatement*> statementList;
};
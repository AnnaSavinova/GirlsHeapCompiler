#pragma once
#include "common.h"
class CMainClass : public IMainClass
{
public:
	CMainClass( std::string, IStatementList* );
	~CMainClass();

	const std::string Id() const;
	const IStatementList* Statements() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
	std::string id;
	IStatementList* statements;
};
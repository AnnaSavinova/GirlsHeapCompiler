#pragma once
#include "Grammar.h"
#include "common.h"
class CMainClass : IMainClass
{
public:
	CMainClass( std::string, IStatementList* );
	~CMainClass();

	const std::string Id() const;
	const IStatementList* Statements() const;

private:
	std::string id;
	IStatementList* statements;
};
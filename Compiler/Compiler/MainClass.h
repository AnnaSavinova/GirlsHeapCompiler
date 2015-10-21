#pragma once
#include "common.h"

class CMainClass : IMainClass
{
public:
	CMainClass( std::string, IStatement* );
	~CMainClass();

	const std::string Id() const;
	const IStatementList* Statements() const;

private:
	std::string id;
	IStatementList* statements;
};
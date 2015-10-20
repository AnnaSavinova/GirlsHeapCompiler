#pragma once
#include "common.h"

class CMainClass : IMainClass
{
public:
	CMainClass( CSymbol*, IStatement* );
	~CMainClass();

	const CSymbol* Id() const;
	const IStatement* Statement() const;

private:
	CSymbol* id;
	IStatement* statement;
};
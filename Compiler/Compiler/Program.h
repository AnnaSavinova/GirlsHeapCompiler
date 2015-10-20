#pragma once
#include "common.h"

class CProgram : IProgram
{
public:
	CProgram( IMainClass*, IClassDeclList* );
	~CProgram();

	const IMainClass* MainClass() const;
	const IClassDeclList* ClassDeclList() const;

private:
	IMainClass* mainClass;
	IClassDeclList* classDeclList;
};
#pragma once
#include "common.h"

class CProgram : IProgram
{
public:
	CProgram( IMainClass*, IClassDeclList*, IVarDeclList*, IMethodDeclList* );
	~CProgram();

	const IMainClass* MainClass() const;
	const IClassDeclList* ClassDeclList() const;
	const IVarDeclList* VarDeclList() const;
	const IMethodDeclList* MethodDeclList() const;

private:
	IMainClass* mainClass;
	IClassDeclList* classDeclList;
	IVarDeclList* varDeclList;
	IMethodDeclList* methodDeclList;
};
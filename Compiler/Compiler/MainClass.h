#pragma once
#include "common.h"

class CMainClass : IMainClass
{
public:
	CMainClass( IClassDeclList*, IVarDeclList*, IMethodDeclList* );
	~CMainClass();

	const IClassDeclList* ClassDeclList() const;
	const IVarDeclList* VarDeclList() const;
	const IMethodDeclList* MethodDeclList() const;

private:
	IMainClass* mainClass;
	IClassDeclList* classDeclList;
	IVarDeclList* varDeclList;
	IMethodDeclList* methodDeclList;
};
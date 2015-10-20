#pragma once
#include "common.h"

class CClassDeclList : IProgram
{
public:
	CClassDeclList( IClassDecl** );
	~CClassDeclList();

	const IMainClass* MainClass() const;
	const IClassDeclList* ClassDeclList() const;
	const IVarDeclList* VarDeclList() const;

private:
	IMainClass* mainClass;
	IClassDeclList* classDeclList;
	IVarDeclList* varDeclList;
};
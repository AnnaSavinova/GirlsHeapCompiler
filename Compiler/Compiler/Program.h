#pragma once
#include "common.h"
class CProgram : public IProgram
{
public:
	CProgram( IMainClass*, IClassDeclList* );
	~CProgram();

	const IMainClass* MainClass() const;
	const IClassDeclList* ClassDeclList() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
	IMainClass* mainClass;
	IClassDeclList* classDeclList;
};
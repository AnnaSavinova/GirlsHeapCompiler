#pragma once
#include "common.h"
class CProgram : public IProgram, public CCoord
{
public:
	CProgram( IMainClass*, IClassDeclList*, int _line );
	~CProgram();

	const IMainClass* MainClass() const;
	const IClassDeclList* ClassDeclList() const;
	virtual void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
	IMainClass* mainClass;
	IClassDeclList* classDeclList;
};
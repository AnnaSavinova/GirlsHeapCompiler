#pragma once
#include "common.h"

class CVarDeclList : public IVarDeclList
{
public:
	CVarDeclList( std::vector<IStatement*> &_varDeclList );
	~CVarDeclList();
	void Accept( IVisitor* ) const;

private:
	std::vector<IStatement*> varDeclList;
};
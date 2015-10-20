#pragma once
#include "common.h"

class CMethodDecl : public IMethodDecl
{
public:
	CMethodDecl( IType* _type, std::string _id, IFormalList* _formalList,
		IVarDeclList* _varDeclList, IStatementList* _statementList,
		IExp* _exp );
	~CMethodDecl();
	void Accept( IVisitor* ) const;
private:
	IType* type;
	std::string id;
	IFormalList* formalList;
	IVarDeclList* varDeclList;
	IStatementList* statementList;
	IExp* exp;
};
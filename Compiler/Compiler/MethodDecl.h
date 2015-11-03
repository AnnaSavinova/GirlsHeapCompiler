#pragma once
#include "common.h"
class CMethodDecl : public IMethodDecl, public CCoord
{
public:
	CMethodDecl( IType* _type, std::string _id, IFormalList* _formalList,
		IVarDeclList* _varDeclList, IStatementList* _statementList,
		IExp* _exp, int _line );
	~CMethodDecl();
	
	const IType* Type() const;
	CSymbol* Id() const;
	const IFormalList* FormalList() const;
	const IVarDeclList* VarDeclList() const;
	const IStatementList* StatementList() const;
	const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
	IType* type;
  CSymbol* id;
	IFormalList* formalList;
	IVarDeclList* varDeclList;
	IStatementList* statementList;
	IExp* exp;
};
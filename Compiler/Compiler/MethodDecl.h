#pragma once
#include "common.h"
class CMethodDecl : public IMethodDecl, public CCoord
{
public:
	CMethodDecl( IType* _type, std::string _name, IFormalList* _formalList,
		IVarDeclList* _varDeclList, IStatementList* _statementList,
		IExp* _result, int _line );
	~CMethodDecl();
	
	const IType* Type() const;
	CSymbol* Name() const;
	const IFormalList* FormalList() const;
	const IVarDeclList* VarDeclList() const;
	const IStatementList* StatementList() const;
	const IExp* Result() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
	IType* type;
    CSymbol* name;
	IFormalList* formalList;
	IVarDeclList* varDeclList;
	IStatementList* statementList;
	IExp* result;
};
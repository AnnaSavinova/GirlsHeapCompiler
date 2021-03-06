#pragma once
#include "common.h"
#include "SymbolsTable.h"

class CSymbTableBuilder : public IVisitor
{
public:
	CSymbTableBuilder();
	~CSymbTableBuilder();
	const CTable* GetSymbolTable() const;
	void Visit( const CAssignmentStatement* assigmentStatement );
	void Visit( const CBinExp* binExp );
	void Visit( const CClassDecl* classDecl );
	void Visit( const CClassDeclList* classDecls );
	void Visit( const CConstructor* constructor );
	void Visit( const CElementAssignment* elemAssign );
	void Visit( const CExpList* expList );
	void Visit( const CFormalList* formalList );
	void Visit( const CId* id );
	void Visit( const CIfStatement* ifStatement );
	void Visit( const CLengthExp* lengthExp );
	void Visit( const CMainClass* mainClass );
	void Visit( const CMethodCall* methodCall );
	void Visit( const CMethodDecl* methodDecl );
	void Visit( const CMethodDeclList* methodDecls );
	void Visit( const CNewInt* newInt );
	void Visit( const CNumber* number );
	void Visit( const CPrintStatement* printStatement );
	void Visit( const CProgram* program );
	void Visit( const CStatementBlock* statementBlock );
	void Visit( const CStatementList* statementList );
	void Visit( const CType* type );
	void Visit( const CUnExp* unExp );
	void Visit( const CVarDecl* varDecl );
	void Visit( const CVarDeclList* varDecls );
	void Visit( const CWhileStatement* whileStatement );
private:
    CClassInfo* currClass;
    CMethodInfo* currMethod;
    CTable* symbTable;
    CType* lastTypeValue;

    std::vector<int> errors;
};


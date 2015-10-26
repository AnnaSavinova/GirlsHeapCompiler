#pragma once
#include "classes.h"

class CPrettyPrinter : public IVisitor
{
public:
	void Visit( const CAssignmentStatement* assigmentStatement );
	void Visit( const CBinExp* binExp );
	void Visit( const CClassDecl* classDecl );
	void Visit( const CClassDeclList* classDecls );
	void Visit( const CExpList* expList );
	void Visit( const ÑFormalList* formalList );
	void Visit( const CIfStatement* ifStatement );
	void Visit( const CLengthExp* lengthExp );
	void Visit( const CMainClass* mainClass );
	void Visit( const CMethodDecl* methodDecl );
	void Visit( const CMethodDeclList* methodDecls);
	void Visit( const CNewClass* newClass );
	void Visit( const CNewInt* newInt );
	void Visit( const CPrintStatement* printStatement );
	void Visit( const CProgram* program );
	void Visit( const CStatementList* statementList );
	void Visit( const CUnExp* unExp );
	void Visit( const CVarDecl* varDecl );
	void Visit( const CVarDeclList* varDecls );
	void Visit( const CWhileStatement* whileStatement );
};
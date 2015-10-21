#include "PrettyPrinter.h"

void CPrettyPrinter::Visit( const CAssignmentStatement* assigmentStatement )
{
	// TODO
}

void CPrettyPrinter::Visit( const CBinExp* binExp )
{
	// TODO
}

void CPrettyPrinter::Visit( const CClassDecl* classDecl )
{
	std::cout << "class " << classDecl->Id();
	if ( !classDecl->ParentId().empty() ) {
		std::cout << " extends " << classDecl->ParentId();
	}
	std::cout << "{" << std::endl;

	if ( classDecl->VarDeclList() != nullptr ) {
		classDecl->VarDeclList()->Accept( this );
	}

	std::cout << std::endl;

	if ( classDecl->MethodDeclList() != nullptr ) {
		classDecl->MethodDeclList()->Accept( this );
	}

	std::cout << std::endl;
}

void CPrettyPrinter::Visit( const CClassDeclList* classDecls )
{
	for ( size_t i = 0; i < classDecls->ClassDeclList()->size(); i++ ) {
		( *( classDecls->ClassDeclList() ) )[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CExpList* expList )
{
	for ( size_t i = 0; i < expList->Expressions()->size(); i++ ) {
		( *( expList->Expressions() ) )[i]->Accept( this );

		if ( i < expList->Expressions()->size() - 1 ) {
			std::cout << ", ";
		}
	}
}

void CPrettyPrinter::Visit( const ÑFormalList* formalList )
{
	// TODO
}

void CPrettyPrinter::Visit( const CFormalRest* formalRest )
{
	// TODO
}

void CPrettyPrinter::Visit( const CIfStatement* ifStatement )
{
	// TODO
}

void CPrettyPrinter::Visit( const CLengthExp* lengthExp )
{
	// TODO
}

void CPrettyPrinter::Visit( const CMainClass* mainClass )
{
	std::cout << "class " << mainClass->Id();
	std::cout << "{" << std::endl;

	std::cout << "public static void main () {" << std::endl;
	if ( mainClass->Statements() != nullptr ) {
		mainClass->Statements()->Accept( this );
	}
	std::cout << "}" << std::endl;

	std::cout << "}" << std::endl;
}

void CPrettyPrinter::Visit( const CMethodDecl* methodDecl )
{ 
	std::cout << "public ";
	
	methodDecl->Type()->Accept( this );
	std::cout << " " << methodDecl->Id() << " ( ";
	if ( methodDecl->FormalList() != nullptr ) {
		methodDecl->FormalList()->Accept( this );
	}
	std::cout << ") {" << std::endl;

	if ( methodDecl->VarDeclList() != nullptr ) {
		methodDecl->VarDeclList()->Accept( this );
	}

	if ( methodDecl->StatementList() != nullptr ) {
		methodDecl->StatementList()->Accept( this );
	}

	std::cout << "return ";
	if ( methodDecl->Expression() != nullptr ) {
		methodDecl->Expression()->Accept( this );
	}
	std::cout << ";" << std::endl;
}

void CPrettyPrinter::Visit( const CMethodDeclList* methodDecls )
{
	for ( size_t i = 0; i < methodDecls->MethodDeclList()->size(); i++ ) {
		( *( methodDecls->MethodDeclList() ) )[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CNewClass* newClass )
{
	// TODO
}

void CPrettyPrinter::Visit( const CNewInt* newInt )
{
	std::cout << "new int[";
	newInt->Expression()->Accept( this );
	std::cout << "]";
}

void CPrettyPrinter::Visit( const CPrintStatement* printStatement )
{
	std::cout << "print ( ";
	printStatement->Expression()->Accept( this );
	std::cout << " );";
}

void CPrettyPrinter::Visit( const CStatementList* statementList )
{
	for ( size_t i = 0; i < statementList->StatementList()->size(); i++ ) {
		( *( statementList->StatementList() ) )[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CUnExp* unExp )
{
	// TODO
}

void CPrettyPrinter::Visit( const CVarDecl* varDecl )
{
	if ( varDecl->Type() != nullptr ) {
		varDecl->Type()->Accept( this );
	}

	std::cout << " " << varDecl->Id() << ";";
}

void CPrettyPrinter::Visit( const CVarDeclList* varDecls )
{
	for ( size_t i = 0; i < varDecls->VarDeclList()->size(); i++ ) {
		( *( varDecls->VarDeclList() ) )[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CWhileStatement* whileStatement )
{
	std::cout << "while( ";
	whileStatement->Expression()->Accept( this );
	std::cout << " ) " << std::endl;

	if ( whileStatement->Statement() != nullptr ) {
		whileStatement->Statement()->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CProgram* program )
{
	if ( program->MainClass() != nullptr ) {
		program->MainClass()->Accept( this );
	}

	if ( program->ClassDeclList() != nullptr ) {
		program->ClassDeclList()->Accept( this );
	}
}

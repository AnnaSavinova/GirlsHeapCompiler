#include "PrettyPrinter.h"

void CPrettyPrinter::Visit( const CAssignmentStatement* assigmentStatement )
{
	std::cout << assigmentStatement->Id() << " = ";
	if ( assigmentStatement->Expression() != nullptr ) {
		assigmentStatement->Expression()->Accept( this );
	}
	std::cout << ";";
}

void CPrettyPrinter::Visit( const CBinExp* binExp )
{
    binExp->Expression1()->Accept( this );
	if( binExp->Operation() == "[]" ) {
		std::cout << "[";
		binExp->Expression2()->Accept( this );
		std::cout << "]";
	} else {
		std::cout << " " << binExp->Operation() << " ";
		binExp->Expression2()->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CClassDecl* classDecl )
{
	std::cout << "class " << classDecl->Id();
	if ( classDecl->ParentId() != nullptr ) {
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

	std::cout << "}" << std::endl;
}

void CPrettyPrinter::Visit( const CClassDeclList* classDecls )
{
	for ( size_t i = 0; i < classDecls->ClassDeclList().size(); i++ ) {
		classDecls->ClassDeclList()[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CConstructor* constructor )
{
    std::cout << "new" << constructor->Id() << "()";

}

void CPrettyPrinter::Visit( const CElementAssignment* elemAssign )
{
    std::cout << elemAssign->Id() << "[";
    elemAssign->Exp1()->Accept( this );
    std::cout << "] = ";
    elemAssign->Exp2()->Accept( this );
	std::cout << ";" << std::endl;
}

void CPrettyPrinter::Visit( const CExpList* expList )
{
	for ( size_t i = 0; i < expList->Expressions().size(); i++ ) {
		expList->Expressions()[i]->Accept( this );

		if ( i < expList->Expressions().size() - 1 ) {
			std::cout << ", ";
		}
	}
}

void CPrettyPrinter::Visit( const CFormalList* formalList )
{	
	for ( int i = 0; i < formalList->List().size() - 1; ++i ) {
		formalList->List()[i]->type->Accept( this );
		std::cout << " " << formalList->List()[i]->id;
		std::cout << ", ";
	}

	if ( formalList->List().size() ) {
		formalList->List()[formalList->List().size() - 1]->type->Accept( this );
		std::cout << " " << formalList->List()[formalList->List().size() - 1]->id;
	}

    std::cout << " ";
}

void CPrettyPrinter::Visit( const CId* id )
{
    std::cout << id->Id();
}

void CPrettyPrinter::Visit( const CIfStatement* ifStatement )
{
	std::cout << "if ( ";
	if ( ifStatement->Expression() != nullptr ) {
		ifStatement->Expression()->Accept( this );
	}
	std::cout << " )" << std::endl;

	if ( ifStatement->ThenStatement() != nullptr ) {
		ifStatement->ThenStatement()->Accept( this );
	}

	if ( ifStatement->ElseStatement() != nullptr ) {
		std::cout << std::endl << "else " << std::endl;
		ifStatement->ElseStatement()->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CLengthExp* lengthExp )
{
	if ( lengthExp->Expression() != nullptr ) {
		lengthExp->Expression()->Accept( this );
		std::cout << ".length" << std::endl;
	}
}

void CPrettyPrinter::Visit( const CMainClass* mainClass )
{
	std::cout << "class " << mainClass->Id() << " ";
	std::cout << "{" << std::endl;

	std::cout << "public static void main () {" << std::endl;
	if ( mainClass->Statements() != nullptr ) {
		mainClass->Statements()->Accept( this );
	}
	std::cout << "}" << std::endl;

	std::cout << "}" << std::endl;
}

void CPrettyPrinter::Visit( const CMethodCall* methodCall )
{
    if( methodCall->Exp() != nullptr ) {
        methodCall->Exp()->Accept( this );
    }
    std::cout << "." << methodCall->Id() << "( ";
    if( methodCall->Args() != nullptr ) {
        methodCall->Args()->Accept( this );
    }
    std::cout << " )";
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
	std::cout << ";" << std::endl << "}" << std::endl;
}

void CPrettyPrinter::Visit( const CMethodDeclList* methodDecls )
{
	for ( size_t i = 0; i < methodDecls->MethodDeclList().size(); i++ ) {
		methodDecls->MethodDeclList()[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CNewInt* newInt )
{
	std::cout << "new int[";
	newInt->Expression()->Accept( this );
	std::cout << "]";
}

void CPrettyPrinter::Visit( const CNumber* number )
{
    std::cout << number->Number();
}

void CPrettyPrinter::Visit( const CPrintStatement* printStatement )
{
	std::cout << "print ( ";
	printStatement->Expression()->Accept( this );
	std::cout << " );";
}

void CPrettyPrinter::Visit( const CStatementList* statementList )
{
	for ( size_t i = 0; i < statementList->StatementList().size(); i++ ) {
		statementList->StatementList()[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CType* type )
{
	std::cout << type->Type();
}

void CPrettyPrinter::Visit( const CUnExp* unExp )
{
	std::cout << unExp->Operation();
	unExp->Expression()->Accept( this );
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
	for ( size_t i = 0; i < varDecls->VarDeclList().size(); i++ ) {
		varDecls->VarDeclList()[i]->Accept( this );
		std::cout << std::endl;
	}
}

void CPrettyPrinter::Visit( const CWhileStatement* whileStatement )
{
	std::cout << "while ( ";
	whileStatement->Expression()->Accept( this );
	std::cout << " ) ";

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

void CPrettyPrinter::Visit( const CStatementBlock* statementBlock )
{
    std::cout << "{" << std::endl;
    statementBlock->Statements()->Accept( this );
    std::cout << "}" << std::endl;
}

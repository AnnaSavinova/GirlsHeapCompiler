#include "TypeChecker.h"

CTypeChecker::CTypeChecker( const CTable* _symbTable ) : symbTable( _symbTable )
{}

CVarInfo* CTypeChecker::findVar( CSymbol* id )
{
	if( currMethod != nullptr ) {
		if( currMethod->FindLocalArg( id ) != nullptr ) {
			return currMethod->FindLocalArg( id );
		} else if( currMethod->FindFormalArg( id ) != nullptr ) {
			return currMethod->FindFormalArg( id );
		}
	} else if( currClass != nullptr && currClass->FindVar( id ) != nullptr ) {
		return currClass->FindVar( id );
	}
	return nullptr;
}

void CTypeChecker::Visit( const CAssignmentStatement * assigmentStatement )
{
	assigmentStatement->Expression()->Accept( this );
	CSymbol* id = assigmentStatement->Id();
	if( findVar( id ) == nullptr ) {
		errors.push_back( assigmentStatement->Line() );
		std::cerr << "At line: " << assigmentStatement->Line() << " undefined variable " << id->String() << std::endl;
	} else {
		std::string varType = currClass->FindVar( id )->Type()->Type();
		std::string exprType = lastTypeValue->Type();
		if( varType != exprType ) {
			errors.push_back( assigmentStatement->Line() );
			std::cerr << "At line: " << assigmentStatement->Line() << " type mismatch: expected " << varType << ", found " << exprType << std::endl;
		}
	}
}

void CTypeChecker::Visit( const CBinExp * binExp )
{
	binExp->Expression1()->Accept( this );
	std::string firstType = lastTypeValue->Type();
	binExp->Expression2()->Accept( this );
	std::string secondType = lastTypeValue->Type();
	if( firstType != secondType ) {
		errors.push_back( binExp->Line() );
		std::cerr << "At line: " << binExp->Line() << " invalid operation between " << firstType << " and " << secondType << std::endl;
	}
}

void CTypeChecker::Visit( const CClassDecl * classDecl )
{
	if( symbTable->FindClass( classDecl->Id() ) == nullptr ) {
		errors.push_back( classDecl->Line() );
		std::cerr << "At line: " << classDecl->Line() << " undefined class " << classDecl->Id()->String() << std::endl;
	} else if( classDecl->ParentId() != nullptr && symbTable->FindClass( classDecl->ParentId() ) == nullptr ) {
		errors.push_back( classDecl->Line() );
		std::cerr << "At line: " << classDecl->Line() << " undefined base class " << classDecl->ParentId()->String() << std::endl;
	} else {
		currClass = symbTable->FindClass( classDecl->Id() );
		if( classDecl->VarDeclList() != nullptr ) {
			classDecl->VarDeclList()->Accept( this );
		}
		if( classDecl->MethodDeclList() != nullptr ) {
			classDecl->MethodDeclList()->Accept( this );
		}
	}
}

void CTypeChecker::Visit( const CClassDeclList * classDecls )
{
	std::vector<IClassDecl*> classDeclList = classDecls->ClassDeclList();
	for( int i = 0; i < classDeclList.size(); ++i ) {
		classDeclList[i]->Accept( this );
	}
}

void CTypeChecker::Visit( const CConstructor * constructor )
{
	CSymbol* id = constructor->Id();
	if( symbTable->FindClass( id ) == nullptr ) {
		errors.push_back( constructor->Line() );
		std::cerr << "At line: " << constructor->Line() << " class " << id << " not found" << std::endl;
	}
	lastTypeValue = new CType( id->String(), constructor->Line() );
}

void CTypeChecker::Visit( const CElementAssignment * elemAssign )
{
	CVarInfo* var = findVar( elemAssign->Id() );
	if( var == nullptr ) {
		errors.push_back( elemAssign->Line() );
		std::cerr << "At line: " << elemAssign->Line() << " undefined variable " << elemAssign->Id()->String() << std::endl;
	} else {
		if( var->Type()->Type() != "int[]" ) {
			errors.push_back( elemAssign->Line() );
			std::cerr << "At line: " << elemAssign->Line() << " variable " << elemAssign->Id()->String() << " isn't an array" << std::endl;
		} else {
			elemAssign->Exp1()->Accept( this );
			std::string leftType = lastTypeValue->Type(); // int

			elemAssign->Exp2()->Accept( this );
			std::string rightType = lastTypeValue->Type(); // int
			if( leftType != "int" ) {
				errors.push_back( elemAssign->Line() );
				std::cerr << "At line: " << elemAssign->Line() << " expected [int], found " << "[" << leftType << "]" << std::endl;
			} else if( rightType != "int" ) {
				errors.push_back( elemAssign->Line() );
				std::cerr << "At line: " << elemAssign->Line() << " expected int in right part of expression, found " << "[" << leftType << "]" << std::endl;
			}
		}
	}
}

void CTypeChecker::Visit( const CExpList * expList )
{
	std::vector<IExp*> exps = expList->Expressions();
	for( int i = 0; i < exps.size(); ++i ) {
		exps[i]->Accept( this );
	}
}

void CTypeChecker::Visit( const CFormalList * formalList )
{
	std::vector<CFormalListElement*> formals = formalList->List();

	for( int i = 0; i < formals.size(); ++i ) {
		formals[i]->type->Accept( this );
		CType* t = lastTypeValue;

		if( currMethod == nullptr ) {
			errors.push_back( formalList->Line() );
			std::cerr << "At line: " << formalList->Line() << " formal list without method" << std::endl;
		} else {
			if( currMethod->FindFormalArg( formals[i]->id ) == nullptr ) {
				errors.push_back( formalList->Line() );
				std::cerr << "At line: " << formalList->Line() << " undefined argument " << formals[i]->id << std::endl;
			}
		}
	}
}

void CTypeChecker::Visit( const CId * id )
{
	lastTypeValue = new CType( id->Id()->String(), id->Line() );
}

void CTypeChecker::Visit( const CIfStatement * ifStatement )
{
	ifStatement->Expression()->Accept( this );
	if( lastTypeValue->Type() != "boolean" ) {
		errors.push_back( ifStatement->Line() );
		std::cerr << "At line: " << ifStatement->Line() << " expected boolean expression, found " << lastTypeValue->Type() << std::endl;
	}
	ifStatement->ThenStatement()->Accept( this );
	ifStatement->ElseStatement()->Accept( this );
}

void CTypeChecker::Visit( const CLengthExp * lengthExp )
{
	lengthExp->Expression()->Accept( this );
	if( lastTypeValue->Type() != "int[]" ) {
		errors.push_back( lengthExp->Line() );
		std::cerr << "At line: " << lengthExp->Line() << " expected array int[], found " << lastTypeValue->Type() << std::endl;
	}
}

void CTypeChecker::Visit( const CMainClass * mainClass )
{
	CSymbol* id = mainClass->Id();
	if( symbTable->FindClass( id ) == nullptr ) {
		errors.push_back( mainClass->Line() );
		std::cerr << "At line: " << mainClass->Line() << " undefined class " << id << std::endl;
	} else {
		currClass = symbTable->FindClass( id );
		if( mainClass->Statements() != nullptr ) {
			mainClass->Statements()->Accept( this );
		}
	}
}

void CTypeChecker::Visit( const CMethodCall * methodCall )
{
	if( methodCall->Exp() != nullptr ) {
		methodCall->Exp()->Accept( this );
	}
	CClassInfo* classInfo = symbTable->FindClass( symbolStorage.Get( lastTypeValue->Type() ) );
	if( classInfo == nullptr ) {
		errors.push_back( methodCall->Line() );
		std::cerr << "At line: " << methodCall->Line() << " undefined class " << lastTypeValue->Type() << std::endl;
	} else {
		CMethodInfo* methodInfo = classInfo->FindMethod( methodCall->Id() );
		if( methodInfo == nullptr ) {
			errors.push_back( methodCall->Line() );
			std::cerr << "At line: " << methodCall->Line() << " undefined method " << methodCall->Id() << std::endl;
		} else {
			// TODO как здесь понять тип аргументов, их количество?
			currMethod = methodInfo;
			if( methodCall->Args() != nullptr ) {
				methodCall->Args()->Accept( this );
			}
			lastTypeValue = currMethod->Type();
		}
	}
}

void CTypeChecker::Visit( const CMethodDecl * methodDecl )
{
	currMethod = currClass->FindMethod( methodDecl->Id() );
	if( methodDecl->FormalList() != nullptr ) {
		methodDecl->FormalList()->Accept( this );
	}
	if( methodDecl->VarDeclList() != nullptr ) {
		methodDecl->VarDeclList()->Accept( this );
	}
	if( methodDecl->StatementList() != nullptr ) {
		methodDecl->StatementList()->Accept( this );
	}
	methodDecl->Expression()->Accept( this );
	std::string returnType = lastTypeValue->Type();
	methodDecl->Type()->Accept( this );
	std::string methodType = lastTypeValue->Type();
	if( methodType != returnType ) {
		errors.push_back( methodDecl->Line() );
		std::cerr << "At line: " << methodDecl->Line() << " return value type mismatch method type, expected " << methodType << ", found " << returnType << std::endl;
	}
}

void CTypeChecker::Visit( const CMethodDeclList * methodDecls )
{
	std::vector< IMethodDecl* > methodDeclList = methodDecls->MethodDeclList();
	for( int i = 0; i < methodDeclList.size(); ++i ) {
		methodDeclList[i]->Accept( this );
	}
}

void CTypeChecker::Visit( const CNewInt * newInt )
{
	newInt->Expression()->Accept( this );
	if( lastTypeValue->Type() != "int" ) {
		errors.push_back( newInt->Line() );
		std::cerr << "At line: " << newInt->Line() << " expected [int], found " << "[" << lastTypeValue->Type() << "]" << std::endl;
	}
	lastTypeValue = new CType( "int[]", newInt->Line() );
}

void CTypeChecker::Visit( const CNumber * number )
{
	lastTypeValue = new CType( "int", number->Line() );
}

void CTypeChecker::Visit( const CPrintStatement * printStatement )
{
	printStatement->Expression()->Accept( this );
}

void CTypeChecker::Visit( const CProgram * program )
{
	if( program != nullptr ) {
		if( program->ClassDeclList() != nullptr ) {
			program->ClassDeclList()->Accept( this );
		}
		if( program->MainClass() != nullptr ) {
			program->MainClass()->Accept( this );
		}
	}
}

void CTypeChecker::Visit( const CStatementBlock * statementBlock )
{
	statementBlock->Statements()->Accept( this );
}

void CTypeChecker::Visit( const CStatementList * statementList )
{
	std::vector< IStatement* > statements = statementList->StatementList();

	for( int i = 0; i < statements.size(); ++i ) {
		statements[i]->Accept( this );
	}
}

void CTypeChecker::Visit( const CType * type )
{
	lastTypeValue = const_cast< CType* >(type);
}

void CTypeChecker::Visit( const CUnExp * unExp )
{
	unExp->Expression()->Accept( this );
}

void CTypeChecker::Visit( const CVarDecl * varDecl )
{
	CVarInfo* var = findVar( varDecl->Id() );
	if( var == nullptr ) {
		errors.push_back( varDecl->Line() );
		std::cerr << "At line: " << varDecl->Line() << " undefined variable " << varDecl->Id()->String() << std::endl;
	} else {
		lastTypeValue = var->Type(); // ??
	}
}

void CTypeChecker::Visit( const CVarDeclList * varDecls )
{
	std::vector< IVarDecl* > varDeclList = varDecls->VarDeclList();
	for( int i = 0; i < varDeclList.size(); ++i ) {
		varDeclList[i]->Accept( this );
	}
}

void CTypeChecker::Visit( const CWhileStatement * whileStatement )
{
	whileStatement->Expression()->Accept( this );
	if( lastTypeValue->Type() != "boolean" ) {
		errors.push_back( whileStatement->Line() );
		std::cerr << "At line: " << whileStatement->Line() << " expected boolean expression, found " << lastTypeValue->Type() << std::endl;
	}
	whileStatement->Statement()->Accept( this );
}

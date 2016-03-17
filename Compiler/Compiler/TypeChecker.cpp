#include "TypeChecker.h"

CTypeChecker::CTypeChecker( const CTable* _symbTable ) : symbTable( _symbTable )
{}

CVarInfo* CTypeChecker::findVar( CSymbol* id )
{
    if( !methods.empty() ) {
        CMethodInfo* currMethod = methods.top();
        if( currMethod->FindLocalArg( id ) != nullptr ) {
            return currMethod->FindLocalArg( id );
        } else if( currMethod->FindFormalArg( id ) != nullptr ) {
            return currMethod->FindFormalArg( id );
        }
    }
    if( currClass != nullptr && currClass->FindVar( id ) != nullptr ) {
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
        std::cerr << "At line " << assigmentStatement->Line() << ": undefined variable " << id->String() << std::endl;
    } else {
        std::string varType = findVar( id )->Type()->Type();
        std::string exprType = lastTypeValue->Type();
        if( varType != exprType && !(varType == "boolean" && exprType == "int") ) {
            errors.push_back( assigmentStatement->Line() );
            std::cerr << "At line " << assigmentStatement->Line() << ": type mismatch: expected " << varType << ", found " << exprType << std::endl;
        }
    }
}

void CTypeChecker::Visit( const CBinExp * binExp )
{
    binExp->Expression1()->Accept( this );
    std::string firstType = lastTypeValue->Type();
    binExp->Expression2()->Accept( this );
    std::string secondType = lastTypeValue->Type();
    std::string op = binExp->Operation();
    if( op == "[]" ) {
        if( firstType != "int[]" ) {
            errors.push_back( binExp->Line() );
            std::cerr << "At line " << binExp->Line() << ": trying to get an element not from array, but from " << firstType << std::endl;
        }
        if( secondType != "int" ) {
            errors.push_back( binExp->Line() );
            std::cerr << "At line " << binExp->Line() << ": invalid type of array index, expected int, found " << secondType << std::endl;
        }
        lastTypeValue = new CType( "int", binExp->Line() );
    } else {
        if( firstType != secondType ) {
            errors.push_back( binExp->Line() );
            std::cerr << "At line " << binExp->Line() << ": invalid operation between " << firstType << " and " << secondType << std::endl;
        }
        if( op == "<" || op == ">" || op == "<=" || op == ">=" /* и так далее... */ )
            lastTypeValue = new CType( "boolean", binExp->Line() );
        else
            lastTypeValue = new CType( firstType, binExp->Line() );
    }
}

void CTypeChecker::Visit( const CClassDecl * classDecl )
{
    if( !methods.empty() ) {
        methods = std::stack< CMethodInfo* >();
    }
    //	currMethod = nullptr;

    if( symbTable->FindClass( classDecl->Id() ) == nullptr ) {
        errors.push_back( classDecl->Line() );
        std::cerr << "At line " << classDecl->Line() << ": undefined class " << classDecl->Id()->String() << std::endl;
    } else if( classDecl->ParentId() != nullptr && symbTable->FindClass( classDecl->ParentId() ) == nullptr ) {
        errors.push_back( classDecl->Line() );
        std::cerr << "At line " << classDecl->Line() << ": undefined base class " << classDecl->ParentId()->String() << std::endl;
    } else {
        std::set <CClassInfo* > parents;
        CClassInfo* parent = symbTable->FindClass( classDecl->ParentId() );
        while( parent != nullptr ) {
            if( parents.find( parent ) != parents.end() ) {
                errors.push_back( classDecl->Line() );
                std::cerr << "At line " << classDecl->Line() << ": cyclic inheritance in class " << classDecl->Id()->String() << " extends " << parent->Name()->String() << std::endl;
                break;
            } else {
                parents.insert( parent );
                parent = symbTable->FindClass( parent->BaseClassName() );
            }
        }
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
    for( size_t i = 0; i < classDeclList.size(); ++i ) {
        classDeclList[i]->Accept( this );
    }
}

void CTypeChecker::Visit( const CConstructor * constructor )
{
    CSymbol* id = constructor->Id();
    if( symbTable->FindClass( id ) == nullptr ) {
        errors.push_back( constructor->Line() );
        std::cerr << "At line " << constructor->Line() << ": class " << id->String() << " not found" << std::endl;
    }
    lastTypeValue = new CType( id->String(), constructor->Line() );
}

void CTypeChecker::Visit( const CElementAssignment * elemAssign )
{
    CVarInfo* var = findVar( elemAssign->Id() );
    if( var == nullptr ) {
        errors.push_back( elemAssign->Line() );
        std::cerr << "At line " << elemAssign->Line() << ": undefined variable " << elemAssign->Id()->String() << std::endl;
    } else {
        if( var->Type()->Type() != "int[]" ) {
            errors.push_back( elemAssign->Line() );
            std::cerr << "At line " << elemAssign->Line() << ": variable " << elemAssign->Id()->String() << " isn't an array" << std::endl;
        } else {
            elemAssign->Exp1()->Accept( this );
            std::string leftType = lastTypeValue->Type(); // int

            elemAssign->Exp2()->Accept( this );
            std::string rightType = lastTypeValue->Type(); // int
            if( leftType != "int" ) {
                errors.push_back( elemAssign->Line() );
                std::cerr << "At line " << elemAssign->Line() << ": expected [int], found " << "[" << leftType << "]" << std::endl;
            } else if( rightType != "int" ) {
                errors.push_back( elemAssign->Line() );
                std::cerr << "At line " << elemAssign->Line() << ": expected int in right part of expression, found " << "[" << leftType << "]" << std::endl;
            }
        }
    }
}

void CTypeChecker::Visit( const CExpList * expList )
{
    CMethodInfo* currMethod = methods.top();
    std::vector<IExp*> exps = expList->Expressions();
    if( exps.size() != currMethod->FormalArgs().size() ) {
        std::cerr << "At line " << expList->Line() << ": expected " << exps.size() << " arguments, found " << currMethod->FormalArgs().size() << std::endl;
        return;
    }

    CMethodInfo* tmp = currMethod;
    methods.pop();
    //	currMethod = methods.top();
    for( size_t i = 0; i < exps.size(); ++i ) {
        std::string expectedType = tmp->FormalArgsOrdered()[i]->Type();

        exps[i]->Accept( this );
        if( lastTypeValue->Type() != expectedType  && !(expectedType == "boolean" && lastTypeValue->Type() == "int") ) {
            std::cerr << "At line " << expList->Line() << ": in argument " << i << " expected " << expectedType << ", found " << lastTypeValue->Type() << std::endl;
        }
    }
    //	currMethod = tmp;
    methods.push( tmp );
}

void CTypeChecker::Visit( const CFormalList * formalList )
{
    std::vector<CFormalListElement*> formals = formalList->List();

    for( size_t i = 0; i < formals.size(); ++i ) {
        formals[i]->type->Accept( this );
        CType* t = lastTypeValue;

        if( methods.empty() ) {
            errors.push_back( formalList->Line() );
            std::cerr << "At line " << formalList->Line() << ": formal list without method" << std::endl;
        } else {
            if( methods.top()->FindFormalArg( formals[i]->id ) == nullptr ) {
                errors.push_back( formalList->Line() );
                std::cerr << "At line " << formalList->Line() << ": undefined argument " << formals[i]->id << std::endl;
            }
        }
    }
}

void CTypeChecker::Visit( const CId * id )
{
    // если это имя класса
    if( id->Id()->String() == "this" ) {
        lastTypeValue = new CType( currClass->Name()->String(), id->Line() );
        return;
    }

    if( symbTable->FindClass( id->Id() ) ) {
        lastTypeValue = new CType( id->Id()->String(), id->Line() );
        return;
    }

    // иначе это имя переменной
    if( findVar( id->Id() ) != nullptr ) {
        lastTypeValue = findVar( id->Id() )->Type();
    } else {
        std::cerr << "At line " << id->Line() << ": undefined id " << id->Id()->String() << std::endl;
    }
    expTypesTable.insert( std::make_pair( reinterpret_cast< const void* > (id), lastTypeValue->Type() ) );
}

void CTypeChecker::Visit( const CIfStatement * ifStatement )
{
    ifStatement->Expression()->Accept( this );
    if( lastTypeValue->Type() != "boolean" && lastTypeValue->Type() != "int" ) {
        errors.push_back( ifStatement->Line() );
        std::cerr << "At line " << ifStatement->Line() << ": expected boolean expression, found " << lastTypeValue->Type() << std::endl;
    }
    ifStatement->ThenStatement()->Accept( this );
    ifStatement->ElseStatement()->Accept( this );
}

void CTypeChecker::Visit( const CLengthExp * lengthExp )
{
    lengthExp->Expression()->Accept( this );
    if( lastTypeValue->Type() != "int[]" ) {
        errors.push_back( lengthExp->Line() );
        std::cerr << "At line " << lengthExp->Line() << ": expected array int[], found " << lastTypeValue->Type() << std::endl;
    }
}

void CTypeChecker::Visit( const CMainClass * mainClass )
{
    CSymbol* id = mainClass->Id();
    if( symbTable->FindClass( id ) == nullptr ) {
        errors.push_back( mainClass->Line() );
        std::cerr << "At line " << mainClass->Line() << ": undefined class " << id->String() << std::endl;
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
        expTypesTable.insert( std::make_pair( reinterpret_cast< const void* > (methodCall), lastTypeValue->Type() ) );
    }
    CClassInfo* classInfo = symbTable->FindClass( symbolStorage.Get( lastTypeValue->Type() ) );
    if( classInfo == nullptr ) {
        errors.push_back( methodCall->Line() );
        std::cerr << "At line " << methodCall->Line() << ": undefined class " << lastTypeValue->Type() << std::endl;
    } else {
        CMethodInfo* methodInfo = classInfo->FindMethod( methodCall->Id() );
        if( methodInfo == nullptr ) {
            errors.push_back( methodCall->Line() );
            std::cerr << "At line " << methodCall->Line() << ": undefined method " << methodCall->Id()->String() << std::endl;
        } else {
            methods.push( methodInfo );
            CClassInfo* oldClass = currClass;
            currClass = classInfo;
            if( methodCall->Args() != nullptr ) {
                methodCall->Args()->Accept( this );
            }
            lastTypeValue = methods.top()->Type();
            methods.pop();
            currClass = oldClass;
        }
    }
}

void CTypeChecker::Visit( const CMethodDecl * methodDecl )
{
    methods.push( currClass->FindMethod( methodDecl->Name() ) );
    //	currMethod = currClass->FindMethod( methodDecl->Id() );
    if( methodDecl->FormalList() != nullptr ) {
        methodDecl->FormalList()->Accept( this );
    }
    if( methodDecl->VarDeclList() != nullptr ) {
        methodDecl->VarDeclList()->Accept( this );
    }
    if( methodDecl->StatementList() != nullptr ) {
        methodDecl->StatementList()->Accept( this );
    }
    methodDecl->Result()->Accept( this );
    std::string returnType = lastTypeValue->Type();
    methodDecl->Type()->Accept( this );
    std::string methodType = lastTypeValue->Type();
    if( methodType != returnType && !(methodType == "boolean" && returnType == "int") ) {
        errors.push_back( methodDecl->Line() );
        std::cerr << "At line " << methodDecl->Line() << ": return value type mismatch method type, expected " << methodType << ", found " << returnType << std::endl;
    }
    methods.pop();
}

void CTypeChecker::Visit( const CMethodDeclList * methodDecls )
{
    std::vector< IMethodDecl* > methodDeclList = methodDecls->MethodDeclList();
    for( size_t i = 0; i < methodDeclList.size(); ++i ) {
        methodDeclList[i]->Accept( this );
    }
}

void CTypeChecker::Visit( const CNewInt * newInt )
{
    newInt->Expression()->Accept( this );
    if( lastTypeValue->Type() != "int" ) {
        errors.push_back( newInt->Line() );
        std::cerr << "At line " << newInt->Line() << ": expected [int], found " << "[" << lastTypeValue->Type() << "]" << std::endl;
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

    for( size_t i = 0; i < statements.size(); ++i ) {
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
        std::cerr << "At line " << varDecl->Line() << ": undefined variable " << varDecl->Id()->String() << std::endl;
    } else {
        lastTypeValue = var->Type(); // ??
    }
}

void CTypeChecker::Visit( const CVarDeclList * varDecls )
{
    std::vector< IVarDecl* > varDeclList = varDecls->VarDeclList();
    for( size_t i = 0; i < varDeclList.size(); ++i ) {
        varDeclList[i]->Accept( this );
    }
}

void CTypeChecker::Visit( const CWhileStatement * whileStatement )
{
    whileStatement->Expression()->Accept( this );
    if( lastTypeValue->Type() != "boolean" && lastTypeValue->Type() != "boolean" ) {
        errors.push_back( whileStatement->Line() );
        std::cerr << "At line " << whileStatement->Line() << ": expected boolean expression, found " << lastTypeValue->Type() << std::endl;
    }
    whileStatement->Statement()->Accept( this );
}

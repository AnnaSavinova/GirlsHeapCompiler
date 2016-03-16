#include "SymbTableBuilder.h"


CSymbTableBuilder::CSymbTableBuilder() : symbTable( new CTable())
{
}


CSymbTableBuilder::~CSymbTableBuilder()
{
}

const CTable * CSymbTableBuilder::GetSymbolTable() const
{
	return symbTable;
}

void CSymbTableBuilder::Visit( const CAssignmentStatement * assigmentStatement )
{
    assigmentStatement->Expression()->Accept( this );
}

void CSymbTableBuilder::Visit( const CBinExp * binExp )
{
    binExp->Expression1()->Accept( this );
    binExp->Expression2()->Accept( this );
}

void CSymbTableBuilder::Visit( const CClassDecl * classDecl )
{
    currMethod = nullptr;
    CSymbol* id = classDecl->Id();
    if( !symbTable->AddClass( id, classDecl->ParentId() ) ) {
        errors.push_back(classDecl->Line());
        std::cerr << "At line " << classDecl->Line() << "duplicate definition class " << id->String() << std::endl;
    } else {
        currClass = symbTable->FindClass( id );
        if( classDecl->VarDeclList() != nullptr ) {
            classDecl->VarDeclList()->Accept( this );
        }
        if( classDecl->MethodDeclList() != nullptr ) {
            classDecl->MethodDeclList()->Accept( this );
        }
    }
}

void CSymbTableBuilder::Visit( const CClassDeclList * classDecls )
{
    std::vector<IClassDecl*> classDeclList = classDecls->ClassDeclList();
    for( size_t i = 0; i < classDeclList.size(); ++i ) {
        classDeclList[i]->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CConstructor * constructor )
{
    //nothing to do
}

void CSymbTableBuilder::Visit( const CElementAssignment * elemAssign )
{
    elemAssign->Exp1()->Accept( this );
    elemAssign->Exp2()->Accept( this );
}

void CSymbTableBuilder::Visit( const CExpList * expList )
{
    std::vector<IExp*> exps = expList->Expressions();
    for( size_t i = 0; i < exps.size(); ++i ) {
        exps[i]->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CFormalList * formalList )
{
    std::vector<CFormalListElement*> formals = formalList->List();

    for( size_t i = 0; i < formals.size(); ++i ) {
        formals[i]->type->Accept( this );
        CType* t = lastTypeValue;

        if( currMethod == nullptr ) {
            errors.push_back( formalList->Line() );
            std::cerr << "At line: " << formalList->Line() << " formal list without method" << std::endl;
        } else {
            if( !currMethod->AddFormalArg( formals[i]->id, t ) ) {
                errors.push_back( formalList->Line() );
                std::cerr << "At line: " << formalList->Line() << " duplicated definition" << std::endl;
            }
        }
    }
}

void CSymbTableBuilder::Visit( const CId * id )
{
    //nothing to do
}

void CSymbTableBuilder::Visit( const CIfStatement * ifStatement )
{
    ifStatement->Expression()->Accept( this );
    ifStatement->ThenStatement()->Accept( this );
    ifStatement->ElseStatement()->Accept( this );
}

void CSymbTableBuilder::Visit( const CLengthExp * lengthExp )
{
    lengthExp->Expression()->Accept( this );
}

void CSymbTableBuilder::Visit( const CMainClass * mainClass )
{
    CSymbol* id = mainClass->Id();
    if( !symbTable->AddClass( id, nullptr ) ) {
        errors.push_back( mainClass->Line() );
        std::cerr <<  "At line: " << mainClass->Line() << "duplicate class definition" << std::endl;
    } else {
        currClass = symbTable->FindClass( id );
        CSymbol* mainName = symbolStorage.Get( "main" );
        CType* t = new CType( std::string( "void" ), mainClass->Line() );
        if( !currClass->AddMethod( mainName, t ) )
        {
            errors.push_back( mainClass->Line() );
            std::cerr <<  "At line: " << mainClass->Line() << "duplicate main method definition" << std::endl;
        } else {
            if( mainClass->Statements() != nullptr ) {
                mainClass->Statements()->Accept( this );
            }
        }
    }
}

void CSymbTableBuilder::Visit( const CMethodCall * methodCall )
{
    if( methodCall->Exp() != nullptr ) {
        methodCall->Exp()->Accept( this );
    }
    if( methodCall->Args() != nullptr ) {
        methodCall->Args()->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CMethodDecl * methodDecl )
{
    methodDecl->Type()->Accept( this );
    CType* t = lastTypeValue;
    if( !currClass->AddMethod( methodDecl->Name(), t ) ) {
        errors.push_back( methodDecl->Line() );
        std::cerr << "At line: " << methodDecl->Line() << " duplicate method definition" << std::endl;
    } else {
        currMethod = currClass->FindMethod( methodDecl->Name() );
        if( methodDecl->FormalList() != nullptr ) {
            methodDecl->FormalList()->Accept( this );
        }
        if( methodDecl->VarDeclList() != nullptr ) {
            methodDecl->VarDeclList()->Accept( this );
        }
        if( methodDecl->StatementList() != nullptr ) {
            methodDecl->StatementList()->Accept( this );
        }
    }
}

void CSymbTableBuilder::Visit( const CMethodDeclList * methodDecls )
{
    std::vector< IMethodDecl* > methodDeclList = methodDecls->MethodDeclList();
    for( size_t i = 0; i < methodDeclList.size(); ++i ) {
        methodDeclList[i]->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CNewInt * newInt )
{
    newInt->Expression()->Accept( this );
}

void CSymbTableBuilder::Visit( const CNumber * number )
{
    //nothing to do here
}

void CSymbTableBuilder::Visit( const CPrintStatement * printStatement )
{
    printStatement->Expression()->Accept( this );
}

void CSymbTableBuilder::Visit( const CProgram * program )
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

void CSymbTableBuilder::Visit( const CStatementBlock * statementBlock )
{
    statementBlock->Statements()->Accept( this );
}

void CSymbTableBuilder::Visit( const CStatementList * statementList )
{
    std::vector< IStatement* > statements = statementList->StatementList();

    for( size_t i = 0; i < statements.size(); ++i ) {
        statements[i]->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CType * type )
{
    //TODO хм.. а что тут делать?
    lastTypeValue = const_cast<CType*>(type);
}

void CSymbTableBuilder::Visit( const CUnExp * unExp )
{
    unExp->Expression()->Accept( this );
}

void CSymbTableBuilder::Visit( const CVarDecl * varDecl )
{
    varDecl->Type()->Accept( this );
    CType* t = lastTypeValue;
    CSymbol* id = varDecl->Id();
    if( currMethod == nullptr ) {
        if( !currClass->AddVar( id, t ) ) {
            errors.push_back( varDecl->Line() );
            std::cerr << "At line: " << varDecl->Line() << " duplicated definition" << std::endl;
        }
    } else if( !currMethod->AddLocalArg( id, t ) ) {
        errors.push_back( varDecl->Line() );
        std::cerr << "At line: " << varDecl->Line() << " duplicated definition" << std::endl;
    }
}

void CSymbTableBuilder::Visit( const CVarDeclList * varDecls )
{
    std::vector< IVarDecl* > varDeclList = varDecls->VarDeclList();
    for( size_t i = 0; i < varDeclList.size(); ++i ) {
        varDeclList[i]->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CWhileStatement * whileStatement )
{
    whileStatement->Expression()->Accept( this );
    whileStatement->Statement()->Accept( this );
}


#include "SymbTableBuilder.h"


CSymbTableBuilder::CSymbTableBuilder()
{
}


CSymbTableBuilder::~CSymbTableBuilder()
{
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
    const CSymbol* id = classDecl->Id();
    if( !symbTable->AddClass( id, classDecl->ParentId() ) ) {
        errors.push_back(classDecl->Line());
        std::cerr << "At line " << classDecl->Line() << "duplicate definition class " << id->String() << std::endl;
    } else {
        currClass = symbTable->FindClass( id );
        classDecl->VarDeclList()->Accept( this );
        classDecl->MethodDeclList()->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CClassDeclList * classDecls )
{
    std::vector<IClassDecl*> classDeclList = classDecls->ClassDeclList();
    for( int i = 0; i < classDeclList.size(); ++i ) {
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
    for( int i = 0; i < exps.size(); ++i ) {
        exps[i]->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CFormalList * formalList )
{
    std::vector<CFormalListElement*> formals = formalList->List();

    for( int i = 0; i < formals.size(); ++i ) {
        formals[i]->type->Accept( this );
        const CType* t = lastTypeValue;

        if( currMethod == nullptr ) {
            errors.push_back( formalList->Line() );
            std::cerr << "At line: " << formalList->Line() << " formal list without method" << std::endl;
        } else {
            currMethod->AddFormalArg( formals[i]->id, t );
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
    if( !symbTable->AddClass( mainClass->Id(), nullptr ) ) {
        errors.push_back( mainClass->Line() );
        std::cerr <<  "At line: " << mainClass->Line() << "duplicate class definition" << std::endl;
    } else {
        mainClass->Statements()->Accept( this );
    }
}

void CSymbTableBuilder::Visit( const CMethodCall * methodCall )
{
    methodCall->Exp()->Accept( this );
    methodCall->Args()->Accept( this );
}

void CSymbTableBuilder::Visit( const CMethodDecl * methodDecl )
{
    methodDecl->Type()->Accept( this );
    CType* t = lastTypeValue;
    if( !currClass->AddMethod( methodDecl->Id(), t ) ) {
        errors.push_back( methodDecl->Line() );
        std::cerr << "At line: " << methodDecl->Line() << " duplicate mathod definition" << std::endl;
    } else {
        currMethod = currClass->FindMethod( methodDecl->Id() );
    }
}


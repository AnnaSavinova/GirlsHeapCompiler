#pragma once
#include "classes.h"
#include <stack>
#include "IRClasses.h"
#include "SymbolsTable.h"

class CIRTranslator : public IVisitor {
public:
    CIRTranslator( const CTable* symbTable );

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
    std::stack< IIRExp* > exps;
    std::stack< IIRStm* > stms;
    std::stack< CIRExpList* > lists;

    std::stack< CFrame* > frames;

    const CTable* symbTable;
    CClassInfo* currentClass;

    enum EVariablePlace {
        E_LOCAL,
        E_FORMAL,
        E_CLASS
    };

    //EVariablePlace getVariablePlace( const CSymbol* var ) const;
};


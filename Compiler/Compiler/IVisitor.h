#pragma once

class CAssignmentStatement;
class CBinExp;
class CClassDecl;
class CClassDeclList;
class CConstructor;
class CElementAssignment;
class CExpList;
class CFormalList;
class CId;
class CIfStatement;
class CLengthExp;
class CMainClass;
class CMethodCall;
class CMethodDecl;
class CMethodDeclList;
class CNewClass;
class CNewInt;
class CNumber;
class CPrintStatement;
class CProgram;
class CStatementBlock;
class CStatementList;
class CType;
class CUnExp;
class CVarDecl;
class CVarDeclList;
class CWhileStatement;


class IVisitor {
public:
    virtual void Visit( const CAssignmentStatement* assigmentStatement ) = 0;
    virtual void Visit( const CBinExp* binExp ) = 0;
    virtual void Visit( const CClassDecl* classDecl ) = 0;
    virtual void Visit( const CClassDeclList* classDecls ) = 0;
    virtual void Visit( const CConstructor* constructor ) = 0;
    virtual void Visit( const CElementAssignment* elemAssign ) = 0;
    virtual void Visit( const CExpList* expList ) = 0;
    virtual void Visit( const CFormalList* formalList ) = 0;
    virtual void Visit( const CId* id ) = 0;
    virtual void Visit( const CIfStatement* ifStatement ) = 0;
    virtual void Visit( const CLengthExp* lengthExp ) = 0;
    virtual void Visit( const CMainClass* mainclass ) = 0;
    virtual void Visit( const CMethodCall* methodCall ) = 0;
    virtual void Visit( const CMethodDecl* methodDecl ) = 0;
    virtual void Visit( const CMethodDeclList* methodDecls ) = 0;
    virtual void Visit( const CNewClass* newclass ) = 0;
    virtual void Visit( const CNewInt* newInt ) = 0;
    virtual void Visit( const CNumber* number ) = 0;
    virtual void Visit( const CPrintStatement* printStatement ) = 0;
    virtual void Visit( const CProgram* program ) = 0;
    virtual void Visit( const CStatementBlock* statementBlock ) = 0;
    virtual void Visit( const CStatementList* statementList ) = 0;
    virtual void Visit( const CType* type ) = 0;
    virtual void Visit( const CUnExp* unExp ) = 0;
    virtual void Visit( const CVarDecl* varDecl ) = 0;
    virtual void Visit( const CVarDeclList* varDecls ) = 0;
    virtual void Visit( const CWhileStatement* whileStatement ) = 0;
};
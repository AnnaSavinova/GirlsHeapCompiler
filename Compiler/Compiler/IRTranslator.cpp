#include "IRTranslator.h"

void CIRTranslator::Visit( const CAssignmentStatement * assigmentStatement )
{

}

void CIRTranslator::Visit( const CBinExp * binExp )
{}

void CIRTranslator::Visit( const CClassDecl * classDecl )
{}

void CIRTranslator::Visit( const CClassDeclList * classDecls )
{}

void CIRTranslator::Visit( const CConstructor * constructor )
{}

void CIRTranslator::Visit( const CElementAssignment * elemAssign )
{
    elemAssign->Exp1.Accept( this );
}

void CIRTranslator::Visit( const CExpList * expList )
{}

void CIRTranslator::Visit( const CFormalList * formalList )
{}

void CIRTranslator::Visit( const CId * id )
{}

void CIRTranslator::Visit( const CIfStatement * ifStatement )
{}

void CIRTranslator::Visit( const CLengthExp * lengthExp )
{}

void CIRTranslator::Visit( const CMainClass * mainClass )
{}

void CIRTranslator::Visit( const CMethodCall * methodCall )
{

}

void CIRTranslator::Visit( const CMethodDecl * methodDecl )
{

}

void CIRTranslator::Visit( const CMethodDeclList * methodDecls )
{
    for ( auto methodDecl : methodDecls->MethodDeclList() ) {
        methodDecl->Accept( this );
    }
}

void CIRTranslator::Visit( const CNewInt * newInt )
{

}

void CIRTranslator::Visit( const CNumber * number )
{
    
}

void CIRTranslator::Visit( const CPrintStatement * printStatement )
{
    
}

void CIRTranslator::Visit( const CProgram * program )
{
    program->MainClass()->Accept( this );
    
    if ( program->ClassDeclList() != nullptr ) {
        program->ClassDeclList()->Accept( this );
    }
}

void CIRTranslator::Visit( const CStatementBlock * statementBlock )
{
    statementBlock->Statements()->Accept( this );
}

void CIRTranslator::Visit( const CStatementList * statementList )
{
    for ( auto stm : statementList->StatementList() ) {
        stm->Accept( this );
    }
}

void CIRTranslator::Visit( const CType * type )
{
    throw std::logic_error( "Unimplemented method Visit( CType )" );
}

void CIRTranslator::Visit( const CUnExp * unExp )
{
    unExp->Expression()->Accept( this );

    IIRExp* exp = exps.top();
    exps.pop();

    EBinOp operation;
    if ( unExp->Operation() == "-" ) {
      exps.push( new CIRMem( new CIRBinOp( MINUS, new CIRConst( 0 ), exp ) ) );
    } else if (unExp->Operation() == "!") {
      exps.push( new CIRMem( new CIRBinOp( OR, new CIRConst( 0 ), exp) ) );
    } else {
      // тогда это странный уноп
    }
}

void CIRTranslator::Visit( const CVarDecl * varDecl )
{
}

void CIRTranslator::Visit( const CVarDeclList * varDecls )
{
    for ( auto varDecl : varDecls->VarDeclList() ) {
        varDecl->Accept( this );
    }
}

void CIRTranslator::Visit( const CWhileStatement * whileStatement )
{

}

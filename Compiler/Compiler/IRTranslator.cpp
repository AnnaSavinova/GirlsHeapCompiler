#include "IRTranslator.h"

CIRTranslator::CIRTranslator( const CTable * _symbTable ) : symbTable( _symbTable )
{}

void CIRTranslator::Visit( const CAssignmentStatement * assigmentStatement )
{
    // для левой части берем аксессор из фрейма и выражение из него
    const IIRExp* left( frames.top()->Local( assigmentStatement->Id() )->GetExp( frames.top()->FP() ) );

    assigmentStatement->Expression()->Accept( this );
    const IIRExp* right = exps.top();
    exps.pop();

    // записываем результат в стек
    stms.push( new CIRMove( left, right ) );
}

void CIRTranslator::Visit( const CBinExp * binExp )
{}

void CIRTranslator::Visit( const CClassDecl * classDecl )
{}

void CIRTranslator::Visit( const CClassDeclList * classDecls )
{
    for( size_t i = 0; i < classDecls->ClassDeclList().size(); ++i ) {
        classDecls->ClassDeclList()[i]->Accept( this );
    }
}

void CIRTranslator::Visit( const CConstructor * constructor )
{}

void CIRTranslator::Visit( const CElementAssignment * elemAssign )
{
    elemAssign->Exp1()->Accept( this );
    IIRExp* index = exps.top();
    exps.pop();

    IIRExp* offset = new CIRBinOp( MUL, index, new CIRConst( CFrame::WordSize() ) );
    IIRExp* array = new CIRMem( frames.top()->Local( elemAssign->Id() )->GetExp( frames.top()->FP() ) );
    IIRExp* lExp = new CIRMem( new CIRBinOp( PLUS, array, offset ) );

    elemAssign->Exp2()->Accept( this );
    IIRExp* rExp = exps.top();
    exps.pop();

    stms.push( new CIRMove( lExp, rExp ) );
}

void CIRTranslator::Visit( const CExpList * expList )
{
    for( size_t i = 0; i < expList->Expressions().size(); ++i ) {
        expList->Expressions()[i]->Accept( this );
    }
}

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
    // TODO!
}

void CIRTranslator::Visit( const CMethodDecl * methodDecl )
{
    // TODO!
}

void CIRTranslator::Visit( const CMethodDeclList * methodDecls )
{
    for ( auto methodDecl : methodDecls->MethodDeclList() ) {
        methodDecl->Accept( this );
    }
}

void CIRTranslator::Visit( const CNewInt * newInt )
{
    // TODO!
}

void CIRTranslator::Visit( const CNumber * number )
{
    stms.emplace( new CIRConst( number->Number() ) );
}

void CIRTranslator::Visit( const CPrintStatement * printStatement )
{
    // TODO!
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
    throw std::logic_error( "Unimplemented method Visit( CVarDecl )" );
}

void CIRTranslator::Visit( const CVarDeclList * varDecls )
{
    throw std::logic_error( "Unimplemented method Visit( CVarDeclList )" );
}

void CIRTranslator::Visit( const CWhileStatement * whileStatement )
{
    // TODO!
}

CIRTranslator::EVariablePlace CIRTranslator::getVariablePlace( const CSymbol * var ) const
{
    if( frames.top()->Local( var ) != nullptr ) {
        return E_LOCAL;
    }

    for( size_t i = 0; i < frames.top()->FormalsCount(); ++i ) {
    }
}

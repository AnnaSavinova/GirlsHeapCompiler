#include "IRTranslator.h"

CIRTranslator::CIRTranslator( const CTable * _symbTable, const  std::map< const void*, std::string > _expTypesTable ) : symbTable( _symbTable ), expTypesTable( _expTypesTable )
{}

void CIRTranslator::Visit( const CAssignmentStatement * assigmentStatement )
{
    const IIRExp* left( frames.top()->GetField( assigmentStatement->Id()->String() )->GetExp( frames.top()->GetFramePointer() ) );

    assigmentStatement->Expression()->Accept( this );
    const IIRExp* right = exps.top();
    exps.pop();

    stms.push( new CIRMove( left, right ) );
}

void CIRTranslator::Visit( const CBinExp * binExp )
{
    binExp->Expression1()->Accept( this );

    IIRExp* left = exps.top();
    exps.pop();

    binExp->Expression2()->Accept( this );

    IIRExp* right = exps.top();
    exps.pop();

    if( binExp->Operation() == "+" ) {
        exps.push( new CIRMem( new CIRBinOp( PLUS, left, right ) ) );
    } else if( binExp->Operation() == "-" ) {
        exps.push( new CIRMem( new CIRBinOp( MINUS, left, right ) ) );
    } else if( binExp->Operation() == "*" ) {
        exps.push( new CIRMem( new CIRBinOp( MUL, left, right ) ) );
    } else if( binExp->Operation() == "<" ) {
        exps.push( new CIRMem( new CIRBinOp( LE, left, right ) ) );
    } else if( binExp->Operation() == "&" ) {
        exps.push( new CIRMem( new CIRBinOp( AND, left, right ) ) );
    } else if( binExp->Operation() == "|" ) {
        exps.push( new CIRMem( new CIRBinOp( OR, left, right ) ) );
    } else if( binExp->Operation() == "[]" ) {
        binExp->Expression1()->Accept( this );
        IIRExp* array = exps.top();
        exps.pop();

        binExp->Expression2()->Accept( this );
        IIRExp* index = exps.top();
        exps.pop();

        IIRExp* offset = new CIRBinOp( MUL, index, new CIRConst( CFrame::GetWordSize() ) );
        exps.push( new CIRMem( new CIRBinOp( PLUS, array, offset ) ) );
    } else {
        //пичаль
    }
}

void CIRTranslator::Visit( const CClassDecl * classDecl )
{
    currentClass = symbTable->FindClass( classDecl->Id() );

    if( classDecl->MethodDeclList() != nullptr ) {
        classDecl->MethodDeclList()->Accept( this );
    }

    currentClass = nullptr;
}

void CIRTranslator::Visit( const CClassDeclList * classDecls )
{
    for( auto classDecl : classDecls->ClassDeclList() ) {
        classDecl->Accept( this );
    }
}

void CIRTranslator::Visit( const CConstructor * constructor )
{
    CClassInfo* info = symbTable->FindClass( constructor->Id() );
    int size = info->VarList().size();

    IIRExp* allocationSize = new CIRBinOp( MUL, new CIRConst( CFrame::GetWordSize() ), new CIRConst( size ) );
    CIRTemp* tmp = new CIRTemp( new CTemp );

    IIRStm* first = new CIRMove( tmp, new CIRCall( symbolStorage.Get( "malloc" ), new CIRExpList( allocationSize, nullptr ) ) );
    IIRStm* second = new CIRExp( new CIRCall( symbolStorage.Get( "memset" ), new CIRExpList( std::vector< IIRExp* >{ new CIRConst( 0 ), allocationSize, tmp } ) ) );
    exps.push( new CIRESeq( new CIRSeq( first, second ), tmp ) );
    lastObjectClass = info;
}

void CIRTranslator::Visit( const CElementAssignment * elemAssign )
{
    elemAssign->Exp1()->Accept( this );
    IIRExp* index = exps.top();
    exps.pop();

    IIRExp* offset = new CIRBinOp( MUL, index, new CIRConst( CFrame::GetWordSize() ) );
    IIRExp* array = new CIRMem( frames.top()->GetField( elemAssign->Id()->String() )->GetExp( frames.top()->GetFramePointer() ) );
    IIRExp* lExp = new CIRMem( new CIRBinOp( PLUS, array, offset ) );

    elemAssign->Exp2()->Accept( this );
    IIRExp* rExp = exps.top();
    exps.pop();

    stms.push( new CIRMove( lExp, rExp ) );
}

void CIRTranslator::Visit( const CExpList * expList )
{
    std::vector<IIRExp*> vectorExp;
    for( size_t i = 0; i < expList->Expressions().size(); ++i ) {
        expList->Expressions()[i]->Accept( this );
        vectorExp.push_back( exps.top() );
        exps.pop();
    }
    lists.push( new CIRExpList( vectorExp ) );
}

void CIRTranslator::Visit( const CFormalList * formalList )
{
    throw std::logic_error( "Translator shouldn't visit formalList" );
}

void CIRTranslator::Visit( const CId * id )
{
    exps.push( const_cast< IIRExp* >(frames.top()->GetField( id->Id()->String() )->GetExp( frames.top()->GetFramePointer() )) );
}

void CIRTranslator::Visit( const CIfStatement * ifStatement )
{
    ifStatement->Expression()->Accept( this );
    IIRExp* condition = exps.top();
    exps.pop();

    ifStatement->ThenStatement()->Accept( this );
    ifStatement->ElseStatement()->Accept( this );
    IIRStm* falseStatement = stms.top();
    stms.pop();
    IIRStm* trueStatement = stms.top();
    stms.pop();

    CIRLabel* trueLabel = new CIRLabel( new CLabel() );
    CIRLabel* falseLabel = new CIRLabel( new CLabel() );
    CIRLabel* endLabel = new CIRLabel( new CLabel() );

    trueStatement = new CIRSeq( trueLabel, new CIRSeq( trueStatement, endLabel ) );
    falseStatement = new CIRSeq( falseLabel, new CIRSeq( falseStatement, endLabel ) );

    stms.push( new CIRCjump( NE, condition, new CIRConst( 0 ), trueLabel, falseLabel ) );
}

void CIRTranslator::Visit( const CLengthExp * lengthExp )
{
    lengthExp->Expression()->Accept( this );
    IIRExp* arrayPtr = exps.top();
    exps.pop();

    CIRTemp* lengthVar = new CIRTemp( new CTemp() );

    CIRMove* move = new CIRMove( lengthVar, arrayPtr );

    exps.push( new CIRESeq( move, lengthVar ) );
}

void CIRTranslator::Visit( const CMainClass * mainClass )
{
    CSymbol* id = mainClass->Id();
    IIRStm* statements = nullptr;
    if( symbTable->FindClass( id ) == nullptr ) {
        std::cerr << "At line " << mainClass->Line() << ": undefined class " << id->String() << std::endl;
    } else {
        currentClass = symbTable->FindClass( id );
        if( mainClass->Statements() != nullptr ) {
            mainClass->Statements()->Accept( this );
            statements = stms.top();
            stms.pop();
        }
    }
    frames.push( new CFrame( new CSymbol( mainClass->Id()->String() + "@main" ) ) );
    frames.top()->AddField( new CSymbol( "this" ), 0 );
    frames.top()->SetRootStatement( statements );
}

void CIRTranslator::Visit( const CMethodCall * methodCall )
{
    // получаем объект, у которого вызывается метод
    methodCall->Exp()->Accept( this );
    IIRExp* object = exps.top();
    exps.pop();

    // имя метода
    CSymbol* method = methodCall->Id();

    CIRExpList* arguments;
    // парсим аргументы (если они есть)
    if( methodCall->Args() != nullptr ) {
        methodCall->Args()->Accept( this );
        arguments = lists.top();
        lists.pop();
    } else {
        arguments = new CIRExpList( nullptr, nullptr );
    }

    arguments = new CIRExpList( object, arguments );

    CIRTemp* resultVar = new CIRTemp( new CTemp() );
    exps.push( new CIRESeq( new CIRMove( resultVar, new CIRCall( method, arguments ) ), resultVar ) );
}

void CIRTranslator::Visit( const CMethodDecl * methodDecl )
{
    // ищем инфу о методе
    CMethodInfo* methodInfo = nullptr;
    for( auto method : currentClass->MethodList() ) {
        if( method.second->Name() == methodDecl->Name() ) {
            methodInfo = method.second;
        }
    }
    if( methodInfo == nullptr ) {
        throw std::logic_error( "Method " + methodDecl->Name()->String() + " wasn't found in " + currentClass->Name()->String() + " in IR" );
    }
    // создаем новый фрейм, в котором записана инфа о методе
    frames.push( new CFrame( currentClass, methodInfo, symbTable ) );

    // парсим команды метода, если есть
    IIRStm* statements = nullptr;
    if( methodDecl->StatementList() != nullptr ) {
        methodDecl->StatementList()->Accept( this );
        statements = stms.top();
        stms.pop();
    }

    // взяли результат выполнения функции
    methodDecl->Result()->Accept( this );
    auto returnedExp = exps.top();
    exps.pop();
    // записали во фрейм
    IIRStm* moveResult = new CIRMove( new CIRTemp( frames.top()->GetReturnValue() ), returnedExp );
    // если метод не содержал команд, то все он только считает результат и записывает его в фрейм
    IIRStm* methodStm = moveResult;

    if( statements != nullptr ) {
        // иначе сначала выполняем команды и потом возимся с результатом
        methodStm = new CIRSeq( statements, moveResult );
    }

    frames.top()->SetRootStatement( methodStm );
}

void CIRTranslator::Visit( const CMethodDeclList * methodDecls )
{
    for( auto methodDecl : methodDecls->MethodDeclList() ) {
        methodDecl->Accept( this );
    }
}

void CIRTranslator::Visit( const CNewInt * newInt )
{
    newInt->Expression()->Accept( this );
    IIRExp* count = exps.top();
    exps.pop();

    IIRExp* allocationSize = new CIRBinOp( PLUS, count, new CIRConst( 1 ) );
    CIRTemp* tmp = new CIRTemp( new CTemp );

    IIRStm* first = new CIRMove( tmp, new CIRCall( symbolStorage.Get( "malloc" ), new CIRExpList( allocationSize, nullptr ) ) );
    IIRStm* second = new CIRExp( new CIRCall( symbolStorage.Get( "memset" ), new CIRExpList( std::vector< IIRExp* >{ new CIRConst( 0 ), allocationSize, tmp } ) ) );
    IIRStm* third = new CIRMove( tmp, count );
    second = new CIRSeq( second, third );
    exps.push( new CIRESeq( new CIRSeq( first, second ), tmp ) );
}

void CIRTranslator::Visit( const CNumber * number )
{
    exps.push( new CIRConst( number->Number() ) );
}

void CIRTranslator::Visit( const CPrintStatement * printStatement )
{
    printStatement->Expression()->Accept( this );
    IIRExp* toPrint = exps.top();
    exps.pop();

    stms.push( new CIRExp( new CIRCall( symbolStorage.Get( "print" ), new CIRExpList( toPrint, nullptr ) ) ) );
}

void CIRTranslator::Visit( const CProgram * program )
{
    program->MainClass()->Accept( this );

    if( program->ClassDeclList() != nullptr ) {
        program->ClassDeclList()->Accept( this );
    }
}

void CIRTranslator::Visit( const CStatementBlock * statementBlock )
{
    statementBlock->Statements()->Accept( this );
}

void CIRTranslator::Visit( const CStatementList * statementList )
{
    for( auto stm : statementList->StatementList() ) {
        stm->Accept( this );
    }
}

void CIRTranslator::Visit( const CType * type )
{
    throw std::logic_error( "Translator shouldn't visit CType" );
}

void CIRTranslator::Visit( const CUnExp * unExp )
{
    unExp->Expression()->Accept( this );

    IIRExp* exp = exps.top();
    exps.pop();

    if( unExp->Operation() == "-" ) {
        exps.push( new CIRMem( new CIRBinOp( MINUS, new CIRConst( 0 ), exp ) ) );
    } else if( unExp->Operation() == "!" ) {
        exps.push( new CIRMem( new CIRBinOp( OR, new CIRConst( 0 ), exp ) ) );
    } else {
        // тогда это странный уноп
    }
}

void CIRTranslator::Visit( const CVarDecl * varDecl )
{
    throw std::logic_error( "Translator shouldn't visit CVarDecl" );
}

void CIRTranslator::Visit( const CVarDeclList * varDecls )
{
    throw std::logic_error( "Translator shouldn't visit CVarDeclList" );
}

void CIRTranslator::Visit( const CWhileStatement * whileStatement )
{
    whileStatement->Expression()->Accept( this );
    whileStatement->Statement()->Accept( this );

    IIRStm* statements = stms.top();
    stms.pop();

    IIRExp* condition = exps.top();
    exps.pop();

    CIRLabel* begin = new CIRLabel( new CLabel() );
    CIRLabel* ifTrue = new CIRLabel( new CLabel() );
    CIRLabel* end = new CIRLabel( new CLabel() );

    IIRStm* cycleStep = new CIRSeq( ifTrue, statements );
    IIRStm* checkCondition = new CIRCjump( LE, condition, new CIRConst( 1 ), ifTrue, end );

    //TODO что-то с безусловным переходом на начало IIRStm* jumpToBegin
    IIRStm* jumpToBegin = new CIRJump( begin );

    stms.push( new CIRSeq( begin, new CIRSeq( checkCondition, new CIRSeq( cycleStep, jumpToBegin ) ) ) );
}

/*CIRTranslator::EVariablePlace CIRTranslator::getVariablePlace( const CSymbol * var ) const
{
    if( frames.top()->Local( var ) != nullptr ) {
        return E_LOCAL;
    }

    for( size_t i = 0; i < frames.top()->FormalsCount(); ++i ) {
    }
}*/

#include "Frame.h"

CFrame::CFrame( const CClassInfo * currentClass, const CMethodInfo * method, const CTable* table )
{
    // декорированное имя функции
    std::string functionDecoratedName = currentClass->Name()->String() + "___" + method->Name()->String();
    name = new CSymbol( functionDecoratedName );
    framePointer = new CTemp( new CSymbol( functionDecoratedName + "___framePointer" ) );
    thisPointer = new CTemp( new CSymbol( functionDecoratedName + "___thisPointer" ) );
    returnValue = new CTemp( new CSymbol( functionDecoratedName + "___returnValue" ) );
    // добавляем поля класса и всех его родителей
    CSymbol* tempClass = currentClass->Name();
    int inObjectNum = 0;
    while( tempClass != nullptr ) {
        CClassInfo* tempClassInfo = table->FindClass( tempClass );
        for( auto var : tempClassInfo->VarList() ) {
            AddField( var.second->Name(), new CInObject( inObjectNum++ ) );
        }
        tempClass = tempClassInfo->BaseClassName();
    }

    // добавляем аргументы метода ("this" -- нулевой)
    int inFrameNum = 0;
    AddField( new CSymbol( "this" ), new CInFrame( inFrameNum++ ) );
    for( auto argument : method->FormalArgs() ) {
        AddField( argument.second->Name(), new CInFrame( inFrameNum++ ) );
    }

    // добавляем локальные переменные метода
    for( auto argument : method->LocalArgs() ) {
        AddField( argument.second->Name(), new CInFrame( inFrameNum++ ) );
    }

}

CFrame::CFrame( const CSymbol * _name ) : name(_name)
{
    std::string functionDecoratedName = name->String();
    framePointer = new CTemp( new CSymbol( functionDecoratedName + "___framePointer" ) );
    thisPointer = new CTemp( new CSymbol( functionDecoratedName + "___thisPointer" ) );
    returnValue = new CTemp( new CSymbol( functionDecoratedName + "___returnValue" ) );
}

void CFrame::AddField( const CSymbol * name, const IAccess * access )
{
    if( fields.find( name->String() ) != fields.end() ) {
        throw std::logic_error( "Reduplication of " + name->String() + " in frame " + name->String() );
        return;
    } else {
        fields.insert( std::make_pair( name->String(), access ) );
    }
}

const IAccess * CFrame::GetField( std::string var ) const
{
    auto access = fields.find( var );
    if( access != fields.end() ) {
        return access->second;
    } else {
        return nullptr;
    }
}

const CTemp* CFrame::GetFramePointer() const
{
    return framePointer;
}

const CTemp* CFrame::GetEax() const
{
    //TODO переписать на нормальный регистр

    CSymbol* sEax = symbolStorage.Get( "Eax" );
    return new CTemp( sEax );
}

const CTemp* CFrame::GetEdx() const
{
    //TODO переписать на нормальный регистр

    CSymbol* sEdx = symbolStorage.Get( "Edx" );
    return new CTemp( sEdx );
}

int CFrame::GetWordSize()
{
    return wordSize;
}

const CTemp * CFrame::GetThisPointer() const
{
    return thisPointer;
}

const CTemp * CFrame::GetReturnValue() const
{
    return returnValue;
}

void CFrame::SetRootStatement( const IIRStm * _root )
{
    root = _root;
}

const IIRExp * CInReg::GetExp( const CTemp * framePtr ) const
{
    throw std::logic_error( "CInReg::GetExp can't be called!" );
}

CInFrame::CInFrame( int _offset )
{
    offset = _offset;
}

const IIRExp * CInFrame::GetExp( const CTemp * framePointer ) const
{
    int offsetInBytes = offset * CFrame::GetWordSize();
    return new CIRMem( new CIRBinOp( PLUS, new CIRTemp( framePointer ), new CIRConst( offsetInBytes ) ) );
}

CInObject::CInObject( int _offset )
{
    offset = _offset;
}

const IIRExp * CInObject::GetExp( const CTemp * thisPointer ) const
{
    int offsetInBytes = offset * CFrame::GetWordSize();
    return new CIRMem( new CIRBinOp( PLUS, new CIRTemp( thisPointer ), new CIRConst( offsetInBytes ) ) );
}

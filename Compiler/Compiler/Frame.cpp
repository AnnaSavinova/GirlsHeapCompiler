#include "Frame.h"

CFrame::CFrame( const CClassInfo * currentClass, const CMethodInfo * method, const CTable* table )
{
    // �������������� ��� �������
    std::string functionDecoratedName = currentClass->Name()->String() + "@" + method->Name()->String();
    name = new CSymbol( functionDecoratedName );
    framePointer = new CTemp( new CSymbol( functionDecoratedName + "@framePointer" ) );
    thisPointer = new CTemp( new CSymbol( functionDecoratedName + "@thisPointer" ) );
    returnValue = new CTemp( new CSymbol( functionDecoratedName + "@returnValue" ) );
    // ��������� ���� ������ � ���� ��� ���������
    CSymbol* tempClass = currentClass->Name();
    int inObjectNum = 0;
    while( tempClass != nullptr ) {
        CClassInfo* tempClassInfo = table->FindClass( tempClass );
        for( auto var : tempClassInfo->VarList() ) {
            AddField( var.second->Name(), new CInObject( inObjectNum++ ) );
        }
        tempClass = tempClassInfo->BaseClassName();
    }

    // ��������� ��������� ������ ("this" -- �������)
    int inFrameNum = 0;
    AddField( new CSymbol( "this" ), new CInFrame( inFrameNum++ ) );
    for( auto argument : method->FormalArgs() ) {
        AddField( argument.second->Name(), new CInFrame( inFrameNum++ ) );
    }

    // ��������� ��������� ���������� ������
    for( auto argument : method->LocalArgs() ) {
        AddField( argument.second->Name(), new CInFrame( inFrameNum++ ) );
    }

}

CFrame::CFrame( const CSymbol * _name ) : name(_name)
{
    std::string functionDecoratedName = name->String();
    framePointer = new CTemp( new CSymbol( functionDecoratedName + "@framePointer" ) );
    thisPointer = new CTemp( new CSymbol( functionDecoratedName + "@thisPointer" ) );
    returnValue = new CTemp( new CSymbol( functionDecoratedName + "@returnValue" ) );
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

CLabel::CLabel() : name( std::to_string( nextUniqueId++ ) )
{}

CLabel::CLabel( const std::string& s ) : name( s )
{}

const std::string & CLabel::Name() const
{
    return name;
}

CTemp::CTemp() : name( std::to_string( nextUniqueId++ ) )
{}

CTemp::CTemp( const CSymbol * symbol ) : name( symbol->String() )
{}

CTemp::~CTemp()
{}

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

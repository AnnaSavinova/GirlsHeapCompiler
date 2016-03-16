#pragma once
#include <vector>
#include <map>
#include "Symbol.h"
#include "SymbolsTable.h"
#include "IRClasses.h"
#include "Temp.h"
#include <list>

//class CClassInfo;
//class CMethodInfo;
//class IIRExp;
//class IIRStm;
//class CIRMem;
//class CIRBinOp;
//class CIRTemp;
//class CIRConst;


class IAccess {
public:
    virtual const IIRExp* GetExp( const CTemp* framePtr ) const = 0;
    virtual ~IAccess() {}
};


class CInFrame : public IAccess
{
public:
    explicit CInFrame( int _offset );
    const IIRExp* GetExp( const CTemp* framePtr ) const;
    //~CInFrame();
private:
    int offset;
};

class CInObject : public IAccess
{
public:
    explicit CInObject( int _offset );
    const IIRExp* GetExp( const CTemp* thisPointer ) const;
    //~CInFrame();
private:
    int offset;

};

class CInReg : public IAccess
{
public:
    const IIRExp* GetExp( const CTemp* framePointer ) const;
    ///~CInReg();
private:
    CTemp * reg;
};


class CFrame {
public:
    CFrame( const CSymbol* _name );
    CFrame( const CClassInfo* curClass, const CMethodInfo* method, const CTable* table );
    //������ � ���������� ����������
    const IAccess* GetField( const CSymbol* ) const;
    const CTemp* GetFramePointer() const;
    static int GetWordSize();
    const CTemp* GetThisPointer() const;
    const CTemp* GetReturnValue() const;

    void AddField( const CSymbol* name, const IAccess* access );
    void SetRootStatement( const IIRStm * _root);
private:
    std::map< const CSymbol *, const IAccess * > fields;
    const CTemp* framePointer;
    const CTemp* thisPointer;
    const CTemp* returnValue;
    static int wordSize;
    const CSymbol* name;
    const IIRStm* root;
};






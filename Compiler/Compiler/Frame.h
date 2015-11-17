#pragma once
#include <vector>
#include "Symbol.h"
#include "IIRExp.h"

// ��������� ����������
class CTemp {
public:
    // ����� ���������� � ���������� ������
    CTemp();
    // ����� ���������� � �������� ������
    explicit CTemp( const CSymbol* symbol );
    ~CTemp();

    const std::string& Name() const { return name; }

private:
    // ������� ��� �������� ���������� ���
    static int nextUniqueId;
    std::string name;
};

//����� - ����� �������� � ����
class CLabel {
public:
    // ������� ����� � ���������� ������
    CLabel();
    // ������� ����� � �������� ������
    explicit CLabel( const std::string& );

    const std::string& Name() const;

private:
    // ������� ��� �������� ���������� ���������������
    static int nextUniqueId;
    std::string name;

};

class IAccess {
public:
    virtual const IIRExp* GetExp( const CTemp* framePtr ) const = 0;
    virtual ~IAccess() {}
};

class CFrame {
public:
    CFrame( const CSymbol* name, int formalsCount );
    //������ � ���������� ����������
    int FormalsCount() const;
    const IAccess* Formal( size_t index ) const;
    const CTemp* FP() const;
private:
    std::vector< IAccess* > formals;
    const CTemp* fp;
};






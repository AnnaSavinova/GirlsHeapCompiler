#pragma once
#include "Symbol.h"

// ��������� ����������
class CTemp
{
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
class CLabel
{
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

class CTempList {
public: 
    CTempList( const CTemp * _head, const CTempList * _tail );
    const CTemp* GetHead() const;
    const CTempList* GetTail() const;
private:
    const CTemp * head;
    const CTempList * tail;
};

class CLabelList {
public:
    CLabelList( const CLabel * _head, const CLabelList * _tail );
    const CLabel* GetHead() const;
    const CLabelList* GetTail() const;
private:
    const CLabel * head;
    const CLabelList * tail;
};

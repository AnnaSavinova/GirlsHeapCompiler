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
    CTempList( CTemp * _head, CTempList * _tail );
    const CTemp* getHead();
    const CTempList* getTail();
private:
    CTemp * head;
    CTempList * tail;
};

class CLabelList {
public:
    CLabelList( CLabel * _head, CLabelList * _tail );
    const CLabel* getHead();
    const CLabelList* getTail();
private:
    CLabel * head;
    CLabelList * tail;
};

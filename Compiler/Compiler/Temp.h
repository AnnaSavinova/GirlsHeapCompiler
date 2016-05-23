#pragma once
#include "Symbol.h"

// Временная переменная
class CTemp
{
public:
    // Новая переменная с уникальным именем
    CTemp();
    // Новая переменная с заданным именем
    explicit CTemp( const CSymbol* symbol );
    ~CTemp();

    const std::string& Name() const { return name; }

private:
    // Счётчик для создания уникальных имён
    static int nextUniqueId;
    std::string name;
};

//Метка - точка перехода в коде
class CLabel
{
public:
    // Создать метку с уникальным именем
    CLabel();
    // Создать метку с заданным именем
    explicit CLabel( const std::string& );

    const std::string& Name() const;

private:
    // Счётчик для создания уникальных идентификаторов
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

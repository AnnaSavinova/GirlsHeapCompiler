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

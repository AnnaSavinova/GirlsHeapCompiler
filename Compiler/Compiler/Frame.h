#pragma once
#include <vector>
#include <map>
#include "Symbol.h"

class IIRExp;

// Временная переменная
class CTemp {
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
class CLabel {
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

class IAccess {
public:
    virtual const IIRExp* GetExp( const CTemp* framePtr ) const = 0;
    virtual ~IAccess() {}
};

class CFrame {
public:
    CFrame( const CSymbol* name, int formalsCount );
    //Доступ к формальным параметрам
    int FormalsCount() const;
    const IAccess* Formal( size_t index ) const;
    const IAccess* Local( const CSymbol* ) const;
    const CTemp* FP() const;
    static int WordSize();
private:
    std::vector< IAccess* > formals;
    std::map< const CSymbol*, const IAccess* > locals;
    const CTemp* fp;
    static int wordSize;
};






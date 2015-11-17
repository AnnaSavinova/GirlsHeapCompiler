#pragma once
#include <vector>
#include "Symbol.h"
class IAccess {
public:
    virtual ~IAccess() {}
};

class CFrame {
public:
    CFrame( const CSymbol* name, int formalsCount );
    //Доступ к формальным параметрам
    int FormalsCount() const;
    const IAccess* Formal( size_t index ) const;
private:
    std::vector< IAccess* > formals;
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




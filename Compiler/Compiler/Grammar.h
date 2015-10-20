#pragma once

class IVisitor
{
public:
	virtual void Visit( const CHost* host );
};

class CHost
{
public:
	virtual void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
};

// Корневой интерфейс программы
class IProgram : public CHost
{
public:
	virtual ~IProgram() {}
};

// Главный класс
class IMainClass : public CHost
{
public:
	virtual ~IMainClass() {}
};

// Список классов
class IClassDeclList : public CHost
{
public:
	virtual ~IClassDeclList() {}
};

// Описание класса
class IClassDecl : public CHost
{
public:
	virtual ~IClassDecl() {}
};

// Список объявлений переменных
class IVarDeclList : public CHost
{
public:
	virtual ~IVarDeclList() {}
};

// Объявление переменной
class IVarDecl : public CHost
{
public:
	virtual ~IVarDecl() {}
};

// Список методов класса
class IMethodDeclList : public CHost
{
public:
	virtual ~IMethodDeclList() {}
};

// Метод класса
class IMethodDecl : public CHost
{
public:
	virtual ~IMethodDecl() {}
};

// Список параметров
class IFormalList : public CHost
{
public:
	virtual ~IFormalList() {}
};

// Тип
class IType : public CHost
{
public:
	virtual ~IType() {}
};

// Последовательность команд
class IStatementList : public CHost
{
public:
	virtual ~IStatementList() {}
};

// Одна команда (или блок)
class IStatement : public CHost
{
public:
	virtual ~IStatement() {}
};

// Последовательность выражений (аргументы функции)
class IExpList : public CHost
{
public:
	virtual ~IExpList() {}
};

// Арифметическое выражение
class IExp : public CHost
{
public:
	virtual ~IExp() {}
};

class IFormalRest : public CHost
{
public:
	virtual ~IFormalRest() {}
};

class IFormalRestList : public CHost
{
public:
	virtual ~IFormalRestList() {}
};
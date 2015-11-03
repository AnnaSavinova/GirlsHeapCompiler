#pragma once

class IVisitor;

class CCoord
{
public:
	int Line() const
	{
		return line;
	}
protected:
	int line;
};

// Корневой интерфейс программы
class IProgram 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IProgram() {}
};

// Главный класс
class IMainClass 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMainClass() {}
};

// Список классов
class IClassDeclList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDeclList() {}
};

// Описание класса
class IClassDecl 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDecl() {}
};

// Список объявлений переменных
class IVarDeclList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDeclList() {}
};

// Объявление переменной
class IVarDecl 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDecl() {}
};

// Список методов класса
class IMethodDeclList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDeclList() {}
};

// Метод класса
class IMethodDecl 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDecl() {}
};

// Список параметров
class IFormalList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalList() {}
};

// Тип
class IType 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IType() {}
};

// Последовательность команд
class IStatementList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatementList() {}
};

// Одна команда (или блок)
class IStatement 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatement() {}
};

// Последовательность выражений (аргументы функции)
class IExpList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IExpList() {}
};

// Арифметическое выражение
class IExp 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IExp() {}
};

class IFormalRest 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalRest() {}
};

class IFormalRestList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalRestList() {}
};
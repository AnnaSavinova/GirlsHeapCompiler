#pragma once

class IVisitor;

class ICoord
{
	int Line() const
	{
		return line;
	}

private:
	int line;
};

// Корневой интерфейс программы
class IProgram : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IProgram() {}
};

// Главный класс
class IMainClass : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMainClass() {}
};

// Список классов
class IClassDeclList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDeclList() {}
};

// Описание класса
class IClassDecl : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDecl() {}
};

// Список объявлений переменных
class IVarDeclList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDeclList() {}
};

// Объявление переменной
class IVarDecl : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDecl() {}
};

// Список методов класса
class IMethodDeclList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDeclList() {}
};

// Метод класса
class IMethodDecl : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDecl() {}
};

// Список параметров
class IFormalList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalList() {}
};

// Тип
class IType : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IType() {}
};

// Последовательность команд
class IStatementList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatementList() {}
};

// Одна команда (или блок)
class IStatement : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatement() {}
};

// Последовательность выражений (аргументы функции)
class IExpList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IExpList() {}
};

// Арифметическое выражение
class IExp : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IExp() {}
};

class IFormalRest : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalRest() {}
};

class IFormalRestList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalRestList() {}
};
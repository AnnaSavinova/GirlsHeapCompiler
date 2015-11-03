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

// �������� ��������� ���������
class IProgram 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IProgram() {}
};

// ������� �����
class IMainClass 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMainClass() {}
};

// ������ �������
class IClassDeclList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDeclList() {}
};

// �������� ������
class IClassDecl 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDecl() {}
};

// ������ ���������� ����������
class IVarDeclList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDeclList() {}
};

// ���������� ����������
class IVarDecl 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDecl() {}
};

// ������ ������� ������
class IMethodDeclList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDeclList() {}
};

// ����� ������
class IMethodDecl 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDecl() {}
};

// ������ ����������
class IFormalList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalList() {}
};

// ���
class IType 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IType() {}
};

// ������������������ ������
class IStatementList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatementList() {}
};

// ���� ������� (��� ����)
class IStatement 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatement() {}
};

// ������������������ ��������� (��������� �������)
class IExpList 
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IExpList() {}
};

// �������������� ���������
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
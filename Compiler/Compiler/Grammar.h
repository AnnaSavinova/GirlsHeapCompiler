#pragma once

class IVisitor;

class IHost
{
	virtual void Accept( IVisitor* ) const = 0;
};

// �������� ��������� ���������
class IProgram : public IHost
{
public:
	virtual ~IProgram() {}
};

// ������� �����
class IMainClass : public IHost
{
public:
	virtual ~IMainClass() {}
};

// ������ �������
class IClassDeclList : public IHost
{
public:
	virtual ~IClassDeclList() {}
};

// �������� ������
class IClassDecl : public IHost
{
public:
	virtual ~IClassDecl() {}
};

// ������ ���������� ����������
class IVarDeclList : public IHost
{
public:
	virtual ~IVarDeclList() {}
};

// ���������� ����������
class IVarDecl : public IHost
{
public:
	virtual ~IVarDecl() {}
};

// ������ ������� ������
class IMethodDeclList : public IHost
{
public:
	virtual ~IMethodDeclList() {}
};

// ����� ������
class IMethodDecl : public IHost
{
public:
	virtual ~IMethodDecl() {}
};

// ������ ����������
class IFormalList : public IHost
{
public:
	virtual ~IFormalList() {}
};

// ���
class IType : public IHost
{
public:
	virtual ~IType() {}
};

// ������������������ ������
class IStatementList : public IHost
{
public:
	virtual ~IStatementList() {}
};

// ���� ������� (��� ����)
class IStatement : public IHost
{
public:
	virtual ~IStatement() {}
};

// ������������������ ��������� (��������� �������)
class IExpList : public IHost
{
public:
	virtual ~IExpList() {}
};

// �������������� ���������
class IExp : public IHost
{
public:
	virtual ~IExp() {}
};
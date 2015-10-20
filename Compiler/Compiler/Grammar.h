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

// �������� ��������� ���������
class IProgram : public CHost
{
public:
	virtual ~IProgram() {}
};

// ������� �����
class IMainClass : public CHost
{
public:
	virtual ~IMainClass() {}
};

// ������ �������
class IClassDeclList : public CHost
{
public:
	virtual ~IClassDeclList() {}
};

// �������� ������
class IClassDecl : public CHost
{
public:
	virtual ~IClassDecl() {}
};

// ������ ���������� ����������
class IVarDeclList : public CHost
{
public:
	virtual ~IVarDeclList() {}
};

// ���������� ����������
class IVarDecl : public CHost
{
public:
	virtual ~IVarDecl() {}
};

// ������ ������� ������
class IMethodDeclList : public CHost
{
public:
	virtual ~IMethodDeclList() {}
};

// ����� ������
class IMethodDecl : public CHost
{
public:
	virtual ~IMethodDecl() {}
};

// ������ ����������
class IFormalList : public CHost
{
public:
	virtual ~IFormalList() {}
};

// ���
class IType : public CHost
{
public:
	virtual ~IType() {}
};

// ������������������ ������
class IStatementList : public CHost
{
public:
	virtual ~IStatementList() {}
};

// ���� ������� (��� ����)
class IStatement : public CHost
{
public:
	virtual ~IStatement() {}
};

// ������������������ ��������� (��������� �������)
class IExpList : public CHost
{
public:
	virtual ~IExpList() {}
};

// �������������� ���������
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
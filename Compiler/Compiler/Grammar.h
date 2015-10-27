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

// �������� ��������� ���������
class IProgram : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IProgram() {}
};

// ������� �����
class IMainClass : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMainClass() {}
};

// ������ �������
class IClassDeclList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDeclList() {}
};

// �������� ������
class IClassDecl : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IClassDecl() {}
};

// ������ ���������� ����������
class IVarDeclList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDeclList() {}
};

// ���������� ����������
class IVarDecl : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IVarDecl() {}
};

// ������ ������� ������
class IMethodDeclList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDeclList() {}
};

// ����� ������
class IMethodDecl : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IMethodDecl() {}
};

// ������ ����������
class IFormalList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IFormalList() {}
};

// ���
class IType : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IType() {}
};

// ������������������ ������
class IStatementList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatementList() {}
};

// ���� ������� (��� ����)
class IStatement : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IStatement() {}
};

// ������������������ ��������� (��������� �������)
class IExpList : public ICoord
{
public:
	virtual void Accept( IVisitor* ) const = 0;
	virtual ~IExpList() {}
};

// �������������� ���������
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
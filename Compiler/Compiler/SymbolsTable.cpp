#include "SymbolsTable.h"

CSymbol * CClassInfo::Name()
{
	return name;
}

std::map<CSymbol*, CVarInfo>& CClassInfo::VarList()
{
	return varList;
}

std::map<CSymbol*, CMethodInfo>& CClassInfo::MethodList()
{
	return methodList;
}

bool CClassInfo::AddVar( CSymbol * name, CType * type )
{
	if( varList.find( name ) != varList.end() ) {
		// ��� ���� ����� ����������
		return false;
	} else {
		varList[name] = CVarInfo( name, type );
	}
}

bool CClassInfo::AddMethod( CSymbol * name, CType * type )
{
	if( methodList.find( name ) != methodList.end() ) {
		// ��� ���� ����� �����
		return false;
	} else {
		methodList[name] = CMethodInfo( name, type );
	}
}

CVarInfo * CClassInfo::FindVar( CSymbol * name )
{
	auto found = varList.find( name );
	if( found == varList.end() ) {
		// �� �����
		return nullptr;
	} else {
		return &(found->second);
	}
}

CMethodInfo * CClassInfo::FindMethod( CSymbol * name )
{
	auto found = methodList.find( name );
	if( found == methodList.end() ) {
		// �� ����� ����� �����
		return false;
	} else {
		return &(found->second);
	}
}

CSymbol * CVarInfo::Name()
{
	return name;
}

CType * CVarInfo::Type()
{
	return type;
}

bool CMethodInfo::AddFormalArg( CSymbol * _name, CType * _type )
{
	if( formalArgs.find( name ) != formalArgs.end() ) {
		// ��� ���� ����� ��������
		return false;
	} else {
		formalArgs[name] = CVarInfo( name, type );
	}
}

bool CMethodInfo::AddLocalArg( CSymbol * name, CType * type )
{
	if( localArgs.find( name ) != localArgs.end() ) {
		// ��� ���� ����� ��������
		return false;
	} else {
		localArgs[name] = CVarInfo( name, type );
	}
}

CVarInfo * CMethodInfo::FindFormalArg( CSymbol * name )
{
	auto found = formalArgs.find( name );
	if( found == formalArgs.end() ) {
		return nullptr;
	} else {
		return &(found->second);
	}
}

CVarInfo * CMethodInfo::FindLocalArg( CSymbol * name )
{
	auto found = localArgs.find( name );
	if( found == localArgs.end() ) {
		return nullptr;
	} else {
		return &(found->second);
	}
}

CSymbol * CMethodInfo::Name()
{
	return name;
}

std::map<CSymbol*, CVarInfo>& CMethodInfo::FormalArgs()
{
	return formalArgs;
}

std::map<CSymbol*, CVarInfo>& CMethodInfo::LocalArgs()
{
	return localArgs;
}

CType * CMethodInfo::Type()
{
	return type;
}

//bool CTable::AddClass( CSymbol* id )
//{
//	if( classesList.find( id ) != classesList.end() ) {
//		// ��� ���� ����� �����
//		return false;
//	} else {
//		classesList[id] = CClassInfo( id );
//	}
//}

bool CTable::AddClass( CSymbol * id, CSymbol * baseClassId )
{
	if( classesList.find( id ) != classesList.end() ) {
		// ��� ���� ����� �����
		return false;
	} else {
		classesList[id] = CClassInfo( id, baseClassId );
	}

}

CClassInfo* CTable::FindClass( CSymbol * id )
{
	auto found = classesList.find( id );
	if( found == classesList.end() ) {
		return nullptr; //
	} else {
		return &(found->second);
	}
}

#include "SymbolsTable.h"

CSymbol * CClassInfo::Name() const
{
	return name;
}

CSymbol * CClassInfo::BaseClassName() const
{
	return baseClassName;
}

std::map<CSymbol*, CVarInfo*>& CClassInfo::VarList()
{
	return varList;
}

std::map<CSymbol*, CMethodInfo*>& CClassInfo::MethodList()
{
	return methodList;
}

bool CClassInfo::AddVar( CSymbol * name, CType * type )
{
	if( varList.find( name ) != varList.end() ) {
		// уже есть такая переменная
		return false;
	} else {
		varList[name] = new CVarInfo( name, type );
        varOrder[name] = varOrder.size();
	}
}

bool CClassInfo::AddMethod( CSymbol * name, CType * type )
{
	if( methodList.find( name ) != methodList.end() ) {
		// уже есть такой метод
		return false;
	} else {
		methodList[name] = new CMethodInfo( name, type );
	}
}

CVarInfo * CClassInfo::FindVar( CSymbol * name ) const
{
	auto found = varList.find( name );
	if( found == varList.end() ) {
		// не нашел
		return nullptr;
	} else {
		return found->second;
	}
}

CMethodInfo * CClassInfo::FindMethod( CSymbol * name ) const
{
	auto found = methodList.find( name );
	if( found == methodList.end() ) {
		// не нашел такой метод
		return false;
	} else {
		return found->second;
	}
}

int CClassInfo::GetVarOrderNumber( CSymbol* var ) const
{
    auto v = varOrder.find( var );
    if( v != varOrder.end() ) {
        return v->second;
    } else {
        //Или что?
        return -1;
    }
}

CSymbol * CVarInfo::Name() const
{
	return name;
}

CType * CVarInfo::Type() const
{
	return type;
}

bool CMethodInfo::AddFormalArg( CSymbol * _name, CType * _type )
{
	if( formalArgs.find( _name ) != formalArgs.end() ) {
		// уже есть такой аргумент
		return false;
	} else {
		formalArgs[_name] = new CVarInfo( _name, _type );
    formalArgsOrdered.push_back(_type);
	}
}

bool CMethodInfo::AddLocalArg( CSymbol * name, CType * type )
{
	if( localArgs.find( name ) != localArgs.end() ) {
		// уже есть такой аргумент
		return false;
	} else {
		localArgs[name] = new CVarInfo( name, type );
	}
}

CVarInfo * CMethodInfo::FindFormalArg( CSymbol * name ) const
{
	auto found = formalArgs.find( name );
	if( found == formalArgs.end() ) {
		return nullptr;
	} else {
		return found->second;
	}
}

CVarInfo * CMethodInfo::FindLocalArg( CSymbol * name ) const
{
	auto found = localArgs.find( name );
	if( found == localArgs.end() ) {
		return nullptr;
	} else {
		return found->second;
	}
}

CSymbol * CMethodInfo::Name() const
{
	return name;
}

std::map<CSymbol*, CVarInfo*>& CMethodInfo::FormalArgs()
{
	return formalArgs;
}

std::map<CSymbol*, CVarInfo*>& CMethodInfo::LocalArgs()
{
	return localArgs;
}

std::vector<CType*>& CMethodInfo::FormalArgsOrdered()
{
  return formalArgsOrdered;
}

CType * CMethodInfo::Type() const
{
	return type;
}

//bool CTable::AddClass( CSymbol* id )
//{
//	if( classesList.find( id ) != classesList.end() ) {
//		// уже есть такой класс
//		return false;
//	} else {
//		classesList[id] = CClassInfo( id );
//	}
//}

bool CTable::AddClass( CSymbol * id, CSymbol * baseClassId )
{
	if( classesList.find( id ) != classesList.end() ) {
		// уже есть такой класс
		return false;
	} else {
		classesList[id] = new CClassInfo( id, baseClassId );
	}

}

CClassInfo* CTable::FindClass( CSymbol * id ) const
{
	auto found = classesList.find( id );
	if( found == classesList.end() ) {
		return nullptr; //
	} else {
		return found->second;
	}
}

CStorage symbolStorage;
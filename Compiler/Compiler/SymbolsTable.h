#pragma once
#include "classes.h"
#include "common.h"

class CVarInfo
{
private:
	std::string name;
	CType* type;
};

class CMethodInfo
{
private:
	std::string name;
	std::map<CSymbol*, CVarInfo> formalArgs;
	std::map<CSymbol*, CVarInfo> localArgs;
};

class CClassInfo
{
private:
	std::string name;
	std::map<CSymbol*, CVarInfo> varInfo;
	std::map<CSymbol*, CMethodInfo> methodInfo;
};

class CTable
{
private:
	std::map<CSymbol*, CClassInfo> classesList;
};

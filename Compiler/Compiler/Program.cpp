#include "Program.h"


CProgram::CProgram( IMainClass* _mainClass, IClassDeclList* _classDeclList, IVarDeclList* _varDeclList, IMethodDeclList* _methodDeclList ) :
	mainClass( _mainClass ),
	classDeclList( _classDeclList ),
	varDeclList( _varDeclList ),
	methodDeclList( _methodDeclList )
{
	assert( _mainClass );
	assert( _classDeclList );
	assert( _varDeclList );
	assert( _methodDeclList );
}

CProgram::~CProgram()
{
	delete mainClass;
	delete classDeclList;
	delete varDeclList;
	delete methodDeclList;
}

const IMainClass* CProgram::MainClass() const
{
	return mainClass;
}

const IClassDeclList* CProgram::ClassDeclList() const
{
	return classDeclList;
}

const IVarDeclList* CProgram::VarDeclList() const
{
	return varDeclList;
}

const IMethodDeclList* CProgram::MethodDeclList() const
{
	return methodDeclList;
}
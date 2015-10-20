#include "Program.h"


CProgram::CProgram( IMainClass* _mainClass, IClassDeclList* _classDeclList ) :
	mainClass( _mainClass ),
	classDeclList( _classDeclList )
{
	assert( _mainClass != nullptr );
}

CProgram::~CProgram()
{
	delete mainClass;
	delete classDeclList;
}

const IMainClass* CProgram::MainClass() const
{
	return mainClass;
}

const IClassDeclList* CProgram::ClassDeclList() const
{
	return classDeclList;
}

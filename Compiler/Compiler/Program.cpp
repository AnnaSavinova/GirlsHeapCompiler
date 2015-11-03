#include "Program.h"


CProgram::CProgram( IMainClass* _mainClass, IClassDeclList* _classDeclList, int _line ) :
	mainClass( _mainClass ),
	classDeclList( _classDeclList )
{
	line = _line;
	assert( _mainClass != nullptr );
}

CProgram::~CProgram()
{
	if ( mainClass != nullptr ) {
		delete mainClass;
	}

	if ( classDeclList != nullptr ) {
		delete classDeclList;
	}
}

const IMainClass* CProgram::MainClass() const
{
	return mainClass;
}

const IClassDeclList* CProgram::ClassDeclList() const
{
	return classDeclList;
}

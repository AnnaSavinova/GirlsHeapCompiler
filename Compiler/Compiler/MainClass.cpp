#include "MainClass.h"


CMainClass::CMainClass( std::string _id, IStatementList* _statements, int _line ) :
	id( symbolStorage.Get( _id ) ),
    statements( _statements )
{
	line = _line;
	// assert( _id );
	assert( _statements );
}

CMainClass::~CMainClass()
{
	// delete id;
	delete statements;
}

CSymbol* CMainClass::Id() const
{
	return id;
}

const IStatementList* CMainClass::Statements() const
{
	return statements;
}

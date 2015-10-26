#include "MainClass.h"


CMainClass::CMainClass( std::string _id, IStatementList* _statements ) :
	id( _id ),
    statements( _statements )
{
	// assert( _id );
	assert( _statements );
}

CMainClass::~CMainClass()
{
	// delete id;
	delete statements;
}

const std::string CMainClass::Id() const
{
	return id;
}

const IStatementList* CMainClass::Statements() const
{
	return statements;
}

#include "MainClass.h"


CMainClass::CMainClass( std::string _id, IStatement* _statement ) :
	id( _id ),
	statement( _statement )
{
	// assert( _id );
	assert( _statement );
}

CMainClass::~CMainClass()
{
	// delete id;
	delete statement;
}

const std::string CMainClass::Id() const
{
	return id;
}

const IStatementList* CMainClass::Statements() const
{
	return statements;
}

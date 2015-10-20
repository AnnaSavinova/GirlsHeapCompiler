#include "MainClass.h"


CMainClass::CMainClass( CSymbol* _id, IStatement* _statement ) :
	id( _id ),
	statement( _statement )
{
	assert( _id );
	assert( _statement );
}

CMainClass::~CMainClass()
{
	delete id;
	delete statement;
}

const IMainClass* CMainClass::Id() const
{
	return id;
}

const IClassDeclList* CMainClass::Statement() const
{
	return statement;
}

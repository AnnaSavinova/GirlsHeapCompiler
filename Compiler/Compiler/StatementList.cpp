#include "StatementList.h"

CStatementList::CStatementList( std::vector<IStatement*>& _statementList )
{
	for( size_t i = 0; i < _statementList.size(); i++ ) {
		assert( _statementList[i] != nullptr );
	}
	statementList = _statementList;
}

CStatementList::~CStatementList()
{
	for( size_t i = 0; i < statementList.size(); i++ ) {
		if( statementList[i] != nullptr ) {
			delete statementList[i];
		}
	}
}

const std::vector<IStatement*>* CStatementList::StatementList() const
{
	return &statementList;
}



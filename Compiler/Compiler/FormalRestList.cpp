#include "FormalRestList.h"

FormalRestList::FormalRestList( std::vector<IFormalRest*>& _formalRestList )
{
	for( size_t i = 0; i < _formalRestList.size(); i++ ) {
		assert( _formalRestList[i] != nullptr );
	}
	formalRestList = _formalRestList;
}

FormalRestList::~FormalRestList()
{
	for( size_t i = 0; i < formalRestList.size(); i++ ) {
		if( formalRestList[i] != nullptr ) {
			delete formalRestList[i];
		}
	}
}

#include "IIRExp.h"
#include "IIRStm.h"

IIRExp::IIRExp()
{
}


IIRExp::~IIRExp()
{
}

CIRExpList::CIRExpList( const IIRExp* _head, CIRExpList* _tail )
{
	head = _head;
	tail = _tail;
}

CIRExpList::CIRExpList( std::vector<IIRExp*>& vectorExp )
{
	if( vectorExp.size() == 1 ) {
		head = vectorExp.front();
		tail = nullptr;
	} else {
		head = vectorExp.front();
		tail = new CIRExpList( std::vector<IIRExp*>( vectorExp.begin() + 1, vectorExp.end() ) );
	}
}

CIRExpList::~CIRExpList()
{
}

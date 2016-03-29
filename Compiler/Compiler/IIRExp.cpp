#include "IIRExp.h"
#include "IIRStm.h"

IIRExp::IIRExp()
{
}


IIRExp::~IIRExp()
{
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

#pragma once
#include "common.h"
#include "Frame.h"
#include <list>

class IIRExp
{
public:
	IIRExp();
	virtual ~IIRExp();
};

class CIRExpList
{
public:
	CIRExpList( IIRExp* _head, CIRExpList* _tail );
	CIRExpList( std::vector<IIRExp*>& vectorExp );
	~CIRExpList();

	IIRExp* GetHead();
	CIRExpList* GetTail();

//	std::list<IIRExp> GetExpList();

private:
	IIRExp* head;
	CIRExpList* tail;
};


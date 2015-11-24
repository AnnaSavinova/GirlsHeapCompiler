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
	CIRExpList( IIRExp head, CIRExpList tail );

private:
	std::list<IIRExp> expList;
};


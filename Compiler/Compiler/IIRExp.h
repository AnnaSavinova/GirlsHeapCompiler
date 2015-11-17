#pragma once
#include "common.h"
#include "Frame.h"
#include <list>

class IIRExp
{
public:
	IIRExp();
	virtual ~IIRExp();
	/*CONST( int value );
	NAME( CLabel label );
	TEMP( CTemp temp );
	BINOP( int binop, CIRExp left, CIRExp right );
	MEM( CIRExp exp );
	CALL( CIRExp func, CIRExpList args );
	ESEQ( CIRStm stm, CIRExp exp );*/
};

class CIRExpList
{
public:
	CIRExpList( IIRExp head, CIRExpList tail );

private:
	std::list<IIRExp> expList;
};


#pragma once
#include <list>
#include <vector>
#include "IRTreePrettyPrinter.h"

class IIRExp
{
public:
	IIRExp();
	virtual ~IIRExp();
    virtual void Accept ( CIRTreePrettyVisitor* visitor ) const = 0;
};

class CIRExpList
{
public:
	CIRExpList( const IIRExp* _head, CIRExpList* _tail );
	CIRExpList( std::vector<IIRExp*>& vectorExp );
	~CIRExpList();

    void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

	const IIRExp* head;
	const CIRExpList* tail;
};


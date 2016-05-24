#pragma once
#include <list>
#include <vector>
#include "IRTreePrettyPrinter.h"

class IIRExp
{
public:
	IIRExp();
    virtual const CIRExpList* Kids() const = 0;
    virtual const IIRExp* Build( const CIRExpList* ) const = 0;
	virtual ~IIRExp();
    virtual void Accept ( CIRTreePrettyVisitor* visitor ) const = 0;
};

class CIRExpList
{
public:
    CIRExpList( const IIRExp* _head, const CIRExpList* _tail ) : head( _head ), tail( _tail ) {};
	CIRExpList( std::vector<IIRExp*>& vectorExp );
	~CIRExpList();

    CIRExpList( const std::vector<const IIRExp *> args )
    {
        if( args.empty() ) {
            head = nullptr;
            tail = nullptr;
        }
        CIRExpList* newTail = new CIRExpList( args.back(), nullptr );
        for( int i = args.size() - 2; i > 0; --i ) {
            newTail = new CIRExpList( args[i], newTail );
        }
        head = args[0];
        tail = newTail;
    }

    void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

	const IIRExp* head;
	const CIRExpList* tail;
};


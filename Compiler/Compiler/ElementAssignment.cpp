#include "ElementAssignment.h"



CElementAssignment::CElementAssignment( std::string _id, IExp* _exp1, IExp* _exp2 ) : id( _id ), exp1( _exp1 ), exp2( _exp2 )
{}


CElementAssignment::~CElementAssignment()
{}

std::string CElementAssignment::Id() const
{
    return id;
}

const IExp * CElementAssignment::Exp1() const
{
    return exp1;
}

const IExp * CElementAssignment::Exp2() const
{
    return exp2;
}

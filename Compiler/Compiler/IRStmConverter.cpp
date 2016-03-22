#include "IRStmConverter.h"

CIRStmConverter::~CIRStmConverter()
{}

CIRStmConverter::CIRStmConverter( IIRStm * _stm ) : stm( _stm )
{}

IIRExp * CIRStmConverter::ToExp() const
{
    //Exp ê Stm
    assert( false );
    std::cerr << "IRTree ÍÅËÜÇß ÏÐÈÂÎÄÈÒÜ STM ê EXP" << std::endl;
    return nullptr;
}

IIRStm * CIRStmConverter::ToStm() const
{
    return stm;
}

IIRStm * CIRStmConverter::ToConditional( CLabel * t, CLabel * f ) const
{
    return nullptr;
}

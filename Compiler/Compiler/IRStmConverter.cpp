#include "IRStmConverter.h"

CIRStmConverter::~CIRStmConverter()
{}

CIRStmConverter::CIRStmConverter( const IIRStm * _stm ) : stm( _stm )
{}

const IIRExp * CIRStmConverter::ToExp() const
{
    //Exp ê Stm
    assert( false );
    std::cerr << "IRTree ÍÅËÜÇß ÏÐÈÂÎÄÈÒÜ STM ê EXP" << std::endl;
    return nullptr;
}

const IIRStm * CIRStmConverter::ToStm() const
{
    return stm;
}

#include "IRJump.h"



CIRJump::CIRJump( IIRExp* _exp, std::vector< CTemp* > _targets ) : exp( _exp ), targets( _targets )
{}


CIRJump::~CIRJump()
{}

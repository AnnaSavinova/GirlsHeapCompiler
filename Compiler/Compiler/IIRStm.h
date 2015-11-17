#pragma once
#include "Frame.h"

class IIRExp;

class IIRStm {
public:
    IIRStm();
    virtual ~IIRStm();

    /*void MOVE( CIRExp dst, CIRExp src );
    void EXP( CIRExp exp );
    void JUMP( CIRExp exp, std::vector< CTemp > targets );
    void CJUMP( int relop, CIRExp left, CIRExp right, CLabel ifTrue, CLabel ifFalse );
    void SEQ( CIRStm left, CIRStm right );
    void LABEL( CLabel label );*/

};

class CIRStmList {
public:
    //CIRStmList( CIRStm head, CIRStmList tail );
private:
};


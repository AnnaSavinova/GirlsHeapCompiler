#include "AsmTreeMaker.h"

namespace CodeGeneration
{
    void CAsmTreeMaker::InitializeTree( const CIRSeq * cmdList ) const
    {
        const CIRSeq* next = cmdList;
        while( next != 0 ) {
            munchStm( next->left );
            next = dynamic_cast<const CIRSeq*>( next->right );
        }
    }
    void CAsmTreeMaker::munchStm( const IIRStm * vertex ) const
    {}
    void CAsmTreeMaker::munchStm( const CIRCjump * vertex ) const
    {}
    void CAsmTreeMaker::munchStm( const CIRJump * vertex ) const
    {}
    void CAsmTreeMaker::munchStm( const CIRLabel * vertex ) const
    {}
    void CAsmTreeMaker::munchStm( const CIRSeq * vertex ) const
    {}
    void CAsmTreeMaker::munchStm( const CIRMove * vertex ) const
    {}
    void CAsmTreeMaker::munchStm( const CIRExp * vertex ) const
    {}
    CTemp * CAsmTreeMaker::munchExp( const IIRExp * expr ) const
    {
        return nullptr;
    }
    CTemp * CAsmTreeMaker::munchExp( const CIRConst * expr ) const
    {
        return nullptr;
    }
    CTemp * CAsmTreeMaker::munchExp( const CIRTemp * expr ) const
    {
        return nullptr;
    }
    CTemp * CAsmTreeMaker::munchExp( const CIRBinOp * expr ) const
    {
        return nullptr;
    }
    CTemp * CAsmTreeMaker::munchExp( const CIRMem * expr ) const
    {
        return nullptr;
    }
    CTemp * CAsmTreeMaker::munchExp( const CIRCall * expr ) const
    {
        return nullptr;
    }
    CTemp * CAsmTreeMaker::munchExpBinopLess( CIRBinOp * expr )
    {
        return nullptr;
    }
    CTempList * CAsmTreeMaker::munchArgs( CExpList * exprList )
    {
        return nullptr;
    }
}

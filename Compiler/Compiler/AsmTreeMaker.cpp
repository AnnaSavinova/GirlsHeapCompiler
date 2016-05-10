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
    void CAsmTreeMaker::munchStm( const IIRStm* vertex ) const
    {
        if( dynamic_cast<const CIRSeq*>(vertex) != 0 ) {
            munchStm( dynamic_cast<const CIRSeq*>(vertex) );
            return;
        }
        if( dynamic_cast<const CIRMove*>(vertex) != 0 ) {
            munchStm( dynamic_cast<const CIRMove*>(vertex) );
            return;
        }
        if( dynamic_cast<const CIRLabel*>(vertex) != 0 ) {
            munchStm( dynamic_cast<const CIRLabel*>(vertex) );
            return;
        }
        if( dynamic_cast<const CIRCjump*>(vertex) != 0 ) {
            munchStm( dynamic_cast<const CIRCjump*>(vertex) );
            return;
        }
        if( dynamic_cast<const CIRExp*>(vertex) != 0 ) {
            munchStm( dynamic_cast<const CIRExp*>(vertex) );
            return;
        }
        if( dynamic_cast<const CIRJump*>(vertex) != 0 ) {
            munchStm( dynamic_cast<const CIRJump*>(vertex) );
            return;
        }
        assert( false );
    };

    void CAsmTreeMaker::munchStm( const CIRCjump * vertex ) const
    {

    }

    void CAsmTreeMaker::munchStm( const CIRJump * vertex ) const
    {}

    void CAsmTreeMaker::munchStm( const CIRLabel * vertex ) const
    {
        const IInstruction* asmInstr = new CLabelAsm( new CLabelList( label->label, 0 ) );
        instruction.push_back( asmInstr );
    }

    void CAsmTreeMaker::munchStm( const CIRSeq * vertex ) const
    {
        munchStm( vertex->left );
        if ( vertex->right != nullptr ) {
            munchStm( vertex->right );
        }
    }
  
    void CAsmTreeMaker::munchStm( const CIRMove * vertex ) const
    {}
    void CAsmTreeMaker::munchStm( const CIRExp * vertex ) const
    {}
    CTemp * CAsmTreeMaker::munchExp( const IIRExp * expr ) const
    {
        if( dynamic_cast<const CIRConst*>( expr ) != 0 ) {
            return munchExp( dynamic_cast<const CIRConst*>( expr ) );
        }
        if( dynamic_cast<const CIRTemp*>( expr ) != 0 ) {
            return munchExp( dynamic_cast<const CIRTemp*>( expr ) );
        }
        if( dynamic_cast<const CIRBinOp*>( expr ) != 0 ) {
            return munchExp( dynamic_cast<const CIRBinOp*>( expr ) );
        }
        if( dynamic_cast<const CIRMem*>( expr ) != 0 ) {
            return munchExp( dynamic_cast<const CIRMem*>( expr ) );
        }
        if( dynamic_cast<const CIRCall*>( expr ) != 0 ) {
            return munchExp( dynamic_cast<const CIRCall*>( expr ) );
        }
        assert( false );
        return 0;
    }
    CTemp * CAsmTreeMaker::munchExp( const CIRConst * expr ) const
    {
        CTemp* newTemp = new CTemp();
        std::string asmCmd = "mov 'd0, ";
        asmCmd += std::to_string( expr->value );
        asmCmd += "\n";
        IInstruction* asmInstruction = new CMoveAsm( asmCmd, newTemp, 0 );
        instruction.push_back( asmInstruction );
        return newTemp;
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

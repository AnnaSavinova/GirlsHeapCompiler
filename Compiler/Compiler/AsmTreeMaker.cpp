#include "AsmTreeMaker.h"

namespace CodeGeneration
{
    void CAsmTreeMaker::InitializeTree( const CIRSeq * cmdList ) const
    {
        const CIRSeq* next = cmdList;
        while( next != 0 ) {
            munchStm( next->left );
            next = dynamic_cast< const CIRSeq* >( next->right );
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
    {
        IInstruction* asmInstr = new COperAsm( "jmp 'j0\n", nullptr, nullptr, new CLabelList( vertex->label, nullptr ) );
        instruction.push_back( asmInstr );
    }

    void CAsmTreeMaker::munchStm( const CIRLabel * vertex ) const
    {
        IInstruction* asmInstr = new CLabelAsm( vertex->label );
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

    const CTemp * CAsmTreeMaker::munchExp( const IIRExp * expr ) const
    {
        if( dynamic_cast< const CIRConst* >( expr ) != 0 ) {
            return munchExp( dynamic_cast< const CIRConst* >( expr ) );
        }
        if( dynamic_cast< const CIRTemp* >( expr ) != 0 ) {
            return munchExp( dynamic_cast< const CIRTemp* >( expr ) );
        }
        if( dynamic_cast< const CIRBinOp* >( expr ) != 0 ) {
            return munchExp( dynamic_cast< const CIRBinOp* >( expr ) );
        }
        if( dynamic_cast< const CIRMem* >( expr ) != 0 ) {
            return munchExp( dynamic_cast< const CIRMem* >( expr ) );
        }
        if( dynamic_cast< const CIRCall* >( expr ) != 0 ) {
            return munchExp( dynamic_cast< const CIRCall* >( expr ) );
        }
        assert( false );
        return 0;
    }

    const CTemp * CAsmTreeMaker::munchExp( const CIRConst * expr ) const
    {
        CTemp* newTemp = new CTemp();
        std::string asmCmd = "mov 'd0, ";
        asmCmd += std::to_string( expr->value );
        asmCmd += "\n";
        IInstruction* asmInstruction = new CMoveAsm( asmCmd, newTemp, 0 );
        instruction.push_back( asmInstruction );
        return newTemp;
    }
    const CTemp * CAsmTreeMaker::munchExp( const CIRTemp * expr ) const
    {
        return expr->temp;
    }
    const CTemp * CAsmTreeMaker::munchExp( const CIRBinOp * expr ) const
    {
        throw std::logic_error( "Не реализован метод CAsmTreeMaker::munchExp( const CIRBinOp * expr )" );
        return nullptr;
    }
    const  CTemp* CAsmTreeMaker::munchExp( const CIRMem * expr ) const
    {
        const CTemp* tmp = munchExp( expr->exp );
	    CTemp* fpTmp = new CTemp();
	    //func.push_back( new CMove( "mov 'd0, 's0\n", new CTempList( fpTmp, 0 ), new CTempList( stackFrame->GetFramePointer(), 0 ) ) );
	    CTemp* resTmp = new CTemp();
	    instruction.push_back( new CMoveAsm( "mov 'd0, ['s1]\n", new CTempList( resTmp, 0 ),
		new CTempList( fpTmp, new CTempList( tmp, 0 ) ) ) );

	    return resTmp;
    }
    const CTemp * CAsmTreeMaker::munchExp( const CIRCall * expr ) const
    {
        return nullptr;
    }
    const CTemp * CAsmTreeMaker::munchExpBinopLess( CIRBinOp * expr )
    {
        CTemp* tmp = new CTemp();
        instruction.push_back( new COperAsm( "mov 'd0, 0\n", new CTempList( tmp, 0 ), 0, 0 ) );

        CTemp* left = new CTemp();
        CTemp* right = new CTemp();
        instruction.push_back( new CMoveAsm( "mov 'd0, 's0\n", left, munchExp( expr->left ) ) );
        instruction.push_back( new CMoveAsm( "mov 'd0, 's0\n", right, munchExp( expr->right ) ) );

        CTempList* source = new CTempList( left, new CTempList( right, 0 ) );

        instruction.push_back( new COperAsm( "cmp 's0, s1\n", 0, source ) );

        CLabel* label = new CLabel();

        instruction.push_back( new COperAsm( "jnl 'l0\n", 0, 0, new CLabelList( label, 0 ) ) );
        instruction.push_back( new COperAsm( "mov 'd0, 1\n", new CTempList( tmp, 0 ), 0 ) );
        instruction.push_back( new CLabelAsm( label ) );

        return tmp;
    }
    CTempList * CAsmTreeMaker::munchArgs( CExpList * exprList )
    {
        return nullptr;
    }


}

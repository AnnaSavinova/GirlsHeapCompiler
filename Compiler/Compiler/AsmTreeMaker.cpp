#include "AsmTreeMaker.h"

namespace CodeGeneration {
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
        if( dynamic_cast< const CIRSeq* >(vertex) != 0 ) {
            munchStm( dynamic_cast< const CIRSeq* >(vertex) );
            return;
        }
        if( dynamic_cast< const CIRMove* >(vertex) != 0 ) {
            munchStm( dynamic_cast< const CIRMove* >(vertex) );
            return;
        }
        if( dynamic_cast< const CIRLabel* >(vertex) != 0 ) {
            munchStm( dynamic_cast< const CIRLabel* >(vertex) );
            return;
        }
        if( dynamic_cast< const CIRCjump* >(vertex) != 0 ) {
            munchStm( dynamic_cast< const CIRCjump* >(vertex) );
            return;
        }
        if( dynamic_cast< const CIRExp* >(vertex) != 0 ) {
            munchStm( dynamic_cast< const CIRExp* >(vertex) );
            return;
        }
        if( dynamic_cast< const CIRJump* >(vertex) != 0 ) {
            munchStm( dynamic_cast< const CIRJump* >(vertex) );
            return;
        }
        assert( false );
    };

    void CAsmTreeMaker::munchStm( const CIRCjump * vertex ) const
    {
        const CTemp* regLeft = munchExp( vertex->left );
        const CTemp* regRight = munchExp( vertex->right );
        CTempList* tmpList = new CTempList( regLeft, new CTempList( regRight, nullptr ) );
        instruction.push_back( new COperAsm( "cmp 's0, 's1\n", nullptr, tmpList ) );
        CLabelList* trueList = new CLabelList( vertex->ifTrue, 0 );
        switch( vertex->relop ) {
            case EBinOp::EQ:
                instruction.push_back( new COperAsm( "je 'l0\n", 0, 0, trueList ) );
                break;
            case EBinOp::GT:
                instruction.push_back( new COperAsm( "jg 'l0\n", 0, 0, trueList ) );
                break;
            case EBinOp::LESS:
                instruction.push_back( new COperAsm( "jle 'l0\n", 0, 0, trueList ) );
                break;
            case EBinOp::NE:
                instruction.push_back( new COperAsm( "jne 'l0\n", 0, 0, trueList ) );
                break;
            // ничего другого у нас вроде нет...
            //case GE:
            //    instruction.push_back( new COperAsm( "jge 'l0\n", 0, 0, trueList ) );
            //    break;
            //case LT:
            //    instruction.push_back( new COperAsm( "jl 'l0\n", 0, 0, trueList ) );
            //    break;
            //case UGE:
            //    instruction.push_back( new COperAsm( "jl 'l0\n", 0, 0, trueList ) );
            //    break;
            //case UGT:
            //    instruction.push_back( new COperAsm( "jle 'l0\n", 0, 0, trueList ) );
            //    break;
            //case ULE:
            //    instruction.push_back( new COperAsm( "jg 'l0\n", 0, 0, trueList ) );
            //    break;
            //case ULT:
            //    instruction.push_back( new COperAsm( "jge 'l0\n", 0, 0, trueList ) );
            //    break;
            default:
                assert( false );
        }
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
        if( vertex->right != nullptr ) {
            munchStm( vertex->right );
        }
    }

    void CAsmTreeMaker::munchStm( const CIRMove * vertex ) const
    {
        //Temp->Mem
        if( dynamic_cast< const CIRMem* >( vertex->Dst() ) ) {
            // NO MEM <- MEM in x86
            const CIRMem* memDst = dynamic_cast< const CIRMem* >( vertex->Dst() );

            if( dynamic_cast< const CIRBinOp* >( memDst->exp ) ) {
                const CIRBinOp* binOp = dynamic_cast< const CIRBinOp* >( memDst->exp );

                // MEM[+(expr,const)] <- Temp
                if( binOp->operation == EBinOp::PLUS ) {

                    if( dynamic_cast< const CIRConst* >( binOp->left ) != 0 ) {
                        const CIRConst* constant = dynamic_cast< const CIRConst* >( binOp->left );

                        std::string cmd = "mov ['d0+";
                        cmd += std::to_string( constant->value );
                        cmd += "],'s0\n";
                        IInstruction* asmInst = new CMoveAsm( cmd, munchExp( binOp->right ), munchExp( vertex->Src() ));
                        instruction.push_back( asmInst );
                        return;

                    } else if( dynamic_cast< const CIRConst* >( binOp->right ) != 0 ) {
                        const CIRConst* constant = dynamic_cast< const CIRConst* >( binOp->right );

                        std::string cmd = "mov ['d0+";
                        cmd += std::to_string( constant->value );
                        cmd += "], 's0\n";
                        IInstruction* asmInst = new CMoveAsm( cmd, munchExp( binOp->left ), munchExp( vertex->Src() ) );
                        instruction.push_back( asmInst );
                        return;
                    }
                }
            }
            std::string cmd = "mov ['d0], 's0\n";
            IInstruction* asmInst = new CMoveAsm( cmd, munchExp( memDst->exp ), munchExp( vertex->Src() ) );
            instruction.push_back( asmInst );
            return;
        } else if( dynamic_cast< const CIRTemp* >( vertex->Dst() ) ) {
            // Temp <- Temp; Temp <- Mem
            const CIRTemp* tmp = dynamic_cast< const CIRTemp* >( vertex->Dst() );

            std::string cmd = "mov 'd0, 's0\n";
            IInstruction* asmInst = new CMoveAsm( cmd, tmp->temp, munchExp( vertex->Src() ) );
            instruction.push_back( asmInst );
            return;
        }
    }

    void CAsmTreeMaker::munchStm( const CIRExp * vertex ) const
    {
        munchExp( vertex->exp );
    }

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

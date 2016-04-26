#pragma once

#include "common.h"
#include "Temp.h"
#include "Frame.h"
#include "Instruction.h"


namespace CodeGeneration
{
    class CAsmTreeMaker {
    public:
        CAsmTreeMaker( CFrame* _frame ) :
            frame( _frame ), isInitialized( false ) {};

        void InitializeTree( CIRSeq* cmdList );
        bool IsInitialized() { return isInitialized; };

        std::list<IInstruction*> GetAsmInstruction() { return instruction; };
        CFrame* GetFrame() { return frame; };

    private:
        std::list<IInstruction*> instruction;
        bool isInitialized;
        CFrame* frame;

        void munchStm( IIRStm* vertex );
        
        void munchStm( CIRCjump* vertex );
        void munchStm( CIRJump* vertex );
        void munchStm( CIRLabel* vertex );
        void munchStm( CIRSeq* vertex );
        void munchStm( CIRMove* vertex );
        void munchStm( CIRExp* vertex );

        CTemp* munchExp( IIRExp* expr );

        CTemp* munchExp( CIRConst* expr );
        CTemp* munchExp( CIRTemp* expr );
        CTemp* munchExp( CIRBinOp* expr );
        CTemp* munchExp( CIRMem* expr );
        CTemp* munchExp( CIRCall* expr );

        CTemp* munchExpBinopLess( CIRBinOp* expr );

        CTempList* munchArgs( CExpList* exprList );
    };


};
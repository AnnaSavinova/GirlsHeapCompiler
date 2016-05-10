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

        void InitializeTree( const CIRSeq* cmdList ) const;
        bool IsInitialized() { return isInitialized; };

        std::list<IInstruction*> GetAsmInstruction() { return instruction; };
        CFrame* GetFrame() { return frame; };

    private:
        mutable std::list<IInstruction*> instruction;
        bool isInitialized;
        CFrame* frame;

        void munchStm( const IIRStm* vertex ) const;
        
        void munchStm( const CIRCjump* vertex ) const;
        void munchStm( const CIRJump* vertex ) const;
        void munchStm( const CIRLabel* vertex ) const;
        void munchStm( const CIRSeq* vertex ) const;
        void munchStm( const CIRMove* vertex ) const;
        void munchStm( const CIRExp* vertex ) const;

        const CTemp* munchExp( const IIRExp* expr ) const;

        const CTemp* munchExp( const CIRConst* expr ) const;
        const CTemp* munchExp( const CIRTemp* expr ) const;
        const CTemp* munchExp( const CIRBinOp* expr ) const;
        const CTemp* munchExp( const CIRMem* expr ) const;
        const CTemp* munchExp( const CIRCall* expr ) const;

        const CTemp* munchExpBinopLess( CIRBinOp* expr );

        CTempList* munchArgs( CExpList* exprList );
    };
};
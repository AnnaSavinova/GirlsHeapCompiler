#pragma once
#include "common.h"

namespace CodeGeneration
{
    class IInstruction {
    public:
        const std::string AsmCode;
        virtual CIRTempList* UsedVars() const = 0;
        virtual CIRTempList* DefindedVars() const = 0;
        virtual CIRLabelList* JumpTargets() const = 0;
        std::string Format( const Temp::CTempMap* varsMapping ) const;
        IInstruction();
        ~IInstruction();
    };
} // namespace CodeGeneration


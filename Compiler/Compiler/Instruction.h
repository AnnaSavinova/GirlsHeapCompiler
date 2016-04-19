#pragma once
#include "common.h"
#include "Temp.h"

namespace CodeGeneration
{
    class IInstruction {
    public:
        const std::string AsmCode;
        virtual CTempList* UsedVars() const = 0;
        virtual CTempList* DefindedVars() const = 0;
        virtual CLabelList* JumpTargets() const = 0;
        std::string Format( const std::map<CTemp, std::string> varsMapping ) const;
        IInstruction();
        ~IInstruction();
    };
} // namespace CodeGeneration


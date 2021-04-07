#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class BinaryOr : public IRInstr
{
    public:
        BinaryOr(BasicBlock *bb, SymbolTableElement a, SymbolTableElement b, SymbolTableElement res);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement a, b, res;
};

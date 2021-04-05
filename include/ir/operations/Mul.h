#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Mul : public IRInstr
{
    public:
        Mul(BasicBlock *bb, SymbolTableElement a, SymbolTableElement b, SymbolTableElement res);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement a, b, res;
};

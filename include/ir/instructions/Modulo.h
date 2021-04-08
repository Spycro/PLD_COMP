#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Modulo : public IRInstr
{
    public:
        Modulo(BasicBlock *bb, SymbolTableElement a, SymbolTableElement b, SymbolTableElement res);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement a, b, res;
};

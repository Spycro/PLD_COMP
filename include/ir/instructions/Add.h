#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Add : public IRInstr
{
    public:
        Add(BasicBlock *bb, SymbolTableElement a, SymbolTableElement b, SymbolTableElement res);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement a, b, res;
};

#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class BinaryAnd : public IRInstr
{
    public:
        BinaryAnd(BasicBlock *bb, SymbolTableElement a, SymbolTableElement b, SymbolTableElement res);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement a, b, res;
};

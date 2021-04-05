#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Rmem : public IRInstr
{
    public:
        Rmem(BasicBlock *bb, SymbolTableElement addressToRead, SymbolTableElement out);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement addressToRead, out;
};

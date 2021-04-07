#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Wmem : public IRInstr
{
    public:
        Wmem(BasicBlock *bb, SymbolTableElement valToWrite_, SymbolTableElement address);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement valToWrite, address;
};

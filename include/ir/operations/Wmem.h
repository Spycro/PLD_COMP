#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Wmem : public IRInstr
{
    public:
        Wmem(BasicBlock *bb, SymbolTableElement ValueToWrite, SymbolTableElement address);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement ValueToWrite, address;
};

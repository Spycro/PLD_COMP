#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class putChar : public IRInstr
{
    public:
        putChar(BasicBlock *bb, SymbolTableElement charToPrint);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement charToPrint;
};

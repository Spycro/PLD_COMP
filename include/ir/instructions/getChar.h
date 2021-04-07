#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class getChar : public IRInstr
{
    public:
        getChar(BasicBlock *bb, SymbolTableElement charDest);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement charDest;
};

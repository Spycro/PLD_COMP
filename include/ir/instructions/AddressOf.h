#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class AddressOf : public IRInstr
{
    public:
        AddressOf(BasicBlock *bb, SymbolTableElement variable, SymbolTableElement pointer);

        void gen_asm(std::ostream &o) override;

    private:
        SymbolTableElement variable, pointer;
};

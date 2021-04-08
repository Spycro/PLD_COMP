#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Copy : public IRInstr
{
public:
    Copy(BasicBlock *bb, SymbolTableElement x, SymbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement x, d;
};

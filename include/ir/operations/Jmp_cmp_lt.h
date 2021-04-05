#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Jmp_cmp_lt : public IRInstr
{
public:
    Jmp_cmp_lt(BasicBlock *bb, SymbolTableElement rightParameter, SymbolTableElement leftParameter);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement rightParameter, leftParameter; //rightParameter the reference value, y the value to compare to de reference value
};

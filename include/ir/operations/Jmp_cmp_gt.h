#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Jmp_cmp_gt : public IRInstr
{
public:
    Jmp_cmp_gt(BasicBlock *bb, SymbolTableElement leftParameter, SymbolTableElement rightParameter);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement leftParameter, rightParameter, d; //leftParameter the value to compare to de reference value, rightParameter the reference value, d the destination value
};
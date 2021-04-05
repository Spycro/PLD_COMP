#pragma once
#include "../IRInstr.h"

//Lesser or equal comparison instruction
class Cmp_ge : public IRInstr
{
public:
    Cmp_ge(BasicBlock *bb, SymbolTableElement leftParameter, SymbolTableElement rightParameter, SymbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement leftParameter, rightParameter, d; //leftParameter the value to compare to de reference value, rightParameter the reference value, d the destination value
};

#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"
#include "ir/CFG.h"

class Call : public IRInstr
{
public:
    Call(BasicBlock *bb_, CFG* cfg_, std::vector<SymbolTableElement> params_ , SymbolTableElement output_);

    void gen_asm(std::ostream &o) override;

private:
    CFG* cfg;
    std::vector<SymbolTableElement> params;
    SymbolTableElement output;
};


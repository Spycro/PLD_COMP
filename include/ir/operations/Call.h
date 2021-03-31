#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Call : public IRInstr
{
public:
    Call(BasicBlock *bb_, std::string functionName_);

    void gen_asm(std::ostream &o) override;

private:
    std::string functionName;
};


#include "ir/operations/Jmp_cmp_lt.h"

#include "ir/BasicBlock.h"

Jmp_cmp_lt::Jmp_cmp_lt(BasicBlock* bb_, SymbolTableElement rightParameter_, SymbolTableElement leftParameter_) : IRInstr(bb_), rightParameter(rightParameter_), leftParameter(leftParameter_){}


void Jmp_cmp_lt::gen_asm(std::ostream &o) {

    std::string valRightParameter, valLeftParameter;

    valRightParameter = rightParameter.getAsm();

    valLeftParameter = leftParameter.getAsm();

    o << "\tmovq " << valLeftParameter << ", %rax" << std::endl; // We need one parameter to be a register
    o << "\tcmpq " << valRightParameter << ", %rax" << std::endl;
    o << "\tjge " << '.' << bb->exit_false->label << std::endl; 
}
#include "ir/instructions/Jmp_cmp_le.h"

#include "ir/BasicBlock.h"

Jmp_cmp_le::Jmp_cmp_le(BasicBlock* bb_, SymbolTableElement leftParameter_, SymbolTableElement rightParameter_) : IRInstr(bb_), leftParameter(leftParameter_), rightParameter(rightParameter_){}


void Jmp_cmp_le::gen_asm(std::ostream &o) {

    std::string valLeftParameter, valRightParameter;

    valLeftParameter = leftParameter.getAsm();

    valRightParameter = rightParameter.getAsm();   

    o << "\tmovq " << valLeftParameter << ", %rax" << std::endl; // We need one parameter to be a register
    o << "\tcmpq " << valRightParameter << ", %rax" << std::endl;
    o << "\tjg " << '.' << bb->exit_false->label << std::endl; 
}
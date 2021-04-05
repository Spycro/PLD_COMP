#include "ir/operations/Cmp_le.h"

#include "ir/BasicBlock.h"

Cmp_le::Cmp_le(BasicBlock* bb_, SymbolTableElement leftParameter_, SymbolTableElement rightParameter_, SymbolTableElement d_) : IRInstr(bb_), leftParameter(leftParameter_), rightParameter(rightParameter_), d(d_){}


void Cmp_le::gen_asm(std::ostream &o) {

    std::string valLeftParameter, valRightParameter, valD;

    valLeftParameter = leftParameter.getAsm();

    valRightParameter = rightParameter.getAsm();  

    valD = d.getAsm();
    o << "\tmovq " << valLeftParameter << ", %rax" << std::endl; // We need one parameter to be a register
    o << "\tcmpq " << valRightParameter << ", %rax" << std::endl;
    o << "\tsetle %al" << std::endl;
    o << "\tmovb %al, " <<  valD << std::endl;
    
}
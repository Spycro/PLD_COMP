#include "ir/operations/Cmp_neq.h"

#include "ir/BasicBlock.h"

Cmp_neq::Cmp_neq(BasicBlock* bb_, SymbolTableElement x_, SymbolTableElement y_, SymbolTableElement d_) : IRInstr(bb_), x(x_), y(y_), d(d_){}


void Cmp_neq::gen_asm(std::ostream &o) {

    std::string valX, valY, valD;

    valX = x.getAsm();

    valY = y.getAsm();

    valD = d.getAsm();
    o << "\tmovq " << valY << ", %rax" << std::endl; // We need one parameter to be a register
    o << "\tcmpq " << valX << ", %rax" << std::endl;
    o << "\tsetne %al" << std::endl;
    o << "\tmovb %al, " <<  valD << std::endl;
    
}
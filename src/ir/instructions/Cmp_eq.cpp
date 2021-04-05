#include "ir/instructions/Cmp_eq.h"

#include "ir/BasicBlock.h"

Cmp_eq::Cmp_eq(BasicBlock* bb_, SymbolTableElement x_, SymbolTableElement y_, SymbolTableElement d_) : IRInstr(bb_), x(x_), y(y_), d(d_){}


void Cmp_eq::gen_asm(std::ostream &o) {

    std::string valX, valY, valD;

    valX = x.getAsm();

    valY = y.getAsm();

    valD = d.getAsm();
    o << "\tmovq " << valY << ", %rax" << std::endl; // We need one parameter to be a register
    o << "\tcmpq " << valX << ", %rax" << std::endl;
    o << "\tsete %al" << std::endl;
    o << "\tmovb %al, " <<  valD << std::endl;
    
}
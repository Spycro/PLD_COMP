#include "ir/instructions/Jmp_cmp_neq.h"

#include "ir/BasicBlock.h"

Jmp_cmp_neq::Jmp_cmp_neq(BasicBlock* bb_, SymbolTableElement x_, SymbolTableElement y_) : IRInstr(bb_), x(x_), y(y_){}


void Jmp_cmp_neq::gen_asm(std::ostream &o) {

    std::string valX, valY;

    valX = x.getAsm();

    valY = y.getAsm();

    o << "\tmovq " << valY << ", %rax" << std::endl; // We need one parameter to be a register
    o << "\tcmpq " << valX << ", %rax" << std::endl;
    o << "\tje " << '.' << bb->getExit_false()->label << std::endl; 
}
#include "ir/operations/Cmp_eq.h"

#include "ir/BasicBlock.h"

Cmp_eq::Cmp_eq(BasicBlock* bb_, SymbolTableElement x_, SymbolTableElement y_, SymbolTableElement d_) : IRInstr(bb_), x(x_), y(y_), d(d_){}


void Cmp_eq::gen_asm(std::ostream &o) {

    std::string valX, valY, valD;

    valX = x.getAsm();

    valY = y.getAsm();

    valD = d.getAsm();

    o << "\tcmpl " << valX << ", " << valY << std::endl;
    o << "\tsetg %al" << std::endl;
    o << "\tmovb %al" <<  valD << std::endl;
    
}
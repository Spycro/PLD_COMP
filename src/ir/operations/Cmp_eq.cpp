#include "ir/operations/Cmp_eq.h"

#include "ir/BasicBlock.h"

Cmp_eq::Cmp_eq(BasicBlock* bb_, symbolTableElement x_, symbolTableElement y_, symbolTableElement d_) : IRInstr(bb_), x(x_), y(y_), d(d_){}


void Cmp_eq::gen_asm(std::ostream &o) {

    std::string valX, valY, valD;

    if(x.isConst){
        valX = "$" + x.constValue;
    }
    else{
        valX = "-" + std::to_string(x.memoryOffset) + "(%rbp)";
    }

    if(y.isConst) {
        valY = "$" + y.constValue;
    }
    else{
        valY = "-" + std::to_string(y.memoryOffset) + "(%rbp)";
    }

    valD = "-" + std::to_string(y.memoryOffset) + "(rbp)";

    o << "\tcmpl " << valX << ", " << valY << std::endl;
    o << "\tsetg %al" << std::endl;
    o << "\tmovb %al" <<  valD << std::endl;
    
}
#include "ir/operations/Jmp_cmp_eq.h"

#include "ir/BasicBlock.h"

Jmp_cmp_eq::Jmp_cmp_eq(BasicBlock* bb_, symbolTableElement x_, symbolTableElement y_) : IRInstr(bb_), x(x_), y(y_){}


void Jmp_cmp_eq::gen_asm(std::ostream &o) {

    std::string valX, valY;

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

    o << "\tcmpl " << valX << ", " << valY << std::endl;
    o << "\tjne " << '.' << bb->exit_false->label << std::endl; 
}
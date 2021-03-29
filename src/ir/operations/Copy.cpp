#include "ir/operations/Copy.h"

Copy::Copy(BasicBlock* bb, symbolTableElement inputX, symbolTableElement inputD) : IRInstr(bb), d(inputD), x(inputX){}


void Copy::gen_asm(std::ostream &o) {

    std::string val, dest;

    if(x.isConst){
        val = "$" + x.constValue;
    }
    else{
        val = "-" + std::to_string(x.memoryOffset) + "(%rbp)";
    }

    dest = "-" + std::to_string(d.memoryOffset) + "(%rbp)";


    o << "\tmovl " << val << ", " << dest << std::endl;

}
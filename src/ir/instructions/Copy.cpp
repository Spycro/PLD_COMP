#include "ir/instructions/Copy.h"

Copy::Copy(BasicBlock* bb, SymbolTableElement inputX, SymbolTableElement inputD) : IRInstr(bb), d(inputD), x(inputX){}


void Copy::gen_asm(std::ostream &o) {

    std::string val, dest;

    val = x.getAsm();
    dest = d.getAsm();


    o << "\tmovq " << val << ", " << dest << std::endl;

}
#include "ir/operations/Copy.h"

Copy::Copy(BasicBlock* bb, Type* t, std::string inputX, std::string inputD) : IRInstr(bb,t), d(inputD), x(inputX){}


void Copy::gen_asm(std::ostream &o) {

    int cst = stoi(x.substr(1));

    int index  = stoi(d.substr(1));
    int regAddr = -4 * index;

    o << "\tmovl " << "$" << cst << ", " << regAddr << "(%rbp)" << std::endl;

}
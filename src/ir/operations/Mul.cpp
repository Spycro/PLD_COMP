#include "ir/operations/Mul.h"
#include "ir/ASMConstants.h"

Mul::Mul(BasicBlock *bb, SymbolTableElement a_, SymbolTableElement b_, SymbolTableElement res_) : IRInstr(bb), a(a_), b(b_), res(res_){}


void Mul::gen_asm(std::ostream &o) {

    std::string val1, val2, dest;

    val1 = a.getAsm();
    val2 = b.getAsm();
    dest = res.getAsm();

    o << "\tmovq " << val1 << ", " << RAX_REGISTER.getAsm() <<std::endl;
    o << "\timulq " << val2 << ", " << RAX_REGISTER.getAsm() << std::endl;
    o << "\tmovq " << RAX_REGISTER.getAsm() << ", " << dest << std::endl;

}

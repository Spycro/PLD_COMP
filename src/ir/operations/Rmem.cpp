#include "ir/operations/Rmem.h"
#include "ir/ASMConstants.h"

Rmem::Rmem(BasicBlock *bb, SymbolTableElement addressToRead_, SymbolTableElement out_) : IRInstr(bb), addressToRead(addressToRead_), out(out_){}


void Rmem::gen_asm(std::ostream &o) {


    o << "\tmovq " << addressToRead.getAsm() << ", " << RAX_REGISTER.getAsm() <<std::endl;
    o << "\tmovq (" << RAX_REGISTER.getAsm() << "), " << RAX_REGISTER.getAsm() <<std::endl;
    o << "\tmovq " << RAX_REGISTER.getAsm() << ", " << out.getAsm()  << std::endl;

}

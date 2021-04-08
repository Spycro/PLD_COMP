#include "ir/instructions/Wmem.h"
#include "ir/ASMConstants.h"
#include "ir/ASMx86Utils.h"

using namespace ASMx86Utils;

Wmem::Wmem(BasicBlock *bb, SymbolTableElement valToWrite_, SymbolTableElement address_) : IRInstr(bb), valToWrite(valToWrite_), address(address_){}


void Wmem::gen_asm(std::ostream &o) {
    o << "\tmovq " << address.getAsm() << ", " << RAX_REGISTER.getAsm() << std::endl;
    // Convert valToWrite to 64 bits
    o << moveTo64Reg(valToWrite, RDX_REGISTER) << std::endl;
    // Move value to target memory address stored in rax
    o << "\tmovq " << RDX_REGISTER.getAsm() << ", (" << RAX_REGISTER.getAsm() << ")" << std::endl;
}

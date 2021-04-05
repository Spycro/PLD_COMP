#include "ir/instructions/Wmem.h"
#include "ir/ASMConstants.h"

Wmem::Wmem(BasicBlock *bb, SymbolTableElement ValueToWrite_, SymbolTableElement address_) : IRInstr(bb), ValueToWrite(ValueToWrite_), address(address_){}


void Wmem::gen_asm(std::ostream &o) {

    std::string inVal, outVal;

    inVal = ValueToWrite.getAsm();
    outVal = address.getAsm();

    o << "\tmovq " << outVal << ", " << RAX_REGISTER.getAsm() <<std::endl;
    o << "\tmovq " << inVal << ", (" << RAX_REGISTER.getAsm() << ")" << std::endl;

}

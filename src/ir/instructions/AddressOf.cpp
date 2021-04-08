#include "ir/instructions/AddressOf.h"
#include "ir/ASMConstants.h"

AddressOf::AddressOf(BasicBlock *bb, SymbolTableElement variable_, SymbolTableElement pointer_) : IRInstr(bb), variable(variable_), pointer(pointer_){}


void AddressOf::gen_asm(std::ostream &o) {


    o << "\tleaq " << variable.getAsm() << ", " << RAX_REGISTER.getAsm() <<std::endl;
    o << "\tmovq " << RAX_REGISTER.getAsm() << ", " << pointer.getAsm() <<std::endl;

}

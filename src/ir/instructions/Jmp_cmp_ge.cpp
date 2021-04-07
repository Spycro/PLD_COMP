#include "ir/instructions/Jmp_cmp_ge.h"

#include "ir/BasicBlock.h"
#include "ir/ASMConstants.h"
#include "ir/ASMx86Utils.h"

using namespace ASMx86Utils;

Jmp_cmp_ge::Jmp_cmp_ge(BasicBlock* bb_, SymbolTableElement leftParameter_, SymbolTableElement rightParameter_) : IRInstr(bb_), leftParameter(leftParameter_), rightParameter(rightParameter_){}


void Jmp_cmp_ge::gen_asm(std::ostream &o) {
    // Convert both operands to 64 bits
    o << moveTo64Reg(leftParameter, RAX_REGISTER) << std::endl;
    o << moveTo64Reg(rightParameter, RDX_REGISTER) << std::endl;

    // Perform 64 bits comparison
    o << "\tcmpq " << RDX_REGISTER.getAsm() << ", " << RAX_REGISTER.getAsm() << std::endl;
    o << "\tjl " << '.' << bb->getExit_false()->label << std::endl;
}
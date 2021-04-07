#include "ir/instructions/Cmp_ge.h"

#include "ir/BasicBlock.h"
#include "ir/ASMConstants.h"
#include "ir/ASMx86Utils.h"

using namespace ASMx86Utils;

Cmp_ge::Cmp_ge(BasicBlock* bb_, SymbolTableElement leftVal_, SymbolTableElement rightVal_, SymbolTableElement dst_) : IRInstr(bb_),
                                                                                                                        leftVal(leftVal_),
                                                                                                                        rightVal(rightVal_),
                                                                                                                        dst(dst_){}

void Cmp_ge::gen_asm(std::ostream &o) {

    // Convert both operands to 64 bits
    o << moveTo64Reg(leftVal, RAX_REGISTER) << std::endl;
    o << moveTo64Reg(rightVal, RDX_REGISTER) << std::endl;

    // Perform 64 bits comparison
    o << "\tcmpq " << RDX_REGISTER.getAsm() << ", " << RAX_REGISTER.getAsm() << std::endl;
    // Put boolean result in 8bit register
    o << "\tsetge " << AL_REGISTER.getAsm() << std::endl;

    // Just move the result in dst if it fits
    // Or else convert it to dst size and move it
    o << moveTo(AL_REGISTER, dst) << std::endl;
    
}
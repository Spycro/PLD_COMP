#include "ir/instructions/Jmp_return.h"

#include "ir/BasicBlock.h"
#include "ir/CFG.h"

Jmp_return::Jmp_return(BasicBlock *bb_, CFG* function_) : IRInstr(bb_), function(function_){}


void Jmp_return::gen_asm(std::ostream &o) {
    o << "\tjmp " << '.' << function->getLastBlock()->label << std::endl; 
}
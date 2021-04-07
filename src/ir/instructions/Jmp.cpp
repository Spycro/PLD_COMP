#include "ir/instructions/Jmp.h"

#include "ir/BasicBlock.h"

Jmp::Jmp(BasicBlock* bb_, shared_ptr<BasicBlock> toJump_) : IRInstr(bb_), toJump(toJump_){}


void Jmp::gen_asm(std::ostream &o) {
    if(toJump){
        o << "\tjmp " << '.' << toJump->label << std::endl; 
    }
}
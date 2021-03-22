#include "../../include/ir/CFG.h"

void CFG::add_bb(BasicBlock* bb){
    bbs.push_back(bb);
}

void CFG::gen_asm(std::ostream& o){
    gen_asm_prologue(o);

    vector<BasicBlock*>::iterator it;
    for(it = bbs.begin(); it != bbs.end(); it++){
        (*it)->gen_asm(o);
    }

    gen_asm_epilogue(o);
}

void CFG::gen_asm_prologue(std::ostream& o) {
    o << ".globl" + "NomFONCTION" + "\n" //a modifier
               " NomFONCTION: \n" //a modifier
               "#prologue\n"
               "	pushq %rbp #save rbp on stack\n"
               "	movq %rsp, %rbp #define rbp for current function\n";
}

void CFG::gen_asm_epilogue(std::ostream& o) {
    o <<       "#epiligue\n" // the epilogue
               "	popq %rbp #restore rbp from stack\n"
               " 	ret\n";
}
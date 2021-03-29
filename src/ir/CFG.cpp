#include "../../include/ir/CFG.h"

CFG::CFG(Function* ast_) : ast(ast_) {}

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
    o << ".globl " << "NomFONCTION" << std::endl //a modifier
               << " NomFONCTION: " << std::endl //a modifier
               << "#prologue" << std::endl //prologue
               << "\tpushq %rbp #save rbp on stack" << std::endl
               << "\tmovq %rsp, %rbp #define rbp for current function" << std::endl;
}

void CFG::gen_asm_epilogue(std::ostream& o) {
    o <<       "#epilogue\n" // the epilogue
               "\tpopq %rbp #restore rbp from stack\n"
               "\tret\n";
}
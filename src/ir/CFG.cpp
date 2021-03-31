#include "../../include/ir/CFG.h"

extern Void voidType;

CFG::CFG(Function* ast_, std::string label_, Type* type_, std::vector<symbolTableElement> params_) : ast(ast_), label(label_), type(type_), params(params_) {}

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
    o << ".globl " << label << std::endl
               << label << ":" << std::endl
               << "#prologue" << std::endl //prologue
               << "\tpushq %rbp #save rbp on stack" << std::endl
               << "\tmovq %rsp, %rbp #define rbp for current function" << std::endl;
}

void CFG::gen_asm_epilogue(std::ostream& o) {
    o <<       "#epilogue\n" ;// the epilogue
    if(type==&voidType){
        o << "\tnop\n";
    }
    o   << "\tpopq %rbp #restore rbp from stack\n"
        << "\tret\n";
}
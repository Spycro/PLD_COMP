#include "ir/CFG.h"
#include "ir/BasicBlock.h"
#include "ir/IRInstr.h"
#include "ir/operations/Add.h"
#include "ir/operations/Copy.h"
#include "ir/operations/Call.h"
#include "ir/operations/Jmp_cmp_eq.h"
#include "type/Int64.h"
#include "type/Void.h"
#include "SymbolTable.h"

Void VOIDTYPE;
Int64 INTTYPE64;

void test_call(){
    SymbolTableElement param1(&INTTYPE64, "1");
    SymbolTableElement param2(&INTTYPE64, "2");
    std::vector<SymbolTableElement> params {param1, param2};

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));
    std::shared_ptr<CFG> secondCFG(new CFG(nullptr, "fct", &VOIDTYPE, params));

    BasicBlock bb0(firstCFG, nullptr);
    Call callInstr(&bb0, secondCFG);

    bb0.add_IRInstr(&callInstr);

    firstCFG->add_bb(&bb0);

    firstCFG->gen_asm(std::cout);
    secondCFG->gen_asm(std::cout);
}

void test_if_else_condition() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr, true);
    BasicBlock bb2(firstCFG, nullptr, true);
    BasicBlock bb3(firstCFG, nullptr);    

    Jmp_cmp_eq condJmp1(&bb0, SymbolTableElement(&INTTYPE64, "2"), SymbolTableElement(&INTTYPE64, "4"));
    Copy copyInstr1(&bb1, SymbolTableElement(&INTTYPE64, "2"), SymbolTableElement(&INTTYPE64, false, false, 8));
    Copy copyInstr2(&bb2, SymbolTableElement(&INTTYPE64, "3"), SymbolTableElement(&INTTYPE64, false, false, 8));

    bb0.add_IRInstr(&condJmp1);
    bb1.add_IRInstr(&copyInstr1);
    bb2.add_IRInstr(&copyInstr2);

    // if branch
    bb0.exit_true = &bb1;
    bb0.exit_false = &bb2;

    // final block in common for if and else
    bb1.exit_true = &bb3;
    bb2.exit_true = &bb3;

    firstCFG->add_bb(&bb0);
    firstCFG->add_bb(&bb1);
    firstCFG->add_bb(&bb2);
    firstCFG->add_bb(&bb3);

    firstCFG->gen_asm(std::cout);
}

void test_if_condition() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr);
    BasicBlock bb2(firstCFG, nullptr);

    Jmp_cmp_eq condJmp1(&bb0, SymbolTableElement(&INTTYPE64, "2"), SymbolTableElement(&INTTYPE64, "4"));
    Copy copyInstr1(&bb1, SymbolTableElement(&INTTYPE64, "2"), SymbolTableElement(&INTTYPE64, false, false, 8));

    bb0.add_IRInstr(&condJmp1);
    bb1.add_IRInstr(&copyInstr1);

    // if branch
    bb0.exit_true = &bb1;
    bb0.exit_false = &bb2;

    // final block in common for if and else
    bb1.exit_true = &bb2;

    firstCFG->add_bb(&bb0);
    firstCFG->add_bb(&bb1);
    firstCFG->add_bb(&bb2);

    firstCFG->gen_asm(std::cout);
}

void test_following_blocks() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr);

    Copy instr1(&bb0, SymbolTableElement(&INTTYPE64, "2"), SymbolTableElement(&INTTYPE64, false, false, 8));
    Copy instr2(&bb1, SymbolTableElement(&INTTYPE64, "4"), SymbolTableElement(&INTTYPE64, false, false, 16));

    bb0.add_IRInstr(&instr1);
    bb1.add_IRInstr(&instr2);
    bb0.exit_true = &bb1;

    firstCFG->add_bb(&bb0);
    firstCFG->add_bb(&bb1);

    firstCFG->gen_asm(std::cout);
}

void test_single_block() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);

    SymbolTableElement symbol1(&INTTYPE64, "2");
    SymbolTableElement symbol2(&INTTYPE64, false, false,8);

    Copy instr1(&bb0, symbol1, symbol2);
    bb0.add_IRInstr(&instr1);

    firstCFG->add_bb(&bb0);

    firstCFG->gen_asm(std::cout);
}

int main(){
    //test_single_block();
    //test_following_blocks();
    //test_if_condition();
    //test_if_else_condition();
    test_call();
}

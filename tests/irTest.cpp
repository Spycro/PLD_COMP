#include "ir/CFG.h"
#include "ir/BasicBlock.h"
#include "ir/IRInstr.h"
#include "ir/operations/Add.h"
#include "ir/operations/Copy.h"
#include "ir/operations/Call.h"
#include "ir/operations/Jmp_cmp_eq.h"
#include "type/Int64.h"

void test_call(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main"));
    std::shared_ptr<CFG> secondCFG(new CFG(nullptr, "fct"));

    BasicBlock bb0(firstCFG, nullptr);
    Call callInstr(&bb0, "fct");

    firstCFG->gen_asm(std::cout);
    secondCFG->gen_asm(std::cout);
}

void test_if_else_condition() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main"));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr, true);
    BasicBlock bb2(firstCFG, nullptr, true);
    BasicBlock bb3(firstCFG, nullptr);
    Int64 intType64;

    Jmp_cmp_eq condJmp1(&bb0, symbolTableElement(&intType64, "2"), symbolTableElement(&intType64, "4"));
    Copy copyInstr1(&bb1, symbolTableElement(&intType64, "2"), symbolTableElement(&intType64, false, false, 8));
    Copy copyInstr2(&bb2, symbolTableElement(&intType64, "3"), symbolTableElement(&intType64, false, false, 8));

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
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main"));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr);
    BasicBlock bb2(firstCFG, nullptr);
    Int64 intType64;

    Jmp_cmp_eq condJmp1(&bb0, symbolTableElement(&intType64, "2"), symbolTableElement(&intType64, "4"));
    Copy copyInstr1(&bb1, symbolTableElement(&intType64, "2"), symbolTableElement(&intType64, false, false, 8));

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
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main"));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr);
    Int64 intType64;

    Copy instr1(&bb0, symbolTableElement(&intType64, "2"), symbolTableElement(&intType64, false, false, 8));
    Copy instr2(&bb1, symbolTableElement(&intType64, "4"), symbolTableElement(&intType64, false, false, 16));

    bb0.add_IRInstr(&instr1);
    bb1.add_IRInstr(&instr2);
    bb0.exit_true = &bb1;

    firstCFG->add_bb(&bb0);
    firstCFG->add_bb(&bb1);

    firstCFG->gen_asm(std::cout);
}

void test_single_block() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main"));

    BasicBlock bb0(firstCFG, nullptr);

    Int64 intType64;

    symbolTableElement symbol1(&intType64, "2");
    symbolTableElement symbol2(&intType64, false, false,8);

    Copy instr1(&bb0, symbol1, symbol2);
    bb0.add_IRInstr(&instr1);

    firstCFG->add_bb(&bb0);

    firstCFG->gen_asm(std::cout);
}

int main(){
    //test_single_block();
    //test_following_blocks();
    //test_if_condition();
    test_if_else_condition();
}

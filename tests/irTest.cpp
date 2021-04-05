#include "ir/CFG.h"
#include "ir/BasicBlock.h"
#include "ir/IRInstr.h"
#include "ir/operations/Div.h"
#include "ir/operations/Mul.h"
#include "ir/operations/Add.h"
#include "ir/operations/Cmp_eq.h"
#include "ir/operations/Cmp_neq.h"
#include "ir/operations/Cmp_ge.h"
#include "ir/operations/Cmp_gt.h"
#include "ir/operations/Cmp_le.h"
#include "ir/operations/Cmp_lt.h"
#include "ir/operations/Sub.h"
#include "ir/operations/Copy.h"
#include "ir/operations/Call.h"
#include "ir/operations/Add.h"
#include "ir/operations/Jmp_cmp_eq.h"
#include "ir/operations/Jmp_cmp_neq.h"
#include "ir/operations/Jmp_cmp_lt.h"
#include "ir/operations/Jmp_cmp_le.h"
#include "ir/operations/Jmp_cmp_gt.h"
#include "ir/operations/Jmp_cmp_ge.h"
#include "type/Int64.h"
#include "type/Void.h"
#include "SymbolTable.h"
#include "ir/ASMConstants.h"

Void VOIDTYPE;
Int64 INTTYPE64;
Int64 INTTYPE32;

void test_operations_mul_div(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);

    SymbolTableElement input1(&INTTYPE64, "2");
    SymbolTableElement input2(&INTTYPE64, "10");
    SymbolTableElement input3(&INTTYPE64, "4");
    SymbolTableElement output(&INTTYPE64, false, false,8);

    Mul instr0(&bb0, input1, input2, output);
    Div instr1(&bb0, output, input3, output);
    Copy instr2(&bb0, output,RAX_REGISTER);
    bb0.add_IRInstr(&instr0);
    bb0.add_IRInstr(&instr1);
    bb0.add_IRInstr(&instr2);

    firstCFG->add_bb(&bb0);

    firstCFG->gen_asm(std::cout);
}
void test_operations_sub_add(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);

    SymbolTableElement input1(&INTTYPE64, "2");
    SymbolTableElement input2(&INTTYPE64, "10");
    SymbolTableElement input3(&INTTYPE64, "4");
    SymbolTableElement output(&INTTYPE64, false, false,8);

    Add instr0(&bb0, input1, input2, output);
    Sub instr1(&bb0, output, input3, output);
    Copy instr2(&bb0, output,RAX_REGISTER);
    bb0.add_IRInstr(&instr0);
    bb0.add_IRInstr(&instr1);
    bb0.add_IRInstr(&instr2);

    firstCFG->add_bb(&bb0);

    firstCFG->gen_asm(std::cout);
}

void test_cmp(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);

    SymbolTableElement input1(&INTTYPE64, "10");
    //SymbolTableElement input1(&INTTYPE64,false, false, 8);

    SymbolTableElement input2(&INTTYPE64, "11");
    SymbolTableElement dest(&INTTYPE64, false, false, 16);

    /* Copy instr0(&bb0, input2, input1);
    bb0.add_IRInstr(&instr0); */

    Cmp_gt instr1(&bb0,input1, input2, dest);
    Copy instr2(&bb0, dest, RAX_REGISTER);    
    bb0.add_IRInstr(&instr1);
    bb0.add_IRInstr(&instr2);

    firstCFG->add_bb(&bb0);

    firstCFG->gen_asm(std::cout);
}

void test_call_many_params(){
    SymbolTableElement param1(&INTTYPE64, "1");
    SymbolTableElement param2(&INTTYPE64, "2");
    SymbolTableElement param3(&INTTYPE64, "3");
    SymbolTableElement param4(&INTTYPE64, "4");
    SymbolTableElement param5(&INTTYPE64, "5");
    SymbolTableElement param6(&INTTYPE64, "6");
    SymbolTableElement param7(&INTTYPE64, "7");
    SymbolTableElement param8(&INTTYPE64, "8");
    std::vector<SymbolTableElement> params {param1, param2, param3, param4, param5, param6, param7, param8};

    SymbolTableElement funParam1(&INTTYPE64,true,true, 8);
    SymbolTableElement funParam2(&INTTYPE64,true,true, 16);
    SymbolTableElement funParam3(&INTTYPE64,true,true, 24);
    SymbolTableElement funParam4(&INTTYPE64,true,true, 32);
    SymbolTableElement funParam5(&INTTYPE64,true,true, 40);
    SymbolTableElement funParam6(&INTTYPE64,true,true, 48);
    SymbolTableElement funParam7(&INTTYPE64,true,true, 56);
    SymbolTableElement funParam8(&INTTYPE64,true,true, 64);
    std::vector<SymbolTableElement> funParams {funParam1, funParam2, funParam3, funParam4, funParam5, funParam6, funParam7, funParam8};

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));
    std::shared_ptr<CFG> secondCFG(new CFG(nullptr, "fct", &INTTYPE64, funParams));

    SymbolTableElement tempOutput(&INTTYPE64,true,true,8);
    BasicBlock bb0(firstCFG, nullptr);
    Call callInstr(&bb0, secondCFG,params, tempOutput);
    Copy copyInstrReturnMain(&bb0,tempOutput ,RAX_REGISTER);
    bb0.add_IRInstr(&callInstr);
    bb0.add_IRInstr(&copyInstrReturnMain);

    firstCFG->add_bb(&bb0);
    firstCFG->incrementVariableCount(1);

    BasicBlock bb1(secondCFG,nullptr);
    Copy copyInstr(&bb0,funParam7 ,RAX_REGISTER);
    bb1.add_IRInstr(&copyInstr);

    secondCFG->add_bb(&bb1);
    secondCFG->incrementVariableCount(8);

    firstCFG->gen_asm(std::cout);
    secondCFG->gen_asm(std::cout);
}

void test_call(){
    SymbolTableElement param1(&INTTYPE64, "1");
    SymbolTableElement param2(&INTTYPE64, "2");
    std::vector<SymbolTableElement> params {param1, param2};

    SymbolTableElement funParam1(&INTTYPE64,true,true, 8);
    SymbolTableElement funParam2(&INTTYPE64,true,true, 16);
    std::vector<SymbolTableElement> funParams {funParam1, funParam2};

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));
    std::shared_ptr<CFG> secondCFG(new CFG(nullptr, "fct", &VOIDTYPE, funParams));

    BasicBlock bb0(firstCFG, nullptr);
    Call callInstr(&bb0, secondCFG,params,SymbolTableElement(&INTTYPE64,true,true,8));

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

    SymbolTableElement res(&INTTYPE64, false, false, 8);

    Jmp_cmp_gt condJmp1(&bb0, SymbolTableElement(&INTTYPE64, "6"), SymbolTableElement(&INTTYPE64, "8"));
    Copy copyInstr1(&bb1, SymbolTableElement(&INTTYPE64, "2"), res);
    Copy copyInstr2(&bb2, res, RAX_REGISTER);

    bb0.add_IRInstr(&condJmp1);
    bb1.add_IRInstr(&copyInstr1);
    bb2.add_IRInstr(&copyInstr2);

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
    //test_call();
    //test_call_many_params();
    //test_operations();
    //test_cmp();
    //test_operations_sub_add();
    test_operations_mul_div();
}

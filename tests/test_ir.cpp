#include "ir/CFG.h"
#include "ir/BasicBlock.h"
#include "ir/IRInstr.h"
#include "ir/instructions/AddressOf.h"
#include "ir/instructions/Rmem.h"
#include "ir/instructions/Wmem.h"
#include "ir/instructions/Div.h"
#include "ir/instructions/Mul.h"
#include "ir/instructions/Add.h"
#include "ir/instructions/Cmp_eq.h"
#include "ir/instructions/Cmp_neq.h"
#include "ir/instructions/Cmp_ge.h"
#include "ir/instructions/Cmp_gt.h"
#include "ir/instructions/Cmp_le.h"
#include "ir/instructions/Cmp_lt.h"
#include "ir/instructions/Sub.h"
#include "ir/instructions/Copy.h"
#include "ir/instructions/Call.h"
#include "ir/instructions/Add.h"
#include "ir/instructions/Jmp_cmp_eq.h"
#include "ir/instructions/Jmp_cmp_neq.h"
#include "ir/instructions/Jmp_cmp_lt.h"
#include "ir/instructions/Jmp_cmp_le.h"
#include "ir/instructions/Jmp_cmp_gt.h"
#include "ir/instructions/Jmp_cmp_ge.h"
#include "ir/instructions/Modulo.h"
#include "type/Int32.h"
#include "type/Int64.h"
#include "type/Void.h"
#include "SymbolTable.h"
#include "ir/ASMConstants.h"

void test_modulo() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant0(&INTTYPE64, "5");
    SymbolTableElement constant1(&INTTYPE64, "3");
    SymbolTableElement res(&INTTYPE64, false, false, 8);

    shared_ptr<Modulo> modulo(new Modulo(bb0.get(), constant0, constant1, res));

    bb0->add_IRInstr(modulo);

    firstCFG->add_bb(bb0);

    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_cmp_neq() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant0(&INTTYPE64, "2");
    SymbolTableElement constant1(&INTTYPE64, "3");
    SymbolTableElement a(&INTTYPE64, false, false, 8);
    SymbolTableElement b(&INTTYPE64, false, false, 16);
    SymbolTableElement c(&INTTYPE64, false, false, 24);

    shared_ptr<Copy> copy0(new Copy(bb0.get(), constant0, a));
    shared_ptr<Copy> copy1(new Copy(bb0.get(), constant1, b));

    shared_ptr<Cmp_neq> cmp_neq(new Cmp_neq(bb0.get(), a, b, c));

    bb0->add_IRInstr(copy0);
    bb0->add_IRInstr(copy1);
    bb0->add_IRInstr(cmp_neq);

    firstCFG->add_bb(bb0);

    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_jmp_cmp_neq() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));
    shared_ptr<BasicBlock> bb1( new BasicBlock(firstCFG.get(), nullptr));
    shared_ptr<BasicBlock> bb2( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant0(&INTTYPE64, "2");
    SymbolTableElement constant1(&INTTYPE64, "3");
    SymbolTableElement a(&INTTYPE64, false, false, 8);
    SymbolTableElement b(&INTTYPE64, false, false, 16);

    shared_ptr<Copy> copy0(new Copy(bb0.get(), constant0, a));
    shared_ptr<Copy> copy1(new Copy(bb0.get(), constant1, b));

    shared_ptr<Jmp_cmp_neq> jmp_cmp_neq(new Jmp_cmp_neq(bb0.get(), a, b));

    bb0->add_IRInstr(copy0);
    bb0->add_IRInstr(copy1);
    bb0->add_IRInstr(jmp_cmp_neq);

    bb0->setExit_true(bb1);

    // if branch
    bb0->setExit_true(bb1);
    bb0->setExit_false(bb2);

    // final block in common for if and else
    bb1->setExit_true(bb2);

    firstCFG->add_bb(bb0);
    firstCFG->add_bb(bb1);
    firstCFG->add_bb(bb2);

    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_div() {

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant1(&INTTYPE64, "5");
    SymbolTableElement constant2(&INTTYPE64, "2");
    SymbolTableElement dest(&INTTYPE64, false, false, 8);

    shared_ptr<Div> instr0(new Div(bb0.get(), constant1, constant2, dest));
    bb0->add_IRInstr(instr0);
    firstCFG->add_bb(bb0);
    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_mul() {

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant1(&INTTYPE64, "2");
    SymbolTableElement constant2(&INTTYPE64, "3");
    SymbolTableElement dest(&INTTYPE64, false, false, 8);

    shared_ptr<Mul> instr0(new Mul(bb0.get(), constant1, constant2, dest));
    bb0->add_IRInstr(instr0);
    firstCFG->add_bb(bb0);
    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_copy() {

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant1(&INTTYPE64, "2");
    SymbolTableElement a(&INTTYPE64, false, false, 8);

    shared_ptr<Copy> instr0(new Copy(bb0.get(), constant1, a));
    bb0->add_IRInstr(instr0);
    firstCFG->add_bb(bb0);
    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_sub() {

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant1(&INTTYPE64, "2");
    SymbolTableElement constant2(&INTTYPE64, "3");
    SymbolTableElement a(&INTTYPE32, false, false, 8);

    shared_ptr<Sub> instr0(new Sub(bb0.get(), constant1, constant2, a));
    bb0->add_IRInstr(instr0);
    firstCFG->add_bb(bb0);
    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_add() {

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant1(&INTTYPE64, "2");
    SymbolTableElement constant2(&INTTYPE64, "3");
    SymbolTableElement a(&INTTYPE32, false, false, 8);

    shared_ptr<Add> instr0(new Add(bb0.get(), constant1, constant2, a));
    bb0->add_IRInstr(instr0);
    firstCFG->add_bb(bb0);
    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

void test_pointers(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));

    SymbolTableElement constant1(&INTTYPE64,"2");
    SymbolTableElement a(&INTTYPE64, false, false,8);
    SymbolTableElement pointer(&INTTYPE64, false, false,16);

    shared_ptr<AddressOf> instr0(new AddressOf(bb0.get(),a,pointer));
    shared_ptr<Wmem> instr1(new Wmem (bb0.get(),constant1,pointer));
    shared_ptr<Rmem> instr2(new Rmem(bb0.get(),pointer,RAX_REGISTER));
    bb0->add_IRInstr(instr0);
    bb0->add_IRInstr(instr1);
    bb0->add_IRInstr(instr2);

    firstCFG->add_bb(bb0);

    firstCFG->gen_asm(std::cout);
    std::cout << std::endl << std::endl;
}

/*
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
*/
/*
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
*/
/*
void test_cmp(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);

    SymbolTableElement input1(&INTTYPE64, "15");
    //SymbolTableElement input1(&INTTYPE64,false, false, 8);

    SymbolTableElement input2(&INTTYPE64, "14");
    SymbolTableElement dest(&INTTYPE64, false, false, 16);

    // Copy instr0(&bb0, SymbolTableElement(&INTTYPE64,"15"), input1);
   // bb0.add_IRInstr(&instr0); 

    Cmp_ge instr1(&bb0,input1, input2, dest);
    Copy instr2(&bb0, dest, RAX_REGISTER);    
    bb0.add_IRInstr(&instr1);
    bb0.add_IRInstr(&instr2);

    firstCFG->add_bb(&bb0);

    firstCFG->gen_asm(std::cout);
}
*/
/*
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
*/

void test_call(){
    SymbolTableElement param1(&INTTYPE64, "1");
    SymbolTableElement param2(&INTTYPE64, "2");
    std::vector<SymbolTableElement> params {param1, param2};

    SymbolTableElement funParam1(&INTTYPE64,true,true, 8);
    SymbolTableElement funParam2(&INTTYPE64,true,true, 16);
    std::vector<SymbolTableElement> funParams {funParam1, funParam2};

    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));
    std::shared_ptr<CFG> secondCFG(new CFG(nullptr, "fct", &VOIDTYPE, funParams));

    shared_ptr<BasicBlock> bb0( new BasicBlock(firstCFG.get(), nullptr));
    shared_ptr<Call> callInstr(new Call(bb0.get(), secondCFG.get(), params, SymbolTableElement(&INTTYPE64,true,true,8)));

    bb0->add_IRInstr(callInstr);

    firstCFG->add_bb(bb0);

    firstCFG->gen_asm(std::cout);
    secondCFG->gen_asm(std::cout);
}

/*
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
    bb0.getExit_true() = &bb1;
    bb0.getExit_false() = &bb2;

    // final block in common for if and else
    bb1.getExit_true() = &bb3;
    bb2.getExit_true() = &bb3;

    firstCFG->add_bb(&bb0);
    firstCFG->add_bb(&bb1);
    firstCFG->add_bb(&bb2);
    firstCFG->add_bb(&bb3);

    firstCFG->gen_asm(std::cout);
}
*/
/*
void test_if_condition() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr);
    BasicBlock bb2(firstCFG, nullptr);

    SymbolTableElement res(&INTTYPE64, false, false, 8);

    Jmp_cmp_le condJmp1(&bb0, SymbolTableElement(&INTTYPE64, "8"), SymbolTableElement(&INTTYPE64, "10"));
    Copy copyInstr1(&bb1, SymbolTableElement(&INTTYPE64, "2"), res);
    Copy copyInstr2(&bb2, res, RAX_REGISTER);

    bb0.add_IRInstr(&condJmp1);
    bb1.add_IRInstr(&copyInstr1);
    bb2.add_IRInstr(&copyInstr2);

    // if branch
    bb0.getExit_true() = &bb1;
    bb0.getExit_false() = &bb2;

    // final block in common for if and else
    bb1.getExit_true() = &bb2;

    firstCFG->add_bb(&bb0);
    firstCFG->add_bb(&bb1);
    firstCFG->add_bb(&bb2);

    firstCFG->gen_asm(std::cout);
}
*/
/*
void test_following_blocks() {
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr, "main", &INTTYPE64));

    BasicBlock bb0(firstCFG, nullptr);
    BasicBlock bb1(firstCFG, nullptr);

    Copy instr1(&bb0, SymbolTableElement(&INTTYPE64, "2"), SymbolTableElement(&INTTYPE64, false, false, 8));
    Copy instr2(&bb1, SymbolTableElement(&INTTYPE64, "4"), SymbolTableElement(&INTTYPE64, false, false, 16));

    bb0.add_IRInstr(&instr1);
    bb1.add_IRInstr(&instr2);
    bb0.getExit_true() = &bb1;

    firstCFG->add_bb(&bb0);
    firstCFG->add_bb(&bb1);

    firstCFG->gen_asm(std::cout);
}
*/
/*
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
*/
int main(){
    //test_single_block();
    //test_following_blocks();
    //test_if_condition();
    //test_if_else_condition();
    //test_call();
    //test_call_many_params();
    //test_operations_sub_add();
    //test_operations_mul_div();
    //test_pointers();
    //test_cmp();
    
    /*
    test_copy();
    test_sub();
    test_add();
    test_mul();
    test_div();
    test_jmp_cmp_neq();
    test_cmp_neq();
    */

   test_modulo();
}

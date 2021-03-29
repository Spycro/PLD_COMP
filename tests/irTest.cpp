#include "ir/CFG.h"
#include "ir/BasicBlock.h"
#include "ir/IRInstr.h"
#include "ir/operations/Add.h"
#include "ir/operations/Copy.h"
#include "type/Int64.h"

int main(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr));
    // std::shared_ptr<Scope> scope(new Scope);

    BasicBlock* bb0 = new BasicBlock(firstCFG,"bb0",nullptr);

    Int64* intType64 = new Int64;

    symbolTableElement symbol1(intType64, "2");
    symbolTableElement symbol2(intType64,false,false,8);

    Copy* instr1 = new Copy(bb0,intType64, symbol1, symbol2);
    bb0->add_IRInstr(instr1);

    firstCFG->add_bb(bb0);

    firstCFG->gen_asm(std::cout);
}

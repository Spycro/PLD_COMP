#include "../include/ir/CFG.h"
#include "../include/ir/BasicBlock.h"
#include "../include/ir/IRInstr.h"
#include "../include/ir/operations/Add.h"
#include "../include/ir/operations/Copy.h"
#include "../include/type/Int.h"

int main(){
    std::shared_ptr<CFG> firstCFG(new CFG(nullptr));
    std::shared_ptr<Scope> scope(new Scope);

    BasicBlock* bb0 = new BasicBlock(firstCFG,"bb0",scope);

    Int* intType = new Int();

    Copy* instr1 = new Copy(bb0,intType, "~1", "$2");
    bb0->add_IRInstr(instr1);

    firstCFG->add_bb(bb0);
}

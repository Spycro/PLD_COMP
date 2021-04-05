#include "ir/IR.h"


#include "type/Int64.h"

IR::IR(std::shared_ptr<Node> rootNode){
    for(auto childNode : rootNode->getChildren()){
        shared_ptr<CFG> tmp = shared_ptr<CFG>(new CFG(dynamic_pointer_cast<Function> (childNode)));
        functions.push_back(tmp );
        tmp->gen_asm(std::cout);
    }
}
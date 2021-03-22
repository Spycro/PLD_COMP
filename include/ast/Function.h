#pragma once

#include "Block.h"
#include "expression/Variable.h"
#include "Node.h"

#include <list>
#include <map>

using namespace std;

class Function : public Node {

    public:

    private:
        shared_ptr<Block> code;
        list<shared_ptr<Variable>> parameters;

};

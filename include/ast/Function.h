#pragma once

#include "Block.h"
#include "expression/Variable.h"
#include "Node.h"

#include <memory>
#include <list>
#include <map>

using namespace std;

class Function : public Node {

    public:
        Function(shared_ptr<Block> code, list<shared_ptr<Variable>> param)
            : code(code), parameters(param) { }

        inline shared_ptr<Block> getCode() { return code; }
        inline list<shared_ptr<Variable>>& getParameters() { return parameters; }
        void toString(int n);
    private:
        shared_ptr<Block> code;
        list<shared_ptr<Variable>> parameters;

};

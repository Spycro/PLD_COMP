#pragma once

#include "Block.h"
#include "expression/Variable.h"
#include "Node.h"

#include <memory>
#include <list>
#include <map>

using namespace std;

//TODO ajouter nom/type ?

class Function : public Node {

    public:
        Function() {}
        Function(shared_ptr<Block> code, list<shared_ptr<Variable>> param)
            : code(code), parameters(param) { }
        inline void setCode(shared_ptr<Block> code) { this->code = code; }
        inline shared_ptr<Block> getCode() { return code; }
        inline list<shared_ptr<Variable>>& getParameters() { return parameters; }
        virtual std::string toString() override;
    private:
        shared_ptr<Block> code;
        list<shared_ptr<Variable>> parameters;
};

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
        Function()
            : code(nullptr) { type=FUNCTION; }

        Function(shared_ptr<Node> code) 
            : code(code) {}

        Function(shared_ptr<Node> code, list<shared_ptr<Node>> param)
            : code(code), parameters(param) { }
            
        inline void setCode(shared_ptr<Node> code) override { this->code = code; }
        inline shared_ptr<Node> getCode() override { return code; }
        inline list<shared_ptr<Node>> getParameters() override { return parameters; }
        void setSymbol(std::string symbol_) override {symbol=symbol_;}
        std::string& getSymbol() override { return symbol; }
        virtual std::string toString() override;
    private:
        std::string symbol;
        shared_ptr<Node> code;
        list<shared_ptr<Node>> parameters;
};

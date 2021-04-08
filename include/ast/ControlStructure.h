#pragma once

#include "Instruction.h"
#include "expression/Expression.h"
#include <memory>

using namespace std;

class ControlStructure : public Instruction {

    public:
        ControlStructure() : test(nullptr), code(nullptr) { type=CONTROLSTRUCTURE; }

        ControlStructure( shared_ptr<Node> test, shared_ptr<Node> code)
         : test(test), code(code) {}
        

        inline shared_ptr<Node> getTest() override { return test; }
        inline void setTest(shared_ptr<Node> test) override { this->test = test; }
        inline shared_ptr<Node> getCode() override { return code; }
        inline void setCode(shared_ptr<Node> code) override {this->code = code; }
        virtual std::string toString() override;
    private:

        shared_ptr<Node> test;
        shared_ptr<Node> code;

};
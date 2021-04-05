#pragma once

#include "Instruction.h"
#include "expression/Expression.h"
#include <memory>

using namespace std;

class ControlStructure : public Instruction {

    public:
        ControlStructure() : test(nullptr), code(nullptr) { }

        ControlStructure( shared_ptr<Expression> test, shared_ptr<Instruction> code)
         : test(test), code(code) {}
        

        inline shared_ptr<Expression> getTest() { return test; }
        inline void setTest(shared_ptr<Expression> test) { this->test = test; }
        inline shared_ptr<Instruction> getCode() { return code; }
        inline void setCode(shared_ptr<Instruction> code) {this->code = code; }
        virtual std::string toString() override;
    private:

        shared_ptr<Expression> test;
        shared_ptr<Instruction> code;

};
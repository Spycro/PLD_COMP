#pragma once

#include "Instruction.h"
#include "expression/Expression.h"
#include <memory>

using namespace std;

class ControlStructure : public Instruction {

    public:
        ControlStructure() {
            test = nullptr;
            code = nullptr;
        }

        ControlStructure( shared_ptr<Expression> test, shared_ptr<Instruction> code)
         : test(test), code(code) {}
        
        virtual ~ControlStructure() {}

        inline shared_ptr<Expression> getTest() { return test; }
        inline shared_ptr<Instruction> getCode() { return code; }
        virtual void toString(int n);
    private:

        shared_ptr<Expression> test;
        shared_ptr<Instruction> code;


};
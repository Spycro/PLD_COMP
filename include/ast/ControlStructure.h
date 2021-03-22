#pragma once

#include "Instruction.h"
#include "expression/Expression.h"

using namespace std;

class ControlStructure : public Instruction {

    public:

    private:

        shared_ptr<Expression> Test;
        shared_ptr<Instruction> code;


};
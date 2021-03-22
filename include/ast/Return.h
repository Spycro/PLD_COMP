#pragma once
#include "Instruction.h"
#include "expression/Expression.h"

using namespace std;

class Return : public Instruction{

    public:

    private:
        shared_ptr<Expression> value;

};
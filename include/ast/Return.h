#pragma once
#include "Instruction.h"
#include "expression/Expression.h"


#include <memory>

using namespace std;

class Return : public Instruction{

    public:
        shared_ptr<Expression> getValue() { return value; }
    private:
        shared_ptr<Expression> value;

};
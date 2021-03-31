#pragma once
#include "Instruction.h"
#include "expression/Expression.h"

#include <memory>

using namespace std;

class Return : public Instruction{

    public:
        Return( shared_ptr<Expression> value) : value(value) { }

        shared_ptr<Expression> getValue() { return value; }
        void toString(int n);
    private:
        shared_ptr<Expression> value;

};
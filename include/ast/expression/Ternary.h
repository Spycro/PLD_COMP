#pragma once

#include "Expression.h"

class Ternary : public Expression{

    public:

    private:
        shared_ptr<Expression> operand1;
        shared_ptr<Expression> operand2;
        shared_ptr<Expression> operand3;

};

#pragma once

#include "Expression.h"

class Ternary : public Expression{

    public:
        void toString(int n);
        Ternary(shared_ptr<Expression> op1, shared_ptr<Expression> op2, shared_ptr<Expression> op3) 
         : operand1(op1), operand2(op2), operand3(op3) {}
        virtual ~Ternary() {}

        inline shared_ptr<Expression> getOperand1() { return operand1; }
        inline shared_ptr<Expression> getOperand2() { return operand2; }
        inline shared_ptr<Expression> getOperand3() { return operand3; }
    private:
        shared_ptr<Expression> operand1;
        shared_ptr<Expression> operand2;
        shared_ptr<Expression> operand3;

};

#pragma once

#include "Expression.h"

using namespace std;

class Unary : public Expression
{
    public:
        Unary() 
            : operand(nullptr) {}

        Unary(shared_ptr<Expression> operand, UnaryOperator op) 
            : operand(operand), op(op) {}

        inline shared_ptr<Expression> getOperand() { return operand; }
        inline UnaryOperator getOp() { return op; }
        void setOperand(shared_ptr<Expression> op) { operand = op; }
        void setOp(UnaryOperator o) { op = o; }

        virtual std::string toString() override;

    private:
        shared_ptr<Expression> operand;
        UnaryOperator op;
};
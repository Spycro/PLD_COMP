#pragma once

#include "Expression.h"

using namespace std;

class Unary : public Expression
{
    public:
        Unary() 
            : operand(nullptr) { type=UNARY; }

        Unary(shared_ptr<Node> operand, UnaryOperator op) 
            : operand(operand), op(op) {}

        inline shared_ptr<Node> getOperand() override { return operand; }
        inline UnaryOperator getUnaryOp() override  { return op; }
        void setOperand(shared_ptr<Node> op) override { operand = op; }
        void setOp(UnaryOperator o) override { op = o; }

        virtual std::string toString() override;

    private:
        shared_ptr<Node> operand;
        UnaryOperator op;
};
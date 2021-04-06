#pragma once

#include "Expression.h"

class Ternary : public Expression
{
    public:
        Ternary() 
            : operand1(nullptr), operand2(nullptr), operand3(nullptr) {type=TERNARY;}

        Ternary(shared_ptr<Node> op1, shared_ptr<Node> op2, shared_ptr<Node> op3) 
            : operand1(op1), operand2(op2), operand3(op3) {}

        inline shared_ptr<Node> getOperand1() override { return operand1; }
        inline shared_ptr<Node> getOperand2() override { return operand2; }
        inline shared_ptr<Node> getOperand3() override { return operand3; }
        virtual std::string toString() override;

    private:
        shared_ptr<Node> operand1;
        shared_ptr<Node> operand2;
        shared_ptr<Node> operand3;
};

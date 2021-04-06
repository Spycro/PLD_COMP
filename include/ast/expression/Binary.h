#pragma once

#include "Expression.h"


using namespace std;

class Binary : public Expression
{

public:
    Binary() 
        : operand1(nullptr), operand2(nullptr){type=BINARY;}

    Binary(shared_ptr<Node> op1, shared_ptr<Node> op2, BinaryOperator op)
        : operand1(op1), operand2(op2), op(op) {}

    inline shared_ptr<Node> getOperand1() override { return operand1; }
    inline shared_ptr<Node> getOperand2() override { return operand2; }
    inline BinaryOperator getOp() override { return op; }
    void setOperand1(shared_ptr<Node> op1) override { operand1 = op1; }
    void setOperand2(shared_ptr<Node> op2) override { operand2 = op2; }
    void setBinaryOperator(BinaryOperator bop) override { op = bop; }

    virtual std::string toString() override;
    
private:
    shared_ptr<Node> operand1;
    shared_ptr<Node> operand2;
    BinaryOperator op;
};

#pragma once

#include "Expression.h"


using namespace std;

class Binary : public Expression
{

public:
    Binary() 
        : operand1(nullptr), operand2(nullptr){}

    Binary(shared_ptr<Expression> op1, shared_ptr<Expression> op2, BinaryOperator op)
        : operand1(op1), operand2(op2), op(op) {}

    inline shared_ptr<Expression> getOperand1() { return operand1; }
    inline shared_ptr<Expression> getOperand2() { return operand2; }
    inline BinaryOperator getOp() { return op; }
    void setOperand1(shared_ptr<Expression> op1) override { operand1 = op1; }
    void setOperand2(shared_ptr<Expression> op2) override { operand2 = op2; }
    void setBinaryOperator(BinaryOperator bop) override { op = bop; }

    virtual std::string toString() override;
    
private:
    shared_ptr<Expression> operand1;
    shared_ptr<Expression> operand2;
    BinaryOperator op;
};

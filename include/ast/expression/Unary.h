#pragma once

#include "Expression.h"
typedef enum  {PREINCR,POSTINCR,PREDECR,POSTDECR,PARENTHESIS,TILD,NOT} UnaryOperator;

using namespace std;

class Unary : public Expression{

    public:
        void toString(int n);
        Unary(shared_ptr<Expression> operand, UnaryOperator op) 
         : operand(operand), op(op) {}

        inline shared_ptr<Expression> getOperand() { return operand; }
        inline UnaryOperator getOp() { return op; }
    private:
        shared_ptr<Expression> operand;
        UnaryOperator op;
};
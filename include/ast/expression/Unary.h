#pragma once

#include "Expression.h"
typedef enum  {PREINCR,POSTINCR,PREDECR,POSTDECR,PARENTHESIS,TILD,NOT} UnaryOperator;

using namespace std;

class Unary : public Expression{

    public:
        Unary(shared_ptr<Expression> operand, UnaryOperator op) 
         : operand(operand), op(op) {}

        inline shared_ptr<Expression> getOperand() { return operand; }
        inline UnaryOperator getOp() { return op; }

        void toString(int n);

    private:
        shared_ptr<Expression> operand;
        UnaryOperator op;
};
#pragma once

#include "Expression.h"
typedef enum  {PLUS,MINUS,MULT,DIV,EQUAL,NE,GTE,LTE,GT,LT,BINAND,LOGAND,BINOR,LOGOR,BINXOR,LOGXOR} BinaryOperator;

using namespace std;

class Binary : public Expression{

    public:
        void toString(int n);
        Binary(shared_ptr<Expression> op1, shared_ptr<Expression> op2, BinaryOperator op)
         : operand1(op1), operand2(op2), op(op) {}
        virtual ~Binary() {}

        inline shared_ptr<Expression> getOperand1() { return operand1; }
        inline shared_ptr<Expression> getOperand2() { return operand2; }
        inline BinaryOperator getOp() { return op; }
    private:
        shared_ptr<Expression> operand1;
        shared_ptr<Expression> operand2;
        BinaryOperator op;

};



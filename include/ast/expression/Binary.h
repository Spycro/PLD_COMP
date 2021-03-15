#pragma once

#include "Expression.h"
typedef enum  {PLUS,MINUS,MULT,DIV,EQUAL,NE,GTE,LTE,GT,LT,BINAND,LOGAND,BINOR,LOGOR,BINXOR,LOGXOR} BinaryOperator;

using namespace std;

class Binary : public Expression{

    public:

    private:
        shared_ptr<Expression> operand1;
        shared_ptr<Expression> operand2;
        BinaryOperator op;

};



#pragma once

#include "Expression.h"
typedef enum  {PLUS,MINUS,MULT,DIV,EQUAL,NE,GTE,LTE,GT,LT,BINAND,LOGAND,BINOR,LOGOR,BINXOR,LOGXOR} Operator;

class Binary : public Expression{

    public:

    private:
        Expression operand1;
        Expression operand2;
        Operator op;

};



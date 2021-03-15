#pragma once

#include "Expression.h"
typedef enum  {PREINCR,POSTINCR,PREDECR,POSTDECR,PARENTHESIS,TILD,NOT} Operator;


class Unary : public Expression{

    public:

    private:
        Expression operand;
        Operator op;
};
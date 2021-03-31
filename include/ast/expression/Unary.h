#pragma once

#include "Expression.h"
typedef enum
{
    PREINCR,
    POSTINCR,
    PREDECR,
    POSTDECR,
    PARENTHESIS,
    TILD,
    NOT
} UnaryOperator;

using namespace std;

class Unary : public Expression
{

public:
    virtual std::string toString() override;

private:
    shared_ptr<Expression> operand;
    UnaryOperator op;
};
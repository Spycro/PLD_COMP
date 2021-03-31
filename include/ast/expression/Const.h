#pragma once

#include "Expression.h"

class Const : public Expression
{

public:
    virtual std::string toString() override;

private:
    int value;
};
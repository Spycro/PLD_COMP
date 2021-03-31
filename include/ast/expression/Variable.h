#pragma once

#include "Expression.h"
#include <string>
using namespace std;

class Variable : public Expression
{

public:
    virtual std::string toString() override;

private:
    string symbol;
};
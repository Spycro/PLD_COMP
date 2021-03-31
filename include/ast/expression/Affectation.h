#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Affectation : public Expression
{

public:
    virtual std::string toString() override;

private:
    string symbol;
    shared_ptr<Expression> value;
};
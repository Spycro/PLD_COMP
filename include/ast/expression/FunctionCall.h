#pragma once

#include "Expression.h"
#include <string>
#include <list>
using namespace std;

class FunctionCall : public Expression
{

public:
    virtual std::string toString() override;

private:
    string symbol;
    list<shared_ptr<Expression>> parameters;
};
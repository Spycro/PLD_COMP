#pragma once

#include "Expression.h"
#include <string>
using namespace std;

class Variable : public Expression {

    public:
        void toString(int n);
    private:
        string symbol;

};
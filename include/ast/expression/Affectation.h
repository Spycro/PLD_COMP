#pragma once

#include "Expression.h"
#include <iostream>
#include <string>

using namespace std;

class Affectation : public Expression {

    public:
        void toString(int n);
    private:

        string symbol;
        shared_ptr<Expression> value;

};
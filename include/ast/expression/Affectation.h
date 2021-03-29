#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Affectation : public Expression {

    public:
        void toString(int n);
    private:

        string symbol;
        shared_ptr<Expression> value;

};
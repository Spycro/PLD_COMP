#pragma once

#include "Expression.h"

class Const : public Expression {

    public:
        void toString(int n);
    private:
        int value;

};
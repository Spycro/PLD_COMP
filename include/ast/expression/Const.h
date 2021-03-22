#pragma once

#include "Expression.h"
#include <iostream>

class Const : public Expression {

    public:
        void toString(int n);
    private:
        int value;

};
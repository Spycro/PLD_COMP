#pragma once

#include "Expression.h"

#include <string>

using namespace std;

class Affectation : public Expression {

    public:

    private:

        string Symbol;
        Expression Value;

};
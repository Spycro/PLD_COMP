#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Affectation : public Expression
{

    public:
        virtual std::string toString() override;
        inline void setValue(shared_ptr<Expression> value) { this->value = value; }
    private:

        string symbol;
        shared_ptr<Expression> value;

};
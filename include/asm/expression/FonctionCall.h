#pragma once

#include "Expression.h"
#include <string>
#include <list>
using namespace std;

class FonctionCall : public Expression {

    public:

    private:
        string symbol;
        list<Expression> parameters;

};
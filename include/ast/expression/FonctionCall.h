#pragma once

#include "Expression.h"
#include <string>
#include <list>
using namespace std;

class FonctionCall : public Expression {

    public:

    private:
        string symbol;
        list<shared_ptr<Expression>> parameters;

};
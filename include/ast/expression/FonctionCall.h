#pragma once

#include "Expression.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;

class FonctionCall : public Expression {

    public:
        void toString(int n);
    private:
        string symbol;
        list<shared_ptr<Expression>> parameters;

};
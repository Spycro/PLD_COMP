#pragma once

#include "Expression.h"
#include <iostream>
typedef enum  {PREINCR,POSTINCR,PREDECR,POSTDECR,PARENTHESIS,TILD,NOT} UnaryOperator;

using namespace std;

class Unary : public Expression{

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Unary"<<endl;
        }
    private:
        shared_ptr<Expression> operand;
        UnaryOperator op;
};
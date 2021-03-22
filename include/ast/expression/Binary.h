#pragma once

#include "Expression.h"
#include <iostream>
typedef enum  {PLUS,MINUS,MULT,DIV,EQUAL,NE,GTE,LTE,GT,LT,BINAND,LOGAND,BINOR,LOGOR,BINXOR,LOGXOR} BinaryOperator;

using namespace std;

class Binary : public Expression{

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Binary"<<endl;
        }
    private:
        shared_ptr<Expression> operand1;
        shared_ptr<Expression> operand2;
        BinaryOperator op;

};



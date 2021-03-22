#pragma once

#include "Expression.h"
#include <iostream>

class Ternary : public Expression{

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Ternary"<<endl;
        }
    private:
        shared_ptr<Expression> operand1;
        shared_ptr<Expression> operand2;
        shared_ptr<Expression> operand3;

};

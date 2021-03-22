#pragma once

#include "Expression.h"
#include <string>
#include <iostream>

using namespace std;

class Array : public Expression {

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Array"<<endl;
        }
    private:
        string symbol;
        shared_ptr<Expression> position;

};
#pragma once

#include "Expression.h"
#include <string>
#include <iostream>
using namespace std;

class Variable : public Expression {

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Variable"<<endl;
        }
    private:
        string symbol;

};
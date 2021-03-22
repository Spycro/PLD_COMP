#pragma once

#include "Expression.h"
#include <iostream>

class Const : public Expression {

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Const"<<endl;
        }
    private:
        int value;

};
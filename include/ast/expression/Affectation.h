#pragma once

#include "Expression.h"
#include <iostream>
#include <string>

using namespace std;

class Affectation : public Expression {

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Affectation"<<endl;
        }
    private:

        string symbol;
        shared_ptr<Expression> value;

};
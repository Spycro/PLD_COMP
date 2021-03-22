#pragma once

#include "Expression.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;

class FonctionCall : public Expression {

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"FonctionCall"<<endl;
        }
    private:
        string symbol;
        list<shared_ptr<Expression>> parameters;

};
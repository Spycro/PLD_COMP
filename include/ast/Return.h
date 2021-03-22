#pragma once
#include "Instruction.h"
#include "expression/Expression.h"

#include <iostream>
#include <memory>

using namespace std;

class Return : public Instruction{

    public:
        shared_ptr<Expression> getValue() { return value; }
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Return"<<endl;
        }
    private:
        shared_ptr<Expression> value;

};
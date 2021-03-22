#pragma once

#include "../Instruction.h"
#include <iostream>

class Expression : public Instruction {

    public:
        virtual void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Expression"<<endl;
        }
    private:

};

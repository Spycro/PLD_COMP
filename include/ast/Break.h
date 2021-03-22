#pragma once
#include "Instruction.h"
#include <iostream>

class Break : public Instruction{

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Break"<<endl;
        }
    private:

};
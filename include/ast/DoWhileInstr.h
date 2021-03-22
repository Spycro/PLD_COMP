#pragma once

#include "ControlStructure.h"
#include <iostream>

class DoWhileInstr : public ControlStructure {

    public:
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"DoWhileInstr"<<endl;
        }
    private:

};
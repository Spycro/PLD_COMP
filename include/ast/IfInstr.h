#pragma once

#include "ControlStructure.h"
#include <memory>
#include <iostream>
using namespace std;

class IfInstr : public ControlStructure {

    public:
        inline shared_ptr<Instruction> getCodeElse() { return codeElse; }
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"IfInstr"<<endl;
        }
    private:
        shared_ptr<Instruction> codeElse;

};
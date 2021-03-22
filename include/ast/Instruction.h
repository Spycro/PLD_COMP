#pragma once
#include "Node.h"
#include <iostream>
class Instruction : public Node{

    public:
        virtual void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Instruction"<<endl;
        }
    private:

};

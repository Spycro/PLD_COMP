#pragma once

#include "ControlStructure.h"
#include <memory>
#include <iostream>

using namespace std;

class ForInstr : public ControlStructure {

    public:
        inline shared_ptr<Expression> getInitialisation() { return initialisation; }
        inline shared_ptr<Expression> getStep() { return step; }
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"ForInstr"<<endl;
        }
    private:
        shared_ptr<Expression> initialisation;
        shared_ptr<Expression> step;

};
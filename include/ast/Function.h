#pragma once

#include "Block.h"
#include "expression/Variable.h"
#include "Node.h"

#include <memory>
#include <list>
#include <map>
#include <iostream>

using namespace std;

class Function : public Node {

    public:
        inline shared_ptr<Block> getCode() { return code; }
        inline list<shared_ptr<Variable>> getParameters() { return parameters; }
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Function"<<endl;
        }
    private:
        shared_ptr<Block> code;
        list<shared_ptr<Variable>> parameters;

};

#pragma once

#include <vector>
#include <memory>
#include <iostream>

using namespace std;


class Node{

    public:
        inline vector<shared_ptr<Node>> getChildren() { return children; } 
        virtual void toString(int n);
    private:
        vector<shared_ptr<Node>> children;
        shared_ptr<Node> parent;
};
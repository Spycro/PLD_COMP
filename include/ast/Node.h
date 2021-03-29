#pragma once

#include <vector>
#include <memory>

using namespace std;


class Node{

    public:
        inline vector<shared_ptr<Node>> getChildren() { return children; } 
        virtual void toString(int n);
        virtual bool isBlock() { return false; }
    private:
        vector<shared_ptr<Node>> children;
        shared_ptr<Node> parent;
};
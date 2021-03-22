#pragma once

#include <vector>
#include <memory>

using namespace std;


class Node{

    public:
        inline vector<shared_ptr<Node>> getChildren() { return children; } 
    private:
        vector<shared_ptr<Node>> children;
        shared_ptr<Node> parent;
};
#pragma once

#include <vector>
#include <memory>

using namespace std;

class Node
{

public:

    Node() {}

    Node(shared_ptr<Node> parent) 
        : parent(parent) {}

    inline vector<shared_ptr<Node>>& getChildren() { return children; }
    inline shared_ptr<Node>& getParent() { return parent; }
    virtual std::string toString();
    virtual bool isBlock() { return false; }

private:
    vector<shared_ptr<Node>> children;
    shared_ptr<Node> parent;
};
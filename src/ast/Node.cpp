#include "ast/Node.h"
#include <iostream>

using namespace std;

void Node::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Node"<<endl;
}

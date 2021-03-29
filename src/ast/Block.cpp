#include "ast/Block.h"
#include <iostream>

using namespace std;

void Block::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Block"<<endl;
}

#include "ast/Break.h"
#include <iostream>

using namespace std;

void Break::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Break"<<endl;
}

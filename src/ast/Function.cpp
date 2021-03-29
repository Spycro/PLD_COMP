#include "ast/Function.h"
#include <iostream>

using namespace std;

void Function::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Function"<<endl;
}

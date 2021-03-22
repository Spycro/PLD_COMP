#include "ast/expression/Array.h"
#include <iostream>

using namespace std;

void Array::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Array"<<endl;
}
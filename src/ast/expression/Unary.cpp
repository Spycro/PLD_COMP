#include "ast/expression/Unary.h"
#include <iostream>

using namespace std;

void Unary::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Unary"<<endl;
}

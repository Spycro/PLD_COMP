#include "ast/expression/Ternary.h"
#include <iostream>

using namespace std;

void Ternary::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Ternary"<<endl;
}

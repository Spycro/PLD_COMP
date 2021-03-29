#include "ast/expression/Expression.h"
#include <iostream>

using namespace std;

void Expression::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Expression"<<endl;
}


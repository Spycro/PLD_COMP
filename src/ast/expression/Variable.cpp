#include "ast/expression/Variable.h"
#include <iostream>

using namespace std;

void Variable::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Variable"<<endl;
}

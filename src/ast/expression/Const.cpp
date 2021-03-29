#include "ast/expression/Const.h"
#include <iostream>

using namespace std;

void Const::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Const"<<endl;
}

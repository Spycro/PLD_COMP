#include "ast/Return.h"
#include <iostream>

using namespace std;

void Return::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"Return"<<endl;
}

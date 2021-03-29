#include "ast/expression/FonctionCall.h"
#include <iostream>

using namespace std;

void FonctionCall::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"FonctionCall"<<endl;
}

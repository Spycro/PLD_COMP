#include "ast/NullInstr.h"
#include <iostream>

using namespace std;

void NullInstr::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"NullInstr"<<endl;
}

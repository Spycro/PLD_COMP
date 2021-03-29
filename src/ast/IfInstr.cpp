#include "ast/IfInstr.h"
#include <iostream>

using namespace std;

void IfInstr::toString(int n) {
    for(int i=0;i<n;i++){
        cout<<"\t";
     }
    cout<<"IfInstr"<<endl;
}
